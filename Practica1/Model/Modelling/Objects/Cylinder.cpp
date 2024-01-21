#include "Cylinder.hh"

Cylinder::Cylinder(){
   center_ = vec3(0, 0, 0);
   radius_ = 2.0;
   height_ = 4.0;
   axis_ = vec3(0, 1, 0);
}
Cylinder::Cylinder(vec3 center, float radius, float height, vec3 axis, float data) : Object(data){
   this->center_ = center;
   this->radius_ = radius;
   this->height_ = height;
   this->axis_ = axis;
}

Cylinder::Cylinder(float data) :Object(data) {

   center_ = vec3(0, 0, 0);
   radius_ = 2.0;
   height_ = 4.0;
   axis_ = vec3(0, 1, 0);
}


bool Cylinder::hit(Ray& r, float tmin, float tmax, HitInfo& info) const {
   vec3 oc = r.getOrigin() - center_;
   float a = r.getDirection().x*r.getDirection().x + r.getDirection().z*r.getDirection().z;
   float b = 2.0 * (oc.x*r.getDirection().x + oc.z*r.getDirection().z);
   float c = oc.x*oc.x + oc.z*oc.z - radius_*radius_;
   float discriminant = b*b - 4*a*c;

   if (discriminant < 0) {
       return false; // No se intersecta con el cilindro
   }

   float t1 = (-b - sqrt(discriminant)) / (2*a);
   float t2 = (-b + sqrt(discriminant)) / (2*a);

   float t_cylinder;

   if (t1 < tmin && t2 < tmin) {
       return false; // La intersección no se encuentra dentro del rango de tiempos
   } else if (t1 > tmax && t2 > tmax) {
       return false; // La intersección excede el rango de tiempos
   } else if (t1 < tmin && t2 > tmax) {
       //Ambas intersecciones están fuera del rango de tiempo
       return false;
   } else if (t1 < tmin || t1 > tmax) {
       t_cylinder = t2; // la intersección es la segunda
   } else if (t2 < tmin || t2 > tmax) {
       t_cylinder = t1; // la intersección es la primera
   } else {
       // ambas intersecciones están dentro del rango de tiempo
       t_cylinder = (t1 < t2) ? t1 : t2; // la intersección es la más cercana
   }

   vec3 p = r.pointAtParameter(t_cylinder);
   if (p.y < center_.y || p.y > center_.y+height_) {
       return false; // la intersección no está dentro del rango de alturas del cilindro
   }

   vec3 normal = (p - center_) / radius_;
   if (glm::dot(normal, r.getDirection()) > 0) {
       normal = -normal;
   }

   info.t = t_cylinder;
   info.p = p;
   info.normal = normal;
   info.mat_ptr = material.get();

   return true;
}

void Cylinder::aplicaTG(shared_ptr<TG> tg){
   if(dynamic_pointer_cast<TranslateTG>(tg)){
       vec4 temp(center_, 1.0);
       temp = tg->getTG() * temp;
       center_.x = temp.x;
       center_.y = temp.y;
       center_.z = temp.z;

   }
}
void Cylinder::read(const QJsonObject& json) {
   Object::read(json);

   if (json.contains("center") && json["center"].isArray()) {
       QJsonArray auxVec = json["center"].toArray();
       center_[0] = auxVec[0].toDouble();
       center_[1] = auxVec[1].toDouble();
       center_[2] = auxVec[2].toDouble();
   }
   if (json.contains("radius") && json["radius"].isDouble()) {
       radius_ = json["radius"].toDouble();
   }
   if (json.contains("h") && json["h"].isDouble()) {
       height_ = json["h"].toDouble();
   }
   if (json.contains("axis") && json["axis"].isArray()) {
       QJsonArray auxVec = json["axis"].toArray();
       axis_[0] = auxVec[0].toDouble();
       axis_[1] = auxVec[1].toDouble();
       axis_[2] = auxVec[2].toDouble();
   }
}

void Cylinder::write(QJsonObject& json) const {
   Object::write(json);

   QJsonArray auxArray;
   auxArray.append(center_.x);
   auxArray.append(center_.y);
   auxArray.append(center_.z);
   json["center"] = auxArray;
   json["radius"] = radius_;
   json["h"] = height_;
   QJsonArray auxArray2;
   auxArray2.append(axis_.x);
   auxArray2.append(axis_.y);
   auxArray2.append(axis_.z);
   json["axis"] = auxArray2;
}

void Cylinder::print(int indentation) const {
   Object::print(indentation);
}
