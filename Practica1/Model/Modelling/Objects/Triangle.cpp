#include "Triangle.hh"

Triangle::Triangle() {
    p1 = vec3(0.0, 0.0, 0.0);
    p2 = vec3(1.0, 0.0, 0.0);
    p3 = vec3(0.5, 1.0, 0.0);
}

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, float data) :Object(data) {
    p1 = v1;
    p2 = v2;
    p3 = v3;
}

Triangle::Triangle(float data) :Object(data) {
    p1 = vec3(0, 0, 0);
    p2 = vec3(1, 0, 0);
    p3 = vec3(0.5, 1, 0);
}

bool Triangle::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    //Calculem la normal del triangle
    vec3 normal = normalize(cross(p2 - p1, p3 - p1));;
        if(abs(dot(raig.getDirection(), normal))<DBL_EPSILON){
            return false;
        }
        float d = -normal[0]*p1[0] - normal[1]*p1[1] - normal[2]*p1[2];

        vec3 rp = raig.getOrigin();
        vec3 vp = raig.getDirection();
        float temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;

        temp /= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];

        vec3 I = raig.pointAtParameter(temp);
        float s1=dot(cross((this->p2-this->p1),I-this->p1),normal);
        float s2=dot(cross((this->p3-this->p2),I-this->p2),normal);
        float s3=dot(cross((this->p1-this->p3),I-this->p3),normal);

        if((s1>0 && s2>0 && s3>0) || (s1<0 && s2<0 && s3<0 )){
            if (temp < tmax && temp > tmin) {
                info.t = temp;
                info.p = raig.pointAtParameter(info.t);
                info.normal = normal;
                info.mat_ptr = material.get();
                return true;
            }
        }
        return false;
}


void Triangle::aplicaTG(shared_ptr<TG> t) {
   mat4 m = t->getTG() * mat4(1.0f); // se obtiene la matriz de transformación de la instancia de TG y se multiplica por la matriz identidad
   p1 = vec3(m * vec4(p1, 1.0f)); // se aplica la matriz de transformación a cada vértice del triángulo
   p2 = vec3(m * vec4(p2, 1.0f));
   p3 = vec3(m * vec4(p3, 1.0f));
}



void Triangle::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("p1") && json["p1"].isArray()) {
        QJsonArray auxVec = json["p1"].toArray();
        p1[0] = auxVec[0].toDouble();
        p1[1] = auxVec[1].toDouble();
        p1[2] = auxVec[2].toDouble();
    }
    if (json.contains("p2") && json["p2"].isArray()) {
        QJsonArray auxVec = json["p2"].toArray();
        p2[0] = auxVec[0].toDouble();
        p2[1] = auxVec[1].toDouble();
        p2[2] = auxVec[2].toDouble();
    }
    if (json.contains("p3") && json["p3"].isArray()) {
        QJsonArray auxVec = json["p3"].toArray();
        p3[0] = auxVec[0].toDouble();
        p3[1] = auxVec[1].toDouble();
        p3[2] = auxVec[2].toDouble();
    }
}


//! [1]
void Triangle::write(QJsonObject &json) const{
    Object::write(json);

    QJsonArray auxArray,auxArray1,auxArray2;
    auxArray.append(p1[0]);auxArray.append(p1[1]);auxArray.append(p1[2]);
    json["p1"] = auxArray;
    auxArray1.append(p1[0]);auxArray1.append(p1[1]);auxArray1.append(p1[2]);
    json["p2"] = auxArray1;
    auxArray2.append(p1[0]);auxArray2.append(p1[1]);auxArray2.append(p1[2]);
    json["p3"] = auxArray2;
}
//! [1]

void Triangle::print(int indentation) const{
    Object::print(indentation);
}
