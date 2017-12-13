#include "mesh.h"

Mesh::Mesh() :
    indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    vertexBuffer.create();
    indexBuffer.create();
}

Mesh::~Mesh() {
    vertexBuffer.destroy();
    indexBuffer.destroy();
}

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

void Mesh::refreshBuffers() {
    QVector3D * normals = new QVector3D[vertexCount()];
    for (unsigned int i = 0, sz = trianglesCount(); i < sz; i++) {
        std::array<unsigned int, 3> t = getTriangle(i);
        QVector3D tmp = QVector3D::crossProduct(getVertex(t[1]) - getVertex(t[0]), getVertex(t[2]) - getVertex(t[0]));
        normals[t[0]] += tmp;
        normals[t[1]] += tmp;
        normals[t[2]] += tmp;
    }
    Mesh::VertexData * v_buffer = new Mesh::VertexData[vertexCount()];
    for (unsigned int i = 0, sz = vertexCount(); i < sz; i++) {
        v_buffer[i].position = getVertex(i);
        v_buffer[i].normal = normals[i].normalized();
        v_buffer[i].texCoord = getUV(i);
    }
    vertexBuffer.bind();
    vertexBuffer.allocate((void *)v_buffer, vertexCount() * sizeof(Mesh::VertexData));
    delete[] v_buffer;
    GLuint * i_buffer = new GLuint[trianglesCount() * 3];
    for (unsigned int i = 0, sz = trianglesCount(); i < sz; i++) {
        i_buffer[i * 3] = getTriangle(i)[0];
        i_buffer[i * 3 + 1] = getTriangle(i)[1];
        i_buffer[i * 3 + 2] = getTriangle(i)[2];
    }
    indexBuffer.bind();
    indexBuffer.allocate((void *)i_buffer, trianglesCount() * 3 * sizeof(GLuint));
    delete[] i_buffer;
}

Mesh& Mesh::operator=(const Mesh& m) {
    V = m.V;
    UV = m.UV;
    T = m.T;
    return *this;
}

void Mesh::draw(QOpenGLShaderProgram *program) {
    vertexBuffer.bind();
    indexBuffer.bind();

    quintptr offset = 0;
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(Mesh::VertexData));

    offset += sizeof(QVector3D);
    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(Mesh::VertexData));

    offset += sizeof(QVector3D);
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(Mesh::VertexData));

    glDrawElements(GL_TRIANGLES, indexBuffer.size() / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}
