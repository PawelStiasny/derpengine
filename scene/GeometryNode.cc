#include "GeometryNode.h"

GeometryNode::GeometryNode(ResourceHandle<Geometry> geometry)
	: geometry(geometry)
{
}

void GeometryNode::doRender(RenderingContext *rc)
{
	geometry->render(rc);
}

void GeometryNode::setGeometry(ResourceHandle<Geometry> g)
{
	geometry = g;
}

