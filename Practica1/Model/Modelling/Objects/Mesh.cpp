#include <QVector>
#include <QVector3D>

#include "Mesh.hh"


Mesh::Mesh(const QString &fileName): Object()
{
    nom = fileName;
    load(fileName);
}

Mesh::Mesh(const QString &fileName, float data): Object(data)
{
    nom = fileName;
    load(fileName);
}

Mesh::~Mesh() {
    if (cares.size() > 0) cares.clear();
    if (vertexs.size() > 0) vertexs.clear();
    if (triangles.size() > 0) triangles.clear();

}

void Mesh::makeTriangles() {
    // TO DO Fase 1: A implementar
    int idx1, idx2, idx3;
    vec3 p1, p2, p3;
    for(unsigned int i = 0; i < cares.size(); i++){
        // Asignem les IDS dels Vertexs
        idx1 = cares[i].idxVertices[0];
        idx2 = cares[i].idxVertices[1];
        idx3 = cares[i].idxVertices[2];

        //Asignem els vectors per la creació dels Triangles segons les ids
        p1 = (vec3) vertexs[idx1];
        p2 = (vec3) vertexs[idx2];
        p3 = (vec3) vertexs[idx3];

        //Creem els triangles i asignem el material
        Triangle *triangle = new Triangle(p1, p2, p3, 1.0);
        triangle->setMaterial(this->material);
        //Afegim els triangles al vector
        triangles.push_back(*triangle);

    }
}


bool Mesh::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    // TODO Fase 1: A implementar
    bool hits = false;
    HitInfo i_aux;
    for(unsigned int i = 0; i < triangles.size(); i++){
        if(triangles[i].hit(raig, tmin, tmax, i_aux)){
            if(i_aux.t < info.t){
                info = i_aux;
                info.mat_ptr = material.get();
            }
            hits = true;
        }
    }
    return hits;

}


void Mesh::aplicaTG(shared_ptr<TG> t) {
    // TO DO: Fase 1
    if(dynamic_pointer_cast<TranslateTG>(t)){
        for(unsigned int i = 0; i < triangles.size(); i++){
            triangles[i].aplicaTG(t);
        }
    }
}

void Mesh::load (QString fileName) {
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        // qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                               lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {

                    }
                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {

                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Face *face = new Face();

                        // get points from v array
                        face->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        cares.push_back(*face);
                    }
                }
            }
            file.close();
            makeTriangles();
        } else {
            qWarning("Boundary object file can not be opened.");
        }
    } else  qWarning("Boundary object file not found.");
}

void Mesh::read (const QJsonObject &json)
{
    Object::read(json);
    if (json.contains("objFileName") && json["objFileName"].isString()) {
        nom = json["objFileName"].toString();
        load(nom);
    }
}


//! [1]
void Mesh::write(QJsonObject &json) const
{
    Object::write(json);
    json["objFileName"] = nom;
}
//! [1]

void Mesh::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "objFileName:\t" << nom << "\n";
}



