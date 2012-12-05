#include "GraphNode.h"
#include <algorithm>
#include <functional>

GraphNode::GraphNode()
{
	parent = NULL;
	visible = true;
}

/// Scene graph manages its memory.
GraphNode::~GraphNode()
{
	if (parent) parent->members.remove(this);

	for (std::list<GraphNode*>::iterator it = members.begin();
			it != members.end(); it++) {
		(*it)->parent = NULL;
		delete *it;
	}
}

/// Template Method that sets up transformations and calls the actual 
/// object and member rendering.
void GraphNode::render(RenderingContext *rc)
{
	if (!visible) return;

	// Apply transformations
	if (pos.isSet() || rot.isSet()) glPushMatrix();
	if (pos.isSet()) glTranslatef(pos.v[0], pos.v[1], pos.v[2]);
	if (rot.isSet()) {
		glRotatef(rot.v[0], 1.0f, 0.0f, 0.0f);
		glRotatef(rot.v[1], 0.0f, 1.0f, 0.0f);
		glRotatef(rot.v[2], 0.0f, 0.0f, 1.0f);
	}

	// Call concrete rendering implementation
	doRender();

	// Render members
	std::for_each(members.begin(), members.end(), 
			std::bind2nd(std::mem_fun(&GraphNode::render), rc));

	// Revert transformations
	if (pos.isSet() || rot.isSet()) glPopMatrix();
}

/// Concrete implementation of node's rendering.
///
/// Base implementation is a no-op.
void GraphNode::doRender()
{
}

void GraphNode::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	pos.v[0] = x;
	pos.v[1] = y;
	pos.v[2] = z;
}

void GraphNode::setRotation(GLfloat x, GLfloat y, GLfloat z)
{
	rot.v[0] = x;
	rot.v[1] = y;
	rot.v[2] = z;
}

void GraphNode::addMember(GraphNode* member)
{
	member->parent = this;
	members.push_back(member);
}

void GraphNode::removeMember(GraphNode* member)
{
	delete member;
}

void GraphNode::setVisibility(bool v)
{
	visible = v;
}

