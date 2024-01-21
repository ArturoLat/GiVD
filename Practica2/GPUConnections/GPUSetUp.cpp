#include "GPUSetUp.hh"

GPUSetUp::GPUSetUp()
{
  camera = make_shared<GPUCamera>(500, 500);
}


shared_ptr<GPUCamera> GPUSetUp::getCamera() {
    return(camera);
}


vec3 GPUSetUp::getGlobalLight() {
    return globalLight;
}

std::vector<shared_ptr<GPULight>> GPUSetUp::getLights() {
    return lights;
}



void GPUSetUp::setCamera(shared_ptr<GPUCamera> cam) {
    this->camera = cam;
}

void GPUSetUp::setGlobalLight(vec3 globalLight) {
    this->globalLight = globalLight;
}
void GPUSetUp::setLights(std::vector<shared_ptr<GPULight>> lights) {
    this->lights = lights;
}

/**
 * @brief GPUSetUp::getLightActual
 * @return
 */
shared_ptr<GPULight> GPUSetUp::getLightActual() {
    // TO DO OPCIONAL: A modificar si es vol canviar el comportament de la GUI
    // Ara per ara dona com a Light actual la darrera que s'ha inserit
    return (lights[lights.size()-1]);
}

/**
 * @brief GPUSetUp::setLightActual
 * @param shared_ptr<Light> l
 */
void GPUSetUp::setLightActual(shared_ptr<GPULight> l){
    lights[lights.size()-1]=l;
}

/**
 * @brief GPUSetUp::addLight
 * @param shared_ptr<Light> l
 */
void GPUSetUp::addLight(shared_ptr<GPULight> l) {
    lights.push_back(l);
}



/**
 * @brief Scene::setAmbientToGPU
 * @param program
 */

// Aquest es el metode que envia les llums a la GPU (N6)
void GPUSetUp::setAmbientGlobalToGPU(shared_ptr<QGLShaderProgram> program){
    // Pràctica 2: Fase 1 lights
    //vec3 vector3D(0.2f, 0.2f, 0.2f); // Valors llum ammbiental (vector de floats) (N6)
    // Obtenim ubi memoria GPU per la variable uniforme glAmbientLight (N6)
    //this->aL =  program->uniformLocation("glAmbientLight");
    // Enviem valors ddel vector 3D a la GPU (N6)
    //glUniform3fv(aL, 1, vector3D);
    vec3 global = vec3(0.3);
    GLuint gl_globalLight = program->uniformLocation("glAmbientLight");
    glUniform3fv(gl_globalLight, 1, global);

}



/* N6
 * El mètode lightsToGPU de la classe GPUSetUp serveix per enviar la informació de totes les llums actives del escenari a la GPU,
 * de manera que puguin ser utilitzades durant el renderitzat de la imatge.
    Aquest mètode recorre el vector de llums actives lights, que conté totes les llums que estan sent utilitzades en el moment de renderitzar
 el model. Per cada llum, es crida el mètode toGPU de la classe GPULight, que s'encarrega d'actualitzar els paràmetres de la llum en el shader
 de OpenGL corresponent.
 */

/**
 * @brief GPUSetUp::lightsToGPU
 * @param program
 */




//Aquest métode pasa les llums a la GPU
void GPUSetUp::lightsToGPU(shared_ptr<QGLShaderProgram> program){
    //Primer assignem el index, ja que el necessitem per buscar la ubicació del uniforme (preparem al vector)
    for(size_t i=0; i < lights.size(); i++){
        lights[i]->setIndex(static_cast<int>(i));
    }
    //Aleshores amb aquest for, ja cridem al toGPu respectiu depenent dels parametres que li ent
    for(size_t i=0; i < lights.size(); i++){
        lights[i]->toGPU(program);
    }
}


// TODO (opcional) si es llegeix el setUp de fitxer cal alctualitzar aquest codi per
// a crear les llums de tipus GPU
void GPUSetUp::read(const QJsonObject &json)
{
    if (json.contains("camera")) {
        QJsonObject camObject = json["camera"].toObject();
        camera->read(camObject);
    }
    if (json.contains("lights") && json["lights"].isArray()) {
        QJsonArray lightsArray = json["lights"].toArray();

        for (int lightIndex = 0; lightIndex < lightsArray.size(); lightIndex++) {
            QJsonObject lightObject = lightsArray[lightIndex].toObject();
            shared_ptr<GPULight> l;
            if (lightObject.contains("type") && lightObject["type"].isString()) {
                QString ligthStr = lightObject["type"].toString().toUpper();
                l = GPULightFactory::getInstance().createLight(LightFactory::getInstance().getLightType(ligthStr));
                l->read(lightObject);
                lights.push_back(l);
            }
        }
    }
    if (json.contains("globalLight") && json["globalLight"].isArray()) {
        QJsonArray globalVec = json["globalLight"].toArray();
        globalLight[0] = globalVec[0].toDouble();
        globalLight[1] = globalVec[1].toDouble();
        globalLight[2] = globalVec[2].toDouble();
    }

}
//! [0]

void GPUSetUp::write(QJsonObject &json) const
{
    QJsonObject cameraObject;
    camera->write(cameraObject);
    json["camera"] = cameraObject;

    QJsonArray lightsArray;
    for (const shared_ptr<GPULight> &l : lights) {
        QJsonObject lightObject;
        auto  value = LightFactory::getInstance().getIndexType (l);
        QString className = LightFactory::getInstance().getNameType(value);

        l->write(lightObject);
        lightObject["type"] = className;
        lightsArray.append(lightObject);
    }
    json["lights"] = lightsArray;

    QJsonArray auxArray;
    auxArray.append(globalLight[0]);auxArray.append(globalLight[1]);auxArray.append(globalLight[2]);
    json["globalLight"] = auxArray;

}

void GPUSetUp::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    camera->print(2);
    QTextStream(stdout) << indent << "Ligths:\t\n";
    for (unsigned int i =0; i< lights.size(); i++) {
        auto value = LightFactory::getInstance().getIndexType (lights[i]);
        QString className = LightFactory::getInstance().getNameType(value);
        QTextStream(stdout) << indent+2 << "type:\t" << className << "\n";

        lights[i]->print(2);

    }
    QTextStream(stdout) << indent << "globalLight:\t" << globalLight[0] << ", "<< globalLight[1] << ", "<< globalLight[2] << "\n";
}


