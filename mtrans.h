
// g++ -Wall mtrans.cpp main.cpp -lopengl32 -lglew32 -lglfw3dll

#ifndef MTRANS_H
#define MTRANS_H

// Include standard headers
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#define PIXEL (float)600.0
#define PI 3.14159265

#include <bits/stdc++.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace std;
using namespace glm;

typedef tuple<float, float, float, float> points;
typedef vector<points> polygon;
typedef vector<float> vfloat;

// Comparation function to sort vertex counter-clockwise using Barycenter
bool cmpBarycenter( tuple<points, points> a, tuple<points, points> b );

// Function that returns sorted vertex counter-clockwise
vfloat sortBarycenter( polygon x );

// Draw Cartesian in the window
void drawCartesian();

// Return vector of vertex made by user
vfloat getVertexByUser();

// Draw the polygon
void drawPolygon(vfloat v);

//Prosedur translate
void commandTranslate(vector<float> *gambarPolygonAwal, float dx, float dy,  int banyakVertex);

//Prosedur dilate
void commandDilate(vector<float> *gambarPolygonAwal, int banyakVertex);

//Prosedur reset
void commandReset(vector<float> kondisiAwal);

void commandRotate(vector<float> *gambarPolygonAwal, float angle_in_degrees,  float a,  float b,  int banyakVertex);

void commandShear(vector<float> *gambarPolygonAwal,  int banyakVertex);

void commandStretch(vector<float> *gambarPolygonAwal,  int banyakVertex);

void commandCustom(vector<float> *gambarPolygonAwal,  int banyakVertex);

// Return polygon after reflection
vector<float> commandReflect(vector<float> polygonBeforeTrans, string input);

#endif