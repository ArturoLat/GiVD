#include "FittedPlane.hh"

FittedPlane::FittedPlane() : Plane(vec3(0,1,0), vec3(0,-1,0), -1.0f){
    this->pmin = vec2(-5.0,-5.0);
    this->pmax = vec2(5.0,5.0);
}

FittedPlane::FittedPlane(float data): Plane(vec3(0,1,0), data, -1.0f){
    this->pmin = vec2(-5.0,-5.0);
    this->pmax = vec2(5.0,5.0);
}

FittedPlane::FittedPlane(vec2 max, vec2 min, vec3 point, vec3 normal, float data): Plane(normal, point, data){
    this->pmin = min;
    this->pmax = max;
}

bool FittedPlane::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    if(Plane::hit(raig, tmin, tmax, info)){
        if(info.p.x<= pmax.x && info.p.x >= pmin.x && info.p.z <= pmax.y && info.p.z >= pmin.y){
            return true;
        }
    }
    return false;
}

void FittedPlane::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {

        // Nomes movem el punt de pas
        vec4 newp(this->point, 1.0);
        newp = t->getTG() * newp;
        this->point.x = newp.x;
        this->point.y = newp.y;
        this->point.z = newp.z;
    }
}

void FittedPlane::read (const QJsonObject &json)
{
    Plane::read(json);

    if (json.contains("pmin") && json["pmin"].isArray()) {
        QJsonArray auxVec = json["pmin"].toArray();
        pmin[0] = auxVec[0].toDouble();
        pmin[1] = auxVec[1].toDouble();
    }

    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        pmax[0] = auxVec[0].toDouble();
        pmax[1] = auxVec[1].toDouble();
    }
}


//! [1]
void FittedPlane::write(QJsonObject &json) const
{
    Plane::write(json);

    QJsonArray auxArray3;
    auxArray3.append(pmin[0]);auxArray3.append(pmin[1]);
    json["pmin"] = auxArray3;

    QJsonArray auxArray4;
    auxArray4.append(pmax[0]);auxArray4.append(pmax[1]);
    json["pmax"] = auxArray4;
}
//! [1]

void FittedPlane::print(int indentation) const
{
    Plane::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "pmin:\t" << pmin[0] << ", "<< pmin[1] << "\n";
    QTextStream(stdout) << indent << "pmax:\t" << pmax[0] << ", "<< pmax[1] << "\n";
    QTextStream(stdout) << indent << "point:\t" << point[0] << ", "<< point[1] << ", "<< point[2] << "\n";
    QTextStream(stdout) << indent << "normal:\t" << normal[0] << ", "<< normal[1] << ", "<< normal[2] << "\n";

}
