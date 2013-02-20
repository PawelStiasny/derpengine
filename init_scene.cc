#include "RenderingContext.h"
#include "scene/GraphNode.h"
#include "scene/Skybox.h"
#include "scene/Terrain.h"
#include "scene/Mech.h"
#include "animations/CameraTracking.h"
#include "animations/MechWalk.h"

static GraphNode *scene = NULL;
static Camera *mechcam = NULL;
static Terrain *terrain = NULL;
static Mech *mech = NULL;

CameraTracking *scene_rot;
MechWalk *walk_animation;

/// Creates the initial scene graph.
GraphNode * init_scene()
{
	scene = new GraphNode;
	scene->addMember(new Skybox);

	mech = new Mech();
	scene->addMember(mech);

	mechcam = new Camera();
	mechcam->setPosition(0.0f, 1.0f, -2.0f);
	mech->addMember(mechcam);
	mechcam->setTarget(mech);
	//mech->setVisibility(false);
	
	terrain = new Terrain("textures/heightmap.bmp", 20.0f);
	scene->addMember(terrain);

	return scene;
}

void setup_context(RenderingContext *rc)
{
	rc->setCamera(mechcam);
}

void init_animations(std::list<Animation*> &animations)
{
	scene_rot = new CameraTracking(mech, mechcam);
	animations.push_back(scene_rot);

	walk_animation = new MechWalk(mech, terrain);
	animations.push_back(walk_animation);
}

