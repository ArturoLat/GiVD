#ifndef MATERIALTEXTURA_HH
#define MATERIALTEXTURA_HH

#include "Texture.hh"
#include "Material.hh"

class MaterialTextura : public Material{
public:
    MaterialTextura();
    MaterialTextura(vec3 ka, vec3 kd, vec3 ks, float sh, float o);
    virtual ~MaterialTextura();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
    virtual vec3 getDiffuse(vec2 uv) const;

    Texture *texture;
};

#endif // MATERIALTEXTURA_HH
