#include "Material.h"

Material::Material(){
    name = "untitled";
    shininess = Shine;
    alpha = 1.f;
    textureFile = "";
    textureID = 0;
}
Material::Material(std::string matName){
    name = matName;
    shininess = Shine;
    alpha = 1.f;
    textureFile = "";
    textureID = 0;
}
Material::Material(std::string matName, Colour ambient, Colour diffuse, Colour specular){
    name = matName;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    shininess = Shine;
    alpha = 1.f;
    textureFile = "";
    textureID = 0;
}

const float Material::Shine = 100.f;
const Material Material::Default = Material("default",
                                            Colour::Grey50, // ambient
                                            Colour::Grey50, // diffuse
                                            Colour::Grey25);// specular

void Material::setName(std::string matName){
    name = matName;
}
void Material::setAmbient(Colour ambient){
    this->ambient = ambient;
}
void Material::setDiffuse(Colour diffuse){
    this->diffuse = diffuse;
}
void Material::setSpecular(Colour specular){
    this->specular = specular;
}
void Material::setShininess(float shininess){
    if (shininess < 0.f){
        shininess = 0.f;
    } else if (shininess > 1000.f){
        shininess = 1000.f;
    }
    this->shininess = shininess;
}
void Material::setAlpha(float alpha){
    if (alpha > 1.f){
        alpha = 1.f;
    } else if (alpha < 0.f){
        alpha = 0.f;
    }
    this->alpha = alpha;
}
void Material::setTextureFile(std::string texFile){
    textureFile = texFile;
}
void Material::setTextureID(GLuint texID){
    textureID = texID;
}

std::string Material::getName(){
    return name;
}
Colour Material::getAmbient(){
    return ambient;
}
Colour Material::getDiffuse(){
    return diffuse;
}
Colour Material::getSpecular(){
    return specular;
}
float Material::getShininess(){
    return shininess;
}
float Material::getAlpha(){
    return alpha;
}
std::string Material::getTextureFile(){
    return textureFile;
}
GLuint Material::getTextureID(){
    return textureID;
}
