#include "../core/ConstructedGeometry.h"
#include <GL/glu.h>

class MechLeg : public ConstructedGeometry
{
private:
	GLfloat length, radius;

public:
	MechLeg(GLfloat length, GLfloat radius);
	virtual void beforeRender(RenderingContext *rc) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	virtual void afterRender(RenderingContext *rc) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
};
