#ifndef GEOMETRYNODE_H
#define GEOMETRYNODE_H

#include "../core/GraphNode.h"
#include "../core/Geometry.h"

/// Renders a shared Geomtery
class GeometryNode : public GraphNode
{
public:
	GeometryNode(ResourceHandle<Geometry> geometry);
	virtual void doRender(RenderingContext *rc);
	void setGeometry(ResourceHandle<Geometry> g);

private:
	ResourceHandle<Geometry> geometry;
};
#endif

