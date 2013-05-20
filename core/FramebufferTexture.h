#ifndef FRAMEBUFFERTEXTURE_H
#define FRAMEBUFFERTEXTURE_H

#include "Texture.h"

class RenderingContext;
class GraphNode;

class FramebufferTexture : public Texture
{
public:
	FramebufferTexture(int w = 1024, int h = 1024);
	virtual ~FramebufferTexture();

	void resize(int w, int h);

	void bindFramebuffer();
	void unbindFramebuffer();
	void renderTo(RenderingContext *rc, GraphNode *scene);

private:
	GLuint framebuffer_id, renderbuffer_id;
	int w, h;
};

#endif
