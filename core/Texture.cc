#include <GL/glew.h>
#include <stdio.h>

#include "Texture.h"

Texture::Texture(const char *path, bool mipmapped, GLenum repeat_mode)
{
	printf("Loading texture %s\n", path);
	this->data = loadImage(path);
	if (!data) {
		texture_id = 0;
		return;
	}

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data->w, data->h, 0, 
			GL_RGBA, GL_UNSIGNED_BYTE, data->pixels);

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
	if (data) SDL_FreeSurface(data);
	glDeleteTextures(1, &texture_id);
}

SDL_Surface * Texture::loadImage(const char *path)
{
	SDL_Surface *image_data = NULL;

	SDL_Surface *t_data = SDL_LoadBMP(path);
	if (!t_data) {
		printf("Could not read texture %s\n", path);
		return NULL;
	}

	SDL_PixelFormat fmt;
	fmt.format = SDL_PIXELFORMAT_ABGR8888;
	fmt.Bmask = 0x00ff0000;
	fmt.Gmask = 0x0000ff00;
	fmt.Rmask = 0x000000ff;
	fmt.Amask = 0xff000000;
	fmt.BitsPerPixel = 32;
	fmt.BytesPerPixel = 4;
	fmt.palette = NULL;
	image_data = SDL_ConvertSurface(t_data, &fmt, 0);
	if (!image_data) {
		printf("Could not convert texture %s\n", path);
		SDL_FreeSurface(t_data);
		return NULL;
	}
	SDL_FreeSurface(t_data);
	return image_data;
}

void Texture::use(GLuint unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

