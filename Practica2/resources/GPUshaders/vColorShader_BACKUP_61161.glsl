#version 330

layout (location = 0) in vec4 vPosition;

uniform mat4 model_view;
uniform mat4 projection;

struct Material{
    vec3 Ka; //Intensitat ambiental
    vec3 Kd; // Intensitat difusa
    vec3 Ks; // Intensitat especular
    float shiness; // Posició (en el cas de llum puntual)
    float opacity; // Direcció (en el cas de llum direccional o llum tipo spot)

};
uniform Material myMaterial;

out vec4 color;

void main()
{

    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    //color = vec4(myMaterial.Ka, 1.0f);
    color = vec4(myMaterial.Kd, 1.0f);
    //color = vec4(myMaterial.Ks, 1.0f);

}
