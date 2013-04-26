#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL2/SDL.h>
#undef main

#include "scene/DemoSceneManager.h"
#include "util/SceneManager.h"
#include "util/InputState.h"
#include "util/Settings.h"
#include "util/ResourceManager.h"

static SDL_Window *win;
static SDL_GLContext gl_context;

SceneManager *active_scene_manager = NULL;

void reshape(int width, int height)
{
	active_scene_manager->onViewportReshape(width, height);
}

/// Sets up a new frame and renders the scene.
void draw_scene()
{
	active_scene_manager->render();
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		const char *error_string = (const char*)gluErrorString(error);
		if (error_string)
			puts(error_string);
		else
			puts("Uknown GL error");
	}

	glFlush();
	SDL_GL_SwapWindow(win);
}

/// Updates scene state
void update_scene(float timestep)
{
	active_scene_manager->update(timestep);
}

int main(int argc, char const *argv[])
{
	Settings settings(argv);
	int w = 800, h = 600;

	printf("derpengine development build\n");

	if (0 != SDL_Init(SDL_INIT_EVERYTHING)) return 1;
	InputState input_state;

	// Set up an OpenGL window
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(
			SDL_GL_CONTEXT_MAJOR_VERSION,
			settings.opengl_version_major);
	SDL_GL_SetAttribute(
			SDL_GL_CONTEXT_MINOR_VERSION,
			settings.opengl_version_minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (settings.enable_msaa) {
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	}

	win = SDL_CreateWindow(
			"Mech",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			w, h,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (!win) {
		const char *sdl_error_string = SDL_GetError();
		assert(sdl_error_string != NULL);
		puts(sdl_error_string);
		SDL_Quit();
		exit(2);
	}

	gl_context = SDL_GL_CreateContext(win);

	glewExperimental= GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("glewInit error: %s\n", glewGetErrorString(err));
	}
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	if (settings.enable_msaa)
		glEnable(GL_MULTISAMPLE);
	else
		glDisable(GL_MULTISAMPLE);

	active_scene_manager = new DemoSceneManager(&settings);

	reshape(w, h);
	input_state.w = w;
	input_state.h = h;

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
						input_state.w = w;
						input_state.h = h;
						reshape(w,h);
					}
					break;

				case SDL_MOUSEMOTION:
					input_state.mouse_x = event.motion.x;
					input_state.mouse_y = event.motion.y;
					break;

				case SDL_QUIT:
					done = 1;
					break;
			}
		}

		input_state.readInputState();

		if (input_state.getKeyState(InputState::KF_EXIT)) {
			done = 1;
		}

		active_scene_manager->handleInput(&input_state);

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
	delete active_scene_manager;
	ResourceManager::getInstance()->clearUnused();
	return 0;
}
