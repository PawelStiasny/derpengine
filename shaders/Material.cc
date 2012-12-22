#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"

Material::Material()
{
	shaders = GLSLProgramPool::getInstance()->getDefaultShaders();
	texture = NULL;
}

Material::~Material()
{
}

void Material::use()
{
	shaders->use();
	//shaders->setUniform...
	glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(diffuse));
	if (texture) texture->use(0);
}

