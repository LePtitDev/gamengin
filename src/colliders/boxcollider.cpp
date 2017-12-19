#include <limits>

#include "boxcollider.h"
#include "../geometry/triangle.h"

bool BoxCollider::intersectRay(const Ray &ray, float &distance) const {
    Transform& transform = gameObject().transform();
    Bounds bound;
    bound.center = transform.position + transform.rotation * offset;
    QVector3D halfSize = size * 0.5f;
    QVector3D points[] = {
        transform.position + transform.rotation * (offset - QVector3D(-halfSize.x(), -halfSize.y(), -halfSize.z())),
        transform.position + transform.rotation * (offset - QVector3D(-halfSize.x(), -halfSize.y(),  halfSize.z())),
        transform.position + transform.rotation * (offset - QVector3D(-halfSize.x(),  halfSize.y(), -halfSize.z())),
        transform.position + transform.rotation * (offset - QVector3D(-halfSize.x(),  halfSize.y(),  halfSize.z())),
        transform.position + transform.rotation * (offset - QVector3D( halfSize.x(), -halfSize.y(), -halfSize.z())),
        transform.position + transform.rotation * (offset - QVector3D( halfSize.x(), -halfSize.y(),  halfSize.z())),
        transform.position + transform.rotation * (offset - QVector3D( halfSize.x(),  halfSize.y(), -halfSize.z())),
        transform.position + transform.rotation * (offset - QVector3D( halfSize.x(),  halfSize.y(),  halfSize.z()))
    };
    for (auto p : points)
        bound.encapsulate(p);
    if (!bound.intersectRay(ray, distance))
        return false;

    Triangle triangles[12] = {
        Triangle(points[0], points[1], points[2]),
        Triangle(points[1], points[2], points[3]),
        Triangle(points[0], points[1], points[4]),
        Triangle(points[1], points[4], points[5]),
        Triangle(points[0], points[2], points[4]),
        Triangle(points[2], points[4], points[6]),
        Triangle(points[1], points[3], points[7]),
        Triangle(points[1], points[5], points[7]),
        Triangle(points[2], points[3], points[7]),
        Triangle(points[2], points[6], points[7]),
        Triangle(points[4], points[5], points[7]),
        Triangle(points[4], points[6], points[7])
    };
    distance = std::numeric_limits<float>::max();
    bool intersection = false;
    for (int i = 0; i < 12; i++) {
        float dist;
        if (triangles[i].intersect(ray, dist)) {
            intersection = true;
            if (distance > dist)
                distance = dist;
        }
    }
    return intersection;
}
