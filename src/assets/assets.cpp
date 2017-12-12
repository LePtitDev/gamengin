#include "assets.h"
#include "../geometry/mesh.h"

#include <cstring>
#include <fstream>
#include <QOpenGLTexture>

Asset * Asset::Load(const char * name, const char * filename) {
    int len = (int)std::strlen(filename);
    int pos = len - 1; while (pos >= 0 && filename[pos] != '.') pos--;
    if (pos < 0)
        return 0;
    pos++;
    if (std::strcmp(filename + pos, "png") == 0)
        return LoadPNG(name, filename);
    if (std::strcmp(filename + pos, "ply") == 0)
        return LoadPLY(name, filename);
    return 0;
}

Asset * Asset::LoadPNG(const char * name, const char *filename)  {
    QImage img(filename);
    if (img.isNull())
        return 0;
    QOpenGLTexture * texture = new QOpenGLTexture(img.mirrored());
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
    return new Asset(name, std::shared_ptr<void>((void *)texture));
}

Asset * Asset::LoadPLY(const char *name, const char *filename) {
    std::ifstream stream(filename);
    if (!stream.is_open())
        return 0;
    Mesh * mesh = new Mesh();
    char c;
    std::string line;
    unsigned int it = 0;
    // VERTEX HEADER
    do {
        line.clear();
        for (it++; (c = stream.get()) != '\n'; it++) line += c;
    } while (strncmp("element vertex ", line.c_str(), sizeof("element vertex")) != 0);
    unsigned int vertCount = std::atoi(line.c_str() + sizeof("element vertex"));
    // FACE HEADER
    do {
        line.clear();
        for (it++; (c = stream.get()) != '\n'; it++) line += c;
    } while (strncmp("element face ", line.c_str(), sizeof("element face")) != 0);
    unsigned int faceCount = std::atoi(line.c_str() + sizeof("element face"));
    do {
        line.clear();
        for (it++; (c = stream.get()) != '\n'; it++) line += c;
    } while (strncmp("end_header", line.c_str(), sizeof("end_header") - 1) != 0);
    // VERTEX READING
    for (unsigned int i = 0; i < vertCount; i++) {
        line.clear();
        for (it++; (c = stream.get()) != '\n'; it++) line += c;
        unsigned int j = 0;
        mesh->addVertex(QVector3D(), QVector2D());
        mesh->getVertex(i).setX(std::atof(line.c_str()));
        for (; line[j] != ' '; j++); j++;
        mesh->getVertex(i).setY(std::atof(line.c_str() + j));
        for (; line[j] != ' '; j++); j++;
        mesh->getVertex(i).setZ(std::atof(line.c_str() + j));
        for (; line[j] != ' '; j++); j++;
        mesh->getNormal(i).setX(std::atof(line.c_str() + j));
        for (; line[j] != ' '; j++); j++;
        mesh->getNormal(i).setY(std::atof(line.c_str() + j));
        for (; line[j] != ' '; j++); j++;
        mesh->getNormal(i).setZ(std::atof(line.c_str() + j));
    }
    // FACE READING
    for (unsigned int i = 0; i < faceCount; i++) {
        line.clear();
        for (it++; (c = stream.get()) != '\n'; it++) line += c;
        unsigned int j = 0;
        std::vector<unsigned int> f;
        unsigned int fcount = std::atoi(line.c_str());
        for (unsigned int k = 0; k < fcount; k++) {
            for (; line[j] != ' '; j++); j++;
            f.push_back(std::atoi(line.c_str() + j));
        }
        for (unsigned k = 2; k < fcount; k++)
            mesh->addTriangle(f[0], f[k - 1], f[k], false);
    }
    stream.close();
    return new Asset(name, std::shared_ptr<void>((void *)mesh));;
}
