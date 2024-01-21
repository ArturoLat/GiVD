#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;

uniform mat4 model_view;
uniform mat4 projection;
uniform vec3 glAmbientLight;


struct Light{
    vec3 Ia; //Intensitat ambiental
    vec3 Id; // Intensitat difusa
    vec3 Is; // Intensitat especular
    vec3 pos; // Posició (en el cas de llum puntual)
    vec3 dir; // Direcció (en el cas de llum direccional o llum tipo spot)
    // Coeficients d'atenuació
    float a;
    float b;
    float c;
    float cosAngle; // Coseno del ángulo de apertura, en el caso de luz tipo spot
};

uniform Light myLights[4]; // 4 represneta el nombre de llums que volem, es arbitraria
struct Material{
    vec3 Ka; //Intensitat ambiental
    vec3 Kd; // Intensitat difusa
    vec3 Ks; // Intensitat especular
    float shiness; // Posició (en el cas de llum puntual)
    float opacity; // Direcció (en el cas de llum direccional o llum tipo spot)

};

uniform Material myMaterial;


void main(void)
{

}
