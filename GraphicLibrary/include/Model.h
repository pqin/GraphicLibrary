#ifndef HX_UTL_MODEL_H
#define HX_UTL_MODEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <Windows.h>
#include <GL/gl.h>

#include "Vector.h"
#include "Vertex.h"
#include "Material.h"

/* Support only one material and/or texture per model.
 * Optimize to draw hi-res models efficiently.
 */
class Model {
private:
    std::string file;
    std::string directory;    // file directory, all file-specified directories relative to this
    // data
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> uv;
    std::vector<GLuint> indices;
    // material
    Material material;
    // smooth or flat shading
    bool smooth;

    // Derived model data: center and scale factor
    Vector_f center;
    float scale;
    /* constants */
    static const std::string emptyVT; // used to identify 'v//vn' token, empty vertex texture index
    /* helper functions */
    bool parse(std::ifstream *in);
    bool parseFace(const unsigned int lineNum, std::string token, VertexIndex *vertex);
    // material file
    bool loadMatLib(const char *filename, std::vector<Material> *materials);
    bool parseMaterial(std::ifstream *in, std::vector<Material> *materials);

    float calculateScale(std::vector<Vector_f> *v);
    Vector_f calculateCenter(std::vector<Vector_f> *v);
public:
    Model();
    ~Model();

    bool load(const char *filename);
    std::string getFilename();
    std::string getDirectory();
    void draw(bool isTextured);
    void dumpTo(std::ostream &os);
    // texture
    std::vector<std::string> getTextureFiles();
    void setTexture(std::string file, GLuint id);
    // calculated data
    Vector_f getCenter();
    float getScale();
    bool isSmooth();
};

#endif
