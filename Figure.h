#pragma once
using namespace std;

typedef struct Vertex
{
	float x, y, z;
	float vertexNormal[4][1];
} MyVertex;

float* pCube(float x, float y, float z);

float* pSphere(float x, float y, float z);

MyVertex* pTorus(float x, float y, float z, float distanceFromOriginToCenterOfTorus, float radiusOfTorus);