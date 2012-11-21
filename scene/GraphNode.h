#include <GL/gl.h>
#include <list>

/// Each graph node is a composite directing rendering of itself and its
/// members.
class GraphNode
{
private:
	struct Vec3 {
		GLfloat v[3];
		bool isSet() {
			return (v[0] != 0.0f) || (v[1] != 0.0f) || (v[2] != 0.0f);
		};
	} pos, rot;

protected:
	std::list<GraphNode*> members;
	GraphNode* parent;

public:
	GraphNode();
	virtual ~GraphNode();
	virtual void render();
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setRotation(GLfloat x, GLfloat y, GLfloat z);
	void addMember(GraphNode* member);
	void removeMember(GraphNode* member);

private:
	virtual void doRender();
};
