#include "RayTracer.hh"


RayTracer::RayTracer(QImage *i):
    image(i) {

    setup = Controller::getInstance()->getSetUp();
    scene = Controller::getInstance()->getScene();
}


void RayTracer::run() {

    init();
    auto camera = setup->getCamera();
    int  width = camera->viewportX;
    int  height = camera->viewportY;

    for (int y = height-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < width; x++) {
            vec3 color(0, 0, 0);
            //TODO FASE 2: mostrejar més rajos per pixel segons el valor de "samples"
            for (int numSamples = 0; numSamples < 10; numSamples++){
                float numrandom = glm::linearRand(0.0,1.0);
                float u = (float(x+numrandom)) / float(width);
                float v = (float(height -y+numrandom)) / float(height);
                vec3 coloraux(0, 0, 0);

                Ray r = camera->getRay(u, v);
                int depth = 1;
                coloraux = this->RayPixel(r, depth);
                color += coloraux;
            }
            // TODO FASE 2: Gamma correction
            color /= 10;
            color = glm::clamp(color,0.0,1.0);
            color = sqrt(color);
            color *= 255;

            setPixel(x, y, color);

        }
    }
}


void RayTracer::setPixel(int x, int y, vec3 color) {

    if (color.r < 0) color.r = 0;
    if (color.g < 0) color.g = 0;
    if (color.b < 0) color.b = 0;

    if (color.r > 255) color.r = 255;
    if (color.g > 255) color.g = 255;
    if (color.b > 255) color.b  = 255;

    image->setPixelColor(x, y, QColor(color.r, color.g, color.b));

}

/* Mètode RayPixel
** TODO: Cal modificar la funcio RayPixel es la funcio recursiva del RayTracing. Cal retocar-lo per:
** FASE 0 per a fer el degradat del fons
** FASES 0 i 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte (via color, depth o normal)
** FASE 2 per incloure els shading més realistes (Blinn-Phong  i ombres)
** FASE 2 per a tractar reflexions i transparències
**
**I si volguessis canviar els colors del degradat? ON els canviaries?
**Per canviar els colors del degradat es fan al RayPixel, exactament, cambiant els valors del vec3(0.5, 0.7, 1).
*/

vec3 RayTracer::RayPixel(Ray &ray, int depth) {
    // Declaració de variables i objectes
    int MAXDEPTH = this->setup->getMAXDEPTH();
    vec3 color = vec3(0);
    vec3 color_shading = vec3(0);
    vec3 color_aux2 = vec3(0);
    vec3 unit_direction;
    HitInfo info;
    Ray rai_sortida;
    float t;

    // Comprovació si el raig col·lisiona amb algun objecte de l'escena
    if(this->scene->hit(ray, 0.0001, float('inf'), info)){
        // Càlcul del color de la llum (usant la tècnica de Blinn-Phong) per a la intersecció
        color_shading = setup->getShadingStrategy()->shading(scene, info, setup->getCamera()->getLookFrom(), setup->getLights(), setup->getGlobalLight());

        // Comprovació si l'objecte reflecteix o transmet la llum
        if(info.mat_ptr->scatter(ray, info, color_aux2, rai_sortida)){
            // Càlcul del color corresponent a la reflexió o transmissió usant una crida recursiva
            color_aux2 *= RayPixel(rai_sortida, depth+1);
        } else {
            // Establim el component ambiental de l'objecte com a color auxiliar
            color_aux2 = info.mat_ptr->Ka;
        }

        // Barreja del color de l'ombra i el color auxiliar de reflexió/transmissió
        if(color_shading != vec3(0) || color_aux2 != vec3(0)){
            color = color_shading + color_aux2;
        }

        // Límit de profunditat de recursió
        if(depth > MAXDEPTH){
            color = color_shading;
        }
    } else {
        // Càlcul del color degradat de fons en cas que el raig no col·lisioni amb cap objecte de l'escena
        if (setup->getBackground()) {
            vec3 ray2 = normalize(ray.getDirection());
            t = (ray2.y + 1) * 0.5f;
            vec3 color1 = this->setup->getDownBackground();
            vec3 color2 = this->setup->getTopBackground();
            color = (1 - t) * color1 + t * color2;
        } else {
            // Si el raig no col·lisiona amb cap objecte, el píxel es pinta de negre
            color = vec3(0, 0, 0);
        }
    }

    return color;
}



void RayTracer::init() {
    auto s = setup->getShadingStrategy();
    auto s_out = ShadingFactory::getInstance().switchShading(s, setup->getShadows());
    if (s_out!=nullptr) setup->setShadingStrategy(s_out);
}

