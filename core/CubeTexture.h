#ifndef CUBETEXTURE_H
#define CUBETEXTURE_H

#include "Texture.h"

class CubeTexture : public Texture
{
public:
	CubeTexture(const char *side_path[6]);
	virtual ~CubeTexture();
	virtual void use(GLuint unit);

	enum {
		CUBE_POSX,
		CUBE_NEGX,
		CUBE_POSY,
		CUBE_NEGY,
		CUBE_POSZ,
		CUBE_NEGZ
	};

private:
	SDL_Surface *side_data[6];
};

#endif
