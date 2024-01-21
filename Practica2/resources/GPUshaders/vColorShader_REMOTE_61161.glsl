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


void setMaterial()
{
    // Intensidad ambiental
    myMaterial.Ka = vec3(0.1f, 0.02f, 0.02f);

    // Intensidad difusa
    myMaterial.Kd = vec3(1.0f, 0.2f, 0.2f);

    // Intensidad especular
    myMaterial.Ks = vec3(1.0f, 1.0f, 1.0f);

    // Brillo
    myMaterial.shiness = 20.0f;

    // Opacidad
    myMaterial.opacity = 2.0f;
}

void main()
{
    setMaterial();

    gl_Position = projection*model_view*vPosition;
    color = vec4(myMaterial.Ka, 1.0f);

}
