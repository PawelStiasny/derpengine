#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../core/RenderingContext.h"
#include "MechLeg.h"

MechLeg::MechLeg(GLfloat length, GLfloat radius)
	: ConstructedGeometry(3*21*5 + 4*22, 3*20*4*2 + 4*20)
{
	this->length = length;
	this->radius = radius;
	float sideways_cyl_radius = 0.16f, sideways_cyl_length = radius + 0.1f;

	// Main bone cylinder
	constructCylinder(radius, length, 20, 4, 2, 4);

	// Joint cylinders
	construction_mx = glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	construction_mx = glm::translate(construction_mx, glm::vec3(0.0f, 0.0f, -sideways_cyl_length/2.0f));
	constructCylinder(sideways_cyl_radius, sideways_cyl_length, 20, 4, 4, 1);
	constructCap(sideways_cyl_radius, 20, false);
	glm::mat4 mt = construction_mx;
	construction_mx = glm::translate(construction_mx, glm::vec3(0.0f, 0.0f, sideways_cyl_length));
	constructCap(sideways_cyl_radius, 20, true);

	construction_mx = glm::translate(glm::vec3(0.0f,0.0f,length)) * mt;
	constructCylinder(sideways_cyl_radius, sideways_cyl_length, 20, 4, 4, 1);
	constructCap(sideways_cyl_radius, 20, false);
	construction_mx = glm::translate(construction_mx, glm::vec3(0.0f, 0.0f, sideways_cyl_length));
	constructCap(sideways_cyl_radius, 20, true);
}

