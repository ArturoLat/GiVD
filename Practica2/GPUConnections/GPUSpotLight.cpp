#include "GPUSpotLight.hh"

GPUSpotLight::GPUSpotLight(vec3 Ia, vec3 Id, vec3 Is, vec3 abc, vec4 pos, vec3 dir, float angle) :
    SpotLight(Ia, Id, Is, abc, pos, dir, angle)
{

}

GPUSpotLight::GPUSpotLight() {
    /*
    SpotLight::Ia = vec3(0.2);
    SpotLight::Id = vec3 (0.8);
    SpotLight::Is = vec3(1);
    SpotLight::a = 0.5;
    SpotLight::b = 0.0;
    SpotLight::c = 0.01;
    SpotLight::pos = vec3 (10,10,20);
    SpotLight::dir = vec3(5);
    SpotLight::cosAngle = 30;
    */
}

void GPUSpotLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    qDebug() << "SpotLights toGPU.....";
    program = p;


    //Hola! Això em permet agafar el termet i-essim, agafo getter i setter de la classe Light!
    int index;

    //index = SpotLight::getIndex();
    index = 0;

    // Obtenir ubis de les variables del Shader
    gl_my_spotLights[index].glIa = program->uniformLocation(QString("mySpotLights[%1].Ia").arg(index));
    gl_my_spotLights[index].glId = program->uniformLocation(QString("mySpotLights[%1].Id").arg(index));
    gl_my_spotLights[index].glIs = program->uniformLocation(QString("mySpotLights[%1].Is").arg(index));
    gl_my_spotLights[index].glABC = program->uniformLocation(QString("mySpotLights[%1].abc").arg(index));
    gl_my_spotLights[index].glPos = program->uniformLocation(QString("mySpotLights[%1].pos").arg(index));
    gl_my_spotLights[index].glDir = program->uniformLocation(QString("mySpotLights[%1].dir").arg(index));
    gl_my_spotLights[index].glCosAngle = program->uniformLocation(QString("mySpotLights[%1].cosAngle").arg(index));


    qDebug() << "SpotLights toGPU2.....";

    // Enviar valors a GPU
    glUniform3fv(gl_my_spotLights[index].glIa, 1, this->SpotLight::getIa());
    glUniform3fv(gl_my_spotLights[index].glId, 1, this->SpotLight::getId());
    glUniform3fv(gl_my_spotLights[index].glIs, 1, this->SpotLight::getIs());
    glUniform3fv(gl_my_spotLights[index].glABC, 1, this->SpotLight::getCoeficients());
    glUniform4fv(gl_my_spotLights[index].glPos, 1, this->SpotLight::getPos());
    glUniform3fv(gl_my_spotLights[index].glDir, 1, this->SpotLight::getDir());
    glUniform1f(gl_my_spotLights[index].glCosAngle, this->SpotLight::getAngle());

    qDebug() << "SpotLights toGPU3.....";
}

vec3 GPUSpotLight::vectorL(vec3 point) {
    return SpotLight::vectorL(point);
}

float GPUSpotLight::attenuation(vec3 point) {
    return SpotLight::attenuation(point);
}

float GPUSpotLight::distanceToLight(vec3 point) {
    return SpotLight::distanceToLight(point);
}
