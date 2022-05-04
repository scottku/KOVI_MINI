#include <stdio.h>
#include <cmath>
#include "stdafx.h"
#include "Figure.h"
#include "Matrix.h"

float* pCube(float x, float y, float z)
{
	float result[8][3] =
	{ { x - 10, y + 10, z + 10 }, //p1
	{ x - 10, y - 10, z + 10 }, //p2
	{ x + 10, y - 10, z + 10 }, //p3
	{ x + 10, y + 10, z + 10 }, //p4
	{ x - 10, y + 10, z - 10 }, //p5
	{ x - 10, y - 10, z - 10 }, //p6
	{ x + 10, y - 10, z - 10 }, //p7
	{ x + 10, y + 10, z - 10 }, //p8
	};
	
	return (float*)result;
}

void pSphere(CPoint pt)
{

}

void makingTorus(CPoint pt) 
{

}