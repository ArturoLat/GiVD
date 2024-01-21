#pragma once

#include "GPUConnections/GPUConnectable.hh"
#include "Model/Modelling/Materials/Material.hh"

using namespace std;

class GPUMaterial: public Material, public GPUConnectable {

public:
    GPUMaterial(vec3 Ka, vec3 Kd, vec3 Ks, float shiness, float opacity);
    GPUMaterial();
    ~GPUMaterial() {};

    void toGPU(shared_ptr<QGLShaderProgram> p);

private:
    struct gl_materials{
       GLuint glKa;
       GLuint glKd;
       GLuint glKs;
       GLuint glShiness;
       GLuint glOpacity;
    };
    gl_materials gl_my_material;
};
