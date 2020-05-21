#ifndef HX_UTL_QUATERNION_H
#define HX_UTL_QUATERNION_H

#include "Vector.h"

class Quaternion {
    private:
        float w;
        float x;
        float y;
        float z;
    public:
        Quaternion();
        Quaternion(float w, float x, float y, float z);

        static const Quaternion Identity;

        float getMagnitude(void);
        void normalize(void);
        Quaternion operator * (Quaternion);
        // setters
        void setW(float w);
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        void set(float w, float x, float y, float z);
        // getters
        float getW();
        float getX();
        float getY();
        float getZ();
        // output
        void print(void);
        // get rotation in angle-axis representation
        void rotate(float angle, float x, float y, float z);
        float getAngle();
        Vector_f getAxis();
};

/* REFERENCES */
// http://www.cprogramming.com/tutorial/3d/quaternions.html

#endif
