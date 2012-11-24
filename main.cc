#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <list>
#include <algorithm>
#include <functional>

#include "scene/GraphNode.h"
#include "animations/Animation.h"

GraphNode* scene = NULL;
std::list<Animation*> animations;

class TestTriangle : public GraphNode
{
private:

public:
	virtual void doRender()
	{
		glBegin(GL_TRIANGLES);					
			glColor3f(0.0f,0.0f,1.0f);			
			glVertex3f( 0.0f, 1.0f, 0.0f);		
			glColor3f(0.0f,1.0f,0.0f);			
			glVertex3f(-1.0f,-1.0f, 0.0f);		
			glColor3f(1.0f,0.0f,0.0f);			
			glVertex3f( 1.0f,-1.0f, 0.0f);		
		glEnd();
	}
};

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
		subject->setRotation(40.0f, rotation++, 0.0f);
	}
};

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
	/*static GLfloat pos[4] =
	{5.0, 5.0, 10.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	scene = new GraphNode;
	TestTriangle *tt = new TestTriangle;
	scene->addMember(tt);

	animations.push_back(new TestSceneRotation(scene));
}

/// Sets up a new frame and renders the scene.
void draw_scene()
{
	static float rotation = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	scene->setPosition(0.0f, 0.0f, -3.0f);

	scene->render();
	glFlush();
	SDL_GL_SwapBuffers();
}

/// Updates scene state
void update_scene()
{
	float timestep = 0.1f;
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
	screen = SDL_SetVideoMode(640, 480, 32, SDL_OPENGL|SDL_RESIZABLE);
	if ( ! screen ) {
		puts(SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	SDL_WM_SetCaption("Mech", "mech");
	reshape(screen->w, screen->h);
	init_scene();

	int done = 0;
	SDL_Event event;
	while ( !done ) {
		while ( SDL_PollEvent(&event) ) {
			switch(event.type) {
				case SDL_VIDEORESIZE:
					screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16,
							SDL_OPENGL|SDL_RESIZABLE);
					if ( screen )
						reshape(screen->w, screen->h);
					break;

				case SDL_QUIT:
					done = 1;
					break;
			}
		}
		keys = SDL_GetKeyState(NULL);

		if ( keys[SDLK_ESCAPE] ) {
			done = 1;
		}

		// update
		update_scene();

		// render
		draw_scene();
	}
	SDL_Quit();
	delete scene;
	return 0;
}
