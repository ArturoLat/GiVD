#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.hh"

class DirectionalLight : public Light {
public:
    DirectionalLight();
    // Parámetros:
    // - dir: dirección de la luz.
    // - Ia: componente ambiental de la luz.
    // - Id: componente difusa de la luz.
    // - Is: componente especular de la luz.
    DirectionalLight(vec3 Ia, vec3 Id, vec3 Is, vec3 dir);
    virtual ~DirectionalLight() {}
    vec3 getDir();
    virtual vec3 vectorL(vec3 point) override;
    virtual float attenuation(vec3 point) override;
    virtual float distanceToLight(vec3 point) override;

    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;
protected:
    vec3 dir;   // dirección de la luz
};

#endif // DIRECTIONALLIGHT_H
