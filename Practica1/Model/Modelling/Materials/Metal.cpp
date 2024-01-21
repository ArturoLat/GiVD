#include "Metal.hh"

Metal::Metal(const vec3& color): Material()
{
    Ks = color;
}


Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}

Metal::~Metal()
{
}

bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 point = rec.p - r_in.getOrigin();
    vec3 target = reflect(point, rec.normal) + (linearRand(0.0f, 1.0f) * Hitable::RandomInSphere());
    r_out =  Ray(rec.p, target);
    color = Ks;
    return true;
}

vec3 Metal::getDiffuse(vec2 uv) const {
    return Ks;
}
