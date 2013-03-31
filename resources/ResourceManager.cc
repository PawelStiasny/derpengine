#include "ResourceManager.h"

ResourceManager * ResourceManager::instance = NULL;

ResourceManager * ResourceManager::getInstance()
{
	if (!instance)
		instance = new ResourceManager;
	return instance;
}

ResourceHandle<GLSLProgram> ResourceManager::getDefaultShaders()
{
	return getShaders("shaders/default.vs", "shaders/default.fs");
}

ResourceHandle<GLSLProgram> ResourceManager::getShaders(const std::string vertex, const std::string fragment)
{
	std::map< std::pair<std::string, std::string>, GLSLProgram* >::iterator it = shader_pool.find(std::make_pair(vertex, fragment));
	if (it == shader_pool.end()) {
		GLSLProgram *new_prog = new GLSLProgram(
				vertex.c_str(), fragment.c_str());
		shader_pool.insert(std::make_pair(
					std::make_pair(vertex, fragment), new_prog));
		return new_prog;
	} else 
		return it->second;
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	// Currently not called
	std::map< std::pair<std::string, std::string>, GLSLProgram* >::iterator it = shader_pool.begin();
	while (it++ != shader_pool.end())
		delete it->second;
	printf("ResourceManager destroyed \n");
}


