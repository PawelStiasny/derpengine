#include "GLSLProgramPool.h"

/// A Material represents a set of parameters for the shader program.
// This can be extended for specific shaders.
class Material
{
public:
	Material();
	~Material();
	virtual void use();
	GLSLProgram * getShaders() { return shaders; };

private:
	GLSLProgram *shaders;
};

