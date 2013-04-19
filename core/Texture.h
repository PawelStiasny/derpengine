#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include "../util/resource.h"
#include <GL/glew.h>

class Texture : public SharedResource
{
public:
	Texture(
			const char *path,
			bool mipmapped = true,
			GLenum repeat_mode = GL_REPEAT);
	virtual ~Texture();
	virtual void use(GLuint unit);

protected:
	static SDL_Surface * loadImage(const char *path);

	Texture() { data = NULL; texture_id = 0; };
	GLuint texture_id;
	SDL_Surface *data;
};

#endif

