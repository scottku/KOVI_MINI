#include <stdio.h>
#include <cmath>
#include "stdafx.h"
#include "Matrix.h"

const double pi = 3.14159265358979;

//// �Ƹ� �ʿ� ���� ��
//float4x4 PlusMatrix(float4x4 &x, float4x4 &y)
//{
//	float4x4 sampleMatrix;
//	for (int i = 0; i < 4; i++)
//	{
//		sampleMatrix.a[i] = x.a[i] + y.a[i];
//		sampleMatrix.b[i] = x.b[i] + y.b[i];
//		sampleMatrix.c[i] = x.c[i] + y.c[i];
//		sampleMatrix.d[i] = x.d[i] + y.d[i];
//	}
//
//	return sampleMatrix;
//}

float* MatrixPlus(float x[4][4], float y[4][4])
{
	float sampleMatrix[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sampleMatrix[i][j] = x[i][j] + y[i][j];
		}
	}

	return (float*)sampleMatrix;
}

float* MatrixMinus(float x[4][4], float y[4][4])
{
	float sampleMatrix[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sampleMatrix[i][j] = x[i][j] - y[i][j];
		}
	}

	return (float*)sampleMatrix;
}

float* MatrixMulti(float x[4][4], float y[4][4])
{
	float sampleMatrix[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0;
			for (int k = 0; k < 4; k++)
			{
				 sum += x[i][k] * y[k][j];
			}
			sampleMatrix[i][j] = sum;
		}
	}

	return (float*)sampleMatrix;
}

float* MatrixMulti(float x[4][4], float y[4][1])
{
	float sampleMatrix[4][1];
	for (int i = 0; i < 4; i++)
	{
		float sum = 0;
		for (int j = 0; j < 4; j++)
		{
			sum += x[i][j] * y[j][0];
		}
		sampleMatrix[i][0] = sum;
	}

	return (float*)sampleMatrix;
}

float* MatrixScale(float a[4][1], float x, float y, float z)
{
	float sampleMatrix[4][4] = { {x, 0 ,0, 0}, {0, y, 0, 0}, {0,0,z,0}, {0,0,0,1} };
	float resultMatrix[4][1] = {};
	for (int i = 0; i < 4; i++)
	{
		float sum = 0;
		for (int j = 0; j < 4; j++)
		{
			sum += sampleMatrix[i][j] * a[j][0];
		}
		resultMatrix[i][0] = sum;
	}

	return (float*)resultMatrix;
}

float* MatrixRotate(float w[4][1], float a, float b, float c)
{
	double sinX = sin(a * pi / 180);
	double cosX = cos(a * pi / 180);
	double sinY = sin(b * pi / 180);
	double cosY = cos(b * pi / 180);
	double sinZ = sin(c * pi / 180);
	double cosZ = cos(c * pi / 180);

	float xRotate[4][4] = { {1, 0, 0, 0}, {0, cosX, sinX, 0}, {0, -sinX, cosX, 0}, {0, 0, 0, 1} };
	float yRotate[4][4] = { {cosY, 0, -sinY, 0}, {0, 1, 0, 0}, {sinY, 0, cosY, 0}, {0, 0, 0, 1} };
	float zRotate[4][4] = { {cosZ, sinZ, 0, 0}, {-sinZ, cosZ, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };

	float myArray[4][1] = { { 0 },{ 0 },{ 0 },{ 0 } };
	float* scaleA = MatrixMulti(xRotate, w);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		myArray[i][0] = *(scaleA + count);
		count++;
	}
	scaleA = MatrixMulti(yRotate, myArray);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		myArray[i][0] = *(scaleA + count);
		count++;
	}
	scaleA = MatrixMulti(zRotate, myArray);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		myArray[i][0] = *(scaleA + count);
		count++;
	}

	return (float*)myArray;
}

float* MatrixTranslate(float a[4][1], float x, float y, float z)
{
	float sampleMatrix[4][4] = { { 1, 0 ,0, x },{ 0, 1, 0, y },{ 0,0,1,z },{ 0,0,0,1 } };
	float resultMatrix[4][1] = {};
	for (int i = 0; i < 4; i++)
	{
		float sum = 0;
		for (int j = 0; j < 4; j++)
		{
			sum += sampleMatrix[i][j] * a[j][0];
		}
		resultMatrix[i][0] = sum;
	}

	return (float*)resultMatrix;
}

float* ViewMatrix(float a[3][1] /*ī�޶� ��ġ*/, float b[3][1] /*��ü ��ġ*/, float c[3][1] /*ī�޶� �þ� ����*/)
{
	float axisZ[4][1] = { {c[0][0]}, {c[1][0]}, {c[2][0]}, {0} };
	float cameraToMaterial[4][1] = { {b[0][0] - a[0][0]}, {b[1][0] - a[1][0]}, {b[2][0] - a[2][0]}, {0} };

	float axisX[4][1] = { {c[2][0]}, {0}, {-c[0][0]}, {0} }; // Up ����(0,1,0)�� ī�޶� �þ� ����(z')�� ������ ���� ���ο� x��
	float axisY[4][1] = { {-(c[0][0] * c[1][0])}, {(c[0][0] * c[0][0]) + (c[2][0] * c[2][0])}, {-(c[1][0] * c[2][0])}, {0} }; // x' ��� z' ���� ������ ���� ���ο� y��

	/*
	1. ������ ī�޶� (0, 0, 0) �������� z���� �ٶ󺸰� �ִٰ� ����
	2. ũ�� ��ȯ�� �ϴ� �ǹ̰� ����, ��ġ ��ȯ�� �����ְ� ���ֱ⸸ �ϸ� �Ǵ� ȸ���� �Ѵٰ� ����
	3. ī�޶� �ٶ󺸴� �þ� ���Ͱ� Ư�� �������� ��ȯ(ȸ��)
	4. ���� ��ǥ�迡�� ī�޶� �������� ��ǥ�踦 �ٽ� ����(ī�޶��� �þ� ����� Up������ ���� ���� �̿��� ���ο� xyz���� ����)
	5. ���ο� xyz���, ���� �࿡�� ī�޶��� ��ġ�������� ������Ʈ�� ��ġ�� ���ϴ� ���͸� ����  
	6. ���ο� xyz���� �������� x �������� ��, y�������� ��, z�������� �� ���������� ��ġ�� �ִ��� �� �� ����.
	7. ���� �� ���� ī�޶� ���尡 ��� ȸ���ߴ����� �� �� ���� -> �װ� ������ ��ü�� ȸ����Ű�� ī�޶� ���忡 ������ ����?
	���� : https://heyzlluck.tistory.com/entry/3-%EB%B7%B0-%ED%96%89%EB%A0%AC
	*/


}