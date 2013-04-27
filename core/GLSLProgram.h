#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include "../util/resource.h"
#include "GLSLObject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <list>
#include <map>
#include <string>

class GLSLProgram : public SharedResource
{
public:
	GLSLProgram(std::list< ResourceHandle<GLSLObject> > shaders);
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
	void setUniformTexSampler(const char *sampler_name, GLuint tex_unit);
	GLuint getTextureUnit(std::string sampler_name);

	enum {
		TEXUNIT_COLOR,
		TEXUNIT_SHADOWMAP,
		TEXUNIT_SPECULAR_CUBEMAP,
		TEXUNIT_USER
	};

	enum {
		ATTR_POSITION	= 0,
		ATTR_NORMAL 	= 1,
		ATTR_UV			= 2
	};

private:
	GLuint program_id;
	GLint uni_mvp, uni_m, uni_normal, uni_cam_pos, uni_mat_ambient,
		  uni_mat_diffuse, uni_mat_specular, uni_mat_shininess, uni_light_pos,
		  uni_shadow_vp;
	bool uniform_warning_displayed;
	std::list< ResourceHandle<GLSLObject> > shaders;
	bool defaults_loaded;
	std::map< std::string, int > sampler_to_texunit;
	int next_free_texunit;

	GLint getUniformLocation(const char *name);
	bool canSetUniform();
};

#endif
