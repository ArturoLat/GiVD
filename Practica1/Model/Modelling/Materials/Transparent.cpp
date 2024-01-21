#include "Transparent.hh"

Transparent::Transparent(){

}

Transparent::Transparent(const vec3& color): Material(){
    this->Kd = color; // color difús!
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, float k) : Material(a, d, s, k)
{
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, float k,float o) : Material(a, d, s, k, o)
{
    this->refractive_index = o;
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float opac, const vec3& kt, const float nut):
    Material(a, d, s, k, opac, nut, kt){

}

Transparent::~Transparent() {}

// Permet la transparència d'un objecte en l'escena en permetre la reflexió i / o la refracció.
bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& r_out) const
{
    vec3 D = r_in.getDirection();
    vec3 N = rec.normal; // Vector normal de la superfície impactada
    float snell; // Índex de refracció
    if(dot(D, N) > 0){
        // Si la direcció del raig i la normal del material apunten en la mateixa direcció, invertim la direcció de la normal i calculem l'índex de refracció corresponent
        N = -N;
        snell = nut / 1; // Índex de refracció del medi al qual es dirigeix la llum, en aquest cas 1

    }else{
        // Si la direcció del raig i la normal del material apunten en direccions oposades, prenem l'índex de refracció de la superfície
        snell = 1 / nut; // Índex de refracció del material
    }

    vec3 t = refract(D, N, snell); // Càlcul del vector de refracció utilitzant la fórmula de Snell
    if(length(t) >= DBL_EPSILON){
        color = this->kt; // Coeficient de transmissió del material
    }else{
        // Si el vector de refracció és menor que l'epsilon (molt a prop de zero), s'utilitza el vector de reflexió
        t = reflect(D, N);
        color= this->Kd; // Component difús del material
    }

    // Construcció del nou raig de sortida amb un petit offset del punt d'impacte cap a la direcció del vector de refracció
    r_out = Ray(rec.p + 0.01f * t, t);

    // Retorna verdader per indicar que el scattering ha ocorregut
    return true;
}



vec3 Transparent::getDiffuse(vec2 point) const
{
    //Retornem coeficient de difusió
    return Kd;
}

