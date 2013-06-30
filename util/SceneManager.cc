#include "SceneManager.h"

#include "../core/GLSLProgram.h"
#include <list>
#include <algorithm>
#include <functional>
//temp
#include "../scene/Tile.h"

SceneManager::SceneManager(Settings *settings)
{
	this->settings = settings;

	scene = new GraphNode;
	rendering_context = new RenderingContext;

	shadowmap_ref = NULL;

	framebuffers[0].setColorTexture(&destination_textures[0]);
	framebuffers[1].setColorTexture(&destination_textures[1]);
	framebuffers[0].setDepthTexture(&depth_tex);
}

SceneManager::~SceneManager()
{
	for (
			std::list<Animation*>::iterator it = animations.begin();
			it != animations.end();
			it++)
		delete *it;
	delete scene;
	delete rendering_context;
}

void SceneManager::render()
{
	// Shadowmap pass
	Light *l = rendering_context->getLight();
	if (settings->enable_shadows && l) {
		if (shadowmap_ref)
			l->buildShadowMap(scene, shadowmap_ref);
		else
			l->buildShadowMap(scene, rendering_context->getCamera());
	}


	//depth_tex.use(GLSLProgram::TEXUNIT_PRE_DEPTH);

	{
		Framebuffer::FramebufferSelection fbsel(framebuffers[0]);

		// Depth pre-pass
		depth_context.setCamera(rendering_context->getCamera());
		depth_context.clear();
		scene->render(&depth_context);

		// Main rendering pass
		rendering_context->clear(/*false*/);
		scene->render(rendering_context);

		ResourceManager::getInstance()->getModel("tile")->render();
	}

	// toggle source and destination textures for each overlay pass
	int destination_framebuffer = 1;
	for (
			std::list<PostOverlay>::iterator
				it = ++(post_overlays.begin()),
				it_end = post_overlays.end();
			it != it_end;
			it++)
	{
		Framebuffer::FramebufferSelection fbsel(framebuffers[destination_framebuffer]);
		it->render(&destination_textures[1 - destination_framebuffer]);
		destination_framebuffer = 1 - destination_framebuffer;
	}

	post_overlays.begin()->render(&destination_textures[1 - destination_framebuffer]);
}

void SceneManager::update(float timestep)
{
	std::for_each(
			animations.begin(),
			animations.end(),
			std::bind2nd(std::mem_fun(&Animation::update), timestep));
}

void SceneManager::onViewportReshape(int width, int height)
{
	rendering_context->reshape(width, height);
	depth_context.reshape(width, height);
	framebuffers[0].resize(width, height);
	framebuffers[1].resize(width, height);
	glViewport(0,0,width,height);
}

void SceneManager::appendPostOverlay(std::string fragment_shader)
{
	PostOverlay ov(
			ResourceManager::getInstance()->getShaders(
				"data/postpass.vs", fragment_shader));
	post_overlays.push_back(ov);
}

