#include "ViewGL/GLWidget.hh"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

    setFocusPolicy( Qt::StrongFocus );

}

GLWidget::GLWidget(const QGLFormat &glf, QWidget *parent) : QGLWidget(glf, parent) {

    setFocusPolicy( Qt::StrongFocus );
    auto cameraGPU = make_shared<GPUCamera>(this->size().width(), this->size().height());
    Controller::getInstance()->getSetUp()->setCamera(cameraGPU);
}

GLWidget::~GLWidget() {

}

/* Interacció amb GL i inicialització dels programes a la GPU */

/**
 * @brief GLWidget::initializeGL()
 */
void GLWidget::initializeGL() {

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RGBA);
    glEnable(GL_DOUBLE);

    initShadersGPU();

    // Creacio d'una Light per a poder modificar el seus valors amb la interficie
    // TO DO: Pràctica 2: Fase 1:  Canviar per a que siguin GPULigths i usar la factory GPULightFactory que facis nova

    // Hola! myGPUSetUp i program, son atributs definits en la classe GLWidget.hh, useulos per cridar a tots els metodes de la classe GPUSetUP (N6)

    this->myGPUSetUp.setAmbientGlobalToGPU(this->program[pasarShader]);

    //llum puntual
    auto pointLight  = GPULightFactory::getInstance().createLight(LightFactory::POINTLIGHT);
    Controller::getInstance()->getSetUp()->lights.push_back(pointLight);

    //llum direccional
    auto directionalLight  = GPULightFactory::getInstance().createLight(LightFactory::DIRECTIONALLIGHT);
    Controller::getInstance()->getSetUp()->lights.push_back(directionalLight);

    //llum SpotLight
    auto spotLight  = GPULightFactory::getInstance().createLight(LightFactory::SPOTLIGHT);
    Controller::getInstance()->getSetUp()->lights.push_back(spotLight);

    Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
    Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);

    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();
    auto scene = Controller::getInstance()->getScene();

    camera->init(this->size().width(), this->size().height(), scene->capsaMinima);
    emit ObsCameraChanged(camera);
    emit FrustumCameraChanged(camera);

    glViewport(camera->vp.pmin[0], camera->vp.pmin[1], camera->vp.a, camera->vp.h);

}

/**
 * @brief GLWidget::paintGL()
 */
void GLWidget::paintGL() {

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();
    auto scene = Controller::getInstance()->getScene();

    camera->toGPU(program[pasarShader]);
    scene->draw();
}

/**
 * @brief GLWidget::resizeGL()
 */
void GLWidget::resizeGL(int width, int height) {


    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    camera->vp.a = width;
    camera->vp.h = height;
    auto scene = Controller::getInstance()->getScene();
    camera->CalculaWindow(scene->capsaMinima);
    glViewport(camera->vp.pmin[0], camera->vp.pmin[1], camera->vp.a, camera->vp.h);
    emit FrustumCameraChanged(camera);
    updateGL();
}

/**
 * @brief GLWidget::initShadersGPU
 */
void GLWidget::initShadersGPU(){
    GLShader *glshader0 = new GLShader("://resources/GPUshaders/vFortniteStorm.glsl", "://resources/GPUshaders/fFortniteStorm.glsl", program[0]);
    GLShader *glshader1 = new GLShader("://resources/GPUshaders/vColorShader.glsl", "://resources/GPUshaders/fColorShader.glsl", program[1]);
    GLShader *glshader2 = new GLShader("://resources/GPUshaders/vDepthShader.glsl", "://resources/GPUshaders/fDepthShader.glsl", program[2]);
    GLShader *glshader3 = new GLShader("://resources/GPUshaders/vNormalShader.glsl", "://resources/GPUshaders/fNormalShader.glsl", program[3]);
    GLShader *glshader4 = new GLShader("://resources/GPUshaders/vGouraud-PhongShader.glsl", "://resources/GPUshaders/fGouraud-PhongShader.glsl", program[4]);
    GLShader *glshader5 = new GLShader("://resources/GPUshaders/vPhong-PhongShader.glsl", "://resources/GPUshaders/fPhong-PhongShader.glsl", program[5]);
    GLShader *glshader6 = new GLShader("://resources/GPUshaders/vGouraud-Blinn-PhongShader.glsl", "://resources/GPUshaders/fGouraud-Blinn-PhongShader.glsl", program[6]);
    GLShader *glshader7 = new GLShader("://resources/GPUshaders/vPhong-Blinn-PhongShader.glsl", "://resources/GPUshaders/fPhong-Blinn-PhongShader.glsl", program[7]);
    GLShader *glshader8 = new GLShader("://resources/GPUshaders/vCellShader.glsl", "://resources/GPUshaders/fCellShader.glsl", program[8]);

    if(glshader0 != nullptr && glshader1 != nullptr && glshader2 != nullptr && glshader3 != nullptr && glshader4 != nullptr && glshader5 != nullptr && glshader6 != nullptr && glshader7 != nullptr && glshader8 != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
    }
}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(400, 400);
}

