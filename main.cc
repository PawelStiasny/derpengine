#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "SDL.h"
#undef main
#include <list>
#include <algorithm>
#include <functional>

#include "RenderingContext.h"
#include "scene/GraphNode.h"
#include "scene/Skybox.h"
#include "scene/Terrain.h"
#include "scene/Mech.h"
#include "animations/CameraTracking.h"
#include "animations/MechWalk.h"

static SDL_Window *win;
static SDL_GLContext context;
bool conf_enable_msaa;

GraphNode *scene = NULL;
RenderingContext *rc;
Camera *mechcam = NULL;
std::list<Animation*> animations;

CameraTracking *scene_rot;
MechWalk *walk_animation;

void reshape(int width, int height)
{
	glViewport(0, 0, (GLint) width, (GLint) height);
	rc->reshape(width, height);
}

/// Sets up rendering and creates the initial scene graph.
void init_scene()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	if (conf_enable_msaa)
		glEnable(GL_MULTISAMPLE);
	else
		glDisable(GL_MULTISAMPLE);

	scene = new GraphNode;
	scene->addMember(new Skybox);

	Mech *mech = new Mech();
	scene->addMember(mech);

	mechcam = new Camera();
	mechcam->setPosition(0.0f, 1.0f, -2.0f);
	mech->addMember(mechcam);
	mechcam->setTarget(mech);
	//mech->setVisibility(false);
	
	Terrain *terrain = new Terrain("textures/heightmap.bmp", 20.0f);
	scene->addMember(terrain);

	rc = new RenderingContext(scene);
	rc->setCamera(mechcam);

	scene_rot = new CameraTracking(mech, mechcam);
	animations.push_back(scene_rot);
	walk_animation = new MechWalk(mech, terrain);
	animations.push_back(walk_animation);
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
#ifdef WIN32
	conf_enable_msaa = true;
#else
	conf_enable_msaa = false;
#endif
	int opengl_version_major = 3, opengl_version_minor = 0;

	while(*++argv) {
		if (!strcmp(*argv, "--enable-msaa"))
			conf_enable_msaa = true;
		else if (!strcmp(*argv, "--disable-msaa"))
			conf_enable_msaa = false;
		else if (!strcmp(*argv, "-g")) {
			opengl_version_major = atoi(*++argv);
			opengl_version_minor = atoi(*++argv);
		}
	}

	Uint8 *keys;
	int w = 800, h = 600;

	printf("derpengine development build\n");

	if (0 != SDL_Init(SDL_INIT_EVERYTHING)) return 1;

	// Set up an OpenGL window
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, opengl_version_major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, opengl_version_minor);

	if (conf_enable_msaa) {
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	}

	win = SDL_CreateWindow("Mech",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			w, h,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if ( ! win ) {
		puts(SDL_GetError());
		SDL_Quit();
		exit(2);
	}

	context = SDL_GL_CreateContext(win);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("glewInit error: %s\n", glewGetErrorString(err));
	}
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	init_scene();
	reshape(w, h);

	Uint32 previous_ticks = SDL_GetTicks();
	Uint32 fps_prev_t = previous_ticks, frames = 0;

	int done = 0;
	SDL_Event event;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
						w = event.window.data1;
						h = event.window.data2;
						reshape(w,h);
					}
					break;

				case SDL_MOUSEMOTION:
					scene_rot->y = 4.0f * (float)(event.motion.y) / (float)(h) - 2.0f;
					scene_rot->rotation = -360.0f * (float)(event.motion.x) / (float)(w);
					break;

				case SDL_QUIT:
					done = 1;
					break;
			}
		}
		keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_ESCAPE]) {
			done = 1;
		}

		if (keys[SDL_SCANCODE_W])
			walk_animation->move_forward = 1;
		else if (keys[SDL_SCANCODE_S])
			walk_animation->move_forward = -1;
		else
			walk_animation->move_forward = 0;

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
