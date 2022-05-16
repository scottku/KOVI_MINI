#include <stdio.h>
#include <cmath>
#include "stdafx.h"
#include "Figure.h"
#include "Matrix.h"

MyVertex* returnPtr;

MyVertex* pCube(float length, float x, float y, float z)
{
	MyVertex result[8] = {};
	result[0].x = x - length; result[0].y = y + length; result[0].z = z + length;
	result[1].x = x - length; result[1].y = y - length; result[1].z = z + length;
	result[2].x = x + length; result[2].y = y - length; result[2].z = z + length;
	result[3].x = x + length; result[3].y = y + length; result[3].z = z + length;
	result[4].x = x - length; result[4].y = y + length; result[4].z = z - length;
	result[5].x = x - length; result[5].y = y - length; result[5].z = z - length;
	result[6].x = x + length; result[6].y = y - length; result[6].z = z - length;
	result[7].x = x + length; result[7].y = y + length; result[7].z = z - length;
	
	returnPtr = (MyVertex*)result;

	return returnPtr;
}

MyVertex* pSphere(float radius, float x, float y, float z)
{
	float result[230][3] = {};
	MyVertex vResult[230] = {};
	int count = 0;
	int num = 0;
	for (int i = 0; i < 21 ; i++) 
	{
		if (((radius/10) * i - radius) * ((radius/10) * i - radius) - radius*radius == 0)
		{
			result[count][0] = 0;
			result[count][1] = 0;
			result[count][2] = (radius/10) * i - radius;
			count++;
		}
		else
		{ // count 1����
			float firstX = (float)sqrt(radius*radius - (((radius/10)*i - radius)*((radius/10)*i - radius))); float firstY = 0;
			float first[4][1] = { {firstX}, {firstY}, {(radius/10) * i - radius}, {1} };
			result[count][0] = firstX; result[count][1] = firstY; result[count][2] = (radius / 10) * i - radius; // result[1][0] ~ result[1][2] ���� ä��
			count++; // result[2][] ä���
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
		vResult[i].x = result[i][0] + x;
		vResult[i].y = result[i][1] + y;
		vResult[i].z = result[i][2] + z;
	}

	return (MyVertex*)vResult;
}

MyVertex* pTorus(float x, float y, float z, float distanceFromOriginToCenterOfTorus, float radiusOfTorus)
{
	float result[144][3] = {};
	Vertex myResult[144] = {};
	float sample[12][3] = {};
	float* ptr;
	// (x, y, z)�� �߽�, �߽ɿ������� distanceFromOriginToCenterOfTorus��ŭ ������ ���� torus�� �߽�, torus�� �������� radiusOfTorus
	// ���� �߽��� (0, 0, 0)�̶�� �����ϰ� ���� ���ϱ� ���� torus�� �߽��� �ϳ� �����Ѵ�. (distanceFromOriginToCenterOfTorus, 0, 0)
	// �� �߽��� �������� xy��鿡 ���� ����Ƿ� �� ���� ������ ���Ѵ�.
	// torus�� �������� radiusOfTorus �̹Ƿ� �߽��� (0, 0, 0)�� ��, �������� radiusOfTorus�� ���� ������ ���Ѵ�.
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
	// ���� ������ distanceFromOriginToCenterOfTorus��ŭ x������ �ű� ��, ������ �߽��� ������ torus�� ���Ѵ�.
	for (int i = 0; i < 12; i++)
	{
		sample[i][0] += distanceFromOriginToCenterOfTorus;
	}
	// ���� �ϳ��� �ҷ��ͼ� 30 * n ��ŭ�� ���� ��, result�� �ִ´�.
	float temp[4][1] = {};
	for (int i = 0; i < 12; i++)
	{
		int ptNumber = 0;
		// �� 12���� 1�� ��������
		for (int j = 0; j < 4; j++)
		{
			pt[j][0] = sample[i][j];
		}
		// �� ���� 30 *n �� ������ ���� result�� �ֱ�.
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
	// ������ �߽����� ��� torus�� ���� ��������, ������ (x, y, z)�� �ű�� ��
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