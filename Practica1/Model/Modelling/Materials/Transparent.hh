#pragma once
#include "Material.hh"

class Transparent : public Material
{
public:
    Transparent();
    Transparent(const vec3& color);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float ri);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float opac, const vec3& kt, const float nut);
    virtual ~Transparent();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& r_out) const;
    virtual vec3 getDiffuse(vec2 point) const;

private:
    //Aquest atribut l'afegim nosaltres, encara que es similar al KT de Material no es igual.
    //Fa referencia a com es "dobla" la llum al ATRAVESSAR un material (Transparent).
    float refractive_index;
};
