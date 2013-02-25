#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H 

#include "scene/GraphNode.h"
#include "RenderingContext.h"
#include "animations/Animation.h"

/// SceneManager holds current engine state and takes care of populating and
/// updating the scene.
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	virtual void update(float timestep);
	virtual void render();
	virtual void onViewportReshape(int width, int height);

protected:
	GraphNode *scene;
	RenderingContext *rendering_context;
	std::list<Animation*> animations;
};

#endif
