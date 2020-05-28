#include "MyGL.h"
#include <glm/gtc/matrix_access.hpp>
#include <algorithm>
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
	double edge[3][3];
	for (int k = 0; k < 3; k++) {
		edge[k][0] = verts[k].position[1] - verts[(k + 1) % 3].position[1];
		edge[k][1] = verts[k].position[0] - verts[(k + 1) % 3].position[0];
		edge[k][2] = verts[k].position[0] * verts[(k + 1) % 3].position[1] - verts[(k + 1) % 3].position[0] * verts[k].position[1];
	}
	double area = 0.5 * (edge[0][2] + edge[1][2] + edge[2][2]);
	double rgb[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rgb[i][j] = 1 / (2 * area) * (verts[0].color[i] * edge[0][j] + verts[1].color[i] * edge[1][j] + verts[2].color[i] * edge[2][j]);
		}
	}
	double depth[3];
	for (int i = 0; i < 3; i++) {
		depth[i] = 1 / (2 * area) * (verts[0].position[2] * edge[0][i] + verts[1].position[2] * edge[1][i] + verts[2].position[2] * edge[2][i]);
	}
	double xmax = std::max(verts[0].position[0], std::max(verts[1].position[0], verts[2].position[0]));
	double xmin = std::min(verts[0].position[0], std::max(verts[1].position[0], verts[2].position[0]));
	double ymax = std::max(verts[0].position[1], std::max(verts[1].position[1], verts[2].position[1]));
	double ymin = std::min(verts[0].position[1], std::max(verts[1].position[1], verts[2].position[1]));
	for (int x = xmin; x <= xmax; x++) {
		for (int y = ymin; y <= ymax; y++) {
			double Exy[3];
			for (int i = 0; i < 3; i++) {
				Exy[i] = edge[i][0] * x + edge[i][1] * y + edge[i][2];
			}
			bool t[3];
			for (int j = 0; j < 3; j++) {
				if (edge[j][0] != 0) {
					t[j] = (edge[j][0] > 0);
				}
				else {
					t[j] = (edge[j][1] > 0);
				}
			}
			int triangle = 0;
			for (int i = 0; i < 3; i++) {
				if ((Exy[i] > 0) || t[i]) {
					triangle++;
				}
			}
			if (triangle == 3) { //삼각형 안에 있음
				glm::vec4 color;
				if (textureEnabled) {
					if (texture.id != 0) {
						// look up color in the texture
						//int x = v.texCoord[0] * (texture.width - 1);
						//int y = v.texCoord[1] * (texture.height - 1);
						color = texture.GetPixel(x, y, 0);
					}
				}
				else {
					for (int i = 0; i < 3; i++) {
						color[i] = rgb[i][0] * x + rgb[i][1] * y + rgb[i][2];
					}
				}
				if (depthTestEnabled) {
					double z = depth[0] * x + depth[1] * y + depth[2];
					if (z < frameBuffer.GetDepth(x, y)) {
						frameBuffer.SetDepth(x, y, z);
						frameBuffer.SetPixel(x, y, color);
					}
					
				}
				else {
					frameBuffer.SetPixel(x, y, color);
				}
			}
		}
	}
	/*
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
	*/

	


	return true;
}

