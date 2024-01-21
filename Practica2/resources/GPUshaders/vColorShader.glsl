#version 330

layout (location = 0) in vec4 vPosition;

uniform mat4 model_view;
uniform mat4 projection;


struct DirLight{
    vec3 Ia; //Intensitat ambiental
    vec3 Id; // Intensitat difusa
    vec3 Is; // Intensitat especular
    vec3 dir; //dir
};

uniform DirLight myDirLights[4]; // num de llums q vull

struct PointLight{
    vec3 Ia; //Intensitat ambiental
    vec3 Id; // Intensitat difusa
    vec3 Is; // Intensitat especular
    vec3 abc;
    vec4 pos; // Posició (en el cas de llum puntual)

};

uniform PointLight myPointLights[4]; //num de llums q vull

struct SpotLight{
    vec3 Ia; //Intensitat ambiental
    vec3 Id; // Intensitat difusa
    vec3 Is; // Intensitat especular
    // Coeficients d'atenuació
    vec3 abc;
    vec4 pos; // Posició (en el cas de llum puntual)
    vec3 dir; // Direcció (en el cas de llum direccional o llum tipo spot)
    float cosAngle; // Coseno del ángulo de apertura, en el caso de luz tipo spot
};

uniform SpotLight mySpotLights[4]; //num de llums q vull

struct Material{
    vec3 Ka; //Intensitat ambiental
    vec3 Kd; // Intensitat difusa
    vec3 Ks; // Intensitat especular
    float shiness; // Posició (en el cas de llum puntual)
    float opacity; // Direcció (en el cas de llum direccional o llum tipo spot)

};
uniform Material myMaterial;

out vec4 color;

uniform vec3 glAmbientLight;

void main()
{

    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;


    //color = vec4(glAmbientLight, 1.0f);
    //color = vec4(myMaterial.Ka, 1.0f);
    color = vec4(myMaterial.Kd, 1.0f);
    //color = vec4(myMaterial.Ks, 1.0f);

}
