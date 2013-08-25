#version 130

uniform mat4x4 MVP;
uniform mat4x4 M;
uniform mat4x4 shadow_VP;
uniform mat3x3 NormalMx;
uniform vec3 cam_pos;
uniform sampler2D height_sampler;

in vec3 v;
in vec3 n;
in vec2 uv;
smooth out vec4 pos;
smooth out vec3 normal;
smooth out vec2 tex_coord;
smooth out vec4 shadowspace_pos;
smooth out float cam_distance;

vec3 get_pos_with_height(vec2 pos)
{
	return vec3(
		pos.x,
		texture(height_sampler, (pos.xy + 128.0) / 256.0).r * 20.0f,
		pos.y);
}

void main()
{
	vec3 mid = get_pos_with_height(v.xz);
	vec4 eye_pos = MVP * vec4(mid, 1.0);
	gl_Position = eye_pos;
	pos = M * vec4(v, 1.0);

	float tunit = 1.0;
	vec2 tpos = v.xz / 256.0;
	vec3
		west = get_pos_with_height(vec2(v.x - tunit, v.z)),
		north = get_pos_with_height(vec2(v.x, v.z + tunit)),
		east = get_pos_with_height(vec2(v.x + tunit, v.z)),
		south = get_pos_with_height(vec2(v.x, v.z - tunit));
	vec3 triangle_normal_acc;
	triangle_normal_acc = normalize(cross(mid - north, west - north));
	triangle_normal_acc += normalize(cross(mid - east, north - east));
	triangle_normal_acc += normalize(cross(mid - south, east - south));
	triangle_normal_acc += normalize(cross(mid - west, south - west));
	triangle_normal_acc *= 0.25f;
	normal = triangle_normal_acc;

	shadowspace_pos = shadow_VP * M * vec4(v, 1.0);
	tex_coord = uv;
	cam_distance = eye_pos.z;
}
