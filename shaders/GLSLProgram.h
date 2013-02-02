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
	void setUniformMVP(
			const glm::mat4& model,
			const glm::mat4& view,
			const glm::mat4& projection,
			const glm::vec3& cam_pos);

	static const GLuint default_tex_sampler = 0;
	enum {
		ATTR_POSITION	= 0,
		ATTR_NORMAL 	= 1,
		ATTR_UV			= 2
	};

private:
	GLuint program_id;
	GLint uni_mvp, uni_m, uni_normal, uni_cam_pos, uni_tex_sampler;

	GLuint compileShader(GLenum type, const char* src);
	GLuint compileFromFile(GLenum type, const char* path);
	GLint getUniformLocation(const char *name);
};

#endif
