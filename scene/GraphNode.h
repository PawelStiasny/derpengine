#ifndef GRAHPHNODE_H
#define GRAHPHNODE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <list>

#include "../shaders/Material.h"

//#include "../RenderingContext.h"
class RenderingContext;

/// Each graph node is a composite directing rendering of itself and its
/// members.
class GraphNode
{
private:
	struct Vec3 {
		Vec3() { v[0] = v[1] = v[2] = 0.0f; }
		GLfloat v[3];
		bool isSet() {
			return (v[0] != 0.0f) || (v[1] != 0.0f) || (v[2] != 0.0f);
		};
		bool isOnes() {
			return (v[0] != 1.0f) || (v[1] != 1.0f) || (v[2] != 1.0f);
		};
	} pos, rot, scale;
	glm::mat4 m_transform;

	bool visible;
	Material *material;

protected:
	std::list<GraphNode*> members;
	GraphNode* parent;

public:
	GraphNode();
	virtual ~GraphNode();

	void render(RenderingContext *rc);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setPosition(const glm::vec3& pos);
	void setRotation(GLfloat x, GLfloat y, GLfloat z);
	glm::vec4 getWorldCoordinates(const glm::vec4& v);
	glm::vec4 getWorldCoordinates();
	glm::vec4 getRelativeCoordinates(const glm::vec4& v);
	void setScale(GLfloat x, GLfloat y, GLfloat z);

	void addMember(GraphNode* member);
	void removeMember(GraphNode* member);

	void setVisibility(bool v);
	void setMaterial(Material *m);

private:
	virtual void doRender(RenderingContext *rc);
	virtual void beforeRender(RenderingContext *rc);
	virtual void afterRender(RenderingContext *rc);
	void updateTransformMatrix();
};

#endif
