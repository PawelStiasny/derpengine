#version 130

uniform mat4x4 MVP;
uniform mat4x4 M;
uniform mat4x4 shadow_VP;
uniform mat3x3 NormalMx;
uniform vec3 cam_pos;

in vec3 v;
in vec3 n;
in vec2 uv;
smooth out vec4 pos;
smooth out vec3 normal;
smooth out vec2 tex_coord;
smooth out vec4 shadowspace_pos;
smooth out float cam_distance;

void main() {
	vec4 eye_pos = MVP * vec4(v, 1.0);
	gl_Position = eye_pos;
	pos = M * vec4(v, 1.0);
	normal = normalize(NormalMx * n);
	shadowspace_pos = shadow_VP * M * vec4(v, 1.0);
	tex_coord = uv;
	cam_distance = eye_pos.z;
}
