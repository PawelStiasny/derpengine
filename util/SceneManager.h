#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H 

#include "InputState.h"
#include "../core/GraphNode.h"
#include "../core/RenderingContext.h"
#include "../core/FramebufferTexture.h"
#include "../core/DepthFramebufferTexture.h"
#include "../core/DepthPassRenderingContext.h"
#include "../core/Framebuffer.h"
#include "../animations/Animation.h"
#include "PostOverlay.h"
#include "Settings.h"
#include <list>
#include <string>

/// SceneManager holds current game state and takes care of populating and
/// updating the scene.
class SceneManager
{
public:
	SceneManager(Settings *settings);
	virtual ~SceneManager();
	virtual void update(float timestep);
	virtual void render();
	virtual void onViewportReshape(int width, int height);
	virtual void handleInput(InputState *st) {};
	void setShadowmapReference(GraphNode *r) { shadowmap_ref = r; };
	void appendPostOverlay(std::string fragment_shader);

protected:
	Settings *settings;
	GraphNode *scene;
	RenderingContext *rendering_context;
	DepthPassRenderingContext depth_context;
	std::list<Animation*> animations;

private:
	Texture *null_shadow_buffer;
	FramebufferTexture main_buffer;
	DepthFramebufferTexture depth_tex;
	Framebuffer fb;
	GraphNode *shadowmap_ref;
	std::list<PostOverlay> post_overlays;
};

#endif
