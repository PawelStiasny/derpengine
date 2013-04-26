#include "Texture.h"

class DepthFramebufferTexture : public Texture
{
public:
	DepthFramebufferTexture();
	virtual ~DepthFramebufferTexture();
	void bindFramebuffer();
	void unbindFramebuffer();

private:
	GLuint framebuffer_id, renderbuffer_id;
	int w, h;
};

