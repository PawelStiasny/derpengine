#include "DemoSceneManager.h"

DemoSceneManager::DemoSceneManager()
{
	scene->addMember(new Skybox);

	mech = new Mech();
	scene->addMember(mech);

	mechcam = new Camera();
	mechcam->setPosition(0.0f, 1.0f, -2.0f);
	mech->addMember(mechcam);
	mechcam->setTarget(mech);

	terrain = new Terrain("textures/heightmap.bmp", 20.0f);
	scene->addMember(terrain);

	rendering_context->setCamera(mechcam);

	scene_rot = new CameraTracking(mech, mechcam);
	animations.push_back(scene_rot);

	walk_animation = new MechWalk(mech, terrain);
	animations.push_back(walk_animation);
}
