#include "GPULight.hh"


GPULight::GPULight(vec3 Ia, vec3 Id, vec3 Is): Light(Ia, Id, Is){
}

GPULight::GPULight() {
}


void GPULight::toGPU(shared_ptr<QGLShaderProgram> p) {
    // TO DO Pràctica 2: Fase 1: enviar les propietats de Ia, Id i Is a la GPU
}



/*
 *     //N6
    // Obtenir ubis de les variables del Shader
    gl_my_lights.glIa = program->uniformLocation("myLights.Ia");
    gl_my_lights.glId = program->uniformLocation("myLights.Id");
    gl_my_lights.glIs = program->uniformLocation("myLights.Is");
    gl_my_lights.glPos = program->uniformLocation("myLights.pos");
    gl_my_lights.glDir = program->uniformLocation("myLights.dir");
    gl_my_lights.glABC = program->uniformLocation("myLights.abc");
    gl_my_lights.glCosAngle = program->uniformLocation("myLights.cosAngle");

    qDebug() << "Lights toGPU2.....";


    // * Valors hadcoded per si vols testeig
    // *
    vec3 vectorIa(0.1f, 0.1f, 0.1f);
    vec3 vectorId(1.0f, 1.0f, 1.0f);
    vec3 vectorIs(0.8f, 0.8f, 0.8f);

    vec3 vectorPos(10, 5, 0); // només es una posició per la llum puntual
    vec3 vectorDireccio(-0.5f, -0.2f, -0.8f);

    //coeficients atenuació
    float a = 0.2f; //coeficient lineal
    float b = 0.3f; // coeficient cuadratic
    float c = 0.5f; //coeficient constant

    //Coseno apertura
    const GLfloat angle_radians = 1.0472f; // 60 graus
    const GLfloat cos_angulo_apertura = cos(angle_radians / 2.0f);

    float cosAngle = cos_angulo_apertura;




    // Enviar valors a GPU
    glUniform3fv(gl_my_lights.glIa, 1, this->getIa());
    glUniform3fv(gl_my_lights.glId, 1, this->getId());
    glUniform3fv(gl_my_lights.glIs, 1, this->getIs());

    glUniform4fv(gl_my_lights.glPos, 1, this->getLightPosition());
    glUniform3fv(gl_my_lights.glDir, 1, this->getDirLight());

    glUniform3fv(gl_my_lights.glABC, 1, this->getCoeficients());

    glUniform1f(gl_my_lights.glCosAngle, this->getCosAngle());

    qDebug() << "Light toGPU3.....";
 */
