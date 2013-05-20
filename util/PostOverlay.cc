#include "PostOverlay.h"
#include "../util/ResourceManager.h"
#include "../scene/Tile.h"

void PostOverlay::render(FramebufferTexture *src)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	post_prog->use();
	src->use(post_prog->TEXUNIT_COLOR);
	ResourceHandle<Geometry> t = ResourceManager::getInstance()->getModel("tile");
	t->render();
}
