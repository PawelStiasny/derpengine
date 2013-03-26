#ifndef RENDERINGCONTEXT_H
#define RENDERINGCONTEXT_H

#include <glm/glm.hpp>

#include "shaders/GLSLProgram.h"
#include "scene/Camera.h"
#include "scene/Light.h"

class RenderingContext
{
public:
	RenderingContext();
	~RenderingContext();

	void clear();
	void reshape(int w, int h);

	void setCamera(Camera *c);
	glm::vec3 getCameraPos();

	void pushMatrix();
	void popMatrix();
	const glm::mat4& getModelMatrix();
	void setModelMatrix(const glm::mat4 &m);

	virtual void setMaterial(Material *m);

	void setLight(Light *l);

private:
	glm::mat4 mvp, m_model, m_view, m_projection;
	std::list<glm::mat4> matrix_stack;
	ResourceHandle<GLSLProgram> active_glsl_program;
	float aspect_ratio;
	int width, height;
	PerspectiveCamera default_cam;
	Camera *active_camera;
	Light *active_light;

	void onProgramChange(GLSLProgram* new_program);
	void updateMatrix();
};

#endif
