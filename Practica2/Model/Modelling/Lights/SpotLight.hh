#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.hh"

class SpotLight : public Light {
public:
    SpotLight();
    // Parámetros:
    // - pos: posición de la luz.
    // - dir: dirección a la que apunta la luz.
    // - Ia: componente ambiental de la luz.
    // - Id: componente difusa de la luz.
    // - Is: componente especular de la luz.
    // - a: coeficiente de atenuación constante.
    // - b: coeficiente de atenuación lineal.
    // - c: coeficiente de atenuación cuadrático.
    // - angle: ángulo de apertura (en radianes) del cono de luz.
    SpotLight(vec3 Ia, vec3 Id, vec3 Is, vec3 abc, vec4 pos, vec3 dir, float cosAngle);

    virtual ~SpotLight() {}
    vec3 getPos();
    vec3 getDir();
    float getAngle();
    vec3 getCoeficients();

    virtual vec3 vectorL(vec3 point) override;
    virtual float attenuation(vec3 point) override;
    virtual float distanceToLight(vec3 point) override;

    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;
protected:
    vec3 pos;       // posicio de la llum
    vec3 dir;       // dirección hacia la que apunta la luz
    float a;        // atenuación: término constante
    float b;        // atenuación: término lineal
    float c;        // atenuación: término cuadrático
    float cosAngle;  // coseno del ángulo de apertura del cono de luz
};

#endif // SPOTLIGHT_H

