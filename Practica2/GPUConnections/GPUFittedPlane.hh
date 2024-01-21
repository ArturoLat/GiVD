#pragma once

#include <library/Common.h>
using namespace Common;

#include <QOpenGLTexture>

#include "GPUConnections/GPUConnectable.hh"
#include "Model/Modelling/Objects/FittedPlane.hh"
#include "GPUConnections/GPUMaterial.hh"
#include "GPUConnections/GPUObject.hh"

class GPUFittedPlane : public FittedPlane, public GPUConnectable, public QObject
{
public:
    GPUFittedPlane();
    GPUFittedPlane(const QString &fileName);

    ~GPUFittedPlane();

    virtual void toGPU(shared_ptr<QGLShaderProgram> p) override;
    virtual void draw() override;

    void read(const QJsonObject &json) override;

private:
    // Estructures per passar a la GPU
    void make();

};
