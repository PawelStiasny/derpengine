#ifndef GRAHPHNODE_H
#define GRAHPHNODE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <list>

#include "../core/Material.h"

//#include "../RenderingContext.h"
class RenderingContext;

/// Each graph node is a composite directing rendering of itself and its
/// members.
class GraphNode
{
public:
	GraphNode();
	virtual ~GraphNode();

	void render(RenderingContext *rc);
	virtual void depthRender(RenderingContext *rc);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setPosition(const glm::vec3& pos);
	void setRotation(GLfloat x, GLfloat y, GLfloat z);
	void setScale(GLfloat x, GLfloat y, GLfloat z);

	glm::vec4 getWorldCoordinates(const glm::vec4& v);
	glm::vec4 getWorldCoordinates();
	glm::vec4 getRelativeCoordinates(const glm::vec4& v);

	void addMember(GraphNode* member);
	void removeMember(GraphNode* member);

	void setVisibility(bool v);

protected:
	virtual void doRender(RenderingContext *rc);
	virtual void beforeRender(RenderingContext *rc);
	virtual void afterRender(RenderingContext *rc);
	virtual void doDepthRender(RenderingContext *rc);

private:
	struct Vec3 {
		Vec3() { v[0] = v[1] = v[2] = 0.0f; }
		GLfloat v[3];
		bool isSet() {
			return (v[0] != 0.0f) || (v[1] != 0.0f) || (v[2] != 0.0f);
		};
		bool isOnes() {
			return (v[0] == 1.0f) && (v[1] == 1.0f) && (v[2] == 1.0f);
		};
	} pos, rot, scale;
	glm::mat4 m_transform;

	bool visible;

	std::list<GraphNode*> members;
	GraphNode* parent;

	void updateTransformMatrix();
};

#endif
