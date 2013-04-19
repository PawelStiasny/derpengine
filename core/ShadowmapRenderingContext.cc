#include "ShadowmapRenderingContext.h"

ShadowmapRenderingContext::ShadowmapRenderingContext()
{
	shadowmap_material.shaders = 
		ResourceManager::getInstance()->getShaders(
				"data/default.vs","data/shadowmap.fs");
	RenderingContext::setMaterial(&shadowmap_material);
}

void ShadowmapRenderingContext::setMaterial(Material *m)
{
	assert(m != &shadowmap_material);
}
