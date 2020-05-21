#include "Model.h"
#include "Material.h"

#include <fstream>
#include <sstream>

const std::string Model::emptyVT = "//";

Model::Model(){
    file = "";
    directory = "";
    scale = 1.f;
    center = Vector_f::Zero;
    smooth = true;
}
Model::~Model(){
    std::cout << "Destroyed model." << std::endl;
}

bool Model::load(const char *filename){
    bool status = false;
    std::ifstream in(filename);
    std::string objFile(filename);
    char separator = '\0';
    size_t pos = 0;

    status = in.is_open();
    if (status){
        file = objFile;
        directory = "";
        pos = objFile.find_last_of("/\\");
        if (pos != std::string::npos){
            file = objFile.substr(pos+1, std::string::npos);
            directory = objFile.substr(0, pos);
            separator = objFile.at(pos);
            directory.append(&separator, 1);
        }
        status = parse(&in);
    } else {
        std::cerr << "File could not be opened or could not be found." << std::endl;
    }
    if (in.is_open()){
        in.close();
    }
    return status;
}

std::string Model::getFilename(){
    return file;
}
std::string Model::getDirectory(){
    return directory;
}

Vector_f Model::getCenter(){
    return center;
}
float Model::getScale(){
    return scale;
}

float Model::calculateScale(std::vector<Vector_f> *v){
    if (v->empty()){
        return 1.f;
    }
    Vector_f min = (*v)[0];
    Vector_f max = (*v)[0];
    // find maximum and minimum values of vertex coordinates
    for (size_t i = 1; i < v->size(); ++i){
        // find minimum
        if (min.x > (*v)[i].x){
            min.x = (*v)[i].x;
        }
        if (min.y > (*v)[i].y){
            min.y = (*v)[i].y;
        }
        if (min.z > (*v)[i].z){
            min.z = (*v)[i].z;
        }
        // find maximum
        if (max.x < (*v)[i].x){
            max.x = (*v)[i].x;
        }
        if (max.y < (*v)[i].y){
            max.y = (*v)[i].y;
        }
        if (max.z < (*v)[i].z){
            max.z = (*v)[i].z;
        }
    }
    Vector_f diff;
    diff = max - min;
    float tempScale = diff.x;
    if (tempScale < diff.y){
        tempScale = diff.y;
    }
    if (tempScale < diff.z){
        tempScale = diff.z;
    }
    if (tempScale <= 0.f){
        tempScale = 1.f;
    }
    return tempScale;
}
Vector_f Model::calculateCenter(std::vector<Vector_f> *v){
    Vector_f tempCenter = Vector_f::Zero;
    Vector_f sum = Vector_f::Zero;
    if (!v->empty()){
        // find maximum and minimum values of vertex coordinates
        for (size_t i = 0; i < v->size(); ++i){
            sum = sum + (*v)[i];
        }
        tempCenter = sum / ((float)v->size());
    }
    return tempCenter;
}

