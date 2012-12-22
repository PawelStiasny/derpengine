#version 130

uniform sampler2D tex_sampler;
in vec4 pos;
in vec4 light_pos;
in vec3 normal;

void main() {
	vec4 light_dir = normalize(light_pos - pos);

	vec4 diffuse = max(0.0, dot(normalize(normal), light_dir.xyz)) * gl_FrontMaterial.diffuse;
	vec4 ambient = gl_FrontMaterial.ambient;

	vec4 texel = texture2D(tex_sampler, gl_TexCoord[0].st);
	gl_FragColor = (diffuse + ambient) * texel;
}