/** Gestio de les animacions i la gravació d'imatges ***/

void GLWidget::setCurrentFrame(){

    auto scene = Controller::getInstance()->getScene();
    scene->update(currentFrame);
    updateGL();
    this->saveFrame();
    currentFrame++;

    if (currentFrame == MAXFRAMES)
        timer->stop();

}

void GLWidget::saveFrame(){
    this->grabFrameBuffer().save("screen_output_"+QVariant(currentFrame).toString()+".jpg");
}

void GLWidget::saveImage(){
    this->grabFrameBuffer().save("screen_output_"+QVariant(currentImage).toString()+".jpg");
    currentImage++;
}



/** Metodes SLOTS que serveixen al builder per a actualitzar l'escena i els objectes */
void GLWidget::updateObject(shared_ptr<GPUMesh> obj) {

    obj->toGPU(program[pasarShader]);
    //llamar a toGPU de GPUObject
    updateGL();
}

void GLWidget::updateScene() {
    // Control de la nova escena a la GPU
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program[pasarShader]);
    Controller::getInstance()->setScene(sc);
    // Podeu utilitzar l'altre constructor de Camera per inicialitzar els
    // parametres de la camera.
    auto camera = make_shared<GPUCamera>(this->size().width(), this->size().height());
    Controller::getInstance()->getSetUp()->setCamera(camera);

    camera->actualitzaCamera(sc->capsaMinima);

    emit ObsCameraChanged(camera);
    emit FrustumCameraChanged(camera);

    updateGL();

}

/** Metodes que es criden des dels menús */

void GLWidget::saveAnimation() {
    // Comença el timer de l'animació
    timer = new QTimer(this);
    currentFrame=0;
    currentImage=0;
    connect(timer, SIGNAL(timeout()), this, SLOT(setCurrentFrame()));
    timer->start(1000);

}

void GLWidget::activaFortniteShader() {
    //TO DO: Pràctica 2: A implementar a la fase 1
    this->pasarShader = 0;
    if(program[pasarShader] != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
        Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
        Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);
        updateScene();
    }
    qDebug()<<"Estic a Fortnite Shader";
}

void GLWidget::activaColorShader() {
    //TO DO: Pràctica 2: A implementar a la fase 1
    this->pasarShader = 1;
    if(program[pasarShader] != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
        Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
        Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);
        updateScene();
    }
    qDebug()<<"Estic a Color Shader";
}

void GLWidget::activaDepthShader() {
    //TO DO: Pràctica 2: A implementar a la fase 1
    this->pasarShader = 2;
    if(program[pasarShader] != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
        Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
        Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);
        updateScene();
    }
    qDebug()<<"Estic a Depth Shader";
}

void GLWidget::activaNormalShader() {
    //TO DO: Pràctica 2: A implementar a la fase 1
    this->pasarShader = 3;
    if(program[pasarShader] != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
        Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
        Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);
        updateScene();
    }
    qDebug()<<"Estic a Normal Shader";
}

void GLWidget::activaGouraudShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    this->pasarShader = 4;
    if(program[pasarShader] != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
        Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
        Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);
        updateScene();
    }
    qDebug()<<"Estic a Gouraud - Phong shader";

}
void GLWidget::activaPhongShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    qDebug()<<"Estic a Phong - Phong Shader";

    this->pasarShader = 5;
    if(program[pasarShader] != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
        Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
        Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);
        updateScene();
    }
}

