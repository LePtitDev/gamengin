#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include <cassert>
#include <QVector3D>

#include "ray.h"

class Triangle {

public:

    // Triangle vertex
    QVector3D a, b, c;

    // Default constructor
    Triangle() {}

    // Basic constructor
    Triangle(const QVector3D& a, const QVector3D& b, const QVector3D& c) :
        a(a), b(b), c(c) {}

    // Copy constructor
    Triangle(const Triangle& tr) : a(tr.a), b(tr.b), c(tr.c) {}

    // Assignation operator
    Triangle& operator=(const Triangle& tr) {
        a = tr.a;
        b = tr.b;
        c = tr.c;
        return *this;
    }

    // Access operator
    QVector3D& operator[](size_t i) {
        return *(&a + i);
    }

    // Access operator
    const QVector3D& operator[](size_t i) const {
        return *(&a + i);
    }

    // Indicate if triangle intersection
    bool intersect(const Ray& ray, float &t) const {
        const float EPSILON = 0.0000001f;
        QVector3D vertex0 = this->a;
        QVector3D vertex1 = this->b;
        QVector3D vertex2 = this->c;
        QVector3D edge1, edge2, h, s, q;
        float a,f,u,v;
        edge1 = vertex1 - vertex0;
        edge2 = vertex2 - vertex0;
        h = QVector3D::crossProduct(ray.direction, edge2);
        a = QVector3D::dotProduct(edge1, h);
        if (a > -EPSILON && a < EPSILON)
            return false;
        f = 1/a;
        s = ray.origin - vertex0;
        u = f * QVector3D::dotProduct(s, h);
        if (u < 0.0 || u > 1.0)
            return false;
        q = QVector3D::crossProduct(s, edge1);
        v = f * QVector3D::dotProduct(ray.direction, q);
        if (v < 0.0 || u + v > 1.0)
            return false;
        t = f * QVector3D::dotProduct(edge2, q);
        return (t > EPSILON);
    }

};

#endif // TRIANGLE_H
