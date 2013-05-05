#include "RenderingContext.h"
#include "Material.h"
#include "../util/ResourceManager.h"

class DepthPassRenderingContext : public RenderingContext
{
public:
	DepthPassRenderingContext();
	virtual ~DepthPassRenderingContext() {};
	virtual void setMaterial(Material *m);

private:
	Material shadowmap_material;
};
