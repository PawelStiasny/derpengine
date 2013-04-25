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

// Implementation of method described in
// "Bump Mapping Unparametrized Surfaces on the GPU"
// Morten S. Mikkelsen, 2010
vec3 pertrurb_normal(vec3 pos, vec3 norm, sampler2D hmap, vec2 st)
{
	vec3 sigmaS = dFdx(pos);
	vec3 sigmaT = dFdy(pos);
	
	vec3 R1 = cross(sigmaT, norm);
	vec3 R2 = cross(norm, sigmaS);

	float det = dot(sigmaS, R1);

	vec2 tex_dx = dFdx(st);
	vec2 tex_dy = dFdy(st);
	vec2 st_ll = st;
	vec2 st_lr = st + tex_dx;
	vec2 st_ul = st + tex_dy;
	float height_ll = texture2D(hmap, st_ll).r;
	float height_lr = texture2D(hmap, st_lr).r;
	float height_ul = texture2D(hmap, st_ul).r;
	float dBs = (height_lr - height_ll) * 0.1;
	float dBt = (height_ul - height_ll) * 0.1;
	vec3 surface_gradient = sign(det) * (dBs*R1 + dBt*R2);
	return normalize(abs(det)*norm - surface_gradient);
}

void main()
{
	//vec4 texel = texture2D(tex_sampler, tex_coord);
	vec3 pnormal =
		pertrurb_normal(pos.xyz/pos.w, normalize(normal), tex_sampler, tex_coord);
	vec4 lp = light_pos;
	vec3 light_dir;
	light_dir = normalize(lp - lp.w * pos).xyz;
	vec3 cam_dir = normalize(pos.xyz - cam_pos);
	float cos_norm_light = dot(pnormal, light_dir);

	vec4 diffuse = max(0.0, cos_norm_light) * mat_diffuse;
	vec4 ambient = mat_ambient;

	vec3 reflect_dir = reflect(cam_dir, pnormal);
	vec4 specular = mat_specular * textureCube(specular_sampler, reflect_dir);


	float visibility = 
		shadow2DProj(
			shadow_sampler,
			shadowspace_pos - vec4(0,0,0.02,0)).r;

	if ((shadowspace_pos.x < 0) || shadowspace_pos.y < 0 || shadowspace_pos.x > 1 || shadowspace_pos.y > 1) {
		visibility = 1;
	}
	diffuse *= visibility;

	gl_FragColor = (diffuse + ambient + specular) * (0.2, 0.2, 0.2, 1.0);
}

