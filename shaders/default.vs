
#version 130

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 NormalMx;
in vec3 v;
out vec4 pos;
out vec4 light_pos;
out vec3 normal;

void main() {
	gl_Position = MVP * vec4(v, 1.0);
	pos = MV * vec4(v, 1.0);
	light_pos = normalize(gl_LightSource[0].position - pos);
	normal = NormalMx * gl_Normal;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
