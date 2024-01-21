#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;


struct Material{
    vec3 Ka; //Intensitat ambiental
    vec3 Kd; // Intensitat difusa
    vec3 Ks; // Intensitat especular
    float shiness; // Posició (en el cas de llum puntual)
    float opacity; // Direcció (en el cas de llum direccional o llum tipo spot)

};
uniform Material myMaterial;

uniform mat4 model_view;
uniform mat4 projection;
out vec3 normal;

void main()
{
    gl_Position = projection * model_view * vPosition;
    gl_Position = gl_Position / gl_Position.w;

    normal = normalize(transpose(inverse(mat3(model_view))) * vNormal);
}

