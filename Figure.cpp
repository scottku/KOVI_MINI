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

void makingTorus(CPoint pt) 
{

}