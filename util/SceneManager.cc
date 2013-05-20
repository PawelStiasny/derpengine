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
	if (settings->enable_shadows && l)
		if (shadowmap_ref)
			l->buildShadowMap(scene, shadowmap_ref);
		else
			l->buildShadowMap(scene, rendering_context->getCamera());


	//depth_tex.use(GLSLProgram::TEXUNIT_PRE_DEPTH);

	if (!post_overlays.empty()) {
		main_buffer.bindFramebuffer();
	}

	// Depth pre-pass
	depth_context.setCamera(rendering_context->getCamera());
	depth_context.clear();
	scene->render(&depth_context);

	// Main rendering pass
	rendering_context->clear(/*false*/);
	scene->render(rendering_context);

	ResourceManager::getInstance()->getModel("tile")->render();

	if (!post_overlays.empty()) {
		main_buffer.unbindFramebuffer();
		post_overlays.begin()->render(&main_buffer);
	}
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
	depth_tex.resize(width, height);
	depth_context.reshape(width, height);
	main_buffer.resize(width, height);
	glViewport(0,0,width,height);
}

void SceneManager::appendPostOverlay(std::string fragment_shader)
{
	PostOverlay ov(
			ResourceManager::getInstance()->getShaders(
				"data/postpass.vs", fragment_shader));
	post_overlays.push_front(ov);
}

