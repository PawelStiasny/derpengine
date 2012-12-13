#ifndef GRAHPHNODE_H
#define GRAHPHNODE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <list>

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
	} pos, rot, scale;

	bool visible;

protected:
	std::list<GraphNode*> members;
	GraphNode* parent;

public:
	GraphNode();
	virtual ~GraphNode();

	void render(RenderingContext *rc);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setRotation(GLfloat x, GLfloat y, GLfloat z);
	glm::vec4 getWorldCoordinates(const glm::vec4& v);
	void setScale(GLfloat x, GLfloat y, GLfloat z);

	void addMember(GraphNode* member);
	void removeMember(GraphNode* member);

	void setVisibility(bool v);

private:
	virtual void doRender(RenderingContext *rc);
	virtual void beforeRender(RenderingContext *rc);
	virtual void afterRender(RenderingContext *rc);
};

#endif
