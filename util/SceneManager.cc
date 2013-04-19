#include "SceneManager.h"

#include "../core/GLSLProgram.h"
#include <list>
#include <algorithm>
#include <functional>

SceneManager::SceneManager(Settings *settings)
{
	this->settings = settings;

	scene = new GraphNode;
	rendering_context = new RenderingContext;

	shadowmap_ref = NULL;

	//if (!settings->enable_shadows)
	//	null_shadow_buffer = new Texture("data/white.bmp");
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
	Light *l = rendering_context->getLight();
	if (settings->enable_shadows && l)
		if (shadowmap_ref)
			l->buildShadowMap(scene, shadowmap_ref);
		else
			l->buildShadowMap(scene, rendering_context->getCamera());
	//else if (!settings->enable_shadows)
	//	null_shadow_buffer->use(GLSLProgram::shadowmap_tex_sampler);
	rendering_context->clear();
	scene->render(rendering_context);
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
}

