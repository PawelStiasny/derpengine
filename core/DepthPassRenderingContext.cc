#include "DepthPassRenderingContext.h"

DepthPassRenderingContext::DepthPassRenderingContext()
{
	shadowmap_material.shaders = 
		ResourceManager::getInstance()->getShaders(
				"data/default.vs","data/shadowmap.fs");
	RenderingContext::setMaterial(&shadowmap_material);
}

void DepthPassRenderingContext::setMaterial(Material *m)
{
	assert(m != &shadowmap_material);
}
