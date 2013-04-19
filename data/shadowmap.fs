#version 130

uniform mat3x3 NormalMx;
uniform sampler2D tex_sampler, shadow_sampler;
uniform vec4 mat_ambient, mat_diffuse, mat_specular;
uniform float mat_shininess;
uniform vec4 light_pos;
uniform vec3 cam_pos;

smooth in vec4 pos;
smooth in vec3 normal;
smooth in vec2 tex_coord;

void main() {
	vec4 texel = texture2D(tex_sampler, tex_coord);
	gl_FragColor = texel;
}

