#ifndef HX_UTL_VECTOR_H
#define HX_UTL_VECTOR_H

#include "CommonConstants.h"

// internal type of Vector_f
typedef float vec_t;

/*
    Vector
*/
struct Vector_f {
    vec_t x;
    vec_t y;
    vec_t z;

    Vector_f();
    Vector_f(vec_t x, vec_t y, vec_t z);

    static const Vector_f Zero;
    static const Vector_f X_Axis;
    static const Vector_f Y_Axis;
    static const Vector_f Z_Axis;

    static vec_t dotProduct(Vector_f e1, Vector_f e2);
    static Vector_f crossProduct(Vector_f e1, Vector_f e2);
    static Vector_f calculateNormal(Vector_f p1, Vector_f p2, Vector_f p3);
    static Vector_f projection(Vector_f e1, Vector_f e2);
    // ray - triangle intersection
    static bool intersects(vec_t *t, Vector_f o, Vector_f d, Vector_f p1, Vector_f p2, Vector_f p3);
    // ray - line segment intersection
    static bool intersects(vec_t *t, Vector_f o, Vector_f d, Vector_f p1, Vector_f p2);

    bool operator==(const Vector_f &e2);
    Vector_f operator+(const Vector_f &e2);
    Vector_f operator-(const Vector_f &e2);
    Vector_f operator*(const vec_t &C);
    Vector_f operator/(const vec_t &C);

    void set(vec_t x2, vec_t y2, vec_t z2);
    void normalize();
};

typedef Vector_f Vertex_f;

#endif
