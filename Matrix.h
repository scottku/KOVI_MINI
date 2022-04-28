#pragma once
using namespace std;

typedef struct Matrix4x4
{
	float a[4];
	float b[4];
	float c[4];
	float d[4];
} float4x4;

//float4x4 PlusMatrix(float4x4 &x, float4x4 &y);

float* MatrixPlus(float a[4][4], float b[4][4]);

float* MatrixMinus(float a[4][4], float b[4][4]);

float* MatrixMulti(float a[4][4], float b[4][4]);
