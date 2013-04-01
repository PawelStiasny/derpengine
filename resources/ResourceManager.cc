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

ResourceHandle<GLSLProgram> ResourceManager::getShaders(
		const std::string vertex,
		const std::string fragment)
{
	std::map< std::pair<std::string, std::string>, GLSLProgram* >::iterator
		it = shader_pool.find(std::make_pair(vertex, fragment));

	if (it == shader_pool.end()) {
		GLSLProgram *new_prog = new GLSLProgram(
				vertex.c_str(), fragment.c_str());
		shader_pool.insert(std::make_pair(
					std::make_pair(vertex, fragment),
					new_prog));
		return new_prog;
	} else 
		return it->second;
}

ResourceHandle<Texture> ResourceManager::getTexture(const std::string path)
{
	std::map< std::string, Texture* >::iterator
		it = texture_pool.find(path);

	if (it == texture_pool.end()) {
		Texture *new_tex = new Texture(path.c_str());
		texture_pool.insert(std::make_pair(path, new_tex));
		return new_tex;
	} else
		return it->second;
}

void ResourceManager::clearUnused()
{
	int remaining = 0, deleted = 0;

	std::map< std::pair<std::string, std::string>, GLSLProgram* >::iterator
		shader_it = shader_pool.begin();
	while (shader_it != shader_pool.end()) {
		if ((shader_it->second)->hasHandles()) {
			remaining++;
		} else {
			delete shader_it->second;
			deleted++;
		}
		shader_it++;
	}

	printf("clearUnused shaders: %d deleted, %d remaining\n", deleted, remaining);

	remaining = 0; deleted = 0;
	std::map< std::string, Texture* >::iterator
		texture_it = texture_pool.begin();
	while (texture_it != texture_pool.end()) {
		if ((texture_it->second)->hasHandles()) {
			remaining++;
		} else {
			delete texture_it->second;
			deleted++;
		}
		texture_it++;
	}

	printf("clearUnused textures: %d deleted, %d remaining\n", deleted, remaining);
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


