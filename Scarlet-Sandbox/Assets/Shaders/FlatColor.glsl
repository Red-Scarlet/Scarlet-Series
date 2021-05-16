// Basic Texture Shader

#type vertex
#version 410 core

layout(location = 0) in vec3 a_Position;

void main() 
{
	gl_Position = vec4(a_Position, 1.0);
}

#type fragment
#version 410 core

layout(location = 0) out vec4 FragColor;

void main() 
{
	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}