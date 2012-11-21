#include <GL/gl.h>
#include <vector>

/// Each graph node is a composite directing rendering of itself and its
/// members.
class GraphNode
{
private:
	struct Vec3 {
		GLfloat v[3];
		bool isSet() { return (v[0] != 0) || (v[1] != 0) || (v[2] != 0); };
	} pos, rot;

public:
	std::vector<GraphNode*> members;
	virtual ~GraphNode();
	virtual void render();
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setRotation(GLfloat x, GLfloat y, GLfloat z);

private:
	virtual void doRender();
};
