#include <SDL/SDL.h>

#include "Terrain.h"

Terrain::Terrain(const char *hmap_path, GLfloat vertical_scaling)
{
	SDL_Surface *heightmap = SDL_LoadBMP(hmap_path);
	if (!heightmap) {
		printf("Could not read terrain map %s\n", hmap_path);
		vertex_data = NULL;
		index_data = NULL;
		w_res = h_res = 0;
		return;
	}

	w_res = heightmap->w;
	h_res = heightmap->h;
	// Assume 8-bit data
	unsigned char *data = (unsigned char*)heightmap->pixels;

	vertex_data = (GLfloat*)malloc(w_res * h_res * 3 * sizeof(GLfloat));
	index_data = (GLuint*)malloc((w_res - 1) * (h_res - 1) * 4 * sizeof(GLuint));

	// Load vertex coordinates
	for (int i = 0; i < w_res; i++)
		for (int j = 0; j < h_res; j++) {
			unsigned int index_low = 3 * (i * w_res + j);
			vertex_data[index_low] = (GLfloat)i - ((GLfloat)w_res / 2.0f);
			vertex_data[index_low+1] = (GLfloat)(data[i * w_res + j]) * vertical_scaling / 256.0f;
			vertex_data[index_low+2] = (GLfloat)j - ((GLfloat)h_res / 2.0f);
		}

	// Generate quad indices
	for (int i = 0; i < (w_res - 1); i++)
		for (int j = 0; j < (h_res - 1); j++) {
			unsigned int index_low = 4 * (i * w_res + j);
			index_data[index_low] = i * w_res + j;
			index_data[index_low+1] = i * w_res + j + 1;
			index_data[index_low+2] = (i+1) * w_res + j + 1;
			index_data[index_low+3] = (i+1) * w_res + j;
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
	glDrawElements(GL_QUADS, 4*(w_res-1)*(h_res-1), GL_UNSIGNED_INT, index_data);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

GLfloat Terrain::getHeight(GLfloat x, GLfloat z)
{
	// TODO: check boundaries and interpolate height values
	return 0.0f;
}

