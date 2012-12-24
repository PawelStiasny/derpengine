#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "SDL.h"
#include "SDL_video.h"
#undef main
#include <list>
#include <algorithm>
#include <functional>

#include "RenderingContext.h"
#include "scene/GraphNode.h"
#include "scene/Skybox.h"
#include "scene/Terrain.h"
#include "scene/Mech.h"
#include "animations/Animation.h"

static SDL_Window *win;
static SDL_GLContext context;

GraphNode *scene = NULL;
RenderingContext *rc;
std::list<Animation*> animations;
int move_forward = 0;

class TestSceneRotation : public Animation
{
private:
	GraphNode* subject;

public:
	TestSceneRotation(GraphNode* subject) : subject(subject) 
	{
		rotation = 0;
		y = 0;
	};

	virtual void update(float timestep)
	{
		glm::vec4 cam_pos = 
			subject->getWorldCoordinates(
				glm::rotate(rotation, glm::vec3(0.0f, 1.0f, 0.0f)) * 
				glm::vec4(0.0f, y, 3.0f, 1.0f));
		rc->setCamera(cam_pos.xyz(), subject);
		while (rotation > 360.0f) rotation -= 360.0f;
	};

	float y;
	float rotation;
} *scene_rot;

class MechWalk : public Animation
{
private:
	Mech* subject;
	Terrain* terrain;

public:
	MechWalk(Mech* subject, Terrain* terrain) : subject(subject), terrain(terrain) {};

	virtual void update(float timestep)
	{
		glm::vec4 current_pos = subject->getWorldCoordinates();
		current_pos.z += move_forward * timestep;
		glm::vec3 new_pos(current_pos.x, terrain->getHeight(current_pos.x, current_pos.z) + 1.5f, current_pos.z);
		subject->setPosition(new_pos.x, new_pos.y, new_pos.z);
	}
};

void reshape(int width, int height)
{
	glViewport(0, 0, (GLint) width, (GLint) height);
	rc->reshape(width, height);
}

/// Sets up rendering and creates the initial scene graph.
void init_scene()
{
	static GLfloat pos[4] =
	{3000.0, 1000.0, -3000.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_MULTISAMPLE);

	scene = new GraphNode;
	scene->addMember(new Skybox);

	Mech *mech = new Mech();
	scene->addMember(mech);
	//mech->setVisibility(false);
	
	Terrain *terrain = new Terrain("textures/heightmap.bmp", 20.0f);
	scene->addMember(terrain);

	rc = new RenderingContext(scene);
	rc->setCamera(glm::vec3(0.0f, 1.0f, -3.0f), mech);

	scene_rot = new TestSceneRotation(mech);
	animations.push_back(scene_rot);
	animations.push_back(new MechWalk(mech, terrain));
}

/// Sets up a new frame and renders the scene.
void draw_scene()
{
	rc->update();
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		puts((const char*)gluErrorString(error));

	glFlush();
	SDL_GL_SwapWindow(win);
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
	//SDL_Surface *screen;
	Uint8 *keys;
	int w = 800, h = 600;

	//CommonState *state;

	printf("Hello!\n");

	if (0 != SDL_Init(SDL_INIT_EVERYTHING)) return 1;

	// Set up an OpenGL window
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	//screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL|SDL_RESIZABLE);
	win = SDL_CreateWindow("Mech",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if ( ! win ) {
		puts(SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	//SDL_WM_SetCaption("Mech", "mech");

	context = SDL_GL_CreateContext(win);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
	  printf("glewInit error: %s\n", glewGetErrorString(err));
	}
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	init_scene();
	//reshape(screen->w, screen->h);
	reshape(w, h);

	Uint32 previous_ticks = SDL_GetTicks();
	Uint32 fps_prev_t = previous_ticks, frames = 0;

	int done = 0;
	SDL_Event event;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				/*case SDL_VIDEORESIZE:
					screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16,
							SDL_OPENGL|SDL_RESIZABLE);
					if (screen)
						reshape(screen->w, screen->h);
					break;
					*/
				case SDL_MOUSEMOTION:
					scene_rot->y = 4.0f * (float)(event.motion.y) / (float)(h) - 2.0f;
					scene_rot->rotation = -360.0f * (float)(event.motion.x) / (float)(w);
					break;

				case SDL_QUIT:
					done = 1;
					break;
			}
		}
		/*keys = SDL_GetKeyState(NULL);

		if (keys[SDLK_ESCAPE]) {
			done = 1;
		}

		if (keys[SDLK_w])
			move_forward = 1;
		else if (keys[SDLK_s])
			move_forward = -1;
		else
			move_forward = 0;*/

		// update
		Uint32 t = SDL_GetTicks();
		update_scene((float)(t - previous_ticks) / 1000.0f);
		previous_ticks = t;

		// count FPS
		frames++;
		if (fps_prev_t + 5000 < t) {
			printf("FPS: %f\n", (float)frames / ((float)(t - fps_prev_t) / 1000.0f));
			fps_prev_t = t;
			frames = 0;
		}

		// render
		draw_scene();
	}
	SDL_Quit();
	delete scene;
	return 0;
}
