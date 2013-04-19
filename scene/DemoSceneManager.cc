#include "DemoSceneManager.h"

static const char *skybox_paths[] = {
			"data/skybox_f.bmp",
			"data/skybox_b.bmp",
			"data/skybox_t.bmp",
			"data/skybox_g.bmp",
			"data/skybox_l.bmp",
			"data/skybox_r.bmp"
};

DemoSceneManager::DemoSceneManager(Settings *settings)
	: SceneManager(settings), specular_environment_map(skybox_paths)
{
	scene->addMember(new Skybox);

	sun = new DirectionalLight();
	sun->setPosition(30.0f, 10.0f, -30.0f);
	scene->addMember(sun);

	mech = new Mech();
	scene->addMember(mech);

	setShadowmapReference(mech);

	mechcam = new PerspectiveCamera();
	mechcam->setPosition(0.0f, 1.0f, -2.0f);
	mech->addMember(mechcam);
	mechcam->setTarget(mech);

	terrain = new Terrain(20.0f);
	scene->addMember(terrain);

	rendering_context->setCamera(mechcam);
	rendering_context->setLight(sun);
	rendering_context->setEnvironmentMap(&specular_environment_map);

	scene_rot = new CameraTracking(mech, mechcam);
	animations.push_back(scene_rot);

	walk_animation = new MechWalk(mech, terrain);
	animations.push_back(walk_animation);
}

void DemoSceneManager::handleInput(InputState *st)
{
	if (st->getKeyState(InputState::KF_FORWARDS))
		walk_animation->move_forward = 1;
	else if (st->getKeyState(InputState::KF_BACKWARDS))
		walk_animation->move_forward = -1;
	else
		walk_animation->move_forward = 0;

	if (st->getKeyState(InputState::KF_ROTATE_SUN)) {
		sun->setPosition(
				20.0f * glm::sin(2.0f * 3.14f * st->getMouseX()),
				100.0f * st->getMouseY(),
				20.0f * glm::cos(2.0f * 3.14f * st->getMouseX()));
	} else {
		scene_rot->y = 4.0f * st->getMouseY() - 2.0f;
		scene_rot->rotation = -360.0f * st->getMouseX();
	}
}

