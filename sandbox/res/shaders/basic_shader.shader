#shader vertex
#version 440 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;
out vec2 v_TexCoord;
out float v_texIndex;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord ;
	v_texIndex = texIndex;
}

#shader fragment
#version 440 core

in vec2 v_TexCoord;
in float v_texIndex;
layout(location = 0) out vec4 color;

uniform sampler2D u_Textures[32];

void main()
{
	int idx = int(v_texIndex);
	vec4 texColor = texture(u_Textures[idx], v_TexCoord);
	color = texColor;
}