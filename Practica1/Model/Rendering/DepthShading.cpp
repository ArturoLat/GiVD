#include "DepthShading.hh"


vec3 DepthShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vector<shared_ptr<Light>> lights, vec3 globalLight) {
    return ((distance(info.p, lookFrom)/5.0f) * vec3(1.f,1.f,1.f));
}
