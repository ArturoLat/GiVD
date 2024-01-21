#include "Builder.hh"


void Builder::newSphere()
{
    vec3 position(0.0, 0.0, 0.0);
    float radius = 0.5;
    QMessageBox msgBox;
    if (Controller::getInstance()->createScene(position, radius))
            msgBox.setText("One Sphere is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newTriangle()
{
    vec3 v1(0.0, 0.0, 0.0);
    vec3 v2(1.0, 0.0, 0.0);
    vec3 v3(0.5, 1.0, 0.0);
    float data = 0.5;
    QMessageBox msgBox;
    if (Controller::getInstance()->createTriangle(v1, v2, v3, data))
            msgBox.setText("One Triangle is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newBox()
{
    vec3 v1(-0.5, -0.5, 0.0);
    vec3 v2(0.5, -0.5, 0.0);
    vec3 v3(0.5, 0.5, 0.0);
    vec3 v4(-0.5, 0.5, 0.0);
    float data = 0.7;
    QMessageBox msgBox;
    if (Controller::getInstance()->createBox(v1, v2, v3,v4, data))
            msgBox.setText("One Box is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newCylinder()
{
    vec3 center_(0, 0, 0);
    float radius_ = 2.0;
    float height_ = 4.0;
    vec3 axis_(0, 1, 0);
    float data = 0.7;
    QMessageBox msgBox;
    if (Controller::getInstance()->createCylinder(center_, radius_, height_, axis_, data))
            msgBox.setText("One Cylinder is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newMesh(){

    QMessageBox msgBox;
    if(Controller::getInstance()->createMesh())
        msgBox.setText("Mesh is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newFittedPlane()
{
    QMessageBox msgBox;

    if (Controller::getInstance()->createFittedPlane(vec2 (5,5), vec2 (-5, -5), vec3(0.0, -1.0, 0.0), vec3 (0.0, 1.0, 0.0) ,-1.0f))
            msgBox.setText("One FittedPlane is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newSimulatedScene()
{
   QMessageBox msgBox;
   if (Controller::getInstance()->createScene())
           msgBox.setText("A simulated Scene is created.");
   else msgBox.setText("Not enough memory. Error.");
   msgBox.exec();
}


void Builder::newVirtualScene()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if(Controller::getInstance()->createScene(SceneFactory::SCENE_TYPES::VIRTUALWORLD, fileName))
            msgBox.setText("Virtual Scene well loaded.");
        else msgBox.setText("Scene NOT loaded. Error reading data.");
        msgBox.exec();
    }
}


void Builder::newDataScene()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if (Controller::getInstance()->createScene(SceneFactory::SCENE_TYPES::REALDATA, fileName)) {
                msgBox.setText("Data Scene well loaded.");
        } else msgBox.setText("Scene NOT loaded. Error reading data.");
        msgBox.exec();
    }
}

void Builder::loadSettings() {
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if (Controller::getInstance()->createSettings(fileName)) {
                msgBox.setText("Visual Settings well loaded.");

        } else msgBox.setText("Settings NOT loaded. Error reading data.");
        msgBox.exec();
        emit settingsChanged();
    }
}

void Builder::activaColorShading() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::COLOR)) {
        msgBox.setText("Color Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}

void Builder::activaDepthShading() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::DEPTH)) {
        msgBox.setText("Depth Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}

void Builder::activaNormalShader() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::NORMAL)) {
        msgBox.setText("Normal Shading created.");
    } else msgBox.setText("Error creating normal shading");
    msgBox.exec();
}

void Builder::activaBlinn_Phong() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::BLINNPHONG)) {
        msgBox.setText("Blinn Phong Shading created.");
    } else msgBox.setText("Error creating Blinn Phong shading");
    msgBox.exec();
}

void Builder::activaPhongShader() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::PHONG)) {
        msgBox.setText("Phong Shading created.");
    } else msgBox.setText("Error creating Phong shading");
    msgBox.exec();
}

void Builder::activaCell_Shading() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::CELL)) {
        msgBox.setText("Cell Shading created.");
    } else msgBox.setText("Error creating Cell shading");
    msgBox.exec();
}
