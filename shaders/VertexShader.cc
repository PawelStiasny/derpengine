#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "VertexShader.h"

const char* VertexShader::vertex_shader_source = 
	"#version 130\n\n"
	"uniform mat4 t;\n"
	"in vec3 v;\n\n"
	"void main() {\n"
	"	gl_Position = t * vec4(v, 1.0);\n"
	"}";

VertexShader::VertexShader()
{
	char log_buff[1024];

	GLuint shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader_id, 1, &vertex_shader_source, NULL);
	glCompileShader(shader_id);
	glGetShaderInfoLog(shader_id, 1023, NULL, log_buff);
	puts(log_buff);

	program_id = glCreateProgram();
	glAttachShader(program_id, shader_id);
	glLinkProgram(program_id);
	glGetShaderInfoLog(shader_id, 1023, NULL, log_buff);
	puts(log_buff);

	glDeleteShader(shader_id);
}

VertexShader::~VertexShader()
{
	glDeleteProgram(program_id);
}

void VertexShader::use()
{
	glUseProgram(program_id);
}

void VertexShader::setUniformMVP(glm::mat4 &mvp)
{
	glUniformMatrix4fv(glGetUniformLocation(program_id, "t"), 1, GL_FALSE, glm::value_ptr(mvp));
}


