#pragma once

#include "library/Singleton.hh"
#include "GPUConnections/GPULight.hh"
#include "GPUConnections/GPUPointLight.hh"
#include "Model/Modelling/Lights/LightFactory.hh"

#include "GPUConnections/GPUSpotLight.hh"
#include "GPUConnections/GPUDirectionalLight.hh"

class GPULightFactory: public Singleton<GPULightFactory>
{
    // needs to be friend in order to
    // access the private constructor/destructor
    friend class Singleton<GPULightFactory>;
private:
    GPULightFactory() {};
    ~GPULightFactory() {};
public:  

    shared_ptr<GPULight> createLight( LightFactory::LIGHT_TYPES t);
    shared_ptr<GPULight> createLight(vec3 Ia, vec3 Id, vec3 Is, vec3 abc, vec4 posicio, vec3 dir, float angle,  LightFactory::LIGHT_TYPES t);

};
