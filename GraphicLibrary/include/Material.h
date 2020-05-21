#ifndef HX_UTL_MATERIAL_H
#define HX_UTL_MATERIAL_H

#include <iostream>
#include <string>
#include <windows.h>
#include <GL/gl.h>

#include "Colour.h"

class Material {
private:
    std::string name;
    Colour ambient;
    Colour diffuse;
    Colour specular;
    float shininess;
    float alpha;
    std::string textureFile;
    GLuint textureID;
public:
    Material();
    Material(std::string matName);
    Material(std::string matName, Colour ambient, Colour diffuse, Colour specular);

    static const Material Default;
    static const float Shine;

    void setName(std::string matName);
    void setAmbient(Colour ambient);
    void setDiffuse(Colour diffuse);
    void setSpecular(Colour specular);
    void setShininess(float shininess);
    void setAlpha(float alpha);
    void setTextureFile(std::string texFile);
    void setTextureID(GLuint texID);

    std::string getName();
    Colour getAmbient();
    Colour getDiffuse();
    Colour getSpecular();
    float getShininess();
    float getAlpha();
    std::string getTextureFile();
    GLuint getTextureID();
};

/* A group of continuous faces sharing a common material. */
struct MatGroup {
    size_t mat; // index of material
    size_t offset;  // starting offset into faces
    size_t len; // number of faces
};

#endif
