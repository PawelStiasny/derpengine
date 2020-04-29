#ifndef GLSLOBJECT_H
#define GLSLOBJECT_H

#include "../util/resource.h"
//#include "../util/FileWatcher.h"
#include "../common.h"

/// Represents a GLSL Shader than can be linked into a GLSLProgram
class GLSLObject : public SharedResource
{
public:
	GLSLObject(GLenum type, const char *shader_path);
	~GLSLObject();

	GLuint getId();
	bool isUsable();

	virtual void onFileChanged();

private:
	GLuint shader_id;

	GLuint compileShader(GLenum type, const char* src);
	GLuint compileFromFile(GLenum type, const char* path);
};

#endif

