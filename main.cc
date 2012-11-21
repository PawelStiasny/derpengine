#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "scene/GraphNode.h"

GraphNode* scene = NULL;

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

void reshape(int width, int height)
{
	GLfloat h = (GLfloat) width / (GLfloat) height;

	glViewport(0, 0, (GLint) width, (GLint) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, h, 1.0f, 10.0f);
}

void init_scene()
{
	static GLfloat pos[4] =
	{5.0, 5.0, 10.0, 0.0};
	/*glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	scene = new GraphNode;
	TestTriangle *tt = new TestTriangle;
	scene->members.push_back(tt);
}

void draw_scene()
{
	static float rotation = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	scene->setPosition(0.0f, 0.0f, -3.0f);
	scene->setRotation(40.0f, rotation++, 0.0f);

	scene->render();
	SDL_GL_SwapBuffers();
}

int main(int argc, char const *argv[])
{
	SDL_Surface *screen;
	Uint8 *keys;

	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(300, 300, 16, SDL_OPENGL|SDL_RESIZABLE);
	if ( ! screen ) {
		puts(SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	SDL_WM_SetCaption("Mech", "mech");
	reshape(screen->w, screen->h);
	init_scene();

	// update animations

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

		// render
		draw_scene();
	}
	SDL_Quit();
	delete scene;
	return 0;
}
