#include <GL/glew.h>
#include <stdio.h>
#include <assert.h>

#include "DepthFramebufferTexture.h"

DepthFramebufferTexture::DepthFramebufferTexture()
{
	w = 1024;
	h = 1024;

	glGenTextures(1, &texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, w, h, 0,
			GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);

	glGenFramebuffers(1, &framebuffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_id, 0);

	// Some drivers require the color attachment to be present, event though
	// we don't render to it.  If the driver complains, create a renderbuffer.
	renderbuffer_id = 0;
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		glGenRenderbuffers(1, &renderbuffer_id);
		glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, w, h);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer_id);
	}

	// If framebuffer is still not complete, we've got an error.
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		puts("Framebuffer creation error");

	switch(glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
		case GL_FRAMEBUFFER_COMPLETE:
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			puts("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			puts("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			puts("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			puts("GL_FRAMEBUFFER_UNSUPPORTED");
			break;
		default:
			puts("Unknown framebuffer status");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

DepthFramebufferTexture::~DepthFramebufferTexture()
{
	glDeleteFramebuffers(1, &framebuffer_id);
	if (renderbuffer_id) glDeleteRenderbuffers(1, &renderbuffer_id);
}

void DepthFramebufferTexture::bindFramebuffer()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
}

void DepthFramebufferTexture::unbindFramebuffer()
{
	int bound_fb;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &bound_fb);
	assert(bound_fb == framebuffer_id);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

