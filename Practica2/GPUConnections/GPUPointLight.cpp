#include "GPUConnections/GPUPointLight.hh"

GPUPointLight::GPUPointLight(vec3 Ia, vec3 Id, vec3 Is, vec3 abc, vec4 pos): PointLight(Ia, Id, Is, abc, pos) {

}

GPUPointLight::GPUPointLight() {
    PointLight::Ia = vec3(0.2);
    PointLight::Id = vec3 (0.8);
    PointLight::Is = vec3(1);
    PointLight::a = 0.5;
    PointLight::b = 0.0;
    PointLight::c = 0.01;
    PointLight::pos = vec3 (10,10,20);
}

void GPUPointLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    qDebug() << "PointLights toGPU.....";
    program = p;
    int index;

    //index = PointLight::getIndex();
    index = 0;

    // Obtenir ubis de les variables del Shader
    gl_my_pointLights[index].glIa = program->uniformLocation(QString("myPointLights[%1].Ia").arg(index));
    gl_my_pointLights[index].glId = program->uniformLocation(QString("myPointLights[%1].Id").arg(index));
    gl_my_pointLights[index].glIs = program->uniformLocation(QString("myPointLights[%1].Is").arg(index));
    gl_my_pointLights[index].glABC = program->uniformLocation(QString("myPointLights[%1].abc").arg(index));
    gl_my_pointLights[index].glPos = program->uniformLocation(QString("myPointLights[%1].pos").arg(index));

    qDebug() << "PointLights toGPU2.....";
    QTextStream(stdout) << "\n\n\n\n" << PointLight::getIa() << "\n\n\n\n";

    // Enviar valors a GPU
    glUniform3fv(gl_my_pointLights[index].glIa, 1, this->PointLight::getIa());
    glUniform3fv(gl_my_pointLights[index].glId, 1, this->PointLight::getId());
    glUniform3fv(gl_my_pointLights[index].glIs, 1, this->PointLight::getIs());
    glUniform3fv(gl_my_pointLights[index].glABC, 1, this->PointLight::getCoeficients());
    glUniform4fv(gl_my_pointLights[index].glPos, 1, this->PointLight::getPos());


    qDebug() << "PointLights toGPU3.....";
}

vec3 GPUPointLight::vectorL(vec3 point) {
    return PointLight::vectorL(point);
}

float GPUPointLight::attenuation(vec3 point) {
    return PointLight::attenuation(point);
}

float GPUPointLight::distanceToLight(vec3 point) {
    return PointLight::distanceToLight(point);
}
