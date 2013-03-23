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
	return getShaders("shaders/default.vs", "shaders/default.fs");
}

GLSLProgram * GLSLProgramPool::getShaders(const std::string vertex, const std::string fragment)
{
	std::map< std::pair<std::string, std::string>, GLSLProgram* >::iterator it = pool.find(std::make_pair(vertex, fragment));
	if (it == pool.end()) {
		GLSLProgram *new_prog = new GLSLProgram(vertex.c_str(), fragment.c_str());
		pool.insert(std::make_pair(
					std::make_pair(vertex, fragment), new_prog));
		return new_prog;
	} else 
		return it->second;
}

GLSLProgramPool::GLSLProgramPool()
{
}

GLSLProgramPool::~GLSLProgramPool()
{
	// Currently not called
	std::map< std::pair<std::string, std::string>, GLSLProgram* >::iterator it = pool.begin();
	while (it++ != pool.end())
		delete it->second;
	printf("GLSLProgramPool destroyed \n");
}


