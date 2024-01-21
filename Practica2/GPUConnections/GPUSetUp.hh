#pragma once


#include "GPUConnections/GPULightFactory.hh"
#include "GPUConnections/GPUCamera.hh"
#include "Model/Rendering/SetUp.hh"

#include "GPULight.hh"

using namespace std;

class GPUSetUp : public SetUp
{
public:
    GPUSetUp();

    shared_ptr<GPUCamera>             getCamera();
    std::vector<shared_ptr<GPULight>> getLights();
    vec3                              getGlobalLight();


    void setCamera(shared_ptr<GPUCamera> cam);
    void setGlobalLight(vec3 globalLight);
    void setLights(std::vector<shared_ptr<GPULight> > lights);

    virtual void read (const QJsonObject &json) override;
    virtual void write (QJsonObject &json) const override;
    virtual void print (int indentation) const override;

    virtual ~GPUSetUp() {};


    // TODO Pràctica 2: FASE 1: Enviar les llums a la GPU

    // He fet els métodes publics, per tal de poder utilitzarlos com vulgui (N6)
    void lightsToGPU(shared_ptr<QGLShaderProgram> program);
    void setAmbientGlobalToGPU(shared_ptr<QGLShaderProgram> program);

    shared_ptr<GPULight> getLightActual();
    void setLightActual(shared_ptr<GPULight> l);
    void addLight(shared_ptr<GPULight> l);
    std::vector<shared_ptr<GPULight>> lights;

private:

    // Camera
    shared_ptr<GPUCamera> camera;

    // My global variables (N6)
    GLuint aL; //ambient light, recorda que esta definida a vshader.gls com glAmbientLight

    // Vector de llums de l'escena




    // Llum global
    vec3 globalLight;


};

