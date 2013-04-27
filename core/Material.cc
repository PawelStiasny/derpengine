#include "Material.h"
#include "GLSLProgram.h"

#include "../util/ResourceManager.h"
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Material::Material()
{
	ResourceManager *rm = ResourceManager::getInstance();
	shaders = rm->getDefaultShaders();
	texture = rm->getTexture("data/white.bmp");
	ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	diffuse = glm::vec4(1.0f);
	specular = glm::vec4(0.0f);
	shininess = 1;
}

Material::~Material()
{
}

void Material::use()
{
	shaders->use();
	shaders->setUniformMaterial(ambient, diffuse, specular, shininess);
	texture->use(GLSLProgram::TEXUNIT_COLOR);
}

bool ConfigurableMaterial::loadDescriptionFile(const char *path)
{
	std::ifstream source_stream(path);
	if (!source_stream) {
		printf("Could not open material %s\n", path);
		return false;
	}

	ResourceManager *rm = ResourceManager::getInstance();
	std::string line;
	while (std::getline(source_stream, line).good()) {
		const char *cstr = line.c_str();

		if (3 == sscanf(cstr, "ambient %f %f %f %f",
					&ambient.r, &ambient.g, &ambient.b, &ambient.a))
			continue;

		if (3 == sscanf(cstr, "diffuse %f %f %f %f",
					&diffuse.r, &diffuse.g, &diffuse.b, &diffuse.a))
			continue;

		if (3 == sscanf(cstr, "specular %f %f %f %f",
					&specular.r, &specular.g, &specular.b, &specular.a))
			continue;

		if (1 == sscanf(cstr, "shininess %f",
					&shininess))
			continue;

		char texpath[2048];
		if (1 == sscanf(cstr, "texture %s", texpath)) {
			texture = rm->getTexture(texpath);
			continue;
		}

		int unit_id;
		char sampler_name[2048];
		if (2 == sscanf(cstr, "texsampler %s %s", sampler_name, texpath)) {
			unit_id = shaders->getTextureUnit(sampler_name);
			printf("sampler %s unit %d\n", sampler_name, unit_id);
			textures.push_back(std::make_pair(
						unit_id,
						rm->getTexture(texpath)));
			continue;
		}

		char vs[2048], fs[2048];
		if (2 == sscanf(cstr, "shaders vertex %s fragment %s", vs, fs)) {
			shaders = rm->getShaders(vs, fs);
			continue;
		}
	}

	return true;
}

void ConfigurableMaterial::use()
{
	Material::use();
	for (std::list< std::pair< int, ResourceHandle<Texture> > >::iterator
			it = textures.begin(), it_end = textures.end();
			it != it_end; it++)
		it->second->use(it->first);
}

