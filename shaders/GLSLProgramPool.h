#include "GLSLProgram.h"

class GLSLProgramPool
{
public:
	static GLSLProgramPool * getInstance();
	GLSLProgram * getDefaultShaders();

private:
	GLSLProgramPool();
	~GLSLProgramPool();
	static GLSLProgramPool *instance;
	GLSLProgram *default_prog_instance;
};

