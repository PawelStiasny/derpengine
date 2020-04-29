#version 140

uniform sampler2D tex_sampler;
uniform float time;

smooth in vec4 pos;
smooth in vec3 normal;
smooth in vec2 tex_coord;

out vec4 color;

void main() {
	vec4 base_col = texture(tex_sampler, tex_coord);
	vec2 pert_coord = tex_coord + 0.05 * vec2(sin(base_col.r-0.5), cos(base_col.g)-1) * sin(time);
	//pert_coord += 0.005 * vec2(sin(time), cos(time));


	vec4 sum = vec4(0.0);
	// radial blur
	vec2 blur_dir = pos.xy;
	sum += texture2D(tex_sampler, pert_coord + 0.02 * blur_dir) * 0.05;
	sum += texture2D(tex_sampler, pert_coord + 0.015 * blur_dir) * 0.09;
	sum += texture2D(tex_sampler, pert_coord + 0.010 * blur_dir) * 0.12;
	sum += texture2D(tex_sampler, pert_coord + 0.005 * blur_dir) * 0.15;
	sum += texture2D(tex_sampler, pert_coord) * 0.16;
	sum += texture2D(tex_sampler, pert_coord - 0.02 * blur_dir) * 0.05;
	sum += texture2D(tex_sampler, pert_coord - 0.015 * blur_dir) * 0.09;
	sum += texture2D(tex_sampler, pert_coord - 0.010 * blur_dir) * 0.12;
	sum += texture2D(tex_sampler, pert_coord - 0.005 * blur_dir) * 0.15;

	color = sum;

	color.b = base_col.b;
	color *= vec4(1,tex_coord.x + 0.6 * sin(time * 0.1), tex_coord.y + 0.6 * cos(time * 0.1),1);
	color *= color;

	color.a = 1.0;
}

