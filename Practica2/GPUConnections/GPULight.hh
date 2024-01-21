#pragma once

#include "GPUConnections/GPUConnectable.hh"
#include "Model/Modelling/Lights/Light.hh"

using namespace std;

class GPULight: public Light, public GPUConnectable {

public:
    //My atributes (N6) (i si, ha de ser un struct perque ho demanen)
    /*
    struct gl_lights{
       GLuint glIa;
       GLuint glId;
       GLuint glIs;
       GLuint glPos; //recorda que es vec4
       GLuint glDir;
       GLuint glABC;
       GLuint glCosAngle; //coseno

    };

    gl_lights gl_my_lights[7];
    */



public:
    /*
     * Constructor de la classe Light.
     * param Ia: component ambient de la llum.
     * param Id: component difosa de la llum.
     * param Is: component especular de la llum.
     * */
    GPULight(vec3 Ia, vec3 Id, vec3 Is);
    GPULight();
    virtual ~GPULight() {};

    //Calcula el factor d'atenuacio de la llum al punt passat per parametre
    virtual float attenuation(vec3 point) override = 0;
    //Calcula el vector L amb origen el punt passat per parametre
    virtual vec3 vectorL(vec3 point) override = 0;
    //Calcula la distancia del punt a la llum
    virtual float distanceToLight(vec3 point) override = 0;

    virtual void toGPU(shared_ptr<QGLShaderProgram> p) override = 0;

    /*
    //Aquest getter em retorna la struct que conté les dades de les meves llums
    struct gl_lights get_gl_my_lights(size_t idx){
        return this->gl_my_lights[idx];
    }*/
};


