#include "Scene.hh"

Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}


Scene::Scene(shared_ptr<Object> ground)
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
    this->ground = ground;
}

bool Scene::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    // TODO FASE 0 i FASE 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Si un objecte es intersecat pel raig, el parametre  de tipus HitInfo conte
    // la informació sobre la interseccio.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig.
    bool enter = false;
    HitInfo aux = info;
    float tmin_aux = tmax;

    if(ground){
        if(ground->hit(raig,tmin,tmax,info)){
            enter = true;
            if(info.t<aux.t){
                aux = info;
            }
        }
    }
    for(int i = 0; i < objects.size(); i++){
        if(objects[i]->hit(raig, tmin, tmin_aux, info)){
            enter = true;
            if(info.t<aux.t){
                aux = info;
            }
        }
    }
    info = aux;
    return enter;
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

//Aquest métode l'usem amb el Cell-Shading permet calcular l'intersecció del raig amb tots els objecte de l'escena
HitInfo Scene::intersect(Ray &r) const{
    HitInfo hitInfo;
    float closest = FLT_MAX;
    for(const shared_ptr<Object> &object : objects) {
        HitInfo tmpHit;
        if(object->hit(r, 0.00001f, closest, tmpHit)) {
            if(tmpHit.t < closest) {
                hitInfo = tmpHit;
                closest = tmpHit.t;
            }
        }
    }
    return hitInfo;
}

