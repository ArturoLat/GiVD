#include "GPUConnections/GPUMaterial.hh"


GPUMaterial::GPUMaterial(vec3 Ka, vec3 Kd, vec3 Ks, float shiness, float opacity): Material(Ka, Kd, Ks, shiness, opacity){
}

GPUMaterial::GPUMaterial() {
}

void GPUMaterial::toGPU(shared_ptr<QGLShaderProgram> p) {
    qDebug() << "Material toGPU.....";
    program = p;

    gl_my_material.glKa = program->uniformLocation("myMaterial.Ka");
    gl_my_material.glKd = program->uniformLocation("myMaterial.Kd");
    gl_my_material.glKs = program->uniformLocation("myMaterial.Ks");
    gl_my_material.glShiness = program->uniformLocation("myMaterial.shiness");
    gl_my_material.glOpacity = program->uniformLocation("myMaterial.opacity");

    qDebug() << "Material toGPU2.....";

    // Enviar valors a GPU
    glUniform3fv(gl_my_material.glKa, 1, this->getAmbient());
    glUniform3fv(gl_my_material.glKd, 1, this->getDiffuse());
    glUniform3fv(gl_my_material.glKs, 1, this->getSpecular());
    glUniform1f(gl_my_material.glShiness, this->getShininess());
    glUniform1f(gl_my_material.glOpacity, this->getOpacity());
    qDebug() << "Material toGPU3.....";
}

