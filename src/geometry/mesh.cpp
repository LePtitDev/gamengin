#include "mesh.h"

unsigned int Mesh::vertexCount() const {
    return (unsigned int)V.size();
}

unsigned int Mesh::trianglesCount() const {
    return (unsigned int)T.size();
}

unsigned int Mesh::addVertex(const QVector3D &v, const QVector2D &uv) {
    V.push_back(v);
    N.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    UV.push_back(uv);
    return (unsigned int)V.size() - 1;
}

unsigned int Mesh::addTriangle(unsigned int a, unsigned int b, unsigned int c, bool addnormal) {
    T.push_back({ a, b, c });
    if (addnormal) {
        QVector3D tmp = QVector3D::crossProduct(V[b] - V[a], V[c] - V[a]);
        N[a] += tmp;
        N[b] += tmp;
        N[c] += tmp;
    }
    return (unsigned int)T.size() - 1;
}

QVector3D& Mesh::getVertex(unsigned int i) {
    return V[i];
}

const QVector3D& Mesh::getVertex(unsigned int i) const {
    return V[i];
}

QVector3D& Mesh::getNormal(unsigned int i) {
    return N[i];
}

const QVector3D& Mesh::getNormal(unsigned int i) const {
    return N[i];
}

QVector2D& Mesh::getUV(unsigned int i) {
    return UV[i];
}

const QVector2D& Mesh::getUV(unsigned int i) const {
    return UV[i];
}

std::array<unsigned int, 3>& Mesh::getTriangle(unsigned int i) {
    return T[i];
}

const std::array<unsigned int, 3>& Mesh::getTriangle(unsigned int i) const {
    return T[i];
}

Mesh& Mesh::operator=(const Mesh& m) {
    V = m.V;
    UV = m.UV;
    T = m.T;
    return *this;
}
