#pragma once
#include "Figure.h"
using namespace std;

typedef struct Matrix4x4
{
	float a[4];
	float b[4];
	float c[4];
	float d[4];
} float4x4;

//float4x4 PlusMatrix(float4x4 &x, float4x4 &y);

float* MatrixPlus(float a[4][4], float b[4][4]); // ����� ����

float* MatrixMinus(float a[4][4], float b[4][4]); // ����� ����

float* MatrixMulti(float a[4][4], float b[4][4]); // ����� ����

float* MatrixMulti(float a[4][4], float b[4][1]);

float* MatrixScale(float a[4][1], float x, float y, float z); // ũ�� ��ȯ

float* MatrixRotate(float a[4][1], float x, float y, float z); // ȸ�� ��ȯ (x�� ������, y�� ������, z�� ������)

float* MatrixTranslate(float a[4][1], float x, float y, float z); // �̵� ��ȯ

float Matrix3x3Calc(float a[3][3]); //3x3 ��� ���

float* VectorPlus(float a[3][1], float b[3][1]);

float* VectorMinus(float a[4][1], float b[4][1]);

float* MatrixNormalize(float a[4][1]); // ���� ����ȭ

float DotProduct(float a[3][1], float b[3][1]); //  ���� ����
//float DotProduct(float a[4][1], float b[4][1]);

float* CrossProduct(float a[4][1], float b[4][1]); // ���� ����
float* CrossProduct2X2(float a[2][1], float b[2][1]);

float* MatrixReverse(float a[4][4]); // �����

float* ViewMatrix(float camera[3][1] /*ī�޶� ��ġ*/, float look[3][1] /*ī�޶� �þ� ����*/); // �� ���

float* ProjectionMatrix(int width, int height, float angle); // ���� ���
float* ProjectionMatrixParallel(int right, int left, int bottom, int top, float n, float f);

float* AffinTransform(float scaleX, float scaleY, float scaleZ, float angleX, float angleY, float angleZ, float transX, float transY, float transZ); // ���� ��� ����
// ������ ���� -> x����� ȸ�� -> y����� ȸ�� -> z����� ȸ�� -> �̵�

float ToScreenX(int width, long left, float x); // ��ũ�� ��ǥ��� ��ȯ
float ToScreenY(int height, long top, float y);

float LightingCos(MyVertex p1, MyVertex p2, MyVertex p3);
float* MakeNewCoordinate(float c[3][1]);
float* vectorRotation(float rv[3][1], float sv[3][1], int angle);
float vectorLength(float a[3][1]);

float* Cube_isitFront(MyVertex vertex1, MyVertex vertex2, MyVertex vertex3, float camera[3][1], float look[3][1], float lightDirection[3][1]);
void CubeMeshDraw(int projNum, float meshData[5], CDC* memDC, float width, float height, float left, float top, MyVertex p1, MyVertex p2, MyVertex p3);
void CubeLineDraw(int projNum, float meshData[5], CDC* memDC, float width, float height, float left, float top, MyVertex p1, MyVertex p2, MyVertex p3);

void DrawSphereLine(int i, CDC* memDC, float width, float heigth, float left, float top, MyVertex v1, MyVertex v2, MyVertex v3, MyVertex vException);
void DrawSphereMesh(int i, int start, CDC* memDC, float width, float height, float left, float top, MyVertex v1, MyVertex v2, MyVertex v3, MyVertex vException, int* array);

void DrawTorusLine(CDC* memDCPtr, float width, float height, float left, float top, MyVertex v1, MyVertex v2, MyVertex v3);
void DrawTorusMesh(int i, int* RGB_array, CDC* memDC, float width, float height, float left, float top, MyVertex v1, MyVertex v2, MyVertex v3);


BOOL isItUpperSide(float NormDirectionVector[3][1], float pointOnPlane[3][1], float point[3][1]);

void MakeVertexToVertexVector(float emptyVector[4][1], MyVertex endVertex, MyVertex startVertex);
void MakeVertexToVertexVector(float emptyVector[3][1], MyVertex endVertex);

void MakeMeshVectors(MyVertex planeVector[3], MyVertex originVector[3], const MyVertex v1, const MyVertex v2, const MyVertex v3);