#include "GPUConnections/GPULightFactory.hh"


//! createLight

// TODO: Pràctica 2: Fase 1: Incloure els diferents tipus de llum
shared_ptr<GPULight> GPULightFactory::createLight( LightFactory::LIGHT_TYPES t) {
    shared_ptr<GPULight> l;
    switch(t) {
    case LightFactory::LIGHT_TYPES::POINTLIGHT:
        l = make_shared<GPUPointLight>();
        break;
    case LightFactory::LIGHT_TYPES::DIRECTIONALLIGHT:
        l = make_shared<GPUDirectionalLight>();
        break;

    case LightFactory::LIGHT_TYPES::SPOTLIGHT:
        l = make_shared<GPUSpotLight>();
        break;

    default:
        break;
    }
    return l;
}
shared_ptr<GPULight> GPULightFactory::createLight(vec3 Ia, vec3 Id, vec3 Is, vec3 abc, vec4 posicio, vec3 dir, float angle, LightFactory::LIGHT_TYPES t) {
    shared_ptr<GPULight> l;
    switch(t) {
    case LightFactory::LIGHT_TYPES::POINTLIGHT:
        l = make_shared<GPUPointLight>(Ia, Id, Is, abc, posicio);
        break;

    case LightFactory::LIGHT_TYPES::DIRECTIONALLIGHT:
        l = make_shared<GPUDirectionalLight>(Ia, Id, Is, dir);
        break;

    case LightFactory::LIGHT_TYPES::SPOTLIGHT:
        l = make_shared<GPUSpotLight>(Ia, Id, Is, abc, posicio, dir, angle);
        break;

    default:
        break;
    }
    return l;
}
