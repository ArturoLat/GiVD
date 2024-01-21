#pragma once

#include "ShadingStrategy.hh"
#include <math.h>
#include <stdlib.h>
#include "library/mat.h"

class NormalShading: public ShadingStrategy
{
public:
    NormalShading() {};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom) override;
    ~NormalShading(){};
};

