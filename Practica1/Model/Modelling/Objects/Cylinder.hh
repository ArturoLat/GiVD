#pragma once
#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"

class Cylinder : public Object {

public:
   Cylinder();
   Cylinder(vec3 center, float radius, float height, vec3 axis, float data);
   Cylinder(float data);
   virtual ~Cylinder() {}

   virtual bool hit(Ray &ray, float t_min, float t_max, HitInfo& info) const override;
   virtual void read(const QJsonObject &json) override;
   virtual void write(QJsonObject &json) const override;
   virtual void aplicaTG(shared_ptr<TG> tg) override;
   virtual void print(int indentation) const override;

private:
   vec3 center_;
   float radius_;
   float height_;
   vec3 axis_;
};
