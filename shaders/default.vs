#version 130

uniform mat4x4 MVP;
uniform mat4x4 M;
uniform mat3x3 NormalMx;
//uniform vec4 light_pos;
uniform vec3 cam_pos;

in vec3 v;
in vec3 n;
in vec2 uv;
smooth out vec4 pos;
//out vec4 light_dir;
smooth out vec3 normal;
smooth out vec2 tex_coord;

void main() {
	gl_Position = MVP * vec4(v, 1.0);
	pos = M * vec4(v, 1.0);
	normal = normalize(NormalMx * n);
	tex_coord = uv;
}
