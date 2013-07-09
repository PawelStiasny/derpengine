#include "GeometryNode.h"
#include "../core/RenderingContext.h"
#include "../util/ResourceManager.h"

GeometryNode::GeometryNode(ResourceHandle<Geometry> geometry)
	: geometry(geometry)
{
	material = ResourceManager::getInstance()->getDefaultMaterial();
}

void GeometryNode::doRender(RenderingContext *rc)
{
	MaterialSelection ms(*material);
	rc->sync(ms.getSelectedShaders());
	geometry->render();
}

void GeometryNode::doDepthRender(RenderingContext *rc)
{
	ResourceHandle<Material> depth_map_material =
		ResourceManager::getInstance()->getDefaultDepthMapMaterial();
	MaterialSelection ms(*depth_map_material);
	rc->sync(ms.getSelectedShaders());
	geometry->render();
}

void GeometryNode::setGeometry(ResourceHandle<Geometry> g)
{
	geometry = g;
}

void GeometryNode::setMaterial(const ResourceHandle<Material> &m)
{
	material = m;
}

