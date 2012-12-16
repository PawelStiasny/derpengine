#include "GLSLProgram.h"

class GLSLProgramPool
{
public:
	GLSLProgram * getDefaultShaders();

	static GLSLProgramPool * getInstance();

private:
	GLSLProgramPool();
	~GLSLProgramPool();

	GLSLProgram *default_prog_instance;

	static GLSLProgramPool *instance;
};

