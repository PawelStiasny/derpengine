#ifndef TERRAIN_H
#define TERRAIN_H

#include "../core/Geometry.h"
#include "../core/Texture.h"
//
/// A single patch of terrain
class TerrainPiece : public Geometry
{
public:
	TerrainPiece(const char *hmap_path, GLfloat vertical_scaling);
	~TerrainPiece();
	GLfloat getHeight(GLfloat x, GLfloat z);
	void syncLOD(int level);
private:
	GLfloat vertical_scaling;
	GLint x_res, z_res;
};

/// A terrain map
//  Actual geometry loading and rendering of terrain patches is delegated to
//  a collection of TerrainPiece instances.
class Terrain : public GraphNode
{
public:
	Terrain(GLfloat vertical_scaling);
	virtual ~Terrain();
	GLfloat getHeight(GLfloat x, GLfloat z);
	void updatePieces(GLfloat ref_x, GLfloat ref_z);
	virtual void doRender(RenderingContext *rc);

private:
	GLfloat vertical_scaling;
	TerrainPiece t;
	Texture hmap;
	ResourceHandle<Material> m;
};

#endif
