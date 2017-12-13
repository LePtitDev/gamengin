#ifndef SHAPES_H
#define SHAPES_H

#include "../gameobject/geometry.h"

#include <QImage>

// Create a cube mesh
void GeometryCube(const char * name);

// Create a plane mesh
void GeometryPlane(const char * name);

// Create a plane mesh
void GeometryUIPlane(const char * name);

// Create a terrain mesh by a heightmap
void GeometryTerrain(const char * name, const QImage& heightmap);

#endif // SHAPES_H
