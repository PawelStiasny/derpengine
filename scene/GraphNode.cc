#include <algorithm>
#include <functional>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "GraphNode.h"
#include "../RenderingContext.h"

GraphNode::GraphNode()
{
	parent = NULL;
	visible = true;
	material = NULL;
	scale.v[0] = scale.v[1] = scale.v[2] = 1.0f;
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

	beforeRender(rc);

	if (material)
		rc->setMaterial(material);

	// Apply transformations
	if (pos.isSet() || rot.isSet() || scale.isOnes()) rc->pushMatrix();
	if (pos.isSet()) {
		glm::mat4 rm = glm::translate(
				rc->getModelMatrix(),
				pos.v[0], pos.v[1], pos.v[2]);
		rc->setModelMatrix(rm);
	}
	if (rot.isSet()) {
		glm::mat4 rm = rc->getModelMatrix();
		if(rot.v[0] != 0.0f)
			rm = glm::rotate(rm, rot.v[0], glm::vec3(1.0f, 0.0f, 0.0f));
		if(rot.v[1] != 0.0f)
			rm = glm::rotate(rm, rot.v[1], glm::vec3(0.0f, 1.0f, 0.0f));
		if(rot.v[2] != 0.0f)
			rm = glm::rotate(rm, rot.v[2], glm::vec3(0.0f, 0.0f, 1.0f));
		rc->setModelMatrix(rm);
	}
	if (scale.isOnes()) {
		glm::mat4 sm = glm::scale(
				rc->getModelMatrix(),
				scale.v[0], scale.v[1], scale.v[2]);
		rc->setModelMatrix(sm);
	}

	// Call concrete rendering implementation
	doRender(rc);

	// Render members
	std::for_each(members.begin(), members.end(), 
			std::bind2nd(std::mem_fun(&GraphNode::render), rc));

	// Revert transformations
	if (pos.isSet() || rot.isSet() || scale.isOnes()) rc->popMatrix();

	afterRender(rc);
}

/// Concrete implementation of node's rendering.
///
/// Base implementation is a no-op.
void GraphNode::doRender(RenderingContext *rc)
{
}

void GraphNode::beforeRender(RenderingContext *rc)
{
}

void GraphNode::afterRender(RenderingContext *rc)
{
}

void GraphNode::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	pos.v[0] = x;
	pos.v[1] = y;
	pos.v[2] = z;
}

void GraphNode::setPosition(const glm::vec3& pos)
{
	this->pos.v[0] = pos.x;
	this->pos.v[1] = pos.y;
	this->pos.v[2] = pos.z;
}

void GraphNode::setRotation(GLfloat x, GLfloat y, GLfloat z)
{
	rot.v[0] = x;
	rot.v[1] = y;
	rot.v[2] = z;
}

void GraphNode::setScale(GLfloat x, GLfloat y, GLfloat z)
{
	scale.v[0] = x;
	scale.v[1] = y;
	scale.v[2] = z;
}

glm::vec4 GraphNode::getWorldCoordinates(const glm::vec4& v)
{
	if (parent == NULL)
		return getRelativeCoordinates(v);
	else
		return parent->getWorldCoordinates(getRelativeCoordinates(v));
}

glm::vec4 GraphNode::getWorldCoordinates()
{
	glm::vec4 zero(0.0f, 0.0f, 0.0f, 1.0f);
	return getWorldCoordinates(zero);
}

glm::vec4 GraphNode::getRelativeCoordinates(const glm::vec4& v)
{
	glm::mat4 mc = glm::translate(pos.v[0], pos.v[1], pos.v[2]);
	mc = glm::rotate(mc, rot.v[0], glm::vec3(1.0f, 0.0f, 0.0f));
	mc = glm::rotate(mc, rot.v[1], glm::vec3(0.0f, 1.0f, 0.0f));
	mc = glm::rotate(mc, rot.v[2], glm::vec3(0.0f, 0.0f, 1.0f));
	mc = glm::scale(mc, scale.v[0], scale.v[1], scale.v[2]);
	return mc * v;
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

void GraphNode::setMaterial(Material *m)
{
	material = m;
}

