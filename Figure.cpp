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

float* pSphere(float x, float y, float z)
{
	#pragma region 이건 아닌거 같아...
	// x^2 + y^2 + z^2 = r^2
	/*float result1[1][3] = {};
	float result2[24][3] = {};
	float result3[24][3] = {};
	float result4[24][3] = {};
	float result5[24][3] = {};
	float result6[24][3] = {};
	float result7[24][3] = {};
	float result8[24][3] = {};
	float result9[24][3] = {};
	float result10[24][3] = {};
	float result11[24][3] = {};
	float result12[24][3] = {};
	float result13[24][3] = {};
	float result14[24][3] = {};
	float result15[24][3] = {};
	float result16[24][3] = {};
	float result17[24][3] = {};
	float result18[24][3] = {};
	float result19[24][3] = {};
	float result20[1][3] = {};
	float* result[20] = { (float*)result1, (float*)result2, (float*)result3, (float*)result4, (float*)result5, (float*)result6, (float*)result7, 
		(float*)result8, (float*)result9, (float*)result10, (float*)result11, (float*)result12, (float*)result13, (float*)result14, (float*)result15, 
		(float*)result16, (float*)result17, (float*)result18, (float*)result19, (float*)result20 };

	for (int i = 0; i < 21; i++)
	{
		if ((i - 10) * (i - 10) - 100 == 0)
		{
			*(result[i] + 0) = 0;
			*(result[i] + 1) = 0;
			*(result[i] + 2) = i - 10;
		}
		else
		{
			int count = 0;
			float firstX = (float)sqrt(100 - (i * i)); float firstY = 0;
			*(result[i] + 0) = firstX; *(result[i] + 1) = 0; *(result[i] + 2) = i - 10;
			float first[4][1] = { {firstX}, {firstY}, {i - 10}, {1} };
			for (int rot = 1; rot < 24; rot++)
			{
				float* ptr = MatrixRotate(first, 0, 0, 15 * rot);
				count = 0;
				for (int c = 0; c < 3; c++)
				{
					*(result[i] + (3 * rot) + c) = *(ptr + count);
				}
			}
		}
	}

	return (float*)result;*/
	#pragma endregion

	float result[230][3] = {};
	int count = 0;
	int num = 0;
	for (int i = 0; i < 21; i++)
	{
		if ((i - 10) * (i - 10) - 100 == 0)
		{
			result[count][0] = 0;
			result[count][1] = 0;
			result[count][2] = i - 10;
			count++;
		}
		else
		{ // count 1부터
			float firstX = (float)sqrt(100 - ((i-10) * (i-10))); float firstY = 0;
			float first[4][1] = { {firstX}, {firstY}, {i - 10}, {1} };
			result[count][0] = firstX; result[count][1] = firstY; result[count][2] = i - 10; // result[1][0] ~ result[1][2] 까지 채움
			count++; // result[2][] 채우기
			for (int rot = 1; rot < 12; rot++)
			{
				float* ptr = MatrixRotate(first, 0, 0, 30 * rot);
				num = 0;
				for (int c = 0; c < 3; c++)
				{
					result[count][c] = *(ptr + num); // result[2][0] = *ptr, result[2][1] = *(ptr + 1), result[2][2] = *(ptr + 2)
					num++;
				}
				count++;
			}
			
		}
	}

	for (int i = 0; i < 230; i++)
	{
		result[i][0] += x;
		result[i][1] += y;
		result[i][2] += z;
	}

	return (float*)result;
}

MyVertex* pTorus(float x, float y, float z, float distanceFromOriginToCenterOfTorus, float radiusOfTorus)
{
	float result[144][3] = {};
	Vertex myResult[144] = {};
	float sample[12][3] = {};
	float* ptr;
	// (x, y, z)가 중심, 중심에서부터 distanceFromOriginToCenterOfTorus만큼 떨어진 곳에 torus의 중심, torus의 반지름은 radiusOfTorus
	// 먼저 중심이 (0, 0, 0)이라고 가정하고 가장 구하기 쉬운 torus의 중심을 하나 생각한다. (distanceFromOriginToCenterOfTorus, 0, 0)
	// 그 중심을 기점으로 xy평면에 원이 생기므로 그 원에 점들을 구한다.
	// torus의 반지름이 radiusOfTorus 이므로 중심이 (0, 0, 0)일 때, 반지름이 radiusOfTorus인 원의 점들을 구한다.
	float pt[4][1] = { {radiusOfTorus}, {0}, {0}, {1} };
	float circlePt[4][1] = {};
	int count;
	for (int i = 0; i < 12; i++)
	{
		ptr = MatrixRotate(pt, 0, 0, 30 * i);
		count = 0;
		for (int j = 0; j < 4; j++)
		{
			circlePt[j][0] = *(ptr + count);
			count++;
		}
		sample[i][0] = circlePt[0][0];
		sample[i][1] = circlePt[1][0];
		sample[i][2] = circlePt[2][0];
	}
	// 구한 점들을 distanceFromOriginToCenterOfTorus만큼 x축으로 옮긴 후, 원점을 중심을 돌려서 torus를 구한다.
	for (int i = 0; i < 12; i++)
	{
		sample[i][0] += distanceFromOriginToCenterOfTorus;
	}
	// 점을 하나씩 불러와서 30 * n 만큼씩 돌린 후, result에 넣는다.
	float temp[4][1] = {};
	for (int i = 0; i < 12; i++)
	{
		int ptNumber = 0;
		// 점 12개중 1개 가져오기
		for (int j = 0; j < 4; j++)
		{
			pt[j][0] = sample[i][j];
		}
		// 그 점을 30 *n 씩 돌려서 값을 result에 넣기.
		for (int j = 0; j < 12; j++)
		{
			ptr = MatrixRotate(pt, 0, (30 * j), 0);
			count = 0;
			for (int k = 0; k < 3; k++)



			{
				result[i + (12 * j)][k] = *(ptr + count);
				count++;
			}
		}
	}
	// 원점을 중심으로 모든 torus의 점을 구했으니, 원점을 (x, y, z)로 옮기면 끝
	float center[3][1] = { {x}, {y}, {z} };
	for (int i = 0; i < 144; i++)
	{
		myResult[i].x = result[i][0] + x;
		myResult[i].y = result[i][1] + y;
		myResult[i].z = result[i][2] + z;

		//result[i][0] += x;
		//result[i][1] += y;
		//result[i][2] += z;
	}

	return (Vertex*)myResult;
}