#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../RenderingContext.h"
#include "MechLeg.h"

MechLeg::MechLeg(GLfloat length, GLfloat radius)
{
	this->length = length;
	this->radius = radius;
	float sideways_cyl_radius = 0.16f, sideways_cyl_length = radius + 0.1f;

	allocCount(3 * 21*5, 3 * 20*4*2);
	constructCylinder(radius, length, 20, 4, 4, 4);
	construction_mx = glm::rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	construction_mx = glm::translate(construction_mx, glm::vec3(0.0f, 0.0f, -sideways_cyl_length/2.0f));
	constructCylinder(sideways_cyl_radius, sideways_cyl_length, 20, 4, 4, 1);
	construction_mx = glm::translate(glm::vec3(0.0f,0.0f,length)) * construction_mx;
	constructCylinder(sideways_cyl_radius, sideways_cyl_length, 20, 4, 4, 1);
	syncBuffers();
}

