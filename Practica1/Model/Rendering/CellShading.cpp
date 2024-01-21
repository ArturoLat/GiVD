#include "CellShading.hh"

vec3 CellShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vector<shared_ptr<Light>> lights, vec3 globalLight) {
    // Sombrejat per el Cell-Shading
    vec3 ambiental = vec3(0.0f);
    vec3 difosa = vec3(0.0f);
    vec3 costat = vec3(0.0f);

    // Aqui definim els colors per a cada efecte de llum
    vec3 sombreado1 = vec3(0.0, 0.0, 0.0);  // luz tenue
    vec3 sombreado2 = vec3(0.3, 0.3, 0.3);  // normal de sombreado
    vec3 sombreado3 = vec3(0.6, 0.6, 0.6);  // sombras marcadas
    vec3 sombreado4 = vec3(0.8, 0.8, 0.8);  // uz fuerte

    // llum ambientañ
    ambiental = info.mat_ptr->Ka * globalLight;

    for(const shared_ptr<Light> &light: lights){
        // Asigna el vector L
        vec3 L = light->vectorL(info.p);
        // Vector Normal
        vec3 N = info.normal;
        // Angle entre L i N
        float cos0 = dot(normalize(N), normalize(L));
        // Atenuació de la llum
        float atte = light->attenuation(info.p);
        // llum difusa
        difosa += atte * info.mat_ptr->Kd * light->getId() * glm::step(0.5f, static_cast<float>(cos0));
    }

    // Iluminació dels "bordes" -> Si dona error, pot ser que hagi implementat la logica malament dels costats
    //Pero en principi el resultat es correcte
    costat = vec3(0.2f);


    // Combina los componentes para obtener el resultado final
    vec3 resultat = ambiental + ((sombreado1 + sombreado2 + sombreado3 + sombreado4) * difosa) + costat;

    return resultat;

}
