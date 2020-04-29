#version 140

vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

float specular_term(vec3 normal, vec3 light, vec3 cam, float shininess)
{
	vec3 halfv = normalize(light + cam);
	float blinn_term = pow( dot(normal, halfv), shininess );
	return clamp(blinn_term, 0.0, 1.0);
}

float diffuse_term(vec3 normal, vec3 light)
{
	float cos_norm_light = dot(normal, light);
	return max(0.0, cos_norm_light);
}

float shadow_term(sampler2DShadow shadow_sampler, vec4 shadowspace_pos)
{
	float visibility = 0.0;
	for (int i = 0; i < 4; i++) {
		visibility += 0.25 * textureProj(
			shadow_sampler,
			shadowspace_pos
				+ vec4(poissonDisk[i] / 700.0, 0.0, 0.0)
				- vec4(0,0,0.02,0));
	}

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
