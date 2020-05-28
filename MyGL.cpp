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
	double edge01[3],  edge12[3], edge20[3];
	double edge[3][3];
	GLVertex& v0 = verts[0];
	GLVertex& v1 = verts[1];
	GLVertex& v2 = verts[2];
	for (int k = 0; k < 3; k++) {
		edge[k][0] = verts[k].position[1] - verts[(k + 1) % 3].position[1];
		edge[k][1] = verts[k].position[0] - verts[(k + 1) % 3].position[0];
		edge[k][2] = verts[k].position[0] * verts[(k + 1) % 3].position[1] - verts[(k + 1) % 3].position[0] * verts[k].position[1];
	}
	edge01[0] = v0.position[1] - v1.position[1];	
	edge01[1] = v0.position[0] - v1.position[0];	
	edge01[2] = v0.position[0] * v1.position[1] - v1.position[0] * v0.position[1];	
	edge12[0] = v1.position[1] - v2.position[1];	
	edge12[1] = v1.position[0] - v2.position[0];	
	edge12[2] = v1.position[0] * v2.position[1] - v2.position[0] * v1.position[1];
	edge20[0] = v2.position[1] - v0.position[1];	
	edge20[1] = v2.position[0] - v0.position[0];	
	edge20[2] = v2.position[0] * v0.position[1] - v0.position[0] * v2.position[1];
	double area = 0.5 * (edge01[2] + edge12[2] + edge20[2]);
	glm::vec4 color0;
	glm::vec4 color1;
	glm::vec4 color2;

	color0 = v0.color;
	color1 = v1.color;
	color2 = v2.color;

	double Arred = 1 / (2 * area) * (color0[0] * edge01[0] + color1[0] * edge12[0] + color2[0] * edge20[0]);
	double Brred = 1 / (2 * area) * (color0[0] * edge01[1] + color1[0] * edge12[1] + color2[0] * edge20[1]);
	double Crred = 1 / (2 * area) * (color0[0] * edge01[2] + color1[0] * edge12[2] + color2[0] * edge20[2]);
	double Arblue = 1 / (2 * area) * (color0[1] * edge01[0] + color1[1] * edge12[0] + color2[1] * edge20[0]);
	double Brblue = 1 / (2 * area) * (color0[1] * edge01[1] + color1[1] * edge12[1] + color2[1] * edge20[1]);
	double Crblue = 1 / (2 * area) * (color0[1] * edge01[2] + color1[1] * edge12[2] + color2[1] * edge20[2]);
	double Argreen = 1 / (2 * area) * (color0[2] * edge01[0] + color1[2] * edge12[0] + color2[2] * edge20[0]);
	double Brgreen = 1 / (2 * area) * (color0[2] * edge01[1] + color1[2] * edge12[1] + color2[2] * edge20[1]);
	double Crgreen = 1 / (2 * area) * (color0[2] * edge01[2] + color1[2] * edge12[2] + color2[2] * edge20[2]);
	double z0 = 1 / (2 * area) * (v0.position[2] * edge01[0] + v1.position[2] * edge12[0] + v2.position[2] * edge20[0]);
	double z1 = 1 / (2 * area) * (v0.position[2] * edge01[1] + v1.position[2] * edge12[1] + v2.position[2] * edge20[1]);
	double z2 = 1 / (2 * area) * (v0.position[2] * edge01[2] + v1.position[2] * edge12[2] + v2.position[2] * edge20[2]);

	double xmax = std::max(v0.position[0], v1.position[0], v2.position[0]);
	double xmin = std::min(v0.position[0], v1.position[0], v2.position[0]);
	double ymax = std::max(v0.position[1], v1.position[1], v2.position[1]);
	double ymin = std::min(v0.position[1], v1.position[1], v2.position[1]);

	for (int x = xmin; x <= xmax; x++) {
		for (int y = ymin; y <= xmax; x++) {
			bool t[3];
			for (int j = 0; j < 3; j++) {

			}
			if (edge01[0] != 0) {
				t[0] = (edge01[0] > 0); 
			}
			else {
				t[0] = (edge01[1] > 0);
			}
			if (edge01[0] != 0) {
				t[1] = (edge12[0] > 0);
			}
			else {
				t[1] = (edge12[1] > 0);
			}
			if (edge01[0] != 0) {
				t[2] = (edge20[0] > 0); 
			}
			else {
				t[2] = (edge20[1] > 0);
			}
			double Exy[3];
			Exy[0] = edge01[0] * x + edge01[1] * y + edge01[2];
			Exy[1] = edge12[0] * x + edge12[1] * y + edge12[2];
			Exy[2] = edge20[0] * x + edge20[1] * y + edge20[2];
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
					color[0] = Arred * x + Brred * y + Crred;
					color[1] = Arblue * x + Brblue * y + Crblue;
					color[2] = Argreen * x + Brgreen * y + Crgreen;
				}

				if (depthTestEnabled) {
					double z = z0 * x + z1 * y + z2;
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

