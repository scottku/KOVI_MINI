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

float* MatrixPlus(float a[4][4], float b[4][4]); // ����� ����

float* MatrixMinus(float a[4][4], float b[4][4]); // ����� ����

float* MatrixMulti(float a[4][4], float b[4][4]); // ����� ����

float* MatrixScale(float a[4][1], float x, float y, float z); // ũ�� ��ȯ

float* MatrixRotate(float a[4][1], float x, float y, float z); // ȸ�� ��ȯ (x�� ������, y�� ������, z�� ������)

float* MatrixTranslate(float a[4][1], float x, float y, float z); // �̵� ��ȯ

float* ViewMatrix(float a[3][1] /*ī�޶� ��ġ*/, float b[3][1] /*��ü ��ġ*/, float c[3][1] /*ī�޶� �þ� ����*/); // �� ���
