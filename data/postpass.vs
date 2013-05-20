#version 130

in vec3 v;
in vec3 n;
in vec2 uv;
smooth out vec4 pos;
smooth out vec3 normal;
smooth out vec2 tex_coord;

void main() {
	vec4 eye_pos = vec4(v, 1.0);
	gl_Position = eye_pos;
	pos = vec4(v, 1.0);
	normal = n;
	tex_coord = uv;
}
