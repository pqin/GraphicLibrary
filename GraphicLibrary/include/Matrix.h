#ifndef HX_UTL_MATRIX_H
#define HX_UTL_MATRIX_H

#include "Vector.h"

struct Matrix_f {
    vec_t A[16];

    // Constructors
    Matrix_f();
    Matrix_f(const vec_t *A);

    // Constants
    static const Matrix_f Zero;
    static const vec_t IDENT_TMP[];
    static const Matrix_f Identity;

    // Data Read/Write
    void set(vec_t *B);
    vec_t* get();

    // Operations
    Matrix_f operator*(const vec_t &C);
    Vector_f operator*(const Vector_f &v);
    Matrix_f operator*(Matrix_f &B);
    // Other Operations
    Matrix_f transpose();
};

#endif
