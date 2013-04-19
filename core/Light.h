#ifndef LIGHT_H
#define LIGHT_H 

#include "GraphNode.h"
#include "Camera.h"
#include "DepthFramebufferTexture.h"

class Light : public GraphNode
{
public:
	virtual void buildShadowMap(GraphNode *scene, GraphNode *reference) = 0;
	virtual void use(GLSLProgram *shaders) = 0;
	virtual ~Light() {};
	virtual Texture * getShadowmap() = 0;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	virtual ~DirectionalLight();
	virtual void buildShadowMap(GraphNode *scene, GraphNode *reference);
	virtual void use(GLSLProgram *shaders);
	virtual Texture * getShadowmap() { return shadowmap; };

private:
	OrthogonalCamera camera;
	DepthFramebufferTexture *shadowmap;
	RenderingContext *shadowmap_rc;
};

#endif
