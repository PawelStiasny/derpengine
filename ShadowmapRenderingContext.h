#include "RenderingContext.h"
#include "shaders/Material.h"
#include "resources/ResourceManager.h"

class ShadowmapRenderingContext : public RenderingContext
{
public:
	ShadowmapRenderingContext();
	virtual ~ShadowmapRenderingContext() {};
	virtual void setMaterial(Material *m);

private:
	Material shadowmap_material;
};
