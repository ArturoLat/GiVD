#include "GPUDirectionalLight.hh"

GPUDirectionalLight::GPUDirectionalLight(vec3 Ia, vec3 Id, vec3 Is, vec3 dir) :
    DirectionalLight(Ia, Id, Is, dir)
{

}

GPUDirectionalLight::GPUDirectionalLight() {
    /*
    DirectionalLight::Ia = vec3(0.2);
    DirectionalLight::Id = vec3 (0.8);
    DirectionalLight::Is = vec3(1);
    DirectionalLight::dir = vec3(1);
    */
}

void GPUDirectionalLight::toGPU(shared_ptr<QGLShaderProgram> p) {
    qDebug() << "DirLights toGPU.....";
    program = p;
    int index;

    //index = DirectionalLight::getIndex();
    index = 0;



    // Obtenir ubis de les variables del Shader
    gl_my_dirLights[index].glIa = program->uniformLocation(QString("myDirLights[%1].Ia").arg(index));
    gl_my_dirLights[index].glId = program->uniformLocation(QString("myDirLights[%1].Id").arg(index));
    gl_my_dirLights[index].glIs = program->uniformLocation(QString("myDirLights[%1].Is").arg(index));
    gl_my_dirLights[index].glDir = program->uniformLocation(QString("myDirLights[%1].dir").arg(index));

    qDebug() << "DirLights toGPU2.....";

    // Enviar valors a GPU
    glUniform3fv(gl_my_dirLights[index].glIa, 1, this->DirectionalLight::getIa());
    glUniform3fv(gl_my_dirLights[index].glId, 1, this->DirectionalLight::getId());
    glUniform3fv(gl_my_dirLights[index].glIs, 1, this->DirectionalLight::getIs());
    glUniform3fv(gl_my_dirLights[index].glDir, 1, this->DirectionalLight::getDir());

    qDebug() << "Light toGPU3.....";
}

// La direcció de la llum no influeix en el vector L
vec3 GPUDirectionalLight::vectorL(vec3 point) {
    return normalize(getDir());
}

// La llum direccional no té atenuació
float GPUDirectionalLight::attenuation(vec3 point) {
    return 1.0;
}

float GPUDirectionalLight::distanceToLight(vec3 point) {
    return 1.0e+38; // Valor suficientment alt per considerar que la llum és a l'infinit
}