void Model::draw(bool isTextured){
    static Colour ambient = material.getAmbient();
    static Colour diffuse = material.getDiffuse();
    static Colour specular = material.getSpecular();
    static const GLfloat shine = material.getShininess()*(128.f / 1000.f);
    static GLfloat amb[4], diff[4], spec[4];

    ambient.fillArray(amb);
    diffuse.fillArray(diff);
    specular.fillArray(spec);

    glColor3f(1.f, 1.f, 1.f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shine);

    static const GLuint texID = material.getTextureID();
    glDisable(GL_TEXTURE_2D);
    if (isTextured && texID > 0){
        glBindTexture(GL_TEXTURE_2D, texID);
        glEnable(GL_TEXTURE_2D);
    } else {
        isTextured = false;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    if (isTextured){
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, &uv[0]);
    }
    // send data
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normals[0]);
    // draw
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, &indices[0]);
    // disable client state
    if (isTextured){
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

bool Model::isSmooth(){
    return smooth;
}

void Model::dumpTo(std::ostream &os){
    os << "vertices:" << vertices.size() << '/' << (vertices.size()/3) << std::endl;
    os << "uv:" << uv.size() <<'/' << (uv.size()/2)<< std::endl;
    os << "normals:" << normals.size() <<'/' << (normals.size()/3)<< std::endl;
    os << "indices:" << indices.size() <<'/' << (indices.size()/3)<< std::endl;
    os << "scale:" << scale << std::endl;
    os << "center:" << center.x << ", " << center.y << ", " << center.z << std::endl;
    os << "material:" << material.getName() << "\tt:" << material.getTextureFile() << "\t" << material.getTextureID() << std::endl;

    for (size_t i = 0; i < vertices.size(); i+=3){
        os << "v " << vertices[i+0] << ' ' << vertices[i+1] << ' ' << vertices[i+2] << std::endl;
    }
    for (size_t i = 0; i < normals.size(); i+=3){
        os << "vn " << normals[i+0] << ' ' << normals[i+1] << ' ' << normals[i+2] << std::endl;
    }
    for (size_t i = 0; i < uv.size(); i+=2){
        os << "vt "<< uv[i+0] << ' ' << uv[i+1] << std::endl;
    }
    for (size_t i = 0; i < indices.size(); i+=3){
        os << "f " << indices[i+0] << '/' << indices[i+0] << '/' << indices[i+0];
        os << ' ' << indices[i+1] << '/' << indices[i+1] << '/' << indices[i+1];
        os << ' ' << indices[i+2] << '/' << indices[i+2] << '/' << indices[i+2] << std::endl;
    }
}

bool Model::parseFace(const unsigned int lineNum, std::string token, VertexIndex *vertex){
    using namespace std;

    static stringstream stream;
    static bool status;
    static int count = 0;
    static size_t pos = 0;

    stream.clear();
    stream.str(token);
    status = true;
    vertex->p = 0;
    vertex->t = 0;
    vertex->n = 0;
    count = 0;
    pos = 0;
    pos = token.find_first_of('/', pos);
    while (pos != 0 && pos != string::npos){
        ++count;
        pos = token.find_first_of('/', pos+1);
    }
    switch (count){
        case 0:
            // 'v'
            stream >> vertex->p;
            break;
        case 1:
            // 'v/vt'
            stream >> vertex->p;
            stream.ignore();
            stream >> vertex->t;
            break;
        case 2:
            if (token.find(emptyVT) != string::npos){
                // 'v//vn'
                stream >> vertex->p;
                stream.ignore();
                stream.ignore();
                stream >> vertex->n;
            } else {
                // 'v/vt/vn'
                stream >> vertex->p;
                stream.ignore();
                stream >> vertex->t;
                stream.ignore();
                stream >> vertex->n;
            }
            break;
        default:
            cerr << "OBJ syntax error:f:" << lineNum << ": Too many slashes in token. " << endl;
            status = false;
    }
    if (vertex->p == 0){
        cerr << "OBJ syntax error:f:" << lineNum << ": Missing v index. Count:" << count << endl;
        status = false;
    }
    return status;
}

bool Model::parse(std::ifstream *in){
    using namespace std;

    bool status = true;
    /* Data structures representing .OBJ model data.
     * v: vertex coordinates, array of Vector_f(x,y,z)s
     * vt: texture coordinates, array of Vector_f(x,y,z)s
     * vn: vertex normals, array of Vector_f(x,y,z)s
     * f: faces, array of faces(array of Vector_f(v,vt,vn)s)
     *    f[i] = single face/polygon, array of Vector_f(v,vt,vn)s
     */
    vector<Vector_f> v;
    vector<Vector_f> vt;
    vector<Vector_f> vn;
    /* Temporary variables */
    Vector_f tempVector, p0, p1, p2;
    vector<GLuint> tempFace;
    VertexIndex vertex;
    GLuint index = 0;
    /* Parse OBJ file. */
    unsigned int lineNum = 0;  // line numbers, number of lines read
    string fileLine;
    stringstream stream;
    string lineID;
    string token;
    string matFile;
    string matName;
    int tokenCount;
    GLuint vTmpIndex;
    bool faceGood = false;
    // Initialize default material
    material = Material::Default;
    vector<Material> materials;

    while (in->good()){
        // read line from OBJ file
        getline(*in, fileLine);
        if (in->good()){
            ++lineNum;
            // put line read into stringstream
            stream.clear();
            stream.str("");
            stream << fileLine;
            // clear Material variables
            matFile = "";

            // get first token: line identifier
            lineID = "";
            stream >> lineID;
            if (lineID == "v"){
                tempVector.set(0, 0, 0);
                stream >> tempVector.x >> tempVector.y >> tempVector.z;
                v.push_back(tempVector);
            } else if (lineID == "vt"){
                tempVector.set(0, 0, 0);
                stream >> tempVector.x >> tempVector.y >> tempVector.z;
                tempVector.y = 1.f - tempVector.y;
                vt.push_back(tempVector);
            } else if (lineID == "vn"){
                tempVector.set(0, 0, 0);
                stream >> tempVector.x >> tempVector.y >> tempVector.z;
                tempVector.normalize();
                vn.push_back(tempVector);
            } else if (lineID == "f"){
                tempFace.clear();
                token = "";
                faceGood = true;
                tokenCount = 0;
                if (!stream.good()){
                    // no more input, line is too short
                    cerr << "OBJ syntax error:f:" << lineNum << ": Insufficient tokens: " << tokenCount << endl;
                    faceGood = false;
                }
                // parse each token in line
                while (stream.good()){
                    // read face tokens as strings
                    token = "";
                    stream >> token;
                    if (token != ""){
                        ++tokenCount;
                        // split along any delimiters
                        if (parseFace(lineNum, token, &vertex)){
                            // convert negative indices
                            if (vertex.p < 0){
                                vertex.p = v.size()  + vertex.p + 1;
                            }
                            if (vertex.t < 0){
                                vertex.t = vt.size() + vertex.t + 1;
                            }
                            if (vertex.n < 0){
                                vertex.n = vn.size() + vertex.n + 1;
                            }
                            // check that indices are within bounds
                            // insert if they are
                            if (vertex.p > 0 && vertex.p <= (int)v.size()){
                                tempFace.push_back((GLuint)vertex.p);
                            }
                            if (vertex.t > 0 && vertex.t <= (int)vt.size()){
                                tempFace.push_back((GLuint)vertex.t);
                            } else {
                                tempFace.push_back(0);
                            }
                            if (vertex.n > 0 && vertex.n <= (int)vn.size()){
                                tempFace.push_back((GLuint)vertex.n);
                            } else {
                                tempFace.push_back(0);
                            }
                        } else {
                            faceGood = false;
                        }
                    }
                }
                // minimum of three vertices constitute a face
                if (tokenCount < 3){
                    cerr << "OBJ syntax error:f:" << lineNum << ": Insufficient tokens: " << tokenCount << endl;
                    faceGood = false;
                }
                // push accumulated vectors
                if (faceGood){
                    // break polygon into triangles; triangle fan
                    for (int ftc = 0; ftc < tokenCount - 2; ++ftc){
                        // insert indices
                        indices.push_back(index);
                        indices.push_back(index+ftc+1);
                        indices.push_back(index+ftc+2);
                    }
                    index += tokenCount;
                    // calculate normal
                    vTmpIndex = tempFace[(0*3)+0] - 1;
                    p0.set(v[vTmpIndex].x, v[vTmpIndex].y, v[vTmpIndex].z);
                    vTmpIndex = tempFace[(1*3)+0] - 1;
                    p1.set(v[vTmpIndex].x, v[vTmpIndex].y, v[vTmpIndex].z);
                    vTmpIndex = tempFace[(2*3)+0] - 1;
                    p2.set(v[vTmpIndex].x, v[vTmpIndex].y, v[vTmpIndex].z);
                    tempVector = Vector_f::calculateNormal(p0, p1, p2);
                    // insert data
                    for (int i = 0; i < tokenCount; ++i){
                        // insert position
                        vTmpIndex = tempFace[(i*3)+0] - 1;
                        if (vTmpIndex >= 0 && vTmpIndex < v.size()){
                            vertices.push_back(v[vTmpIndex].x);
                            vertices.push_back(v[vTmpIndex].y);
                            vertices.push_back(v[vTmpIndex].z);
                        }
                        // insert texture coordinates
                        vTmpIndex = tempFace[(i*3)+1] - 1;
                        if (vTmpIndex >= 0 && vTmpIndex < vt.size()){
                            uv.push_back(vt[vTmpIndex].x);
                            uv.push_back(vt[vTmpIndex].y);
                        }
                        // insert normal
                        vTmpIndex = tempFace[(i*3)+2] - 1;
                        if (vTmpIndex >= 0 && vTmpIndex < vn.size()){
                            normals.push_back(vn[vTmpIndex].x);
                            normals.push_back(vn[vTmpIndex].y);
                            normals.push_back(vn[vTmpIndex].z);
                        } else {
                            normals.push_back(tempVector.x);
                            normals.push_back(tempVector.y);
                            normals.push_back(tempVector.z);
                        }
                    }

                    // clear temporary index array
                    tempFace.clear();
                } else {
                    status = false;
                }
            } else if (lineID == "mtllib"){
                matFile = "";
                stream >> matFile;
                matFile = directory + matFile;
                loadMatLib(matFile.c_str(), &materials);
            } else if (lineID == "usemtl"){
                matName = material.getName();
                stream >> matName;
                if (matName.compare(material.getName()) != 0){
                    // search for material with matching name
                    for (size_t i = 0; i < materials.size(); ++i){
                        if (matName.compare(materials[i].getName()) == 0){
                            material = materials[i];
                        }
                    }
                }
            } else if (lineID == "s"){
                token = "";
                stream >> token;
                if (token == "1" || token == "on"){
                    smooth = true;
                } else if (token == "0" || token == "off") {
                    smooth = false;
                }
                token = "";
            } else {
                // unsupported/unknown line identifier, ignore
                // may just be blank line
                continue;
            }
        }
    }

    scale = calculateScale(&v);
    center = calculateCenter(&v);
    // scale vertices while keeping normals the same
    for (size_t i = 0; i < vertices.size(); ++i){
        vertices[i] = vertices[i] / scale;
    }

    return status;
}
bool Model::loadMatLib(const char *filename, std::vector<Material> *materials){
    bool status = false;
    std::ifstream in(filename);

    std::cout << "Opening material file '" << filename << "'...";
    status = in.is_open();
    if (status){
        std::cout << "OK" << std::endl;
        parseMaterial(&in, materials);
    } else {
        std::cout << "failed" << std::endl;
    }
    if (in.is_open()){
        in.close();
    }
    return status;
}
bool Model::parseMaterial(std::ifstream *in, std::vector<Material> *materials){
    using namespace std;

    static stringstream stream;
    static string fileLine;
    static string lineID;
    static size_t matCount;

    static Material mat;
    static Colour colour;
    static string matName, texName;
    static float r, g, b, a;

    matCount = 0;
    while (in->good()){
        // read line from OBJ file
        getline(*in, fileLine);
        if (in->good()){
            // put line read into stringstream
            stream.clear();
            stream.str("");
            stream << fileLine;
            // clear tokens
            lineID = "";
            matName = "";
            texName = "";
            r = 0.f;
            g = 0.f;
            b = 0.f;
            a = 1.f;
            // get line type
            stream >> lineID;
            if (lineID == "newmtl"){    // new material
                if (matCount > 0){
                    materials->push_back(mat);
                }
                stream >> matName;
                mat.setName(matName);
                ++matCount;
            } else if (lineID == "Ka"){
                stream >> r >> g >> b;
                colour.set(r, g, b);
                mat.setAmbient(colour);
            } else if (lineID == "Kd"){
                stream >> r >> g >> b;
                colour.set(r, g, b);
                mat.setDiffuse(colour);
            } else if (lineID == "Ks"){
                stream >> r >> g >> b;
                colour.set(r, g, b);
                mat.setSpecular(colour);
            } else if (lineID == "Ns"){
                stream >> r;
                mat.setShininess(r);
            } else if (lineID == "map_Kd"){
                stream >> texName;
                mat.setTextureFile( (directory + texName) );
            } else if (lineID == "d"){
                stream >> a;
                mat.setAlpha(a);
            }
        }
    }
    if (matCount > 0){
        materials->push_back(mat);
    }

    return true;
}

std::vector<std::string> Model::getTextureFiles(){
    std::vector<std::string> files;
    std::string file = "";
    Material material0 = Material::Default;
    std::string texFile0 = material0.getTextureFile();
    std::string texFile1 = material.getTextureFile();
    if (texFile0.compare(texFile1) != 0){
        files.push_back(texFile1);
    }
    return files;
}
void Model::setTexture(std::string file, GLuint id){
    std::string tName = "";
    tName = material.getTextureFile();
    if (file.compare( tName ) == 0){
        material.setTextureID(id);
    }
}
