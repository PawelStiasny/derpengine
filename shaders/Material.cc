#include "Material.h"

Material::Material()
{
	shaders = GLSLProgramPool::getInstance()->getDefaultShaders();
}

Material::~Material()
{
}

void Material::use()
{
	shaders->use();
	//shaders->setUniform...
}


