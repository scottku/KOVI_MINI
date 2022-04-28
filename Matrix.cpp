#include <stdio.h>
#include <cmath>
#include "stdafx.h"
#include "Matrix.h"

const double pi = 3.14159265358979;

//// 아마 필요 없을 것
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

float* ViewMatrix(float a[3][1] /*카메라 위치*/, float b[3][1] /*물체 위치*/, float c[3][1] /*카메라 시야 방향*/)
{
	float axisZ[4][1] = { {c[0][0]}, {c[1][0]}, {c[2][0]}, {0} };
	float cameraToMaterial[4][1] = { {b[0][0] - a[0][0]}, {b[1][0] - a[1][0]}, {b[2][0] - a[2][0]}, {0} };

	float axisX[4][1] = { {c[2][0]}, {0}, {-c[0][0]}, {0} }; // Up 벡터(0,1,0)와 카메라 시야 방향(z')를 외적해 얻은 새로운 x축
	float axisY[4][1] = { {-(c[0][0] * c[1][0])}, {(c[0][0] * c[0][0]) + (c[2][0] * c[2][0])}, {-(c[1][0] * c[2][0])}, {0} }; // x' 축과 z' 축을 외적해 얻은 새로운 y축

	/*
	1. 기존의 카메라가 (0, 0, 0) 원점에서 z축을 바라보고 있다고 가정
	2. 크기 변환은 일단 의미가 없고, 위치 변환은 더해주고 빼주기만 하면 되니 회전만 한다고 가정
	3. 카메라가 바라보는 시야 벡터가 특정 방향으로 변환(회전)
	4. 기존 좌표계에서 카메라를 기준으로 좌표계를 다시 설정(카메라의 시야 방향과 Up벡터의 외적 등을 이용해 새로운 xyz축을 생성)
	5. 새로운 xyz축과, 기존 축에서 카메라의 위치에서부터 오브젝트의 위치로 향하는 벡터를 내적  
	6. 새로운 xyz축을 기준으로 x 방향으로 얼마, y방향으로 얼마, z방향으로 얼마 떨어진곳에 위치해 있는지 알 수 있음.
	7. 기존 축 기준 카메라 월드가 몇도씩 회전했는지도 알 수 있음 -> 그걸 역으로 물체를 회전시키면 카메라 월드에 재적용 가능?
	참고 : https://heyzlluck.tistory.com/entry/3-%EB%B7%B0-%ED%96%89%EB%A0%AC
	*/


}