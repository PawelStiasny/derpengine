#version 130

float specular_term(vec3 normal, vec3 light, vec3 cam, float shininess)
{
	return pow(
			max(0.0, dot(cam, reflect(light, normal))), shininess);
}

float diffuse_term(vec3 normal, vec3 light)
{
	float cos_norm_light = dot(normal, light);
	return max(0.0, cos_norm_light);
}

float shadow_term(sampler2DShadow shadow_sampler, vec4 shadowspace_pos)
{
	float visibility =
		textureProj(shadow_sampler, shadowspace_pos - vec4(0,0,0.02,0));

	vec2 not_in_shadowspace = 
		step(shadowspace_pos.xy, vec2(0.0,0.0)) +
		step(vec2(1.0, 1.0), shadowspace_pos.xy);
	not_in_shadowspace = min(not_in_shadowspace, vec2(1.0,1.0));
	visibility = max(
		visibility,
		min(not_in_shadowspace.x + not_in_shadowspace.y, 1.0));

	return visibility;
}

vec4 linear_fog(vec4 color, vec4 fog_color, float cam_distance)
{
	/* TODO: parametrize distance */
	float fog = clamp((cam_distance - 110.0) * 0.12, 0.0, 1.0);
	return mix( color, fog_color, fog );
}
