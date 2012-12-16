#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class GLSLProgram {
public:
	GLSLProgram(
		const char *vertex_shader_path = "shaders/default.vs",
		const char *fragment_shader_path = "shaders/default.fs");
	~GLSLProgram();
	void use();
	void setUniformMVP(glm::mat4& mvp);
	void setUniformTexSampler(GLuint i);

private:
	GLuint program_id;
	GLuint uni_mvp, uni_tex_sampler;

	GLuint compileShader(GLenum type, const char* src);
	GLuint compileFromFile(GLenum type, const char* path);
};

#endif
