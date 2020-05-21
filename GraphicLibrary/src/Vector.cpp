#include "Vector.h"

#include <cmath>

// constructors
Vector_f::Vector_f(){
    x = 0.f;
    y = 0.f;
    z = 0.f;
}
Vector_f::Vector_f(vec_t x, vec_t y, vec_t z){
    this->x = x;
    this->y = y;
    this->z = z;
}

// constants
const Vector_f Vector_f::Zero(0.f, 0.f, 0.f);
const Vector_f Vector_f::X_Axis(1.f, 0.f, 0.f);
const Vector_f Vector_f::Y_Axis(0.f, 1.f, 0.f);
const Vector_f Vector_f::Z_Axis(0.f, 0.f, 1.f);

void Vector_f::set(vec_t x, vec_t y, vec_t z){
    this->x = x;
    this->y = y;
    this->z = z;
}
void Vector_f::normalize(){
    static vec_t length;
    length = dotProduct(*this, *this);
    if (length > EPSILON && length != 1.f){
        length = sqrt( length );
        x = x / length;
        y = y / length;
        z = z / length;
    }
}
vec_t Vector_f::dotProduct(Vector_f e1, Vector_f e2){
    static vec_t dot;
    dot = (e1.x * e2.x) + (e1.y * e2.y) + (e1.z * e2.z);
    return dot;
}
Vector_f Vector_f::crossProduct(Vector_f e1, Vector_f e2){
   static Vector_f n;
   n.x = (e1.y * e2.z) - (e1.z * e2.y);
   n.y = (e1.z * e2.x) - (e1.x * e2.z);
   n.z = (e1.x * e2.y) - (e1.y * e2.x);
   return n;
}
Vector_f Vector_f::calculateNormal(Vector_f p1, Vector_f p2, Vector_f p3){
   static Vector_f n;
   static Vector_f e1, e2;
   e1 = p2 - p1;
   e2 = p3 - p1;

   n = Vector_f::crossProduct(e1, e2);
   n.normalize();
   return n;
}
/* Vector projection of e1 onto e2. */
Vector_f Vector_f::projection(Vector_f e1, Vector_f e2){
    static Vector_f proj;
    proj = e2 * (dotProduct(e1, e2) / dotProduct(e2, e2));
    return proj;
}

bool Vector_f::operator==(const Vector_f &e2){
    if (x == e2.x &&
        y == e2.y &&
        z == e2.z){
        return true;
    } else {
        return false;
    }
}
Vector_f Vector_f::operator+(const Vector_f &e2){
    static Vector_f sum;
    sum.x = x + e2.x;
    sum.y = y + e2.y;
    sum.z = z + e2.z;
    return sum;
}
Vector_f Vector_f::operator-(const Vector_f &e2){
    static Vector_f diff;
    diff.x = x - e2.x;
    diff.y = y - e2.y;
    diff.z = z - e2.z;
    return diff;
}
Vector_f Vector_f::operator*(const vec_t &C){
    static Vector_f product;
    product.x = C * x;
    product.y = C * y;
    product.z = C * z;
    return product;
}
Vector_f Vector_f::operator/(const vec_t &C){
    static Vector_f quotient;
    quotient.x = x / C;
    quotient.y = y / C;
    quotient.z = z / C;
    return quotient;
}

// Möller–Trumbore intersection algorithm
// Calculates ray - triangle intersection
bool Vector_f::intersects(vec_t *t, Vector_f o, Vector_f d, Vector_f p1, Vector_f p2, Vector_f p3){
    static Vector_f e1, e2;
    static vec_t a, u, v;

    static Vector_f s, h, q;
    static vec_t f, t0;
    // get edges
    e1 = p2 - p1;
    e2 = p3 - p1;

    // calculate determinant
    h = crossProduct(d, e2);
    a = dotProduct(e1, h);
    if (a > -EPSILON && a < EPSILON){
        return false;
    }
    f = 1.f/a;

    // calculate u
    s = o - p1;
    u = dotProduct(s, h) * f;
    if (u < 0.f || u > 1.f){
        return false;
    }

    // calculate v
    q = crossProduct(s, e1);
    v = dotProduct(d, q) * f;
    if (v < 0.0f || v > 1.0f){
        return false;
    }

    t0 = dotProduct(e2, q) * f;
    *t = t0;
    return true;
}
// Calculates ray - line segment intersection
bool Vector_f::intersects(vec_t *t, Vector_f o, Vector_f d, Vector_f p1, Vector_f p2){
    return false;
}
