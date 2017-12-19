#ifndef RAY_H
#define RAY_H

#include <array>
#include <QVector3D>

class Ray {

public:

    // Ray origin and direction
    QVector3D origin, direction;

    // Default constructor
    Ray() {}

    // Basic constructor
    Ray(const QVector3D& origin, const QVector3D& direction) :
        origin(origin), direction(direction) {}

    // Copy constuctor
    Ray(const Ray& r) : origin(r.origin), direction(r.direction) {}

    // Assignation operator
    Ray& operator=(const Ray& ray) {
        origin = ray.origin;
        direction = ray.direction;
        return *this;
    }

    // Returns a point at distance units along the ray
    QVector3D getPoint(float distance) const {
        return origin + direction.normalized() * distance;
    }

    // Get ray sign
    std::array<int, 3> sign() const {
        QVector3D inv = invertDirection();
        return { inv.x() < 0.0f ? 1 : 0, inv.y() < 0.0f ? 1 : 0, inv.z() < 0.0f ? 1 : 0 };
    }

    // Inverted direction
    QVector3D invertDirection() const {
        QVector3D dir = direction.normalized();
        return QVector3D(1.0f / dir.x(), 1.0f / dir.y(), 1.0f / dir.z());
    }

};

#endif // RAY_H
