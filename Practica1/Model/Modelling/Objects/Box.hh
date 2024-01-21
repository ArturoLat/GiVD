#pragma once

#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"

class Box : public Object {
public:
   Box();
   Box(vec3 v1, vec3 v2, vec3 v3, vec3 v4, float d);
   Box(float data);
   virtual ~Box() {}


   virtual bool hit(Ray &ray, float t_min, float t_max, HitInfo& info) const override;
   virtual void read(const QJsonObject &json) override;
   virtual void write(QJsonObject &json) const override;
   virtual void aplicaTG(shared_ptr<TG> tg) override;
   virtual void print(int indentation) const override;

private:
   vec3 p1, p2, p3, p4;
};
