#version 130

uniform sampler2D tex_sampler;
uniform sampler2DShadow shadow_sampler;
uniform vec4 mat_ambient, mat_diffuse, mat_specular;
uniform float mat_shininess;
uniform vec4 light_pos;
uniform vec3 cam_pos;

smooth in vec4 pos;
smooth in vec3 normal;
smooth in vec2 tex_coord;
smooth in vec4 shadowspace_pos;
smooth in float cam_distance;

out vec4 color;

/* defined in std.fs */
float diffuse_term(vec3 normal, vec3 light);
float shadow_term(sampler2DShadow shadow_sampler, vec4 shadowspace_pos);
float specular_term(vec3 normal, vec3 light, vec3 cam, float shininess);
vec4 linear_fog(vec4 color, vec4 fog_color, float cam_distance);

void main() {
	vec4 lp = light_pos;
	vec3 light_dir;
	light_dir = normalize(lp - lp.w * pos).xyz;
	vec3 cam_dir = normalize(cam_pos - pos.xyz);

	vec4 diffuse =
		diffuse_term(normal, light_dir) *
		mat_diffuse;
	vec4 ambient = mat_ambient;
	vec4 specular =
		specular_term(normal, light_dir, cam_dir, mat_shininess) *
		mat_specular;

	vec4 texel = texture(tex_sampler, tex_coord);

	float visibility = shadow_term(shadow_sampler, shadowspace_pos);

	diffuse *= visibility;
	specular *= visibility;

	color = (diffuse + ambient + specular) * texel;
	/*color = linear_fog( color, vec4(0.67, 0.81, 0.65, 0.0), cam_distance );*/
}

