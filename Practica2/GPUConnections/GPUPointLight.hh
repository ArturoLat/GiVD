#pragma once

#include "GPUConnections/GPULight.hh"
#include "Model/Modelling/Lights/PointLight.hh"

class GPUPointLight: public GPULight, public PointLight {
public:
    GPUPointLight();
    /*
     * Constructor de la classe PointLight.
     * param posicio: posició de la llum.
     * param Ia: component ambient de la llum.
     * param Id: component difosa de la llum.
     * param Is: component especular de la llum.
     * param a: coeficient a de l'atenuacio.
     * param b: coeficient b de l'atenuacio.
     * param c: coeficient c de l'atenuacio.
     * */
    GPUPointLight(vec3 Ia, vec3 Id, vec3 Is, vec3 abc, vec4 pos);
    virtual ~GPUPointLight() {}

    virtual void toGPU(shared_ptr<QGLShaderProgram> p) override;

    virtual vec3 vectorL(vec3 point) override;
    virtual float attenuation(vec3 point) override;
    virtual float distanceToLight(vec3 point) override;
private:

    struct gl_pointLight{
       GLuint glIa;
       GLuint glId;
       GLuint glIs;
       GLuint glABC;
       GLuint glPos;

    };

    gl_pointLight gl_my_pointLights[5];

    //int index;
};

