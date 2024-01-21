#include "NormalShading.hh"


vec3 NormalShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vector<shared_ptr<Light>> lights, vec3 globalLight) {
    return (info.normal + 1.0f) / 2.0f;
}
