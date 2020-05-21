#include "Matrix.h"

#include <iostream>
#include <cstring>

Matrix_f::Matrix_f(){
    std::fill(A, A+16, 0.f);
}
Matrix_f::Matrix_f(const vec_t *A){
    memcpy(this->A, A, 16*sizeof(vec_t));
}

const Matrix_f Matrix_f::Zero;
const vec_t Matrix_f::IDENT_TMP[] = {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
};
const Matrix_f Matrix_f::Identity(IDENT_TMP);

void Matrix_f::set(vec_t *B){
    memcpy(A, B, 16*sizeof(vec_t));
}
vec_t* Matrix_f::get(){
    return this->A;
}

Matrix_f Matrix_f::operator*(const vec_t &C){
    static vec_t B[16];
    memcpy(B, A, 16*sizeof(vec_t));

    for (size_t i = 0; i < 16; ++i){
        B[i] = C*B[i];
    }
    return B;
}
Vector_f Matrix_f::operator*(const Vector_f &v){
    static Vector_f b, translation;

    b.x = (A[0]*v.x) + (A[4]*v.y) + (A[8]*v.z);
    b.y = (A[1]*v.x) + (A[5]*v.y) + (A[9]*v.z);
    b.z = (A[2]*v.x) + (A[6]*v.y) + (A[10]*v.z);

    translation.set(A[12], A[13], A[14]);

    b = b + translation;
    return b;
}
Matrix_f Matrix_f::operator*(Matrix_f &B){
    static Matrix_f M;
    static vec_t C[16];

    vec_t *bData = B.get();
    std::fill(C, C+16, 0.f);

    for (size_t r = 0; r < 4; ++r){
        for (size_t c = 0; c < 4; ++c){
            // for each entry C_rc
            C[(r*4)+c] = bData[(r*4)+0] * A[(0*4)+c];
            for (size_t k = 1; k < 4; ++k){
                C[(r*4)+c] += ( bData[(r*4)+k] * A[(k*4)+c] );
            }
        }
    }

    M.set(C);
    return M;
}

Matrix_f Matrix_f::transpose(){
    static Matrix_f T;
    static vec_t At[16];
    for (size_t r = 0; r < 4; ++r){
        for (size_t c = 0; c < 4; ++c){
            At[(r*4)+c] = A[(c*4)+r];
        }
    }
    T.set(At);
    return T;
}
