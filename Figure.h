#pragma once
using namespace std;

typedef struct Vertex
{
	float x, y, z;
	float lightStrength1, lightStrength2, lightStrength3;
} MyVertex;

MyVertex* pCube(float length, float x, float y, float z);

MyVertex* pSphere(float radius,  float x, float y, float z);

MyVertex* pTorus(float x, float y, float z, float distanceFromOriginToCenterOfTorus, float radiusOfTorus);