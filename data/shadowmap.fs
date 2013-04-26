/* Shader ised in light space rendering to the shadowmap */

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

out vec4 color;

void main() {
	color = vec4(1.0,1.0,1.0,1.0);
}

