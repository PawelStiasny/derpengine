#ifndef DEPTHFRAMEBUFFERTEXTURE_H
#define DEPTHFRAMEBUFFERTEXTURE_H

#include "Texture.h"

class RenderingContext;
class GraphNode;

class DepthFramebufferTexture : public Texture
{
public:
	DepthFramebufferTexture(int w = 1024, int h = 1024);
	virtual ~DepthFramebufferTexture();

	void resize(int w, int h);

	void bindFramebuffer();
	void unbindFramebuffer();
	void renderTo(RenderingContext *rc, GraphNode *scene);

private:
	GLuint framebuffer_id, renderbuffer_id;
	int w, h;
};

#endif
