#include "CellShadow.hh"

float CellShadow::computeShadow(shared_ptr<Scene> scene, shared_ptr<Light> light, vec3 point){
    // Punt iluminat per llum?
    HitInfo info = HitInfo();
    Ray shadowRay(point, light->vectorL(point));
    // He implementat aquest métode (intersect) a la classe Scene.cpp
    //Em permet saber la intersecció del raig amb tots el objecte de l'escena
    HitInfo shadowHit = scene->intersect(shadowRay);
    if(shadowHit.t > 0.0 && shadowHit.t < light->distanceToLight(point)) {
        return 1.0; // hi ha ombra
    }
    else {
        return 0.0; // No si ha ombra
    }

}


vec3 CellShadow::shading(shared_ptr<Scene> scene, HitInfo &info, vec3 lookFrom, vector<shared_ptr<Light>> lights, vec3 globalLight){
    // Cell-Shading ombrejat values
    vec3 ambiental = vec3(0.0f);
    vec3 difosa = vec3(0.0f);
    vec3 costat = vec3(0.0f);

    // Colors del sombrejat
    vec3 sombreado1 = vec3(0.0, 0.0, 0.0);  // luz tenue
    vec3 sombreado2 = vec3(0.3, 0.3, 0.3);  // normal de sombreado
    vec3 sombreado3 = vec3(0.6, 0.6, 0.6);  // sombras marcadas
    vec3 sombreado4 = vec3(0.8, 0.8, 0.8);  // luz fuerte

    // llum ambient
    ambiental = info.mat_ptr->Ka * globalLight;

    for(const shared_ptr<Light> &light: lights){
        // Hi ha ombra?
        if(computeShadow(scene, light, info.p) > 0.0) {
            continue; // Busquemm seguent llum
        }
        // Asigna el vector L
        vec3 L = light->vectorL(info.p);
        // Vector Normal
        vec3 N = info.normal;
        // Angle L / N
        float cos0 = dot(normalize(N), normalize(L));
        // Retorna la atenuación
        float atte = light->attenuation(info.p);
        // Calcula la luz difusa (Escala el valor coseno para reducir el número de niveles)
        difosa += atte * info.mat_ptr->Kd * light->getId() * glm::step(0.5f, static_cast<float>(cos0));
    }

    // Intentem calcular la iluminació dels "bordes"
    costat = vec3(0.2f);

    // Resultat final
    vec3 resultat = ambiental + ((sombreado1 + sombreado2 + sombreado3 + sombreado4) * difosa) + costat;

    return resultat;
}

