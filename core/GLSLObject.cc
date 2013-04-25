#include "GLSLObject.h"
#include <fstream>
#include <stdlib.h>

GLSLObject::GLSLObject(GLenum type, const char *shader_path)
	//: fw(shader_path)
{
	shader_id = compileFromFile(type, shader_path);
	//if (shader_id) fw.registerObserver(this);
}

GLSLObject::~GLSLObject()
{
	if (shader_id)
		glDeleteShader(shader_id);
}

GLuint GLSLObject::getId()
{
	return shader_id;
}

bool GLSLObject::isUsable()
{
	return (shader_id != 0); 
}

GLuint GLSLObject::compileFromFile(GLenum type, const char *path)
{
	printf("Compiling shader %s\n", path);
	std::ifstream source_stream(path);
	if (!source_stream) {
		printf("Could not open shader %s\n", path);
		return 0;
	}

	std::string source(
			(std::istreambuf_iterator<char>(source_stream)),
			std::istreambuf_iterator<char>());

	return compileShader(type, source.c_str());
}

GLuint GLSLObject::compileShader(GLenum type, const char* src)
{
	int log_len = 0;
	GLint compile_success = GL_TRUE;
	char *log_buff = NULL;

	GLuint shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &src, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_success);

	if (compile_success == GL_TRUE)
		return shader_id;

	// If compilation failed, print the error log
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);
	log_buff = (char*)malloc(log_len);
	glGetShaderInfoLog(shader_id, log_len, NULL, log_buff);
	puts(log_buff);
	free(log_buff);
	return 0;
}

void GLSLObject::onFileChanged()
{
	printf("GLSLObject: shader source changed!\n");
}

