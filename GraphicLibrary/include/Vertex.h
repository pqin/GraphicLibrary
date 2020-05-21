#ifndef HX_UTL_VERTEX_H
#define HX_UTL_VERTEX_H

#include <windows.h>
#include <GL/gl.h>

struct Vertex {
	GLfloat px;	// position
	GLfloat py;
	GLfloat pz;
	GLfloat nx;	// normal
	GLfloat ny;
	GLfloat nz;
	GLfloat tu;	// texture
	GLfloat tv;
};

struct VertexIndex {
	GLint p;	// position
	GLint n;	// normal
	GLint t;	// texture

	VertexIndex();
	VertexIndex(GLint p1, GLint n1, GLint t1);

	static const VertexIndex Zero;

	bool operator==(const VertexIndex& b);
	bool operator!=(const VertexIndex& b);

	void set(GLint p1, GLint n1, GLint t1);
};

#endif
