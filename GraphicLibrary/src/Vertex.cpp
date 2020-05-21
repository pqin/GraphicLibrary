#include "Vertex.h"

VertexIndex::VertexIndex(){
    p = 0;
    n = 0;
    t = 0;
};
VertexIndex::VertexIndex(GLint p1, GLint n1, GLint t1){
    p = p1;
    n = n1;
    t = t1;
};

const VertexIndex VertexIndex::Zero = VertexIndex(0, 0, 0);

bool VertexIndex::operator==(const VertexIndex &b){
    if (p == b.p &&
        n == b.n &&
        t == b.t){
        return true;
    } else {
        return false;
    }
};
bool VertexIndex::operator!=(const VertexIndex &b){
    if (*this == b){
        return false;
    } else {
        return true;
    }
};

void VertexIndex::set(GLint p1, GLint n1, GLint t1){
    p = p1;
    n = n1;
    t = t1;
};
