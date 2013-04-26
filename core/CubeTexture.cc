#include "CubeTexture.h"

CubeTexture::CubeTexture(const char *side_path[6])
{
	printf("Loading cube texture %s,%s,%s,%s,%s,%s\n", 
			side_path[0], side_path[1], side_path[2],
			side_path[3], side_path[4], side_path[5]);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

	int i;
	for (i = 0; i < 6; i++) {
		side_data[i] = loadImage(side_path[i]);

		if (!side_data[i]) {
			int j;
			for (j = 0; j < 6; j++)
				if (side_data[j]) SDL_FreeSurface(side_data[j]);
			printf("Cube texture not loaded\n");
			return;
		}
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA8, side_data[CUBE_POSX]->w,
			side_data[CUBE_POSX]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			side_data[CUBE_POSX]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA8, side_data[CUBE_NEGX]->w,
			side_data[CUBE_NEGX]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			side_data[CUBE_NEGX]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA8, side_data[CUBE_POSY]->w,
			side_data[CUBE_POSY]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			side_data[CUBE_POSY]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA8, side_data[CUBE_NEGY]->w,
			side_data[CUBE_NEGY]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			side_data[CUBE_NEGY]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA8, side_data[CUBE_POSZ]->w,
			side_data[CUBE_POSZ]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			side_data[CUBE_POSZ]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA8, side_data[CUBE_NEGZ]->w,
			side_data[CUBE_NEGZ]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			side_data[CUBE_NEGZ]->pixels);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

CubeTexture::~CubeTexture()
{
	int i;
	for (i = 0; i < 6; i++)
		if (side_data[i]) SDL_FreeSurface(side_data[i]);

	glDeleteTextures(1, &texture_id);
}

void CubeTexture::use(GLuint unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
}

