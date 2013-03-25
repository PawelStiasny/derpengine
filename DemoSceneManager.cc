#include "DemoSceneManager.h"

DemoSceneManager::DemoSceneManager()
{
	scene->addMember(new Skybox);

	sun = new DirectionalLight();
	sun->setPosition(30.0f, 10.0f, -30.0f);
	//sun->setPosition(5.0f, 8.0f, 5.0f);
	scene->addMember(sun);

	mech = new Mech();
	scene->addMember(mech);

	//mechcam = new PerspectiveCamera();
	//mechcam->setPosition(0.0f, 1.0f, -2.0f);
	//mech->addMember(mechcam);
	//mechcam->setTarget(mech);

	terrain = new Terrain("textures/heightmap.bmp", 20.0f);
	scene->addMember(terrain);

	//rendering_context->setCamera(mechcam);
	rendering_context->setLight(sun);

	/*Tile *t = new Tile();
	Material *m = new Material();
	m->ambient = glm::vec4(1.0f);
	m->diffuse = glm::vec4(0.0f,0.0f,0.0f,1.0f);
	m->specular = glm::vec4(0.0f,0.0f,0.0f,1.0f);
	m->shininess = 1.0f;
	m->texture = sun->getShadowmap();
	t->setMaterial(m);

	t->setPosition(3, 20, 3);
	scene->addMember(t);*/

	mechcam = new PerspectiveCamera;
	mechcam->setPosition(0.0f, 1.0f, -2.0f);
	mech->addMember(mechcam);
	rendering_context->setCamera(mechcam);

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

	scene_rot->y = 4.0f * st->getMouseY() - 2.0f;
	scene_rot->rotation = -360.0f * st->getMouseX();
}

void DemoSceneManager::render()
{
	sun->buildShadowMap(scene, mech);
	SceneManager::render();
}
