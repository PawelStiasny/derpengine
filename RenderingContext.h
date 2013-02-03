#ifndef RENDERINGCONTEXT_H
#define RENDERINGCONTEXT_H

#include <glm/glm.hpp>

#include "scene/GraphNode.h"
#include "shaders/GLSLProgram.h"
#include "scene/Camera.h"

class RenderingContext
{
public:
	RenderingContext(GraphNode *scene);
	~RenderingContext();
	GraphNode* getScene();

	void update();
	void reshape(int w, int h);

	void setCamera(Camera *c);
	glm::vec3 getCameraPos();

	void pushMatrix();
	void popMatrix();
	const glm::mat4& getModelMatrix();
	void setModelMatrix(glm::mat4 &m);

	void setMaterial(Material *m);

	void setLight(const glm::vec4 &new_pos);

private:
	glm::mat4 mvp, m_model, m_view, m_projection;
	std::list<glm::mat4> matrix_stack;
	GraphNode *scene;
	GLSLProgram *active_glsl_program;
	float aspect_ratio;
	Camera default_cam, *active_camera;
	glm::vec4 light_pos;

	void onProgramChange(GLSLProgram* new_program);
	void updateMatrix();
};

#endif
