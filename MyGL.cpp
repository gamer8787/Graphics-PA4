#include "MyGL.h"
#include <glm/gtc/matrix_access.hpp>
//------------------------------------------------------------------------------
MyGL::MyGL()
    :
    _doTriangulate( false ),
    _doRasterize( false ) {
}

//------------------------------------------------------------------------------
MyGL::~MyGL()
{}

//------------------------------------------------------------------------------
bool MyGL::TriangulatePolygon( const vector<GLVertex> &polygonVerts,
                               vector<GLVertex> &triangleVerts ) {
    if( !_doTriangulate )
        return false;

    //
    // YOUR CODE HERE
    //

    // Implement triangulation here.
    // Keep in mind that the color of the first scene (F1) will depend on your implementation.
    // You must set it right so that it should not feel so "glitchy".

    // just make a triangle out of the first three vertices for now

	if (polygonVerts.size() >= 3) {
		/*
		triangleVerts.push_back( polygonVerts[0] );
		triangleVerts.push_back( polygonVerts[1] );
		triangleVerts.push_back( polygonVerts[2] );
		*/
		for (int i = 0; i <= polygonVerts.size() - 3; i++) {
			triangleVerts.push_back(polygonVerts[0]);
			triangleVerts.push_back(polygonVerts[i + 1]);
			triangleVerts.push_back(polygonVerts[i + 2]);
		}
		return true;

	}
	else {
        return true;
    }
}

//------------------------------------------------------------------------------
bool MyGL::RasterizeTriangle(GLVertex verts[3]) {
	if (!_doRasterize)
		return false;

	//
	// YOUR CODE HERE
	//

	// Implement rasterization here. You are NOT required to implement wireframe mode (i.e. 'w' key mode).

	// just render the vertices for now
	for (int i = 0; i < 3; i++) {
		GLVertex &v = verts[i];
		glm::vec4 color;
		if (textureEnabled) {
			if (texture.id != 0) {
				// look up color in the texture
				int x = v.texCoord[0] * (texture.width - 1);
				int y = v.texCoord[1] * (texture.height - 1);
				color = texture.GetPixel(x, y, 0);
			}
		}
		else
			color = v.color;

		frameBuffer.SetPixel(v.position[0], v.position[1], color);

		// depthTestEnabled is 0 if the polygon forms a background.
		// depthTestEnabled is 1 otherwise.
		if (depthTestEnabled)
			frameBuffer.SetDepth(v.position[0], v.position[1], v.position[2]);
	}


	return true;
}

