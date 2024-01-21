#pragma once

#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"

class Triangle: public Object  {
public:
    Triangle();

    Triangle(vec3 v1, vec3 v2, vec3 v3, float data);
    //Crea una triangle unitari amb 3 vèrtexs
    Triangle(float data);
    virtual ~Triangle() {}
    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

private:

    vec3 p1,p2,p3;

};
