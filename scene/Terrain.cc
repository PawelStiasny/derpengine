#include "Terrain.h"

#include "../util/ResourceManager.h"
#include "GeometryNode.h"

#include <SDL2/SDL.h>
#include <glm/gtx/fast_square_root.hpp>
#include <glm/gtc/type_ptr.hpp>

Terrain::Terrain(GLfloat vertical_scaling)
	: t("data/heightmap.bmp", vertical_scaling)
{
	GeometryNode *gn = new GeometryNode(&t);
	gn->setMaterial(
			ResourceManager::getInstance()->getMaterial("data/mat_terrain"));
	addMember(gn);
}

Terrain::~Terrain()
{
}

/// Returns interpolated height for the given (x,z) coordinates.
//  The coordinates are in object space, (0,0) beeing the center.
GLfloat Terrain::getHeight(GLfloat x, GLfloat z)
{
	return t.getHeight(x, z);
}

/// Syncs TerrainPieces to proper LOD based on observers position.
void Terrain::updatePieces(GLfloat ref_x, GLfloat ref_z)
{
	// TODO
}

void Terrain::doRender(RenderingContext *rc)
{
}

#define vindex(x, z) (3 * ((z) * x_res + x))
#define vecx(x, z) vertex_data[vindex(x,z)]
#define vecy(x, z) vertex_data[vindex(x,z)+1]
#define vecz(x, z) vertex_data[vindex(x,z)+2]

TerrainPiece::TerrainPiece(const char *hmap_path, GLfloat vertical_scaling)
	: Geometry(true)
{
	SDL_Surface *heightmap = SDL_LoadBMP(hmap_path);
	if (!heightmap) {
		printf("Could not read terrain map %s\n", hmap_path);
		vertex_data = NULL;
		index_data = NULL;
		x_res = z_res = 0;
		return;
	}

	this->vertical_scaling = vertical_scaling;
	x_res = heightmap->w;
	z_res = heightmap->h;
	printf("terrain res: %d %d\n", x_res, z_res);
	// Assume 8-bit data
	unsigned char *data = (unsigned char*)heightmap->pixels;

	allocCount(x_res * z_res, (x_res - 1) * (z_res - 1) * 2);

	// Load vertex coordinates and uv data
	for (int z = 0; z < z_res; z++)
		for (int x = 0; x < x_res; x++) {
			// Vertex coords
			unsigned int index_low = vindex(x, z);
			vertex_data[index_low] = (GLfloat)x - ((GLfloat)x_res / 2.0f);
			vertex_data[index_low+1] = (GLfloat)(data[z * x_res + x]) * vertical_scaling / 256.0f;
			vertex_data[index_low+2] = (GLfloat)z - ((GLfloat)z_res / 2.0f);

			// Vertex UV
			unsigned int uv_index_low = 2 * (z * x_res + x);
			uv_data[uv_index_low] = (float)z * 0.1;
			uv_data[uv_index_low+1] = (float)x * 0.1;
		}

	// Generate triangle indices
	for (int z = 0; z < (z_res - 1); z++)
		for (int x = 0; x < (x_res - 1); x++) {
			unsigned int index_low = 6 * (z * (x_res-1) + x);

			index_data[index_low+0] = z * x_res + x + 1;
			index_data[index_low+1] = z * x_res + x;
			index_data[index_low+2] = (z+1) * x_res + x + 1;

			index_data[index_low+3] = z * x_res + x;
			index_data[index_low+4] = (z+1) * x_res + x;
			index_data[index_low+5] = (z+1) * x_res + x + 1;
		}

	// Compute normals
	for (int z = 1; z < (z_res - 1); z++)
		for (int x = 1; x < (x_res - 1); x++) {
			// coordinates of neighbour vertices
			glm::vec3
				mid(vecx(x,z), vecy(x,z), vecz(x,z)),
				west(vecx(x-1,z), vecy(x-1,z), vecz(x-1,z)),
				north(vecx(x,z+1), vecy(x,z+1), vecz(x,z+1)),
				east(vecx(x+1,z), vecy(x+1,z), vecz(x+1,z)),
				south(vecx(x,z-1), vecy(x,z-1), vecz(x,z-1));

			// average face normals for a smooth vertex normal
			glm::vec3 triangle_normal_acc;
			triangle_normal_acc = glm::fastNormalize(glm::cross(mid - north, west - north));
			triangle_normal_acc += glm::fastNormalize(glm::cross(mid - east, north - east));
			triangle_normal_acc += glm::fastNormalize(glm::cross(mid - south, east - south));
			triangle_normal_acc += glm::fastNormalize(glm::cross(mid - west, south - west));
			triangle_normal_acc *= 0.25f;

			memcpy(&normal_data[vindex(x,z)], (float*)glm::value_ptr(triangle_normal_acc), sizeof(float)*3);
		}

	syncBuffers();
	SDL_FreeSurface(heightmap);

}

TerrainPiece::~TerrainPiece()
{
}

/// Returns interpolated height for the given (x,z) coordinates.
//  The coordinates are in patch space, (0,0) beeing the center.
GLfloat TerrainPiece::getHeight(GLfloat x, GLfloat z)
{
	int ix = (int)floor(x) + x_res / 2;
	int iz = (int)floor(z) + z_res / 2;

	// check boundaries
	if (
			(ix < 0) || 
			((ix+1) >= x_res) || 
			(iz < 0) || 
			((iz+1) >= z_res))
		return 0.0f;

	float dx = x - floor(x);
	float dz = z - floor(z);

	// bilinear interpolation of height values
	float h0 = (1.0f - dx) * vecy(ix,iz) + dx * vecy(ix+1, iz);
	float h1 = (1.0f - dx) * vecy(ix,iz+1) + dx * vecy(ix+1, iz+1);
	return (1.0f - dz) * h0 + dz * h1;
}

void TerrainPiece::syncLOD(int level)
{
	// TODO
}

