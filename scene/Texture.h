#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Texture
{
public:
	Texture(const char* path, bool mipmapped = true);
	~Texture();
	void use(GLuint unit);

private:
	GLuint texture_id;
	SDL_Surface *data;
};

#endif
