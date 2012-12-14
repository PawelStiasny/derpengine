
#version 130

uniform mat4 MVP;
in vec3 v;

void main() {
	gl_Position = MVP * vec4(v, 1.0);
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
