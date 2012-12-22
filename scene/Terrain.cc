#include <SDL/SDL.h>

#include "Terrain.h"

Terrain::Terrain(const char *hmap_path, GLfloat vertical_scaling)
{
	SDL_Surface *heightmap = SDL_LoadBMP(hmap_path);
	if (!heightmap) {
		printf("Could not read terrain map %s\n", hmap_path);
		vertex_data = NULL;
		index_data = NULL;
		x_res = z_res = 0;
		return;
	}

	this->vertical_scaling = vertical_scaling;
	x_res = heightmap->w;
	z_res = heightmap->h;
	// Assume 8-bit data
	unsigned char *data = (unsigned char*)heightmap->pixels;

	vertex_data = (GLfloat*)malloc(x_res * z_res * 3 * sizeof(GLfloat));
	index_data = (GLuint*)malloc((x_res - 1) * (z_res - 1) * 4 * sizeof(GLuint));

	// Load vertex coordinates
	for (int i = 0; i < x_res; i++)
		for (int j = 0; j < z_res; j++) {
			unsigned int index_low = 3 * (i * x_res + j);
			vertex_data[index_low] = (GLfloat)i - ((GLfloat)x_res / 2.0f);
			vertex_data[index_low+1] = (GLfloat)(data[i * x_res + j]) * vertical_scaling / 256.0f;
			vertex_data[index_low+2] = (GLfloat)j - ((GLfloat)z_res / 2.0f);
		}

	// Generate quad indices
	for (int i = 0; i < (x_res - 1); i++)
		for (int j = 0; j < (z_res - 1); j++) {
			unsigned int index_low = 4 * (i * x_res + j);
			index_data[index_low] = i * x_res + j;
			index_data[index_low+1] = i * x_res + j + 1;
			index_data[index_low+2] = (i+1) * x_res + j + 1;
			index_data[index_low+3] = (i+1) * x_res + j;
		}

	SDL_FreeSurface(heightmap);
}

Terrain::~Terrain()
{
	free(vertex_data);
	free(index_data);
}

void Terrain::doRender(RenderingContext *rc)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex_data);
	glDrawElements(GL_QUADS, 4*(x_res-1)*(z_res-1), GL_UNSIGNED_INT, index_data);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/// Returns interpolate height for the given (x,z) coordinates.
// The coordinates are in object space, (0,0) beeing the center.
GLfloat Terrain::getHeight(GLfloat x, GLfloat z)
{
	// check boundaries
	if (
			((int)x < -((int)x_res/2)) || 
			((int)x > ((int)x_res/2)) || 
			((int)z < -((int)z_res/2)) || 
			((int)z > ((int)z_res/2)))
		return 0.0f;

	// interpolate height value
	return 1.0f * vertical_scaling;
}

