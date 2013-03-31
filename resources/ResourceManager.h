#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "../shaders/GLSLProgram.h"
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

private:
	ResourceManager();
	~ResourceManager();

	static ResourceManager *instance;

	std::map< std::pair<std::string, std::string>, GLSLProgram* > shader_pool;
};

#endif

