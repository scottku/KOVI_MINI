#include <stdio.h>
#include "stdafx.h"
#include "Matrix.h"

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