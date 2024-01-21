#pragma once

#include "ShadingFactory.hh"
#include "ColorShading.hh"
#include "ColorShadow.hh"
#include "NormalShading.hh"
#include "BlinnPhongShading.hh"
#include "PhongShading.hh"
#include "CellShading.hh"
#include "BlinnPhongShadow.hh"
#include "NormalShadow.hh"
#include "CellShadow.hh"
#include "PhongShadow.hh"
#include "DepthShading.hh"

class ShadingFactory
{
public:
    ShadingFactory() {};
    typedef enum  SHADING_TYPES{
        COLOR,
        COLORSHADOW,
        NORMAL,
        NORMALSHADOW,
        DEPTH,
        PHONG,
        PHONGSHADOW,
        BLINNPHONG,
        BLINNPHONGSHADOW,
        CELL,
        CELLSHADOW
    } SHADING_TYPES;

    static ShadingFactory& getInstance() {
        static ShadingFactory instance;
        return instance;
    }

    shared_ptr<ShadingStrategy>   createShading(SHADING_TYPES t);
    SHADING_TYPES                 getShadingType(QString s);
    QString                       getNameType(SHADING_TYPES t);
    ShadingFactory::SHADING_TYPES getIndexType(shared_ptr<ShadingStrategy> m);
    shared_ptr<ShadingStrategy>   switchShading(shared_ptr<ShadingStrategy> m, bool shadow);
};

