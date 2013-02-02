#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "GLSLProgram.h"

Material::Material()
{
	shaders = GLSLProgramPool::getInstance()->getDefaultShaders();
	texture = NULL;
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
	if (texture) texture->use(GLSLProgram::default_tex_sampler);
}

