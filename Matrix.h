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

float* MatrixMulti(float a[4][4], float b[4][1]);

float* MatrixScale(float a[4][1], float x, float y, float z); // 크기 변환

float* MatrixRotate(float a[4][1], float x, float y, float z); // 회전 변환 (x를 축으로, y를 축으로, z를 축으로)

float* MatrixTranslate(float a[4][1], float x, float y, float z); // 이동 변환

float Matrix3x3Calc(float a[3][3]); //3x3 행렬 계산

float* VectorPlus(float a[4][1], float b[4][1]);

float* VectorMinus(float a[4][1], float b[4][1]);

float* MatrixNormalize(float a[4][1]); // 벡터 정규화

float DotProduct(float a[3][1], float b[3][1]); //  벡터 내적
//float DotProduct(float a[4][1], float b[4][1]);

float* CrossProduct(float a[4][1], float b[4][1]); // 벡터 외적

float* MatrixReverse(float a[4][4]); // 역행렬

float* ViewMatrix(float camera[3][1] /*카메라 위치*/, float material[3][1] /*물체 위치*/, float look[3][1] /*카메라 시야 방향*/); // 뷰 행렬

float* ProjectionMatrix(int width, int height, float angle, float near, float far); // 투영 행렬

float* AffinTransform(float scaleX, float scaleY, float scaleZ, float angleX, float angleY, float angleZ, float transX, float transY, float transZ); // 아핀 행렬 생성
// 스케일 증가 -> x축기준 회전 -> y축기준 회전 -> z축기준 회전 -> 이동

float ToScreenX(int width, long left, float x); // 스크린 좌표계로 변환
float ToScreenY(int height, long top, float y);
