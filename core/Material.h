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
	ResourceHandle<GLSLProgram> & getShaders() { return shaders; };

	glm::vec4 ambient, diffuse, specular;
	GLfloat shininess;
	ResourceHandle<GLSLProgram> shaders;
	ResourceHandle<Texture> texture;

	class MaterialSelection
	{
	public:
		MaterialSelection(Material &mat);
		~MaterialSelection();

	private:
		Material *selected, *previous;
		GLSLProgramSelection ps;
	};

protected:
	virtual void doUse();

private:
	void use();
	static /*thread_local*/ Material *active_material;
};

typedef Material::MaterialSelection MaterialSelection;

class ConfigurableMaterial : public Material
{
public:
	bool loadDescriptionFile(const char *path);
protected:
	virtual void doUse();
private:
	std::list< std::pair< int, ResourceHandle<Texture> > > textures;
};

#endif

