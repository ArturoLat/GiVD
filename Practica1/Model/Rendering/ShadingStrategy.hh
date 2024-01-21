#pragma once

#include "Model/Modelling/Scene.hh"
#include "Model/Modelling/Lights/Light.hh"


class ShadingStrategy {
 public:
    // TODO: Fase 2: Canviar el mètode per passar les llums per calcular el shading
    virtual vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom,vector<shared_ptr<Light>> lights, vec3 globalLight) {
        return vec3(0.0, 0.0, 0.0);
    };

    // FASE 2: Calcula si el punt "point" és a l'ombra segons si el flag està activat o no
    virtual float computeShadow(shared_ptr<Scene> scene, shared_ptr<Light> light, vec3 point){
        return 0.0f;
    };

    virtual ~ShadingStrategy() {};
};
