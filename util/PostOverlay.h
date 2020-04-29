#ifndef POSTOVERLAY_H
#define POSTOVERLAY_H

#include "../core/GLSLProgram.h"
#include "../core/FramebufferTexture.h"

/// Handles full screen post-processing effects
class PostOverlay {
public:
	PostOverlay(ResourceHandle<GLSLProgram> post_prog) : post_prog(post_prog) {};
	~PostOverlay() {};
	void render(FramebufferTexture *src);

private:
	ResourceHandle<GLSLProgram> post_prog;
};

#endif
