#include "SpotLight.hh"

SpotLight::SpotLight(vec3 Ia, vec3 Id, vec3 Is, vec3 abc, vec4 pos, vec3 dir, float cosAngle) :
    Light(Ia, Id, Is, abc, pos, dir, cosAngle)
{

}

SpotLight::SpotLight() {
}

vec3 SpotLight::getPos() {
    return this->pos;
}

vec3 SpotLight::getDir() {
    return this->dir;
}

vec3 SpotLight::getCoeficients(){
    return vec3(a, b, c);
}

float SpotLight::getAngle(){
    return this->cosAngle;
}

vec3 SpotLight::vectorL(vec3 point) {
    return normalize(pos - point);
}

float SpotLight::attenuation(vec3 point) {
    float d = distanceToLight(point);
    return 1.0f / (a * d * d + b * d + c);
}

float SpotLight::distanceToLight(vec3 point) {
    return length(pos - point);
}

void SpotLight::read(const QJsonObject &json) {
    Light::read(json);
    pos = vec3(json["pos_x"].toDouble(), json["pos_y"].toDouble(), json["pos_z"].toDouble());
    dir = vec3(json["dir_x"].toDouble(), json["dir_y"].toDouble(), json["dir_z"].toDouble());
    a = json["a"].toDouble();
    b = json["b"].toDouble();
    c = json["c"].toDouble();
    cosAngle = cosf(json["angle"].toDouble() / 2);
}

void SpotLight::write(QJsonObject &json) const {
    Light::write(json);
    json["pos_x"] = pos.x;
    json["pos_y"] = pos.y;
    json["pos_z"] = pos.z;
    json["dir_x"] = dir.x;
    json["dir_y"] = dir.y;
    json["dir_z"] = dir.z;
    json["a"] = a;
    json["b"] = b;
    json["c"] = c;
    json["angle"] = acosf(cosAngle) * 2;
}

void SpotLight::print(int indentation) const {
    Light::print(indentation);
    printf("%*s" "- type: %s\n", indentation, "", "Spot Light");
    printf("%*s" "- position: (%.2f, %.2f, %.2f)\n", indentation, "", pos.x, pos.y, pos.z);
    printf("%*s" "- direction: (%.2f, %.2f, %.2f)\n", indentation, "", dir.x, dir.y, dir.z);
    printf("%*s" "- ambient: (%.2f, %.2f, %.2f)\n", indentation, "", Ia.x, Ia.y, Ia.z);
    printf("%*s" "- diffuse: (%.2f, %.2f, %.2f)\n", indentation, "", Id.x, Id.y, Id.z);
    printf("%*s" "- specular: (%.2f, %.2f, %.2f)\n", indentation, "", Is.x, Is.y, Is.z);
    printf("%*s" "- attenuation: a=%.5f b=%.5f c=%.5f\n", indentation, "", a, b, c);
    printf("%*s" "- angle: %.2f degrees\n", indentation, "", acosf(cosAngle) * 2 * 180 / M_PI);
}
