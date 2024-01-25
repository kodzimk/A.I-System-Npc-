#vertex
#version 330 core

layout(location = 0) in vec3 Apos;

uniform mat4 model;

void main()
{
  gl_Position = model * vec4(Apos.x,Apos.y,Apos.z,1.0);
};