#include "BlinnPhongShadow.hh"

float BlinnPhongShadow::computeShadow(shared_ptr<Scene> scene, shared_ptr<Light> light, vec3 point){
    float result = 0.01f;
    HitInfo info = HitInfo();
    vec3 L = normalize(light->vectorL(point)); //creamos el vector del punto a la luz.
    Ray ray_hit = Ray(point + result * L, L); //creamos un rayo facha que empieza en el punto y va hacia la luz. S'afegeix el 0.01f per el shadow acne
    float distanceLight = light->distanceToLight(point);
    if(scene->hit(ray_hit, 0.0001, distanceLight, info)){//comprobamos si el rayo intercepta algún objeto, y en caso de que sí lo haga entonces devuelve true y por tanto el valor es de 0.
        return 0.0f;
    }
    return 1.0f; //sino es de 1
}

vec3 BlinnPhongShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom,vector<shared_ptr<Light>> lights, vec3 globalLight) {
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
        float factorOmbra = computeShadow(scene, light, info.p);
        //Calcul difosa (EL max asegura que sigui sempre major a 0)
        difosa += factorOmbra * atte * info.mat_ptr->Kd * light->getId() * glm::max(cos0, 0.0f);
        //Calcul Specular
        //Calcul del vector del observador
        vec3 V = lookFrom - info.p;
        //Calcul del vector mig
        vec3 H = normalize(V + L);
        //Calcul specular
        specular += factorOmbra * atte * info.mat_ptr->Ks * light->getIs() * pow(dot(N, H), info.mat_ptr->shininess);

    }
    //Si volem que sigui solament ambiental, hem de eliminar la attenuacio en el for en cada calcul
    //return ambiental; //Solament ambiental
    //return difosa; //Solament difosa
    //return specular; //Solament specular
    //return ambiental+difosa+specular; //Conjuntament
    return ambiental+difosa+specular+global; //Amb el global
}
