#ifndef RENDERINGCONTEXT_H
#define RENDERINGCONTEXT_H

#include "GLSLProgram.h"
#include "Camera.h"
#include "Light.h"
#include "CubeTexture.h"

#include <glm/glm.hpp>

class RenderingContext
{
public:
	RenderingContext();
	virtual ~RenderingContext();

	void clear(bool clear_z = true);
	void reshape(int w, int h);

	void setCamera(Camera *c);
	Camera * getCamera() { return active_camera; };
	glm::vec3 getCameraPos();

	void pushMatrix();
	void popMatrix();
	const glm::mat4& getModelMatrix();
	void setModelMatrix(const glm::mat4 &m);

	void setLight(Light *l);
	Light * getLight() { return active_light; };
	void setEnvironmentMap(CubeTexture *specular);

	void sync(GLSLProgram* program);

private:
	glm::mat4 mvp, m_model, m_view, m_projection;
	std::list<glm::mat4> matrix_stack;
	float aspect_ratio;
	int width, height;
	PerspectiveCamera default_cam;
	Camera *active_camera;
	Light *active_light;
	CubeTexture *env_map_specular;
};

#endif
