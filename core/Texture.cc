#include <GL/glew.h>
#include <stdio.h>

#include "Texture.h"

Texture::Texture(const char *path, bool mipmapped, GLenum repeat_mode)
{
	printf("Loading texture %s\n", path);
	this->data = NULL;
	SDL_Surface *t_data = SDL_LoadBMP(path);
	if (!t_data) {
		printf("Could not read texture %s\n", path);
		texture_id = 0;
		return;
	}

	SDL_PixelFormat fmt;
	fmt.format = SDL_PIXELFORMAT_ARGB8888;
	fmt.Bmask = 0x000000ff;
	fmt.Gmask = 0x0000ff00;
	fmt.Rmask = 0x00ff0000;
	fmt.Amask = 0xff000000;
	fmt.BitsPerPixel = 32;
	fmt.BytesPerPixel = 4;
	fmt.palette = NULL;
	this->data = SDL_ConvertSurface(t_data, &fmt, 0);
	if (!data) {
		printf("Could not convert texture %s\n", path);
		texture_id = 0;
		SDL_FreeSurface(t_data);
		return;
	}
	SDL_FreeSurface(t_data);

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat_mode);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_id);
	if (data) SDL_FreeSurface(data);
}

void Texture::use(GLuint unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

