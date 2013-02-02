#version 130

uniform mat3x3 NormalMx;
uniform sampler2D tex_sampler;
uniform vec4 mat_ambient, mat_diffuse, mat_specular;
uniform float mat_shininess;
//uniform vec4 light_pos;
const vec4 light_pos = vec4(300.0, 100.0, -300.0, 0.0);
uniform vec3 cam_pos;

smooth in vec4 pos;
smooth in vec3 normal;
smooth in vec2 tex_coord;

void main() {
	vec4 lp = light_pos;
	vec3 light_dir;
	light_dir = normalize(lp - lp.w * pos).xyz;
	vec3 cam_dir = normalize(pos.xyz - cam_pos);
	float cos_norm_light = dot(normal, light_dir);

	vec4 diffuse = max(0.0, cos_norm_light) * mat_diffuse;
	vec4 ambient = mat_ambient;
	vec4 specular =
			pow(
				max(0.0, dot(cam_dir, reflect(light_dir, normal))),
				mat_shininess) *
			mat_specular;

	vec4 texel = texture2D(tex_sampler, tex_coord);
	gl_FragColor = (diffuse + ambient + specular) * texel;
}

