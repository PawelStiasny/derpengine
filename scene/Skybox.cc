#include "Skybox.h"
#include "../RenderingContext.h"
#include "../shaders/Material.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

enum SIDES {
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

Skybox::Skybox()
{
	// Load sides
	t[FRONT] = new Tile("textures/skybox_f.bmp");
	t[FRONT]->setPosition(0.0f, 0.0f, 1.0f);
	t[BACK] = new Tile("textures/skybox_b.bmp");
	t[BACK]->setPosition(0.0f, 0.0f, -1.0f);
	t[BACK]->setRotation(0.0f, 180.0f, 0.0f);
	t[LEFT] = new Tile("textures/skybox_l.bmp");
	t[LEFT]->setPosition(-1.0f, 0.0f, 0.0f);
	t[LEFT]->setRotation(0.0f, -90.0f, 0.0f);
	t[RIGHT] = new Tile("textures/skybox_r.bmp");
	t[RIGHT]->setPosition(1.0f, 0.0f, 0.0f);
	t[RIGHT]->setRotation(0.0f, 90.0f, 0.0f);
	t[TOP] = new Tile("textures/skybox_t.bmp");
	t[TOP]->setPosition(0.0f, 1.0f, 0.0f);
	t[TOP]->setRotation(-90.0f, 0.0f, 0.0f);
	t[BOTTOM] = new Tile("textures/skybox_g.bmp");
	t[BOTTOM]->setPosition(0.0f, -1.0f, 0.0f);
	t[BOTTOM]->setRotation(90.0f, 0.0f, 0.0f);
	for (int i = 0; i < 6; i++)
		addMember(t[i]);

	Material *m = new Material();
	m->ambient = glm::vec4(1.0f);
	m->diffuse = glm::vec4(0.0f);
	setMaterial(m);
}

Skybox::~Skybox()
{
	for (int i = 0; i < 6; i++) delete t[i];
}

void Skybox::beforeRender(RenderingContext *rc)
{
	glm::vec3 camera_pos = rc->getCameraPos();
	glm::mat4 unit(1.0f);
	rc->pushMatrix();
	rc->setModelMatrix(unit);
	setPosition(camera_pos.x, camera_pos.y, camera_pos.z);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
}

void Skybox::afterRender(RenderingContext *rc)
{
	glPopAttrib();
	rc->popMatrix();
}
