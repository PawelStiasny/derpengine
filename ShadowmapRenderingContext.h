#include "RenderingContext.h"
#include "shaders/Material.h"
#include "shaders/GLSLProgramPool.h"

class ShadowmapRenderingContext : public RenderingContext
{
public:
	ShadowmapRenderingContext();
	virtual void setMaterial(Material *m);

private:
	Material shadowmap_material;
};
