#include "DirectionalLight.hh"

DirectionalLight::DirectionalLight(vec3 Ia, vec3 Id, vec3 Is, vec3 dir) :
    Light(Ia, Id, Is, dir){

}

DirectionalLight::DirectionalLight() {
}

vec3 DirectionalLight::getDir() {
    return dir;
}

vec3 DirectionalLight::vectorL(vec3 point) {
    return -dir;
}

//Aquest metodes no tenen molt sentit en una llum Direccional, pero com son virtual a LIGHT es deuen implementar
//Com no l'usarem, retornem un valor float i ja esta (N6)
float DirectionalLight::attenuation(vec3 point) {
    return 1.0f;
}


//Pel que fa al mètode distanceToLight, com que la llum és direccional, no hi ha una posició exacta de la llum a la qual es pugui calcular
//la distància. En canvi, ppodem calcular la distància des del punt a la direcció oposada de la llum. Alguna cosa així:
// (N6)

float DirectionalLight::distanceToLight(vec3 point) {
    vec3 oppositeDirection = -1.0f * getDir();
    float distance = dot(point, oppositeDirection);
    return distance;
}



void DirectionalLight::read(const QJsonObject &json) {
    Light::read(json);
    dir = vec3(json["dir_x"].toDouble(), json["dir_y"].toDouble(), json["dir_z"].toDouble());
}

void DirectionalLight::write(QJsonObject &json) const {
    Light::write(json);
    json["dir_x"] = dir.x;
    json["dir_y"] = dir.y;
    json["dir_z"] = dir.z;
}

void DirectionalLight::print(int indentation) const {
    Light::print(indentation);
    printf("%*s" "- type: %s\n", indentation, "", "Directional Light");
    printf("%*s" "- direction: (%.2f, %.2f, %.2f)\n", indentation, "", dir.x, dir.y, dir.z);
    printf("%*s" "- ambient: (%.2f, %.2f, %.2f)\n", indentation, "", Ia.x, Ia.y, Ia.z);
    printf("%*s" "- diffuse: (%.2f, %.2f, %.2f)\n", indentation, "", Id.x, Id.y, Id.z);
    printf("%*s" "- specular: (%.2f, %.2f, %.2f)\n", indentation, "", Is.x, Is.y, Is.z);
}
