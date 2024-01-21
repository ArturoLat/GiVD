#ifndef GPUOBJECT_H
#define GPUOBJECT_H
#include "Model/Modelling/Objects/Object.hh"
#include "GPUConnections/GPUConnectable.hh"
#include "GPUConnections/GPUMaterial.hh"

class GPUObject: public Object, public GPUConnectable{
public:
    GPUObject();
    ~GPUObject() {};
    void toGPU(shared_ptr<QGLShaderProgram> p) override;






private:
    shared_ptr<GPUMaterial> material;
};

#endif // GPUOBJECT_H
