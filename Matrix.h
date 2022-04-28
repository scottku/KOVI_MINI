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

float* MatrixPlus(float a[4][4], float b[4][4]); // 행렬의 덧셈

float* MatrixMinus(float a[4][4], float b[4][4]); // 행렬의 뺄셈

float* MatrixMulti(float a[4][4], float b[4][4]); // 행렬의 곱셈

float* MatrixScale(float a[4][1], float x, float y, float z); // 크기 변환

float* MatrixRotate(float a[4][1], float x, float y, float z); // 회전 변환 (x를 축으로, y를 축으로, z를 축으로)

float* MatrixTranslate(float a[4][1], float x, float y, float z); // 이동 변환

float* ViewMatrix(float a[3][1] /*카메라 위치*/, float b[3][1] /*물체 위치*/, float c[3][1] /*카메라 시야 방향*/); // 뷰 행렬
