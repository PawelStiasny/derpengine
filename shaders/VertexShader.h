#include <glm/glm.hpp>

class VertexShader {
public:
	VertexShader();
	void use();
	void setUniformMVP(glm::mat4& mvp);
private:
	GLuint program_id;
	static const char *vertex_shader_source;
};

