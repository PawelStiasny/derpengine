#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "../shaders/GLSLProgram.h"
#include "../shaders/Texture.h"
#include "resource.h"

#include <map>
#include <string>
#include <utility>

/// Creates and pools instances of SharedResource
class ResourceManager
{
public:
	static ResourceManager * getInstance();

	ResourceHandle<GLSLProgram> getShaders(
			const std::string vertex,
			const std::string fragment);
	ResourceHandle<GLSLProgram> getDefaultShaders();

	ResourceHandle<Texture> getTexture(const std::string path);

	//ResourceHandle<Material> getMaterial(const std::string name);

	//ResourceHandle<Geometry> getModel(const std::string name);

private:
	ResourceManager();
	~ResourceManager();

	static ResourceManager *instance;

	std::map< std::pair<std::string, std::string>, GLSLProgram* > shader_pool;
	std::map< std::string, Texture* > texture_pool;
};

#endif

