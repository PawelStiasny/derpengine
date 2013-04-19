#include "RenderingContext.h"
#include "Material.h"
#include "../util/ResourceManager.h"

class ShadowmapRenderingContext : public RenderingContext
{
public:
	ShadowmapRenderingContext();
	virtual ~ShadowmapRenderingContext() {};
	virtual void setMaterial(Material *m);

private:
	Material shadowmap_material;
};
