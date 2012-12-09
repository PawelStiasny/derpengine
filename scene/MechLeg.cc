#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../RenderingContext.h"
#include "MechLeg.h"

MechLeg::MechLeg(GLfloat length, GLfloat radius)
{
	this->length = length;
	this->radius = radius;
	quad_obj = gluNewQuadric();
	quad_obj_inv = gluNewQuadric();
	gluQuadricTexture(quad_obj, GL_TRUE);
	gluQuadricOrientation(quad_obj, GLU_OUTSIDE);
	gluQuadricTexture(quad_obj_inv, GL_TRUE);
	gluQuadricOrientation(quad_obj_inv, GLU_INSIDE);
}

/// Render capped cylinders making the leg.
void MechLeg::doRender(RenderingContext *rc)
{
	glm::mat4 model_coords = rc->getModelMatrix();

	// Main leg part
	gluCylinder(quad_obj, radius, radius, length, 20, 1);

	// Sideways joint cylinders
	float sideways_cyl_radius = 0.16f, sideways_cyl_length = radius + 0.1f;

	glm::mat4 sideways_coords = glm::rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	sideways_coords = glm::translate(sideways_coords, glm::vec3(0.0f, 0.0f, -sideways_cyl_length/2.0f));

	glm::mat4 m = model_coords * sideways_coords;
	rc->setModelMatrix(m);
	gluCylinder(quad_obj, sideways_cyl_radius, sideways_cyl_radius, sideways_cyl_length, 20, 1);
	gluDisk(quad_obj_inv, 0.0f, sideways_cyl_radius, 20, 4);
	m = glm::translate(m, glm::vec3(0.0f, 0.0f, sideways_cyl_length));
	rc->setModelMatrix(m);
	gluDisk(quad_obj, 0.0f, sideways_cyl_radius, 20, 4);

	glm::mat4 top_translated_coords = glm::translate(glm::vec3(0.0f,0.0f,length));
	m = model_coords * top_translated_coords * sideways_coords;
	rc->setModelMatrix(m);
	gluCylinder(quad_obj, sideways_cyl_radius, sideways_cyl_radius, sideways_cyl_length, 20, 1);
	gluDisk(quad_obj_inv, 0.0f, sideways_cyl_radius, 20, 4);
	m = glm::translate(m, glm::vec3(0.0f, 0.0f, sideways_cyl_length));
	rc->setModelMatrix(m);
	gluDisk(quad_obj, 0.0f, sideways_cyl_radius, 20, 4);

	rc->setModelMatrix(model_coords);
}
