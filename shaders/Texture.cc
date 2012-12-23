#include <GL/glew.h>
#include <stdio.h>

#include "Texture.h"

Texture::Texture(const char *path, bool mipmapped)
{
	data = SDL_LoadBMP(path);
	if (!data) {
		printf("Could not read texture %s\n", path);
		texture_id = 0;
		return;
	}

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, data->w, data->h, 0, 
			GL_BGRA, GL_UNSIGNED_BYTE, data->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (mipmapped) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_id);
	SDL_FreeSurface(data);
}

void Texture::use(GLuint unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

