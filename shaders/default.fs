#version 120

//uniform mat4x4 MVP;
//uniform mat4x4 MV;
//uniform mat3x3 NormalMx;
uniform sampler2D tex_sampler;
in vec4 pos;
in vec4 light_pos;
in vec3 normal;

void main() {
	//gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_FragColor = texture2D(tex_sampler, gl_TexCoord[0].st);
    /*
	vec4 light_dir = light_pos;

	vec4 diffuse = max(0.0, dot(normalize(normal), light_dir.xyz)) * gl_FrontMaterial.diffuse;
	vec4 ambient = gl_FrontMaterial.ambient;

	//vec4 texel = texture2D(tex_sampler, gl_TexCoord[0].st);
    vec4 texel = vec4(1.0, 1.0, 1.0, 1.0);
	gl_FragColor = (diffuse + ambient) * texel;*/
}

