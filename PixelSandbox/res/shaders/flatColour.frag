#version 450 core
out vec4 FragColour;

//RGb Colour Data
uniform float rVal;
uniform float gVal;
uniform float bVal;

void main()
{
	FragColour = vec4(rVal, gVal, bVal, 1.0);
}




