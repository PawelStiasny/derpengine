#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "GLSLProgramPool.h"
#include "Texture.h"

/// A Material represents a set of parameters for the shader program.
// This can be extended for specific shaders.
class Material
{
public:
	Material();
	virtual ~Material();
	virtual void use();
	ResourceHandle<GLSLProgram> & getShaders() { return shaders; };

	glm::vec4 ambient, diffuse, specular;
	GLfloat shininess;
	ResourceHandle<GLSLProgram> shaders;
	Texture *texture;
};

#endif

