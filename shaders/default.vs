
#version 120

uniform mat4x4 MVP;
uniform mat4x4 MV;
uniform mat3x3 NormalMx;
//uniform sampler2D tex_sampler;
in vec3 v;
out vec4 pos;
out vec4 light_pos;
out vec3 normal;

void main() {
	gl_Position = MVP * vec4(v, 1.0);
	//gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[0] = vec4(0.0, 0.0, 0.0, 0.0);
	
	pos = MV * vec4(v, 1.0);
	light_pos = normalize(gl_LightSource[0].position - pos);
	//normal = NormalMx * gl_Normal;
	//normal = gl_Normal.xyz;
	
}
