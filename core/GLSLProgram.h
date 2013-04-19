#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include "../util/resource.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

class GLSLProgram : public SharedResource {
public:
	GLSLProgram(
		const char *vertex_shader_path = "data/default.vs",
		const char *fragment_shader_path = "data/default.fs");
	~GLSLProgram();
	void use();
	void setUniformMVP(
			const glm::mat4& model,
			const glm::mat4& view,
			const glm::mat4& projection,
			const glm::vec3& cam_pos);
	void setUniformMaterial(
			const glm::vec4& mat_ambient,
			const glm::vec4& mat_diffuse,
			const glm::vec4& mat_specular,
			float mat_shininess);
	void setUniformShadowVP(
			const glm::mat4& vp);
	void setUniformLight(const glm::vec4& light_pos);

	static const GLuint default_tex_sampler = 0;
	static const GLuint shadowmap_tex_sampler = 2;
	enum {
		ATTR_POSITION	= 0,
		ATTR_NORMAL 	= 1,
		ATTR_UV			= 2
	};

private:
	GLuint program_id;
	GLint uni_mvp, uni_m, uni_normal, uni_cam_pos, uni_tex_sampler,
		  uni_shadow_sampler, uni_mat_ambient, uni_mat_diffuse,
		  uni_mat_specular, uni_mat_shininess, uni_light_pos, uni_shadow_vp;
	bool uniform_warning_displayed;

	GLuint compileShader(GLenum type, const char* src);
	GLuint compileFromFile(GLenum type, const char* path);
	GLint getUniformLocation(const char *name);
	bool canSetUniform();
};

#endif
