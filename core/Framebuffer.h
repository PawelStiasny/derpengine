#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

class FramebufferTexture;
class DepthFramebufferTexture;
class GraphNode;
class RenderingContext;

class Framebuffer
{
public:
	Framebuffer(unsigned int w = 256, unsigned int h = 256);
	~Framebuffer();

	void setColorTexture(FramebufferTexture *tex);
	void setDepthTexture(DepthFramebufferTexture *tex);
	void resize(unsigned int w, unsigned int h);
	bool isComplete();

	void renderTo(RenderingContext *rc, GraphNode *scene);

	/// Switches active Framebuffer on construction and restores previous
	/// selection on destruction in a RAII fashion.
	class FramebufferSelection
	{
	public:
		FramebufferSelection(Framebuffer &fb)
		{
			this->fb = &fb;
			fb.bindFramebuffer();
		};
		~FramebufferSelection() {
			fb->unbindFramebuffer();
		};

	private:
		Framebuffer *fb;
	};

private:
	GLuint framebuffer_id;

	FramebufferTexture *color_tex;
	DepthFramebufferTexture *depth_tex;
	GLuint color_renderbuffer_id, depth_renderbuffer_id;
	GLint width, height;

	void bindFramebuffer();
	void unbindFramebuffer();
	void createColorRenderbuffer();
	void createDepthRenderbuffer();

	static GLuint active_framebuffer_id;
};


#endif
