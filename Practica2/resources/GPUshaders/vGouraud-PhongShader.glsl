#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;

struct Material {
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float shiness;
    float opacity;
};

uniform Material myMaterial;

struct DirLight {
    vec3 Ia;
    vec3 Id;
    vec3 Is;
    vec3 dir;
};

uniform DirLight myDirLights[4];

struct PointLight {
    vec3 Ia;
    vec3 Id;
    vec3 Is;
    vec3 abc;
    vec4 pos;
};

uniform PointLight myPointLights[4];

struct SpotLight {
    vec3 Ia;
    vec3 Id;
    vec3 Is;
    vec3 abc;
    vec4 pos;
    vec3 dir;
    float cosAngle;
};

uniform SpotLight mySpotLights[4];

uniform vec4 obs;
uniform mat4 model_view;
uniform mat4 projection;
uniform vec3 glAmbientLight;

out vec3 color;


void main() {

    vec4 transformedNormal = model_view * vec4(vNormal, 0.0);
    vec4 normal = normalize(transformedNormal);

    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    vec4 L, N, V, R;
    float attenuation, dist, cos;
    N = normalize(normal);

    for (int i = 0; i < 4; i++) {
        V = normalize(obs - vPosition);
        if(myDirLights[i].dir != vec3(0)){
            ambient += myDirLights[i].Ia * myMaterial.Ka;
            L = vec4(normalize(-myDirLights[i].dir), 1.0f);
            cos = dot(L, N);
            R = 2.0f * N * cos - L;
            diffuse += myDirLights[i].Id * myMaterial.Kd * cos;
            specular += myDirLights[i].Is * myMaterial.Ks * pow(max(dot(V, R),0.0f), myMaterial.shiness);
        }else if(mySpotLights[i].dir != vec3(0)){
            ambient += mySpotLights[i].Ia * myMaterial.Ka;
            L = vec4(normalize(-mySpotLights[i].dir), 1.0f);
            cos = dot(L, N);
            R = 2.0f * N * cos - L;
            diffuse += mySpotLights[i].Id * myMaterial.Kd * cos;
            specular += mySpotLights[i].Is * myMaterial.Ks * pow(max(dot(V, R),0.0f), myMaterial.shiness);
        }else{
            ambient += myPointLights[i].Ia * myMaterial.Ka;
            L = normalize(myPointLights[i].pos - vPosition);
            cos = dot(L, N);
            R = 2.0f * N * cos - L;
            diffuse += myPointLights[i].Id * myMaterial.Kd * cos;
            specular += myPointLights[i].Is * myMaterial.Ks * pow(max(dot(V, R),0.0f), myMaterial.shiness);
        }
    }
    color =  (glAmbientLight * myMaterial.Ka) + ambient + diffuse + specular;
    gl_Position = projection * model_view * vPosition;
    gl_Position = gl_Position / gl_Position.w;
}


