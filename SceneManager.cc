#include "SceneManager.h"

#include <list>
#include <algorithm>
#include <functional>

SceneManager::SceneManager()
{
	scene = new GraphNode;
	rendering_context = new RenderingContext;
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

