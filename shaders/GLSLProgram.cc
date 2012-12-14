#include <fstream>
#include <string>
#include <iterator>
#include <glm/gtc/type_ptr.hpp>

#include "GLSLProgram.h"

GLSLProgram::GLSLProgram(
		const char *vertex_shader_path, 
		const char *fragment_shader_path)
{
	program_id = 0;
	
	GLuint vertex_shader_id = compileFromFile(GL_VERTEX_SHADER, vertex_shader_path);
	GLuint fragment_shader_id = compileFromFile(GL_FRAGMENT_SHADER, fragment_shader_path);

	char log_buff[1024];
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);
	glGetShaderInfoLog(vertex_shader_id, 1023, NULL, log_buff);
	puts(log_buff);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	uni_mvp = glGetUniformLocation(program_id, "MVP");
	uni_tex_sampler = glGetUniformLocation(program_id, "tex_sampler");
}

GLuint GLSLProgram::compileFromFile(GLenum type, const char *path)
{
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

GLuint GLSLProgram::compileShader(GLenum type, const char* src)
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

GLSLProgram::~GLSLProgram()
{
	glDeleteProgram(program_id);
}

void GLSLProgram::use()
{
	glUseProgram(program_id);
}

void GLSLProgram::setUniformMVP(glm::mat4 &mvp)
{
	if (program_id == 0) return;

	glUniformMatrix4fv(
			uni_mvp,
			1, GL_FALSE, glm::value_ptr(mvp));
}

void GLSLProgram::setUniformTexSampler(GLuint i)
{
	if (program_id == 0) return;

	glUniform1i(uni_tex_sampler, i);
}

