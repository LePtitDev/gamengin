#ifndef BOUNDS_H
#define BOUNDS_H

#include "ray.h"

#include <cmath>
#include <QVector3D>

class Bounds {

public:

    // Bounds center and size
    QVector3D center, size;

    // Default constructor
    Bounds() {}

    // Assign constructor
    Bounds(const QVector3D& center, const QVector3D& size) :
        center(center), size(size) {}

    // Copy constructor
    Bounds(const Bounds& b) : center(b.center), size(b.size) {}

    // Assignation operator
    Bounds& operator=(const Bounds& box) {
        center = box.center;
        size = box.size;
        return *this;
    }

    // Half size of bounds
    QVector3D extents() const {
        return size * 0.5f;
    }

    // Max point of box
    QVector3D max() const {
        return center + extents();
    }

    // Min point of box
    QVector3D min() const {
        return center - extents();
    }

    // The closest point on the bounding box
    QVector3D closestPoint(const QVector3D& point) const {
        QVector3D result = point, _min = min(), _max = max();
        for (int i = 0; i < 3; i++) {
            if (point[i] < _min[i]) result[i] = _min[i];
            else if (point[i] > _max[i]) result[i] = _max[i];
        }
        return result;
    }

    // Is point contained in the bounding box ?
    bool contains(const QVector3D& point) const {
        QVector3D _max = max(), _min = min();
        return _min.x() >= point.x() && point.x() <= _max.x() &&
               _min.y() >= point.y() && point.y() <= _max.y() &&
               _min.z() >= point.z() && point.z() <= _max.z();
    }

    // Grows the Bounds to include the point
    void encapsulate(const QVector3D& point) {
        QVector3D _max = max(), _min = min();
        if (point.x() < _min.x()) _min.setX(point.x());
        if (point.y() < _min.y()) _min.setY(point.y());
        if (point.z() < _min.z()) _min.setZ(point.z());
        if (point.x() > _max.x()) _max.setX(point.x());
        if (point.y() > _max.y()) _max.setY(point.y());
        if (point.z() > _max.z()) _max.setZ(point.z());
        center = (_max + _min) * 0.5f;
        size = _max - _min;
    }

    // Expand the bounds by increasing its size by amount along each side
    void expand(const QVector3D& amount) {
        size += amount;
    }

    // Does ray intersect this bounding box ?
    bool intersectRay(const Ray& ray, float& distance) const {
        QVector3D param[2] = { min(), max() }, inv_dir = ray.invertDirection();
        std::array<int, 3> sign = ray.sign();
        float tmin, tmax, tymin, tymax, tzmin, tzmax;
        tmin = (param[sign[0]].x() - ray.origin.x()) * inv_dir.x();
        tmax = (param[1 - sign[0]].x() - ray.origin.x()) * inv_dir.x();
        tymin = (param[sign[1]].y() - ray.origin.y()) * inv_dir.y();
        tymax = (param[1 - sign[1]].y() - ray.origin.y()) * inv_dir.y();
        if ((tmin > tymax) || (tymin > tmax))
            return false;
        if (tymin > tmin)
            tmin = tymin;
        if (tymax < tmax)
            tmax = tymax;
        tzmin = (param[sign[2]].z() - ray.origin.z()) * inv_dir.z();
        tzmax = (param[1 - sign[2]].z() - ray.origin.z()) * inv_dir.z();
        if ((tmin > tzmax) || (tzmin > tmax))
            return false;
        if (tzmin > tmin)
            tmin = tzmin;
        if (tzmax < tmax)
            tmax = tzmax;

        distance = contains(ray.origin) ? 0.0f : tmin;
        return true;
    }

    // Does another bounding box intersect with this bounding box ?
    bool intersects(const Bounds& box) {
        QVector3D a = min(), b = box.min();
        return (std::abs(a.x() - b.x()) * 2.0f < (size.x() + box.size.x())) &&
               (std::abs(a.y() - b.y()) * 2.0f < (size.y() + box.size.y()));
    }

    // The smallest distance between the point and this bounding box
    float distance(const QVector3D& point) {
        return (closestPoint(point) - point).length();
    }

};

#endif // BOUNDS_H
