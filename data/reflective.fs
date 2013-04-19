#version 130

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

void main() {
	vec4 lp = light_pos;
	vec3 light_dir;
	light_dir = normalize(lp - lp.w * pos).xyz;
	vec3 cam_dir = normalize(pos.xyz - cam_pos);
	float cos_norm_light = dot(normal, light_dir);

	vec4 diffuse = max(0.0, cos_norm_light) * mat_diffuse;
	vec4 ambient = mat_ambient;

	vec3 reflect_dir = reflect(cam_dir, normal);
	vec4 specular = mat_specular * textureCube(specular_sampler, reflect_dir);

	vec4 texel = texture2D(tex_sampler, tex_coord);

	float visibility = 
		shadow2DProj(
			shadow_sampler,
			shadowspace_pos - vec4(0,0,0.02,0)).r;

	if ((shadowspace_pos.x < 0) || shadowspace_pos.y < 0 || shadowspace_pos.x > 1 || shadowspace_pos.y > 1) {
		visibility = 1;
	}
	diffuse *= visibility;

	gl_FragColor = (diffuse + ambient + specular) * texel;
}

