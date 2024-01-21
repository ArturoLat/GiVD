#include "Box.hh"


Box::Box() {
   p1 = vec3(-0.5, -0.5, 0.0);
   p2 = vec3(0.5, -0.5, 0.0);
   p3 = vec3(0.5, 0.5, 0.0);
   p4 = vec3(-0.5, 0.5, 0.0);
}

Box::Box(vec3 v1, vec3 v2, vec3 v3, vec3 v4, float d) :Object(d) {
   p1 = v1;
   p2 = v2;
   p3 = v3;
   p4 = v4;
}

Box::Box(float data) : Object(data) {
   p1 = vec3(-0.5, -0.5, 0);
   p2 = vec3(0.5, -0.5, 0);
   p3 = vec3(0.5, 0.5, 0);
   p4 = vec3(-0.5, 0.5, 0);

}

bool Box::hit(Ray &ray, float t_min, float t_max, HitInfo& info) const {
   vec3 normal = cross(p2 - p1, p4 - p1);
   if (abs(dot(ray.getDirection(), normal)) < DBL_EPSILON) {
       return false;
   }

   float d = -normal[0]*p1[0] - normal[1]*p1[1] - normal[2]*p1[2];
   float ndotv = dot(normal, ray.getDirection());
   float t = -(d + dot(normal, ray.getOrigin())) / ndotv;

   if (t < t_min || t > t_max) {
       return false;
   }

   vec3 p = ray.pointAtParameter(t);

   vec3 v1 = p2 - p1; vec3 w1 = p - p1;
   vec3 v2 = p3 - p2; vec3 w2 = p - p2;
   vec3 v3 = p4 - p3; vec3 w3 = p - p3;
   vec3 v4 = p1 - p4; vec3 w4 = p - p4;
   vec3 c1 = cross(v1, w1);
   vec3 c2 = cross(v2, w2);
   vec3 c3 = cross(v3, w3);
   vec3 c4 = cross(v4, w4);

   if (dot(c1, c2) >= 0 && dot(c2, c3) >= 0 && dot(c3, c4) >= 0) {
       info.t = t;
       info.p = p;
       info.normal = normalize(normal);
       info.mat_ptr = material.get();
       return true;
   }

   return false;
}

void Box::aplicaTG(shared_ptr<TG> t)  {
       mat4 m = t->getTG() * mat4(1.0f); // se obtiene la matriz de transformación de la instancia de TG y se multiplica por la matriz identidad
       p1 = vec3(m * vec4(p1, 1.0f)); // se aplica la matriz de transformación a cada vértice de la caja
       p2 = vec3(m * vec4(p2, 1.0f));
       p3 = vec3(m * vec4(p3, 1.0f));
       p4 = vec3(m * vec4(p4, 1.0f));
}


void Box::read(const QJsonObject& json) {
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
   if (json.contains("p4") && json["p4"].isArray()) {
       QJsonArray auxVec = json["p4"].toArray();
       p4[0] = auxVec[0].toDouble();
       p4[1] = auxVec[1].toDouble();
       p4[2] = auxVec[2].toDouble();
   }
}

void Box::write(QJsonObject& json) const {
   Object::write(json);

   QJsonArray auxArray, auxArray1, auxArray2, auxArray3;
   auxArray.append(p1[0]); auxArray.append(p1[1]); auxArray.append(p1[2]);
   json["p1"] = auxArray;
   auxArray1.append(p2[0]); auxArray1.append(p2[1]); auxArray1.append(p2[2]);
   json["p2"] = auxArray1;
   auxArray2.append(p3[0]); auxArray2.append(p3[1]); auxArray2.append(p3[2]);
   json["p3"] = auxArray2;
   auxArray3.append(p4[0]); auxArray3.append(p4[1]); auxArray3.append(p4[2]);
   json["p4"] = auxArray3;
}

void Box::print(int indentation) const {
   Object::print(indentation);
}
