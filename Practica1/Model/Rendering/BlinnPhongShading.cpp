#include "BlinnPhongShading.hh"


vec3 BlinnPhongShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom,vector<shared_ptr<Light>> lights, vec3 globalLight) {
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
        //Angul entre L i N
        float cos0 = dot(normalize(N),normalize(L));
        //Calcul atenuacio
        float atte = light->attenuation(info.p);
        //Calcul difosa (EL max asegura que sigui sempre major a 0)
        difosa += atte * info.mat_ptr->Kd * light->getId() * glm::max(cos0, 0.0f);
        //Calcul Specular
        //Calcul del vector del observador
        vec3 V = lookFrom - info.p;
        //Calcul del vector mig
        vec3 H = normalize(V + L);
        //Calcul specular
        specular += atte * info.mat_ptr->Ks * light->getIs() * pow(dot(N, H), info.mat_ptr->shininess);
    }
    //Si volem que sigui solament ambiental, hem de eliminar la attenuacio en el for en cada calculS
    //return ambiental; //Solament ambiental
    //return difosa; //Solament difosa
    //return specular; //Solament specular
    //return ambiental+difosa+specular; //Conjuntament
    return ambiental+difosa+specular+global; //Amb el global
}
