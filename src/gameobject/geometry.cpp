#include  "geometry.h"
#include "gameobject.h"

Geometry::Geometry(GameObject * parent) :
    Component(parent),
    mesh(0)
{

}

bool Geometry::assignMesh(const char *name) {
    Asset * asset = Asset::Find(name);
    if (asset == 0)
        return false;
    mesh = asset;
    return true;
}

void Geometry::destroy() {
    removeComponent();
    delete this;
}

void Geometry::clone(GameObject * c) {
    Geometry * g = c->addComponent<Geometry>();
    g->mesh = mesh;
}

void Geometry::draw(QOpenGLShaderProgram *program) {
    if (mesh != 0)
        mesh->getData<Mesh>()->draw(program);
}
