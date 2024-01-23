#vertex
#version 330 core

layout(location = 0) in vec3 Apos;

void main()
{
  gl_Position = vec4(Apos,1.0f);
};