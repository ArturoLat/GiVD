#pragma once

#include "Plane.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Object.hh"
#include "glm/gtx/constants.hpp"


class FittedPlane: public Plane{
public:
    FittedPlane();
    FittedPlane(float data);
    FittedPlane(vec2 max, vec2 min, vec3 point, vec3 normal, float data);
    virtual ~FittedPlane(){}

    virtual bool hit(Ray &r, float tmin, float tmax, HitInfo &info) const override;

    virtual void aplicaTG(shared_ptr<TG> tg) override;


    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 normal;
    vec3 point;
    vec2 pmin;
    vec2 pmax;

private:

};


