#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class GLSLProgram {
public:
	GLSLProgram();
	~GLSLProgram();
	void use();
	void setUniformMVP(glm::mat4& mvp);
	void setUniformTexSampler(GLuint i);
private:
	GLuint program_id;
	static const char *vertex_shader_source;
	static const char *fragment_shader_source;

	GLuint compileShader(GLenum type, const char* src);
};

#endif
