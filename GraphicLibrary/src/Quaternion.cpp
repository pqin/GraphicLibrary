#include "Quaternion.h"
#include "CommonConstants.h"

#include <iostream>
#include <cmath>

Quaternion::Quaternion(){
    x = 0;
    y = 0;
    z = 0;
    w = 1;
};
Quaternion::Quaternion(float w, float x, float y, float z){
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
};

const Quaternion Quaternion::Identity = Quaternion(1.f, 0.f, 0.f, 0.f);

float Quaternion::getMagnitude(){
    float magnitude = sqrt((x*x)+(y*y)+(z*z)+(w*w));
    return magnitude;
};
void Quaternion::normalize(){
    float magnitude = sqrt((x*x)+(y*y)+(z*z)+(w*w));
    if (magnitude > 0.f){
        x = x / magnitude;
        y = y / magnitude;
        z = z / magnitude;
        w = w / magnitude;
    }
};
Quaternion Quaternion::operator* (Quaternion Q2){
    static Quaternion temp;
    temp.w = (w*Q2.w) - (x*Q2.x) - (y*Q2.y) - (z*Q2.z);
    temp.x = (w*Q2.x) + (x*Q2.w) + (y*Q2.z) - (z*Q2.y);
    temp.y = (w*Q2.y) - (x*Q2.z) + (y*Q2.w) + (z*Q2.x);
    temp.z = (w*Q2.z) + (x*Q2.y) - (y*Q2.x) + (z*Q2.w);

    return temp;
};
void Quaternion::rotate(float angle, float vx, float vy, float vz){
    // convert degrees to radians
    angle = angle * ((float)PI / 360.f);
    float sine = sin( angle );
    float cosine = cos( angle );

    // normalize vector
    float length = sqrt((vx*vx)+(vy*vy)+(vz*vz));
    if (length > 0.f){
        vx = vx / length;
        vy = vy / length;
        vz = vz / length;
        // new quaternion
        w = cosine;
        x = vx * sine;
        y = vy * sine;
        z = vz * sine;
    }
};

void Quaternion::setW(float w){
    this->w = w;
};
void Quaternion::setX(float x){
    this->x = x;
};
void Quaternion::setY(float y){
    this->y = y;
};
void Quaternion::setZ(float z){
    this->z = z;
};
void Quaternion::set(float w, float x, float y, float z){
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
};
float Quaternion::getW(){
    return w;
};
float Quaternion::getX(){
    return x;
};
float Quaternion::getY(){
    return y;
};
float Quaternion::getZ(){
    return z;
};
void Quaternion::print(void){
    using namespace std;
    cout << w << ' ' << x << ' ' << y << ' ' << z << " (" << getMagnitude() << ')' << endl;
};
// convert to rotation matrix as angle-axis representation
float Quaternion::getAngle(){
    float angle = acos(w)*2.f;
    return angle;
};
Vector_f Quaternion::getAxis(){
    Vector_f axis;
    if (getAngle() != 0.f){
        axis.set(x, y, z);
        axis.normalize();
    }
    return axis;
};
