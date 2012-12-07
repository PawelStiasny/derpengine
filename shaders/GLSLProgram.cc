#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "GLSLProgram.h"

const char* GLSLProgram::vertex_shader_source = 
	"#version 130\n\n"

	"uniform mat4 MVP;\n"
	"in vec3 v;\n\n"

	"void main() {\n"
	"	gl_Position = MVP * vec4(v, 1.0);\n"
	"}";

const char* GLSLProgram::fragment_shader_source =
	"#version 130\n\n"

	"void main() {\n"
	"	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
	"}";

GLSLProgram::GLSLProgram()
{
	char log_buff[1024];
	GLuint vertex_shader_id = compileVertexShader();
	GLuint fragment_shader_id = compileFragmentShader();

	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);
	glGetShaderInfoLog(vertex_shader_id, 1023, NULL, log_buff);
	puts(log_buff);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}

GLuint GLSLProgram::compileVertexShader()
{
	char log_buff[1024];

	GLuint shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader_id, 1, &vertex_shader_source, NULL);
	glCompileShader(shader_id);
	glGetShaderInfoLog(shader_id, 1023, NULL, log_buff);
	puts(log_buff);

	return shader_id;
}

GLuint GLSLProgram::compileFragmentShader()
{
	char log_buff[1024];

	GLuint shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader_id, 1, &fragment_shader_source, NULL);
	glCompileShader(shader_id);
	glGetShaderInfoLog(shader_id, 1023, NULL, log_buff);
	puts(log_buff);

	return shader_id;
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
	glUniformMatrix4fv(
			glGetUniformLocation(program_id, "MVP"), 
			1, GL_FALSE, glm::value_ptr(mvp));
}


