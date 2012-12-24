#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../RenderingContext.h"
#include "MechLeg.h"

MechLeg::MechLeg(GLfloat length, GLfloat radius)
{
	this->length = length;
	this->radius = radius;
	float sideways_cyl_radius = 0.16f, sideways_cyl_length = radius + 0.1f;

	allocCount(3 * 21*21, 3 * 20*20*2);
	constructCylinder(radius, length, 20, 4, 4, 4);
	construction_mx = glm::rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	construction_mx = glm::translate(construction_mx, glm::vec3(0.0f, 0.0f, -sideways_cyl_length/2.0f));
	constructCylinder(sideways_cyl_radius, sideways_cyl_length, 20, 4, 4, 1);
	construction_mx = glm::translate(glm::vec3(0.0f,0.0f,length)) * construction_mx;
	constructCylinder(sideways_cyl_radius, sideways_cyl_length, 20, 4, 4, 1);
	syncBuffers();
}

/*
/// Render capped cylinders making the leg.
void MechLeg::doRender(RenderingContext *rc)
{
	
	return;

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
}*/
