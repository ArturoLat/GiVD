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

    vec4 L, N, V, H;
    float attenuation, dist;
    N = normalize(normal);

    for (int i = 0; i < 4; i++) {
        V = normalize(obs - vPosition);
        if(myDirLights[i].dir != vec3(0)){
            ambient += myDirLights[i].Ia * myMaterial.Ka;
            L = vec4(normalize(-myDirLights[i].dir), 1.0f);
            diffuse += myDirLights[i].Id * myMaterial.Kd * max(dot(L, N), 0.0f);
            H = normalize(L+V);
            specular += myDirLights[i].Is * myMaterial.Ks * pow(max(dot(H, N),0.0f), myMaterial.shiness);
        }else if(mySpotLights[i].dir != vec3(0)){
            ambient += mySpotLights[i].Ia * myMaterial.Ka;
            L = vec4(normalize(-mySpotLights[i].dir), 1.0f);
            if(abs(mySpotLights[i].abc.x)<0.001f && abs(mySpotLights[i].abc.y)<0.001f && abs(mySpotLights[i].abc.z)<0.001f ){
                attenuation = 1;
            }else{
                dist = distance(mySpotLights[i].pos, vPosition);
                attenuation = 1.0f/(mySpotLights[i].abc.z*dist*dist + mySpotLights[i].abc.y*dist + mySpotLights[i].abc.x);
            }
            diffuse += (mySpotLights[i].Id * myMaterial.Kd * max(dot(L, N), 0.0f)) * attenuation;
            H = normalize(L+V);
            specular += (mySpotLights[i].Is * myMaterial.Ks * pow(max(dot(H, N),0.0f), myMaterial.shiness)) * attenuation;
        }else{
            ambient += myPointLights[i].Ia * myMaterial.Ka;
            L = normalize(myPointLights[i].pos - vPosition);
            if(abs(myPointLights[i].abc.x)<0.001f && abs(myPointLights[i].abc.y)<0.001f && abs(myPointLights[i].abc.z)<0.001f ){
                attenuation = 1;
            }else{
                dist = distance(myPointLights[i].pos, vPosition);
                attenuation = 1.0f/(myPointLights[i].abc.z*dist*dist + myPointLights[i].abc.y*dist + myPointLights[i].abc.x);
            }
            diffuse += (myPointLights[i].Id * myMaterial.Kd * max(dot(L,N), 0.0f)) * attenuation;
            H = normalize(L+V);
            specular += (myPointLights[i].Is * myMaterial.Ks * pow(max(dot(H, N),0.0f), myMaterial.shiness)) * attenuation;
        }
    }

    //color = glAmbientLight * myMaterial.Ka
    //color = ambient;
    //color = diffuse;
    //color = specular;
    color =  (glAmbientLight * myMaterial.Ka) + ambient + diffuse + specular;
    gl_Position = projection * model_view * vPosition;
    gl_Position = gl_Position / gl_Position.w;
}

