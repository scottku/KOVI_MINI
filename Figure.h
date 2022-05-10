#pragma once
using namespace std;

typedef struct Vertex
{
	float x, y, z;
	float vertexNormal[4][1];
} MyVertex;

MyVertex* pCube(float x, float y, float z);

MyVertex* pSphere(float x, float y, float z);

MyVertex* pTorus(float x, float y, float z, float distanceFromOriginToCenterOfTorus, float radiusOfTorus);