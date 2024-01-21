#pragma once

#include <vector>
#include <string>
#include <limits>

#include <QString>
#include <QFile>
#include <QRegularExpression>

#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "Object.hh"

using namespace std;

class FittedPlane: public Object{
public:
    FittedPlane();

    virtual ~FittedPlane(){}

    virtual bool hit(Ray &r, float tmin, float tmax, HitInfo &info) const override;

    virtual void aplicaTG(shared_ptr<TG> tg) override;


    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 normal;
    vec3 point;
    vec2 pmin;
    vec2 pmax;

private:

};

