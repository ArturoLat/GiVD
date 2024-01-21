#include "PhongShading.hh"


vec3 PhongShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vector<shared_ptr<Light>> lights, vec3 globalLight) {
    vec3 ambiental= vec3(0.0f);
    vec3 difosa= vec3(0.0f);
    vec3 specular = vec3(0.0f);

    vec3 global = info.mat_ptr->Ka * globalLight;

    for(const shared_ptr<Light> &light: lights){
        //Calcul ambiental
        ambiental = info.mat_ptr->Ka * light->getIa();
        //Asignem el vector L
        vec3 L = light->vectorL(info.p);
        //Vector Normal
        vec3 N = info.normal;
        //Calcul atenuacio
        float atte = light->attenuation(info.p);
        //Angul entre L i N
        float cos0 = dot(normalize(N),normalize(L));
        //Calcul difosa
        difosa += atte * info.mat_ptr->Kd * light->getId() * glm::max(cos0, 0.0f);
        //Calcul specular
        //Vector del observador
        vec3 V = lookFrom - info.p;
        //Calculem el raig reflectit amb el incident (L) i la normal (N)
        vec3 R = 2.0f * N * dot(L, N) - L;
        specular += atte * info.mat_ptr->Ks * light->getIs() * pow(dot(normalize(R), normalize(V)), info.mat_ptr->shininess);;

    }
    //return ambiental; //Solament ambiental
    //return difosa; //Solament difosa
    //return specular; //Solament specular
    return ambiental+difosa+specular; //Conjuntament
}
