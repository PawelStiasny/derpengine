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

void reshape(int width, int height)
{
	glViewport(0, 0, (GLint) width, (GLint) height);
	rc->reshape(width, height);
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
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_MULTISAMPLE);

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
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 1);
	screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL|SDL_RESIZABLE);
	if ( ! screen ) {
		puts(SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	SDL_WM_SetCaption("Mech", "mech");
	glewInit();
	init_scene();
	reshape(screen->w, screen->h);

	Uint32 previous_ticks = SDL_GetTicks();
	Uint32 fps_prev_t = previous_ticks, frames = 0;

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
