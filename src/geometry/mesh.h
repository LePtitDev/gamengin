#ifndef MESH_H
#define MESH_H

#include <vector>
#include <array>

#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class Mesh : protected QOpenGLFunctions {

public:

    // Elements of vertex buffer
    struct VertexData {
        QVector3D position;
        QVector3D normal;
        QVector2D texCoord;
    };

private:

    // Vertex buffer
    QOpenGLBuffer vertexBuffer;

    // Triangle index buffer
    QOpenGLBuffer indexBuffer;

    // Vertex list
    std::vector<QVector3D> V, N;

    // UV coordinates list
    std::vector<QVector2D> UV;

    // Triangle indexs list
    std::vector<std::array<unsigned int, 3>> T;

public:

    // Basic constructor
    Mesh();

    // Destructor
    ~Mesh();

    // Get vertex count
    unsigned int vertexCount() const;

    // Get triangles count
    unsigned int trianglesCount() const;

    // Add a new vertex
    // Return the vertex ID
    unsigned int addVertex(const QVector3D& v, const QVector2D& uv);

    // Add a new triangle
    // Return the triangle ID
    unsigned int addTriangle(unsigned int a, unsigned int b, unsigned int c, bool addnormal = true);

    // Get a vertex
    QVector3D& getVertex(unsigned int i);

    // Get a vertex
    const QVector3D& getVertex(unsigned int i) const;

    // Get a normal
    QVector3D& getNormal(unsigned int i);

    // Get a normal
    const QVector3D& getNormal(unsigned int i) const;

    // Get a vertex UV coordinates
    QVector2D& getUV(unsigned int i);

    // Get a vertex UV coordinates
    const QVector2D& getUV(unsigned int i) const;

    // Get a triangle indexs
    std::array<unsigned int, 3>& getTriangle(unsigned int i);

    // Get a triangle indexs
    const std::array<unsigned int, 3>& getTriangle(unsigned int i) const;

    // Refresh buffers
    void refreshBuffers();

    // Assign operator
    Mesh& operator=(const Mesh& m);

    void draw(QOpenGLShaderProgram *program);

};

#endif // MESH_H
