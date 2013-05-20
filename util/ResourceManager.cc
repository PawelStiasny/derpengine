#include "ResourceManager.h"
#include "../core/Texture.h"
#include "../core/Material.h"
#include "../core/GLSLProgram.h"
#include "../core/GLSLObject.h"
#include "../scene/Tile.h"
#include <list>

ResourceManager * ResourceManager::instance = NULL;

ResourceManager * ResourceManager::getInstance()
{
	if (!instance)
		instance = new ResourceManager;
	return instance;
}

ResourceHandle<GLSLProgram> ResourceManager::getDefaultShaders()
{
	return getShaders("data/default.vs", "data/default.fs");
}

ResourceHandle<GLSLProgram> ResourceManager::getShaders(
		const std::string vertex,
		const std::string fragment)
{
	std::map< std::pair<std::string, std::string>, GLSLProgram* >::iterator
		it = glsl_program_pool.find(std::make_pair(vertex, fragment));

	if (it == glsl_program_pool.end()) {
		std::list< ResourceHandle<GLSLObject> > shaders;
		shaders.push_back(getGLSLProgram(GL_VERTEX_SHADER, vertex.c_str()));
		shaders.push_back(getGLSLProgram(GL_FRAGMENT_SHADER, fragment.c_str()));
		GLSLProgram *new_prog = new GLSLProgram(shaders);

		glsl_program_pool.insert(std::make_pair(
					std::make_pair(vertex, fragment),
					new_prog));

		return new_prog;
	} else 
		return it->second;
}

ResourceHandle<GLSLObject> ResourceManager::getGLSLProgram(
		int type,
		const std::string name)
{
	std::map< std::pair<int, std::string>, GLSLObject* >::iterator
		it = glsl_object_pool.find(std::make_pair(type, name));

	if (it == glsl_object_pool.end()) {
		GLSLObject *new_obj = new GLSLObject(type, name.c_str());
		glsl_object_pool.insert(std::make_pair(
					std::make_pair(type, name),
					new_obj));

		return new_obj;
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

ResourceHandle<Material> ResourceManager::getMaterial(const std::string path)
{
	std::map< std::string, Material* >::iterator
		it = material_pool.find(path);

	if (it == material_pool.end()) {
		ConfigurableMaterial *new_mat = new ConfigurableMaterial;
		new_mat->loadDescriptionFile(path.c_str());
		material_pool.insert(std::make_pair(path, new_mat));
		return new_mat;
	} else
		return it->second;
}

void ResourceManager::clearUnused()
{
	int remaining = 0, deleted = 0;

	std::map< std::string, Material* >::iterator
		material_it = material_pool.begin();
	while (material_it != material_pool.end()) {
		if ((material_it->second)->hasHandles()) {
			printf("material %s in use\n", material_it->first.c_str());
			remaining++;
		} else {
			delete material_it->second;
			deleted++;
		}
		material_it++;
	}

	printf("clearUnused materials: %d deleted, %d remaining\n", deleted, remaining);

	remaining = 0; deleted = 0;
	std::map< std::pair<std::string, std::string>, GLSLProgram* >::iterator
		shader_it = glsl_program_pool.begin();
	while (shader_it != glsl_program_pool.end()) {
		if ((shader_it->second)->hasHandles()) {
			printf("Shaders %s, %s in use\n",
					shader_it->first.first.c_str(),
					shader_it->first.second.c_str());
			remaining++;
		} else {
			delete shader_it->second;
			deleted++;
		}
		shader_it++;
	}

	printf("clearUnused programs: %d deleted, %d remaining\n", deleted, remaining);

	remaining = 0; deleted = 0;
	std::map< std::pair<int, std::string>, GLSLObject* >::iterator
		shader_object_it = glsl_object_pool.begin();
	while (shader_object_it != glsl_object_pool.end()) {
		if ((shader_object_it->second)->hasHandles()) {
			printf("Shader %s in use\n",
					shader_object_it->first.second.c_str());
			remaining++;
		} else {
			delete shader_object_it->second;
			deleted++;
		}
		shader_object_it++;
	}

	printf("clearUnused shaders: %d deleted, %d remaining\n", deleted, remaining);

	remaining = 0; deleted = 0;
	std::map< std::string, Texture* >::iterator
		texture_it = texture_pool.begin();
	while (texture_it != texture_pool.end()) {
		if ((texture_it->second)->hasHandles()) {
			printf("Texture %s in use\n", texture_it->first.c_str());
			remaining++;
		} else {
			delete texture_it->second;
			deleted++;
		}
		texture_it++;
	}

	printf("clearUnused textures: %d deleted, %d remaining\n", deleted, remaining);
}

ResourceHandle<Geometry> ResourceManager::getModel(const std::string name)
{
	// TODO

	if (name == "tile") {
		if (!tile) tile = new Tile();
		return tile;
	}
}

ResourceManager::ResourceManager()
{
	tile = NULL;
}

ResourceManager::~ResourceManager()
{
	// Currently not called
	clearUnused();
	printf("ResourceManager destroyed \n");
}


