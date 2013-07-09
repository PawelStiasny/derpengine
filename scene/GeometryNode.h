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
	virtual void doDepthRender(RenderingContext *rc);
	void setGeometry(ResourceHandle<Geometry> g);
	void setMaterial(const ResourceHandle<Material> &m);

private:
	ResourceHandle<Geometry> geometry;
	ResourceHandle<Material> material;
};
#endif

