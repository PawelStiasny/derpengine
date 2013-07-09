#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "resource.h"
#include "../core/Material.h"

#include <map>
#include <string>
#include <utility>

// Forward declaration of returned types
class GLSLProgram;
class GLSLObject;
//class Material;
class Texture;
class Tile;
class Geometry;

/// Creates and pools instances of SharedResource
class ResourceManager
{
public:
	static ResourceManager * getInstance();

	ResourceHandle<GLSLProgram> getShaders(
			const std::string vertex,
			const std::string fragment);
	ResourceHandle<GLSLProgram> getDefaultShaders();

	ResourceHandle<GLSLObject> getGLSLProgram(int type, const std::string name);

	ResourceHandle<Texture> getTexture(const std::string path);

	ResourceHandle<Material> getMaterial(const std::string name);
	ResourceHandle<Material> getDefaultMaterial();
	ResourceHandle<Material> getDefaultDepthMapMaterial();

	ResourceHandle<Geometry> getModel(const std::string name);

	void clearUnused();

private:
	ResourceManager();
	~ResourceManager();

	static ResourceManager *instance;

	std::map< std::pair<std::string, std::string>, GLSLProgram* > glsl_program_pool;
	std::map< std::pair<int, std::string>, GLSLObject* > glsl_object_pool;
	std::map< std::string, Texture* > texture_pool;
	std::map< std::string, Material* > material_pool;
	Material *default_material, *default_depth_map_material;
	Tile *tile;
};

#endif

