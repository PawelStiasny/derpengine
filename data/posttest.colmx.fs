#version 130

uniform sampler2D tex_sampler;

smooth in vec4 pos;
smooth in vec3 normal;
smooth in vec2 tex_coord;

out vec4 color;

void main() {
	mat3 color_mod = mat3(
	// Blueish
	/*
		0.4, 0.1, 0.4,
		0.1, 0.4, 0.4,
		0.0, 0.0, 0.6*/
		0.0, 1.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 0.0, 1.0
	);
	color = texture2D(tex_sampler, tex_coord);
	color.rgb = color_mod * color.rgb;
	color.a = 1.0;
}

