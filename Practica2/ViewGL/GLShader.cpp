#include "GLShader.hh"

GLShader::GLShader(const char* vShaderFile, const char* fShaderFile, shared_ptr<QGLShaderProgram> &program){
    QGLShader *vshader = new QGLShader(QGLShader::Vertex);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment);

    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    program = std::make_shared<QGLShaderProgram>();
    program->addShader(vshader);
    program->addShader(fshader);
}

//Metode per activar un shader
void GLShader::activateShader(shared_ptr<QGLShaderProgram> p){
    p->link();
    p->bind();

;}

//Metode per activar shaders de textures
void GLShader::activateShaderTexture(){
    //TO DO: Pràctica 2:  implementar a la fase 1
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
}
