#ifndef MATERIAL_H
#define MATERIAL_H

#include "../util/resource.h"
#include "GLSLProgram.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <list>

/// A Material represents a set of parameters for the shader program.
//  This can be extended for specific shaders.
class Material : public SharedResource
{
public:
	Material();
	virtual ~Material();
	virtual void use();
	ResourceHandle<GLSLProgram> & getShaders() { return shaders; };

	glm::vec4 ambient, diffuse, specular;
	GLfloat shininess;
	ResourceHandle<GLSLProgram> shaders;
	ResourceHandle<Texture> texture;

private:
};

class ConfigurableMaterial : public Material
{
public:
	bool loadDescriptionFile(const char *path);
	virtual void use();
private:
	std::list< std::pair< int, ResourceHandle<Texture> > > textures;
};

#endif

