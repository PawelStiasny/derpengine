#include "GLSLProgramPool.h"

GLSLProgramPool * GLSLProgramPool::instance = NULL;

GLSLProgramPool * GLSLProgramPool::getInstance()
{
	if (!instance)
		instance = new GLSLProgramPool;
	return instance;
}

GLSLProgram * GLSLProgramPool::getDefaultShaders()
{
	return default_prog_instance;
}

GLSLProgramPool::GLSLProgramPool()
{
	default_prog_instance = new GLSLProgram;
}

GLSLProgramPool::~GLSLProgramPool()
{
	delete default_prog_instance;
}


