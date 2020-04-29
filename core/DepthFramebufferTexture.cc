#include "../common.h"
#include <stdio.h>
#include <assert.h>

#include "DepthFramebufferTexture.h"
#include "RenderingContext.h"
#include "GraphNode.h"

DepthFramebufferTexture::DepthFramebufferTexture(int w, int h)
	: w(w), h(h)
{
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
}

DepthFramebufferTexture::~DepthFramebufferTexture()
{
}

void DepthFramebufferTexture::resize(int w, int h)
{
	this->w = w;
	this->h = h;
	GLint texture_binding = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &texture_binding);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, w, h, 0,
			GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, texture_binding);
}

