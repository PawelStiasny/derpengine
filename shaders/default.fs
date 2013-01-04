#version 130

uniform mat3x3 NormalMx;
uniform sampler2D tex_sampler;
uniform vec4 light_pos;
uniform vec3 cam_pos;

smooth in vec4 pos;
//in vec4 light_dir
smooth in vec3 normal;

void main() {
	vec4 lp = gl_LightSource[0].position;
	vec3 light_dir;
	if (lp.w == 0.0)
		light_dir = normalize(lp).xyz;
	else
		light_dir = normalize(lp - pos).xyz;
	vec3 cam_dir = normalize(pos.xyz - cam_pos);
	float cos_norm_light = dot(normal, light_dir);

	vec4 diffuse = max(0.0, cos_norm_light) * gl_FrontMaterial.diffuse;
	vec4 ambient = gl_FrontMaterial.ambient;
	vec4 specular;
	if (cos_norm_light > 0.0)
		specular = 
			pow(
				max(0.0, dot(cam_dir, reflect(light_dir, normal))),
				gl_FrontMaterial.shininess) *
			gl_FrontMaterial.specular;
	else
		specular = vec4(0,0,0,0);

	vec4 texel = texture2D(tex_sampler, gl_TexCoord[0].st);
	gl_FragColor = (diffuse + ambient + specular) * texel;
}

