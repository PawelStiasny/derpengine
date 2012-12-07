#include <glm/glm.hpp>

class GLSLProgram {
public:
	GLSLProgram();
	~GLSLProgram();
	void use();
	void setUniformMVP(glm::mat4& mvp);
private:
	GLuint program_id;
	static const char *vertex_shader_source;
	static const char *fragment_shader_source;

	GLuint compileVertexShader();
	GLuint compileFragmentShader();
};

