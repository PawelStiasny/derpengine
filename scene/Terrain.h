#ifndef TERRAIN_H
#define TERRAIN_H

#include "Geometry.h"

class Terrain : public Geometry
{
public:
	Terrain(const char *hmap_path, GLfloat vertical_scaling);
	~Terrain();
	GLfloat getHeight(GLfloat x, GLfloat z);

private:
	GLint x_res, z_res;
	GLfloat vertical_scaling;
	Material *m;
};

#endif
