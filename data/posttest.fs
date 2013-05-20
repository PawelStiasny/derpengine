#version 130

uniform sampler2D tex_sampler;

smooth in vec4 pos;
smooth in vec3 normal;
smooth in vec2 tex_coord;

out vec4 color;

void main() {
	vec4 base_col = texture(tex_sampler, tex_coord);
	vec2 pert_coord = tex_coord + 0.05 * vec2(sin(base_col.r), cos(base_col.g));

   float blurSize = 0.005 * (1 - base_col.b);
   vec4 sum = vec4(0.0);
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   sum += texture2D(tex_sampler, vec2(pert_coord.x, pert_coord.y - 4.0*blurSize)) * 0.05;
   sum += texture2D(tex_sampler, vec2(pert_coord.x, pert_coord.y - 3.0*blurSize)) * 0.09;
   sum += texture2D(tex_sampler, vec2(pert_coord.x, pert_coord.y - 2.0*blurSize)) * 0.12;
   sum += texture2D(tex_sampler, vec2(pert_coord.x, pert_coord.y - blurSize)) * 0.15;
   sum += texture2D(tex_sampler, vec2(pert_coord.x, pert_coord.y)) * 0.16;
   sum += texture2D(tex_sampler, vec2(pert_coord.x, pert_coord.y + blurSize)) * 0.15;
   sum += texture2D(tex_sampler, vec2(pert_coord.x, pert_coord.y + 2.0*blurSize)) * 0.12;
   sum += texture2D(tex_sampler, vec2(pert_coord.x, pert_coord.y + 3.0*blurSize)) * 0.09;
   sum += texture2D(tex_sampler, vec2(pert_coord.x, pert_coord.y + 4.0*blurSize)) * 0.05;
 
	color = sum;

	color.b = base_col.b;
	color.a = 1.0;
	color *= vec4(1,tex_coord.x,tex_coord.y,1);
	color *= color;
}

