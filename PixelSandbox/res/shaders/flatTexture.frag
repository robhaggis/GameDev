#version 450 core
out vec4 FragColour;

in vec3 ourColor;
in vec2 texCoord;

// texture sampler
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	FragColour = texture(texture0, texCoord);
}