void GLWidget::activaGouraudBlinnShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    qDebug()<<"Estic a Gouraud - Blinn-Phong shader";

    this->pasarShader = 6;
    if(program[pasarShader] != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
        Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
        Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);
        updateScene();
    }
}
void GLWidget::activaBlinnPhongShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    qDebug()<<"Estic a Phong - Blinn-Phong Shader";

    this->pasarShader = 7;
    if(program[pasarShader] != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
        Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
        Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);
        updateScene();
    }
}

void GLWidget::activaToonShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    qDebug()<<"Estic a Toon";
    this->pasarShader = 8;
    if(program[pasarShader] != nullptr){
        program[pasarShader]->link();
        program[pasarShader]->bind();
        Controller::getInstance()->getSetUp()->lightsToGPU(program[pasarShader]);
        Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(this->program[pasarShader]);
        updateScene();
    }
}


void GLWidget::activaReflection() {
   //TO DO: Pràctica 2:  implementar a la fase 2
     qDebug()<<"Estic a Reflection";
}

void GLWidget::activaEnvMapping() {
    //TO DO: Pràctica 2:  implementar a la fase 2
    qDebug()<<"Estic a Environmental Mapping";
}

void GLWidget::activaTransparency() {
    //TO DO: Pràctica 2:  implementar a la fase 2
    qDebug()<<"Estic a Transparencia";
}



void GLWidget::setPerspective(float nearPlane, float farPlane)
{
    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    camera->setFrustum(camera->vfovRadians DEGREES, nearPlane, farPlane, TipProj::PERSPECTIVA);

    updateGL();
}

void GLWidget::setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up)
{
    vec4 lookfrom(eye[0], eye[1], eye[2], 1.0);
    vec4 lookat(center[0], center[1], center[2], 1.0);
    vec4 vup(up[0], up[1], up[2], 1.0);

    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    camera->setObservador(lookfrom, lookat, vup);

    updateGL();
}

void GLWidget::setLighting(const QVector3D &lightPos, const QVector3D &Ia, const QVector3D &Id,
                           const QVector3D &Is, const QVector3D &coefs)
{
    vec4 lightPosition(lightPos[0],lightPos[1], lightPos[2], 1.0) ;
    vec3 intensityA( Ia[0], Ia[1], Ia[2]);
    vec3 intensityD( Id[0], Id[1], Id[2]);
    vec3 intensityS( Is[0], Is[1], Is[2]);

    auto lights = Controller::getInstance()->getSetUp()->getLights();
    lights[0]->setIa(intensityA);
    lights[0]->setId(intensityD);
    lights[0]->setIs(intensityS);
    updateGL();
}


/**  Mètodes d'interacció amb el ratolí */

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        if(lastPos.y()!= event->y() && lastPos.x()!= event->x()) {
           setXRotation(dy);
           setYRotation(dx);
        } else if(lastPos.y()!= event->y()) {// rotar la camera
            setXRotation(dy);
        } else if (lastPos.x()!= event->x()) {
            setYRotation(dx);
        }

    } else if (event->buttons() & Qt::RightButton) {
       // Zoom: canviar la mida de la window
        if(lastPos.y()> event->y())
             Zoom(-1);
        else
             Zoom(1);
    }

    lastPos = event->pos();
}


void GLWidget::setXRotation(int angle)
{
    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    if (angle >0) {
        camera->angX += 5;
    } else if (angle<0)
        camera->angX -= 5;
    qNormalizeAngle(camera->angX);

    camera->rotaCamera();

    emit ObsCameraChanged(camera);

    updateGL();
}

void GLWidget::setYRotation(int angle)
{
    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    if (angle >0) {
        camera->angY += 5;
    } else if (angle<0)
        camera->angY-= 5;
    qNormalizeAngle(camera->angY);

    camera->rotaCamera();

    emit ObsCameraChanged(camera);

    updateGL();
}

void GLWidget::qNormalizeAngle(double &angle)
{
    while (angle < 0)
        angle += 360*16;
    while (angle > 360)
        angle -= 360*16;
}

void GLWidget::Zoom (int positiu) {

    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    camera->AmpliaWindow(positiu*(0.005));

    emit FrustumCameraChanged(camera);

    updateGL();
}

