#include "../common.h"
#include <stdio.h>
#include <assert.h>

#include "FramebufferTexture.h"
#include "RenderingContext.h"
#include "GraphNode.h"

FramebufferTexture::FramebufferTexture(int w, int h)
	: w(w), h(h)
{
	glGenTextures(1, &texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

FramebufferTexture::~FramebufferTexture()
{
}

void FramebufferTexture::resize(int w, int h)
{
	this->w = w;
	this->h = h;
	GLint texture_binding = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &texture_binding);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, texture_binding);
}

