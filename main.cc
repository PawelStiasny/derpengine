#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL/SDL.h>
#include <list>
#include <algorithm>
#include <functional>

#include "RenderingContext.h"
#include "scene/GraphNode.h"
#include "scene/Mech.h"
#include "animations/Animation.h"

GraphNode *scene = NULL;
RenderingContext *rc;
std::list<Animation*> animations;
GLuint sh_program_id;

class TestSceneRotation : public Animation
{
private:
	float rotation;
	GraphNode* subject;

public:
	TestSceneRotation(GraphNode* subject) : subject(subject) 
	{
		rotation = 0;
	};

	virtual void update(float timestep)
	{
		subject->setRotation(0.0f, rotation += timestep*8, 0.0f);
		while (rotation > 360.0f) rotation -= 360.0f;
	}
};

const char* vertex_shader_source = 
	"#version 130\n\n"
	"uniform mat4 t;\n"
	"in vec3 v;\n\n"
	"void main() {\n"
	"	gl_Position = t * vec4(v, 1.0);\n"
	//"	gl_Position.w = 1.0;\n"
	"}";

void use_vertex_shader()
{
	char log_buff[1024];

	GLuint shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader_id, 1, &vertex_shader_source, NULL);
	glCompileShader(shader_id);
	glGetShaderInfoLog(shader_id, 1023, NULL, log_buff);
	puts(log_buff);

	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, shader_id);
	glLinkProgram(program_id);
	glGetShaderInfoLog(shader_id, 1023, NULL, log_buff);
	puts(log_buff);

	glDeleteShader(shader_id);

	glUseProgram(program_id);

	/*glm::mat4 Projection = glm::perspective(60.0f, 4.0f/3.0f, 1.0f, 10.0f);
	Projection *= glm::translate(0.0f, 0.0f, -3.0f);
	//glm::mat4 Projection = glm::mat4(1.0);
	glUniformMatrix4fv(glGetUniformLocation(program_id, "t"), 1, GL_FALSE, &Projection[0][0]);*/
	sh_program_id = program_id;
}

void reshape(int width, int height)
{
	GLfloat ratio = (GLfloat) width / (GLfloat) height;

	glViewport(0, 0, (GLint) width, (GLint) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, ratio, 1.0f, 10.0f);
}

/// Sets up rendering and creates the initial scene graph.
void init_scene()
{
	static GLfloat pos[4] =
	{5.0, 5.0, 10.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	use_vertex_shader();

	scene = new GraphNode;
	GraphNode *mech = new Mech();
	scene->addMember(mech);

	rc = new RenderingContext(scene);
	rc->setCamera(glm::vec3(0.0f, 1.0f, -3.0f), mech);

	animations.push_back(new TestSceneRotation(scene));
}

/// Sets up a new frame and renders the scene.
void draw_scene()
{
	rc->program_id = sh_program_id;

	//scene->setPosition(0.0f, 0.0f, -3.0f);

	rc->update();
}

/// Updates scene state
void update_scene(float timestep)
{
	std::for_each(
			animations.begin(),
			animations.end(),
			std::bind2nd(std::mem_fun(&Animation::update), timestep));
}

int main(int argc, char const *argv[])
{
	SDL_Surface *screen;
	Uint8 *keys;

	if (0 != SDL_Init(SDL_INIT_EVERYTHING)) return 1;

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL|SDL_RESIZABLE);
	if ( ! screen ) {
		puts(SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	SDL_WM_SetCaption("Mech", "mech");
	glewInit();
	reshape(screen->w, screen->h);
	init_scene();

	Uint32 previous_ticks = SDL_GetTicks();

	int done = 0;
	SDL_Event event;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_VIDEORESIZE:
					screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16,
							SDL_OPENGL|SDL_RESIZABLE);
					if (screen)
						reshape(screen->w, screen->h);
					break;

				case SDL_QUIT:
					done = 1;
					break;
			}
		}
		keys = SDL_GetKeyState(NULL);

		if (keys[SDLK_ESCAPE]) {
			done = 1;
		}

		// update
		Uint32 t = SDL_GetTicks();
		update_scene((float)(t - previous_ticks) / 1000);
		previous_ticks = t;

		// render
		draw_scene();
	}
	SDL_Quit();
	delete scene;
	return 0;
}
