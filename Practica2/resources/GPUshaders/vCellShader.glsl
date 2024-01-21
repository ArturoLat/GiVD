#version 330

layout (location = 0) in vec4 vPosition; // Posició dels vèrtexs
layout (location = 1) in vec4 vColor; // Color dels vèrtexs
layout (location = 2) in vec3 vNormal; // Normal dels vèrtexs

uniform mat4 model_view; // Matriu de modelat i visualització
uniform mat4 projection; // Matriu de projecció

out vec4 position;
out vec3 normal;

void main()
{
    gl_Position = projection * model_view * vPosition;
    gl_Position = gl_Position / gl_Position.w;
    normal = vNormal;
    position = vPosition;
}
