#ifndef GLSLPROGRAMPOOL_H
#define GLSLPROGRAMPOOL_H

#include "GLSLProgram.h"
#include "../resource.h"

#include <map>
#include <string>
#include <utility>

class GLSLProgramPool
{
public:
	ResourceHandle<GLSLProgram> getDefaultShaders();
	ResourceHandle<GLSLProgram> getShaders(const std::string vertex, const std::string fragment);

	static GLSLProgramPool * getInstance();

private:
	GLSLProgramPool();
	~GLSLProgramPool();

	std::map< std::pair<std::string, std::string>, GLSLProgram* > pool;

	static GLSLProgramPool *instance;
};

#endif

