#pragma once

#include "ShadingStrategy.hh"
#include "Model/Modelling/Lights/Light.hh"
#include "math.h"

class BlinnPhongShading: public ShadingStrategy
{
public:
    BlinnPhongShading() {};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vector<shared_ptr<Light>> lights, vec3 globalLight) override;
    ~BlinnPhongShading(){};
};

