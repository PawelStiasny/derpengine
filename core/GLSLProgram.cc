#include <string>
#include <iterator>
#include <glm/gtc/type_ptr.hpp>

#include "GLSLProgram.h"
#include "../util/ResourceManager.h"

GLSLProgram::GLSLProgram(std::list< ResourceHandle<GLSLObject> > shaders)
{
	program_id = 0;
	this->shaders = shaders;

	program_id = glCreateProgram();
	glBindAttribLocation(program_id, ATTR_POSITION, "v");
	glBindAttribLocation(program_id, ATTR_NORMAL, "n");
	glBindAttribLocation(program_id, ATTR_UV, "uv");
	
	for (
			std::list< ResourceHandle<GLSLObject> >::iterator
				it = shaders.begin(), it_end = shaders.end();
			it != it_end;
			it++)
	{
		if ((*it)->isUsable())
			glAttachShader(program_id, (*it)->getId());
		else
			puts("Trying to link unusable shader");
	}
	glLinkProgram(program_id);
	char log_buff[2048];
	glGetProgramInfoLog(program_id, 2047, NULL, log_buff);
	puts(log_buff);

	uniform_warning_displayed = false;
	uni_mvp = getUniformLocation("MVP");
	uni_m = getUniformLocation("M");
	uni_normal = getUniformLocation("NormalMx");
	uni_cam_pos = getUniformLocation("cam_pos");
	uni_tex_sampler = getUniformLocation("tex_sampler");
	uni_shadow_sampler = getUniformLocation("shadow_sampler");
	uni_specular_sampler = getUniformLocation("specular_sampler");
	uni_mat_ambient = getUniformLocation("mat_ambient");
	uni_mat_diffuse = getUniformLocation("mat_diffuse");
	uni_mat_specular = getUniformLocation("mat_specular");
	uni_mat_shininess = getUniformLocation("mat_shininess");
	uni_light_pos = getUniformLocation("light_pos");
	uni_shadow_vp = getUniformLocation("shadow_VP");

	printf("\n");
}

GLint GLSLProgram::getUniformLocation(const char *name)
{
	GLuint r = -1;

	r = glGetUniformLocation(program_id, name);
	if (r == -1) {
		if (!uniform_warning_displayed) {
			uniform_warning_displayed = true;
			printf("Failed to get location of uniforms: %s", name);
		} else {
			printf(", %s", name);
		}
	}

	return r;
}

GLSLProgram::~GLSLProgram()
{
	glDeleteProgram(program_id);
}

void GLSLProgram::use()
{
	glUseProgram(program_id);
	if (uni_shadow_sampler != -1)
		glUniform1i(uni_shadow_sampler, shadowmap_tex_sampler);
	if (uni_specular_sampler != -1)
		glUniform1i(uni_specular_sampler, specular_cubemap_sampler);
}

bool GLSLProgram::canSetUniform()
{
	if (program_id == 0) return false;

	// use() must be called before setting an uniform
	GLint current_program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
	assert(current_program == program_id);

	return true;
}

void GLSLProgram::setUniformMVP(
		const glm::mat4& model,
		const glm::mat4& view,
		const glm::mat4& projection,
		const glm::vec3& cam_pos)
{
	if (!canSetUniform()) return;

	//glm::mat4 mv = view * model;
	//glm::mat4 mvp = projection * mv;
	glm::mat4 mvp = projection * view * model;
	glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(model)));

	if (uni_mvp != -1)
		glUniformMatrix4fv(uni_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
	if (uni_m != -1)
		glUniformMatrix4fv(uni_m, 1, GL_FALSE, glm::value_ptr(model));
	if (uni_normal != -1)
		glUniformMatrix3fv(uni_normal, 1, GL_FALSE, glm::value_ptr(normal));

	if (uni_cam_pos != -1)
		glUniform3fv(uni_cam_pos, 1, glm::value_ptr(cam_pos));
}

void GLSLProgram::setUniformShadowVP(const glm::mat4& vp)
{
	if (!canSetUniform()) return;

	if (uni_shadow_vp != -1)
		glUniformMatrix4fv(uni_shadow_vp, 1, GL_FALSE, glm::value_ptr(vp));
}

void GLSLProgram::setUniformMaterial(
		const glm::vec4& mat_ambient,
		const glm::vec4& mat_diffuse,
		const glm::vec4& mat_specular,
		float mat_shininess)
{
	if (!canSetUniform()) return;

	if (uni_mat_ambient != -1)
		glUniform4fv(uni_mat_ambient, 1, glm::value_ptr(mat_ambient));
	if (uni_mat_diffuse != -1)
		glUniform4fv(uni_mat_diffuse, 1, glm::value_ptr(mat_diffuse));
	if (uni_mat_specular != -1)
		glUniform4fv(uni_mat_specular, 1, glm::value_ptr(mat_specular));
	if (uni_mat_shininess != -1)
		glUniform1f(uni_mat_shininess, mat_shininess);
}

void GLSLProgram::setUniformLight(const glm::vec4& light_pos)
{
	if (!canSetUniform()) return;

	if (uni_light_pos != -1)
		glUniform4fv(uni_light_pos, 1, glm::value_ptr(light_pos));
}

