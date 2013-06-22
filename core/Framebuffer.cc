#include "Framebuffer.h"

#include "FramebufferTexture.h"
#include "DepthFramebufferTexture.h"
#include "GraphNode.h"
#include "RenderingContext.h"

GLuint Framebuffer::active_framebuffer_id = 0;

Framebuffer::Framebuffer(unsigned int w, unsigned int h)
	: width(w), height(h)
{
	color_tex = NULL;
	depth_tex = NULL;
	color_renderbuffer_id = 0;
	depth_renderbuffer_id = 0;

	glGenFramebuffers(1, &framebuffer_id);
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &framebuffer_id);

	// Delete renderbuffers if any were created
	if (color_renderbuffer_id)
		glDeleteRenderbuffers(1, &color_renderbuffer_id);
	if (depth_renderbuffer_id)
		glDeleteRenderbuffers(1, &depth_renderbuffer_id);
}

void Framebuffer::createColorRenderbuffer()
{
	if (color_renderbuffer_id)
		return;

	color_renderbuffer_id = 0;
	glGenRenderbuffers(1, &color_renderbuffer_id);
	glBindRenderbuffer(GL_RENDERBUFFER, color_renderbuffer_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, color_renderbuffer_id);
} 

void Framebuffer::createDepthRenderbuffer()
{
	if (depth_renderbuffer_id)
		return;

	depth_renderbuffer_id = 0;
	glGenRenderbuffers(1, &depth_renderbuffer_id);
	glBindRenderbuffer(GL_RENDERBUFFER, depth_renderbuffer_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,
			GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_renderbuffer_id);
} 

void Framebuffer::setColorTexture(FramebufferTexture *tex)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

	color_tex = tex;
	if (tex) {
		if (color_renderbuffer_id) {
			glDeleteRenderbuffers(1, &color_renderbuffer_id);
			color_renderbuffer_id = 0;
		}

		tex->resize(width, height);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex->getId(), 0);
	} else {
		if (!color_renderbuffer_id)
			createColorRenderbuffer();
	}


	glBindFramebuffer(GL_FRAMEBUFFER, active_framebuffer_id);
}

void Framebuffer::setDepthTexture(DepthFramebufferTexture *tex)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

	depth_tex = tex;
	if (tex) {
		if (depth_renderbuffer_id) {
			glDeleteRenderbuffers(1, &depth_renderbuffer_id);
			depth_renderbuffer_id = 0;
		}

		tex->resize(width, height);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, tex->getId(), 0);
	} else {
		if (!depth_renderbuffer_id)
			createDepthRenderbuffer();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, active_framebuffer_id);
}

void Framebuffer::resize(unsigned int w, unsigned int h)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

	width = w;
	height = h;

	if (color_tex)
		color_tex->resize(w, h);
	else if (color_renderbuffer_id) {
		glBindRenderbuffer(GL_RENDERBUFFER, color_renderbuffer_id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
	}

	if (depth_tex)
		depth_tex->resize(w, h);
	else if (depth_renderbuffer_id) {
		glBindRenderbuffer(GL_RENDERBUFFER, depth_renderbuffer_id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, active_framebuffer_id);
}

bool Framebuffer::isComplete()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

	switch(glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
		case GL_FRAMEBUFFER_COMPLETE:
			return true;

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
	return false;

	glBindFramebuffer(GL_FRAMEBUFFER, active_framebuffer_id);
}

void Framebuffer::bindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
	active_framebuffer_id = framebuffer_id;

	if (!color_tex && !color_renderbuffer_id)
		createColorRenderbuffer();

	if (!depth_tex && !depth_renderbuffer_id)
		createDepthRenderbuffer();
}

void Framebuffer::unbindFramebuffer()
{
	assert(active_framebuffer_id == framebuffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	active_framebuffer_id = 0;
}

void Framebuffer::renderTo(RenderingContext *rc, GraphNode *scene)
{
	GLint prev_draw_buffer;
	glGetIntegerv(GL_DRAW_BUFFER, &prev_draw_buffer);
	glDrawBuffer(GL_NONE);

	bindFramebuffer();
	//rc->reshape(w, h);
	rc->clear();
	scene->render(rc);
	unbindFramebuffer();

	glDrawBuffer(prev_draw_buffer);
}
