#version 140

uniform sampler2D tex_sampler;
uniform sampler2DShadow shadow_sampler;
uniform samplerCube specular_sampler;
uniform vec4 mat_ambient, mat_diffuse, mat_specular;
uniform float mat_shininess;
uniform vec4 light_pos;
uniform vec3 cam_pos;

smooth in vec4 pos;
smooth in vec3 normal;
smooth in vec2 tex_coord;
smooth in vec4 shadowspace_pos;

out vec4 color;

/* defined in std.fs */
float diffuse_term(vec3 normal, vec3 light);
float shadow_term(sampler2DShadow shadow_sampler, vec4 shadowspace_pos);

void main() {
	vec4 lp = light_pos;
	vec3 light_dir;
	light_dir = normalize(lp - lp.w * pos).xyz;
	vec3 cam_dir = normalize(cam_pos - pos.xyz);

	vec4 diffuse = diffuse_term(pnormal, light_dir) * mat_diffuse;
	vec4 ambient = mat_ambient;

	vec3 reflect_dir = reflect(cam_dir, normal);
	vec4 specular = mat_specular * texture(specular_sampler, -reflect_dir);

	vec4 texel = texture(tex_sampler, tex_coord);

	float visibility = shadow_term(shadow_sampler, shadowspace_pos);

	diffuse *= visibility;

	color = (diffuse + ambient + specular) * texel;
}

