#include <stdio.h>
#include <cmath>
#include "stdafx.h"
#include "Matrix.h"
#include "Figure.h"

const double pi = 3.14159265358979;
float* arrayReturnPtr;

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

float* MatrixNormalize(float a[4][1])
{
	float length = (float)sqrt(pow(a[0][0], 2) + (float)pow(a[1][0], 2) + (float)pow(a[2][0], 2));

	float result[4][1];
	result[0][0] = a[0][0] / length;
	result[1][0] = a[1][0] / length;
	result[2][0] = a[2][0] / length;
	result[3][0] = 0;

	return (float*)result;
}

float Matrix3x3Calc(float a[3][3])
{
	float x = a[0][0] * ((a[1][1] * a[2][2]) - (a[1][2] * a[2][1]));
	float y = (-1) * (a[0][1] * ((a[1][0] * a[2][2]) - (a[1][2] * a[2][0])));
	float z = a[0][2] * ((a[1][0] * a[2][1]) - (a[1][1] * a[2][0]));
	float result = x + y + z;
	return result;
}

float DotProduct(float a[3][1], float b[3][1])
{
	return a[0][0] * b[0][0] + a[1][0] * b[1][0] + a[2][0] * b[2][0];
}
//float DotProduct(float a[4][1], float b[4][1])
//{
//	float x[3][1] = { {a[0][0]}, {a[1][0]}, {a[2][0]} };
//	float y[3][1] = { {b[0][0]}, {b[1][0]}, {b[2][0]} };
//
//	return x[0][0] * y[0][0] + x[1][0] * y[1][0] + x[2][0] * y[2][0];
//}

float* CrossProduct(float a[4][1], float b[4][1])
{
	float x[3][1] = { { a[0][0] },{ a[1][0] },{ a[2][0] } };
	float y[3][1] = { { b[0][0] },{ b[1][0] },{ b[2][0] } };

	float result[4][1] = {};
	result[0][0] = (a[1][0] * b[2][0]) - (a[2][0] * b[1][0]);
	result[1][0] = -((a[0][0] * b[2][0]) - (a[2][0] * b[0][0]));
	result[2][0] = (a[0][0] * b[1][0]) - (a[1][0] * b[0][0]);
	result[3][0] = 1;

	return (float*)result;
}
float* CrossProduct2X2(float a[2][1], float b[2][1])
{
	float x[3][1] = { {a[0][0]}, {a[1][0]}, {0} };
	float y[3][1] = { {b[0][0]}, {b[1][0]}, {0} };

	float result[3][1] = {};
	result[2][0] = a[0][0] * b[1][0] - a[1][0] * b[0][0];

	return (float*)result;
}

float* MatrixReverse(float a[4][4]) // TODO : for������ �ٲܸ��Ѱ� ������?
{
	float result[4][4] = {};
	// �Ʒ� ������δ�  0�϶� Ŀ�� ����.
	//// ���콺 ���� �ҰŹ�
	//// (1) 1���� �̿��� 2,3,4 ���� x���� 0���� -> �׵���ĵ� ���� ������� ����
	//float x = a[1][0] / a[0][0];
	//a[1][0] = a[1][0] - (x * a[0][0]); a[1][1] = a[1][1] - (x * a[0][1]); a[1][2] = a[1][2] - (x * a[0][2]); a[1][3] = a[1][3] - (x * a[0][3]);
	//same[1][0] = same[1][0] - (x * same[0][0]); same[1][1] = same[1][1] - (x * same[0][1]); same[1][2] = same[1][2] - (x * same[0][2]); same[1][3] = same[1][3] - (x * same[0][3]);
	//x = a[2][0] / a[0][0];
	//a[2][0] = a[2][0] - (x * a[0][0]); a[2][1] = a[2][1] - (x * a[0][1]); a[2][2] = a[2][2] - (x * a[0][2]); a[2][3] = a[2][3] - (x * a[0][3]);
	//same[2][0] = same[2][0] - (x * same[0][0]); same[2][1] = same[2][1] - (x * same[0][1]); same[2][2] = same[2][2] - (x * same[0][2]); same[2][3] = same[2][3] - (x * same[0][3]);
	//x = a[3][0] / a[0][0];
	//a[3][0] = a[3][0] - (x * a[0][0]); a[3][1] = a[3][1] - (x * a[0][1]); a[3][2] = a[3][2] - (x * a[0][2]); a[3][3] = a[3][3] - (x * a[0][3]);
	//same[3][0] = same[3][0] - (x * same[0][0]); same[3][1] = same[3][1] - (x * same[0][1]); same[3][2] = same[3][2] - (x * same[0][2]); same[3][3] = same[3][3] - (x * same[0][3]);
	//////////
	////// 2���� �̿��� 3,4  ���� y���� 0���� -> �׵���ĵ� ���� �������
	//x = a[2][1] / a[1][1];
	//a[2][1] = a[2][1] - (x * a[1][1]); a[2][2] = a[2][2] - (x * a[1][2]); a[2][3] = a[2][3] - (x * a[1][3]);
	//same[2][0] = same[2][0] - (x * same[1][0]); same[2][1] = same[2][1] - (x * same[1][1]); same[2][2] = same[2][2] - (x * same[1][2]); same[2][3] = same[2][3] - (x * same[1][3]);
	//x = a[3][1] / a[1][1];
	//a[3][1] = a[3][1] - (x * a[1][1]); a[3][2] = a[3][2] - (x * a[1][2]); a[3][3] = a[3][3] - (x * a[1][3]);
	//same[3][0] = same[3][0] - (x * same[1][0]); same[3][1] = same[3][1] - (x * same[1][1]); same[3][2] = same[3][2] - (x * same[1][2]); same[3][3] = same[3][3] - (x * same[1][3]);
	//////////
	////// 3���� �̿��� 4���� z���� 0���� -> �׵���ĵ� ���� �������
	//x = a[3][2] / a[2][2];
	//a[3][2] = a[3][2] - (x * a[2][2]); a[3][3] = a[3][3] - (x * a[2][3]);
	//same[3][0] = same[3][0] - (x * same[2][0]); same[3][1] = same[3][1] - (x * same[2][1]); same[3][2] = same[3][2] - (x * same[2][2]); same[3][3] = same[3][3] - (x * same[2][3]);
	//////////
	////// a[3][3]�� 1�� ����
	//x = a[3][3];
	//a[3][3] = a[3][3] / x; // 1�� ����
	//same[3][0] = same[3][0] / x; same[3][1] = same[3][1] / x; same[3][2] = same[3][2] / x; same[3][3] = same[3][3] / x;
	//////////
	////// a[3][3]�� Ȱ���� a[n][3]�� ���� 0���� ����
	//x = a[2][3];
	//a[2][3] = 0; // �� ���κ��� 0���� ���� ��
	//same[2][0] = same[2][0] - (same[3][0] * x); same[2][1] = same[2][1] - (same[3][1] * x); same[2][2] = same[2][2] - (same[3][2] * x); same[2][3] = same[2][3] - (same[3][3] * x);
	//x = a[1][3];
	//a[1][3] = 0;
	//same[1][0] = same[1][0] - (same[3][0] * x); same[1][1] = same[1][1] - (same[3][1] * x); same[1][2] = same[1][2] - (same[3][2] * x); same[1][3] = same[1][3] - (same[3][3] * x);
	//x = a[0][3];
	//a[0][3] = 0;
	//same[0][0] = same[0][0] - (same[3][0] * x); same[0][1] = same[0][1] - (same[3][1] * x); same[0][2] = same[0][2] - (same[3][2] * x); same[0][3] = same[0][3] - (same[3][3] * x);
	//////////
	////// a[2][2]�� 1�� ����
	//x = a[2][2];
	//a[2][2] = a[2][2] / x; // 1�� ����
	//same[2][0] = same[2][0] / x; same[2][1] = same[2][1] / x; same[2][2] = same[2][2] / x; same[2][3] = same[2][3] / x;
	//////////
	////// a[2][2]�� Ȱ���� a[n][2]�� ���� 0���� ����
	//x = a[1][2];
	//a[1][2] = 0;
	//same[1][0] = same[1][0] - (same[2][0] * x); same[1][1] = same[1][1] - (same[2][1] * x); same[1][2] = same[1][2] - (same[2][2] * x); same[1][3] = same[1][3] - (same[2][3] * x);
	//x = a[0][2];
	//a[0][2] = 0;
	//same[0][0] = same[0][0] - (same[2][0] * x); same[0][1] = same[0][1] - (same[2][1] * x); same[0][2] = same[0][2] - (same[2][2] * x); same[0][3] = same[0][3] - (same[2][3] * x);
	//////////
	////// a[1][1]�� 1�� ����
	//x = a[1][1];
	//a[1][1] = a[1][1] / x;
	//same[1][0] = same[1][0] / x; same[1][1] = same[1][1] / x; same[1][2] = same[1][2] / x; same[1][3] = same[1][3] / x;
	//////////
	////// a[1][1]�� Ȱ���� a[n][1]�� ���� 0���� ����
	//x = a[0][1];
	//a[0][1] = 0;
	//same[0][0] = same[0][0] - (same[1][0] * x); same[0][1] = same[0][1] - (same[1][1] * x); same[0][2] = same[0][2] - (same[1][2] * x); same[0][3] = same[0][3] - (same[1][3] * x);
	//////////
	////// a[0][0]�� 1�� ����
	//x = a[0][0];
	//a[0][0] = a[0][0] / x;
	//same[0][0] = same[0][0] / x; same[0][1] = same[0][1] / x; same[0][2] = same[0][2] / x; same[0][3] = same[0][3] / x;
	//////// �׵���ķ� ��������Ƿ� same ����� ���� ����� ����� ������� ��������� ��.

	// ���μ� ���
	float C1[3][3] = { {a[1][1], a[1][2], a[1][3]}, {a[2][1], a[2][2], a[2][3]}, {a[3][1], a[3][2], a[3][3]} };
	float C2[3][3] = { {a[1][0], a[1][2], a[1][3]}, {a[2][0], a[2][2], a[2][3]}, {a[3][0], a[3][2], a[3][3]} };
	float C3[3][3] = { {a[1][0], a[1][1], a[1][3]}, {a[2][0], a[2][1], a[2][3]}, {a[3][0], a[3][1], a[3][3]} };
	float C4[3][3] = { {a[1][0], a[1][1], a[1][2]}, {a[2][0], a[2][1], a[2][2]}, {a[3][0], a[3][1], a[3][2]} };
	float C5[3][3] = { {a[0][1], a[0][2], a[0][3]}, {a[2][1], a[2][2], a[2][3]}, {a[3][1], a[3][2], a[3][3]} };
	float C6[3][3] = { {a[0][0], a[0][2], a[0][3]}, {a[2][0], a[2][2], a[2][3]}, {a[3][0], a[3][2], a[3][3]} };
	float C7[3][3] = { {a[0][0], a[0][1], a[0][3]}, {a[2][0], a[2][1], a[2][3]}, {a[3][0], a[3][1], a[3][3]} };
	float C8[3][3] = { {a[0][0], a[0][1], a[0][2]}, {a[2][0], a[2][1], a[2][2]}, {a[3][0], a[3][1], a[3][2]} };
	float C9[3][3] = { {a[0][1], a[0][2], a[0][3]}, {a[1][1], a[1][2], a[1][3]}, {a[3][1], a[3][2], a[3][3]} };
	float C10[3][3] = { {a[0][0], a[0][2], a[0][3]}, {a[1][0], a[1][2], a[1][3]}, {a[3][0], a[3][2], a[3][3]} };
	float C11[3][3] = { {a[0][0], a[0][1], a[0][3]}, {a[1][0], a[1][1], a[1][3]}, {a[3][0], a[3][1], a[3][3]} };
	float C12[3][3] = { {a[0][0], a[0][1], a[0][2]}, {a[1][0], a[1][1], a[1][2]}, {a[3][0], a[3][1], a[3][2]} };
	float C13[3][3] = { {a[0][1], a[0][2], a[0][3]}, {a[1][1], a[1][2], a[1][3]}, {a[2][1], a[2][2], a[2][3]} };
	float C14[3][3] = { {a[0][0], a[0][2], a[0][3]}, {a[1][0], a[1][2], a[1][3]}, {a[2][0], a[2][2], a[2][3]} };
	float C15[3][3] = { {a[0][0], a[0][1], a[0][3]}, {a[1][0], a[1][1], a[1][3]}, {a[2][0], a[2][1], a[2][3]} };
	float C16[3][3] = { {a[0][0], a[0][1], a[0][2]}, {a[1][0], a[1][1], a[1][2]}, {a[2][0], a[2][1], a[2][2]} };
	////
	float detA = a[0][0] * Matrix3x3Calc(C1) - a[0][1] * Matrix3x3Calc(C2) + a[0][2] * Matrix3x3Calc(C3) - a[0][3] * Matrix3x3Calc(C4);
	
	if (detA == 0) return 0;

	result[0][0] = Matrix3x3Calc(C1) / detA;
	result[1][0] = Matrix3x3Calc(C2) / detA * (-1);
	result[2][0] = Matrix3x3Calc(C3) / detA;
	result[3][0] = Matrix3x3Calc(C4) / detA * (-1);
	result[0][1] = Matrix3x3Calc(C5) / detA * (-1);
	result[1][1] = Matrix3x3Calc(C6) / detA;
	result[2][1] = Matrix3x3Calc(C7) / detA * (-1);
	result[3][1] = Matrix3x3Calc(C8) / detA;
	result[0][2] = Matrix3x3Calc(C9) / detA;
	result[1][2] = Matrix3x3Calc(C10) / detA * (-1);
	result[2][2] = Matrix3x3Calc(C11) / detA;
	result[3][2] = Matrix3x3Calc(C12) / detA * (-1);
	result[0][3] = Matrix3x3Calc(C13) / detA * (-1);
	result[1][3] = Matrix3x3Calc(C14) / detA;
	result[2][3] = Matrix3x3Calc(C15) / detA * (-1);
	result[3][3] = Matrix3x3Calc(C16) / detA;

	arrayReturnPtr = (float*)result;

	return arrayReturnPtr;
}

float* ViewMatrix(float a[3][1] /*ī�޶� ��ġ*/, float c[3][1] /*ī�޶� �þ� ����*/) // ���� (x,y,z) ����ȭ �� �����Ƿ� �ϴ� 1�� �����
{
	float axisZ[4][1] = { {c[0][0]}, {c[1][0]}, {c[2][0]}, {0} }; // ī�޶� �þ� ���� -> ���ο� z��
	float* normZ = MatrixNormalize(axisZ); // z�� ����ȭ
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		axisZ[i][0] = *(normZ + count);
		count++;
	}

	float Up[4][1] = { {0}, {1}, {0}, {1} };
	float bParallel[3][1] = {};
	float* ifParallel = CrossProduct(axisZ, Up);
	count = 0;
	for (int i = 0; i < 3; i++)
	{
		bParallel[i][0] = *(ifParallel + count);
		count++;
	}

	float axisX[4][1] = {};
	float axisY[4][1] = {};
	if (bParallel[0][0] != 0 || bParallel[1][0] != 0 || bParallel[2][0] != 0) // ���� ī�޶� ��Ȳ�� up���Ͱ� ������ �ƴ϶��
	{
		//axisX[4][1] = { { c[2][0] }, { 0 }, { -c[0][0] }, { 0 } }; // Up ����(0,1,0)�� ī�޶� �þ� ����(z')�� ������ ���� ���ο� x��
		axisX[0][0] = c[2][0];
		axisX[1][0] = 0;
		axisX[2][0] = -c[0][0];

		float* normX = MatrixNormalize(axisX); // x�� ����ȭ
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisX[i][0] = *(normX + count);
			count++;
		}

		//axisY[4][1] = { { -(c[0][0] * c[1][0]) }, { (c[0][0] * c[0][0]) + (c[2][0] * c[2][0]) }, { -(c[1][0] * c[2][0]) }, { 0 } }; // x' ��� z' ���� ������ ���� ���ο� y��
		axisY[0][0] = -(c[0][0] * c[1][0]);
		axisY[1][0] = (c[0][0] * c[0][0]) + (c[2][0] * c[2][0]);
		axisY[2][0] = -(c[1][0] * c[2][0]);

		float* normY = MatrixNormalize(axisY); // y�� ����ȭ
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisY[i][0] = *(normY + count);
			count++;
		}
	}
	else
	{
		float newUp[4][1] = { { 0 },{ 0 },{ 1 },{ 1 } };
		ifParallel = CrossProduct(newUp, axisZ);
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisX[i][0] = *(ifParallel + count);
			count++;
		}

		float* normX = MatrixNormalize(axisX); // x�� ����ȭ
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisX[i][0] = *(normX + count);
			count++;
		}

		ifParallel = CrossProduct(axisZ, axisX);
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisY[i][0] = *(ifParallel + count);
			count++;
		}

		float* normY = MatrixNormalize(axisY); // y�� ����ȭ
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisY[i][0] = *(normY + count);
			count++;
		}
	}

	// �⺻���� �� ��� ����
	// ( ���ο�x���� x, ���ο� x���� y, ���ο� x���� z, Dot(ī�޶� ��ġ, ���ο� x���� ����) )
	// ( ���ο�y���� x, ���ο� y���� y, ���ο� y���� z, Dot(ī�޶� ��ġ, ���ο� y���� ����) )
	// ( ���ο�z���� x, ���ο� z���� y, ���ο� z���� z, Dot(ī�޶� ��ġ, ���ο� z���� ����) )
	// ( 0, 0, 0, 1)

	//// ���� ī�޶� ȸ���� ȸ�� ��ĺ��� ���� -> �ᱹ ī�޶��� ��ġ�� �������� ����� �۾�
	float cameraRotate[4][4] = {};
	float originX[3][1] = { { c[2][0] },{ 0 },{ -c[0][0] } }; //x��
	cameraRotate[0][0] = axisX[0][0]; cameraRotate[1][0] = axisX[1][0]; cameraRotate[2][0] = axisX[2][0];
	float originY[3][1] = { { -(c[0][0] * c[1][0]) },{ (c[0][0] * c[0][0]) + (c[2][0] * c[2][0]) },{ -(c[1][0] * c[2][0]) } }; //y��
	cameraRotate[0][1] = axisY[0][0]; cameraRotate[1][1] = axisY[1][0]; cameraRotate[2][1] = axisY[2][0];
	float originZ[3][1] = { { c[0][0] },{ c[1][0] },{ c[2][0] } }; //z��
	cameraRotate[0][2] = axisZ[0][0]; cameraRotate[1][2] = axisZ[1][0]; cameraRotate[2][2] = axisZ[2][0];
	cameraRotate[3][3] = 1;
	////////////////////////////
	//// ī�޶� ��ġ�� ���� �̵� ��� ����
	float cameraTrans[4][4] = {};
	cameraTrans[0][0] = 1; cameraTrans[1][1] = 1; cameraTrans[2][2] = 1; cameraTrans[3][3] = 1;
	cameraTrans[0][3] = a[0][0]; cameraTrans[1][3] = a[1][0]; cameraTrans[2][3] = a[2][0];
	////////////////////////////
	//// �� ����� ��
	float viewMatrix[4][4] = {};
	float* prtCamMulti = MatrixMulti(cameraTrans, cameraRotate);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			viewMatrix[i][j] = *(prtCamMulti + count);
			count++;
		}
	}
	////////////////////////////
	//// �� ����� ����� -> ī�޶� ������ �ݴ� �������� ��ü�� �����̴ϱ�.
	if (MatrixReverse(viewMatrix) == 0)
	{
		AfxMessageBox(_T("������� �������� �ʽ��ϴ�."));
		return 0;
	}
	float* prtCamReverse = MatrixReverse(viewMatrix);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			viewMatrix[i][j] = *(prtCamReverse + count);
			count++;
		}
	}
	////////////////////////////
	//// ī�޶��� z���� ��ü�� z���̶� ������ �� �ݴ� -> ī�޶�� ���� ���߷��� ���� ��ü�� +z ���� ī�޶� ���������� ȸ���Ǿ� -z���� ī�޶� ���� -> ��ü�� y������ 180�� ȸ��
	float rotateY[4][4] = {};
	rotateY[0][0] = -1; rotateY[1][1] = 1; rotateY[2][2] = -1; rotateY[3][3] = 1;
	float* prtCamMulti2 = MatrixMulti(rotateY, viewMatrix);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			viewMatrix[i][j] = *(prtCamMulti2 + count);
			count++;
		}
	}
	//////////////////////////// ī�޶� �������� ������ �� ���� ��ü ��ġ���� ī�޶� �̵��Ѹ�ŭ �ݴ�� �̵� -> ī�޶� ȸ���� �ݴ�� ȸ�� -> ��������� ���� �ݴ���� ���̴� ���� �����ϰ��� ��ü�� y�� 180�� ȸ��;
	/// ���� �� ��� �ϼ�

	//float result[4][4];
	//float originX[3][1] = { { c[2][0] },{ 0 },{ -c[0][0] } }; //x��
	//result[0][0] = axisX[0][0]; result[0][1] = axisX[1][0]; result[0][2] = axisX[2][0]; result[0][3] = DotProduct(a, originX);
	//float originY[3][1] = { { -(c[0][0] * c[1][0]) },{ (c[0][0] * c[0][0]) + (c[2][0] * c[2][0]) },{ -(c[1][0] * c[2][0]) } }; //y��
	//result[1][0] = axisY[0][0]; result[1][1] = axisY[1][0]; result[1][2] = axisY[2][0]; result[1][3] = DotProduct(a, originY);
	//float originZ[3][1] = { { c[0][0] },{ c[1][0] },{ c[2][0] } }; //z��
	//result[2][0] = axisZ[0][0]; result[2][1] = axisZ[1][0]; result[2][2] = axisZ[2][0]; result[2][3] = DotProduct(a, originZ);
	//result[3][0] = 0; result[3][1] = 0, result[3][2] = 0; result[3][3] = 1;

	//// �ش� �� ����� ������� ���� ��ü�� ��������� ��
	//float viewMatrix[4][4];
	//float* reverseResult = MatrixReverse(result);
	//count = 0;
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		viewMatrix[i][j] = *(reverseResult + count);
	//		count++;
	//	}
	//}

	return (float*)viewMatrix;
	//return (float*)result;
}

float* ProjectionMatrix(int width, int height, float angle)
{
	//GetClientRect()�� ��Ⱦ�� ���� ��
	float a = (float)width / (float)height;
	double distance = 1 / tan((angle/2) * pi / 180);
	float d = (float)distance;
	float projection[4][4] = {};
	projection[0][0] = d / a;
	projection[1][1] = d;

	projection[2][2] = -1;
	projection[3][3] = 1;
	
	arrayReturnPtr = (float*)projection;
	return arrayReturnPtr;
}
float* ProjectionMatrixParallel(int right, int left, int bottom, int top, float n, float f)
{
	float projection[4][4] = {};
	projection[0][0] = 2.f / (right - left);
	projection[1][1] = -2.f / (top - bottom);
	projection[2][2] = -2.f / (f - n);

	projection[2][3] = -(f + n) / (f - n);

	projection[3][3] = 1;

	arrayReturnPtr = (float*)projection;
	return arrayReturnPtr;
}

float* AffinTransform(float scaleX, float scaleY, float scaleZ, float angleX, float angleY, float angleZ, float transX, float transY, float transZ)
{
	float scale[4][4] = {};
	scale[0][0] = scaleX; scale[1][1] = scaleY; scale[2][2] = scaleZ; scale[3][3] = 1;

	double sinX = sin(angleX * pi / 180);
	double cosX = cos(angleX * pi / 180);
	double sinY = sin(angleY * pi / 180);
	double cosY = cos(angleY * pi / 180);
	double sinZ = sin(angleZ * pi / 180);
	double cosZ = cos(angleZ * pi / 180);
	float rotateX[4][4] = {};
	rotateX[0][0] = 1; rotateX[1][1] = (float)cosX; rotateX[1][2] = (float)sinX; rotateX[2][1] = (float)sinX * (-1); rotateX[2][2] = (float)cosX; rotateX[3][3] = 1;
	float rotateY[4][4] = {};
	rotateY[0][0] = (float)cosY; rotateY[0][2] = (float)sinY * (-1); rotateY[1][1] = 1; rotateY[2][0] = (float)sinY; rotateY[2][2] = (float)cosY; rotateY[3][3] = 1;
	float rotateZ[4][4] = {};
	rotateZ[0][0] = (float)cosZ; rotateZ[0][1] = (float)sinZ; rotateZ[1][0] = (float)sinZ * (-1); rotateZ[1][1] = (float)cosZ; rotateZ[2][2] = 1; rotateZ[3][3] = 1;

	float transform[4][4] = {};
	transform[0][0] = 1; transform[1][1] = 1; transform[2][2] = 1; transform[3][3] = 1;
	transform[0][3] = transX; transform[1][3] = transY; transform[2][3] = transZ;

	float result[4][4] = {}; // for������ �ٲ� �� ���� �� ����
	float* ptr = MatrixMulti(rotateX, scale);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = *(ptr + count);
			count++;
		}
	}
	ptr = MatrixMulti(rotateY, result);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = *(ptr + count);
			count++;
		}
	}
	ptr = MatrixMulti(rotateZ, result);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = *(ptr + count);
			count++;
		}
	}
	ptr = MatrixMulti(transform, result);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = *(ptr + count);
			count++;
		}
	}

	return (float*)result;
}

float ToScreenX(int width, long left, float x)
{
	float result;
	result = x * (width / 2) + left + width / 2;

	return result;
}
float ToScreenY(int height, long top, float y)
{
	float result;
	result = (-1) * y * (height / 2) + top + height / 2;

	return result;
}

float LightingCos(MyVertex p1, MyVertex p2, MyVertex p3)
{
	float testVector1[4][1] = {};
	float testVector2[4][1] = {};
	float testNorm[4][1] = {};
	float testA = (p1.x + p2.x + p3.x) / 3;
	float testB = (p1.y + p2.y + p3.y) / 3;
	float testC = (p1.z + p2.z + p3.z) / 3;
	float lightOrigin[4][1] = { { testA },{ testB },{ testC },{ 1 } };
	testVector1[0][0] = -p1.x + p2.x; testVector1[1][0] = -p1.y + p2.y; testVector1[2][0] = -p1.z + p2.z;
	testVector2[0][0] = -p2.x + p3.x; testVector2[1][0] = -p2.y + p3.y; testVector2[2][0] = -p2.z + p3.z;
	float* testPtr = CrossProduct(testVector1, testVector2);
	int testCount = 0;
	for (int k = 0; k < 4; k++)
	{
		testNorm[k][0] = *(testPtr + testCount);
		testCount++;
	}
	testPtr = MatrixNormalize(testNorm);
	testCount = 0;
	for (int k = 0; k < 4; k++)
	{
		testNorm[k][0] = *(testPtr + testCount);
		testCount++;
	}
	testPtr = MatrixNormalize(lightOrigin);
	testCount = 0;
	for (int k = 0; k < 4; k++)
	{
		lightOrigin[k][0] = *(testPtr + testCount);
		testCount++;
	}

	float lightOrigin3X3[3][1] = { { lightOrigin[0][0] },{ lightOrigin[1][0] },{ lightOrigin[2][0] } };
	float testNorm3X3[3][1] = { { testNorm[0][0] },{ testNorm[1][0] },{ testNorm[2][0] } };

	float testResult = DotProduct(testNorm3X3, lightOrigin3X3);
	if (testResult > 0) testResult = 0;

	return testResult;
}

float* MakeNewCoordinate(float c[3][1]) // ���� ī�޶� �����ִ� ����
{
#pragma region ���� ī�޶� �ٶ󺸰��ִ� ������ ī�޶���ǥ���� z���̶�� �� ��, xyz ���� ���⺤�� ���ϱ�
	float axisZ[4][1] = { { c[0][0] },{ c[1][0] },{ c[2][0] },{ 0 } }; // ī�޶� �þ� ���� -> ���ο� z��
	float* normZ = MatrixNormalize(axisZ); // z�� ����ȭ
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		axisZ[i][0] = *(normZ + count);
		count++;
	}
	float Up[4][1] = { { 0 },{ 1 },{ 0 },{ 1 } };
	float bParallel[3][1] = {};
	float* ifParallel = CrossProduct(axisZ, Up);
	count = 0;
	for (int i = 0; i < 3; i++)
	{
		bParallel[i][0] = *(ifParallel + count);
		count++;
	}

	float axisX[4][1] = {};
	float axisY[4][1] = {};
	if (bParallel[0][0] != 0 || bParallel[1][0] != 0 || bParallel[2][0] != 0) // ���� ī�޶� ��Ȳ�� up���Ͱ� ������ �ƴ϶��
	{
		axisX[0][0] = c[2][0];
		axisX[1][0] = 0;
		axisX[2][0] = -c[0][0];

		float* normX = MatrixNormalize(axisX); // x�� ����ȭ
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisX[i][0] = *(normX + count);
			count++;
		}

		axisY[0][0] = -(c[0][0] * c[1][0]);
		axisY[1][0] = (c[0][0] * c[0][0]) + (c[2][0] * c[2][0]);
		axisY[2][0] = -(c[1][0] * c[2][0]);

		float* normY = MatrixNormalize(axisY); // y�� ����ȭ
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisY[i][0] = *(normY + count);
			count++;
		}
	}
	else
	{
		float newUp[4][1] = { { 0 },{ 0 },{ 1 },{ 1 } };
		ifParallel = CrossProduct(newUp, axisZ);
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisX[i][0] = *(ifParallel + count);
			count++;
		}

		float* normX = MatrixNormalize(axisX); // x�� ����ȭ
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisX[i][0] = *(normX + count);
			count++;
		}

		ifParallel = CrossProduct(axisZ, axisX);
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisY[i][0] = *(ifParallel + count);
			count++;
		}

		float* normY = MatrixNormalize(axisY); // y�� ����ȭ
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			axisY[i][0] = *(normY + count);
			count++;
		}
	}
#pragma endregion
	//axisX, axisY, axisZ
	float axis[3][3] = { { axisX[0][0], axisX[1][0], axisX[2][0] },
						{axisY[0][0], axisY[1][0], axisY[2][0]},
						{axisZ[0][0], axisZ[1][0], axisZ[2][0]} };
	return (float*)axis;
}

float* vectorRotation(float rv[3][1], float sv[3][1], int angle) //(ȸ���� ����, ȸ���� ���ؼ�, ����)
{
	// rv = (0, v1), sv = (0, v2) ->���ʹϾ�
	float cosAngle = (float)cos((angle/2)*pi/180);
	float sinAngle = (float)sin((angle/2)*pi/180);

	float tv[4][1] = {};
	float rv41[4][1] = { {rv[0][0]}, {rv[1][0]}, {rv[2][0]}, 1 };
	float sv41[4][1] = { {sv[0][0] * sinAngle}, {sv[1][0] * sinAngle}, {sv[2][0] * sinAngle}, 1 };
	float* tvPtr = CrossProduct(sv41, rv41);
	int tvCount = 0;
	for (int i = 0; i < 4; i++)
	{
		tv[i][0] = *(tvPtr + tvCount);
		tv[i][0] *= 2;
		tvCount++;
	}
	float crsPrdRvTv[4][1] = {};
	tvPtr = CrossProduct(sv41, tv);
	tvCount = 0;
	for (int i = 0; i < 4; i++)
	{
		crsPrdRvTv[i][0] = *(tvPtr + tvCount);
		tvCount++;
	}

	float result[4][1] = {};
	for (int i = 0; i < 4; i++)
	{
		result[i][0] = rv[i][0] + cosAngle * tv[i][0] + crsPrdRvTv[i][0];
	}

	tvCount = 0;
	tvPtr = MatrixNormalize(result);
	for (int i = 0; i < 4; i++)
	{
		result[i][0] = *(tvPtr + tvCount);
		tvCount++;
	}

	return (float*)result;
}

float vectorLength(float a[3][1])
{
	float x = pow(a[0][0], 2);
	float y = pow(a[1][0], 2);
	float z = pow(a[2][0], 2);

	return sqrt(x + y + z);
}


float* Cube_isitFront(MyVertex vertex1, MyVertex vertex2, MyVertex vertex3, float camera[3][1], float look[3][1], float lightDirection[3][1])
{
	float brightness1[4][1] = {};
	float brightness2[4][1] = {};
	float brightNorm[3][1] = {};
	float dotProd, dotResult1, dotResult2, dotResult3, dotResultParallel;
	float originToVertex1[3][1], originToVertex2[3][1], originToVertex3[3][1];
	int rgbRate;
	float* bPtr;
	int bCount;

	brightness1[0][0] = -vertex1.x + vertex2.x; brightness1[1][0] = -vertex1.y + vertex2.y;
	brightness1[2][0] = -vertex1.z + vertex2.z;
	brightness2[0][0] = -vertex2.x + vertex3.x; brightness2[1][0] = -vertex2.y + vertex3.y;
	brightness2[2][0] = -vertex2.z + vertex3.z;
	originToVertex1[0][0] = -camera[0][0] + vertex1.x; originToVertex1[1][0] = -camera[1][0] + vertex1.y;
	originToVertex1[2][0] = -camera[2][0] + vertex1.z;
	originToVertex2[0][0] = -camera[0][0] + vertex2.x; originToVertex2[1][0] = -camera[1][0] + vertex2.y;
	originToVertex2[2][0] = -camera[2][0] + vertex2.z;
	originToVertex3[0][0] = -camera[0][0] + vertex3.x; originToVertex3[1][0] = -camera[1][0] + vertex3.y;
	originToVertex3[2][0] = -camera[2][0] + vertex3.z;

	bPtr = CrossProduct(brightness1, brightness2);
	bCount = 0;
	for (int i = 0; i < 3; i++)
	{
		brightNorm[i][0] = *(bPtr + bCount);
		bCount++;
	}
	dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
	if (dotProd < 0)dotProd = 0;
	dotResult1 = DotProduct(brightNorm, originToVertex1);
	dotResult2 = DotProduct(brightNorm, originToVertex2);
	dotResult3 = DotProduct(brightNorm, originToVertex3);
	dotResultParallel = DotProduct(brightNorm, look) / vectorLength(look);
	
	float result[5] = { dotProd, dotResult1, dotResult2, dotResult3, dotResultParallel };

	return (float*)result;
}
void CubeMeshDraw(int projNum, float meshData[5], CDC* memDC, float width, float height, float left, float top, MyVertex p1, MyVertex p2, MyVertex p3)
{
	CBrush brush;
	CBrush* prevBrush;
	float dotProd, dotResult1, dotResult2, dotResult3, dotResultParallel;
	int rgbRate;
	if (projNum == 0)
	{
		dotResult1 = meshData[1]; dotResult2 = meshData[2]; dotResult3 = meshData[3];

		if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
		{
			rgbRate = (int)round(80 + 175 * meshData[0]);
			brush.CreateSolidBrush(RGB(0, rgbRate, 0));
			prevBrush = memDC->SelectObject(&brush);
			memDC->BeginPath();
			memDC->MoveTo(ToScreenX(width, left, p1.x), ToScreenY(height, top, p1.y));
			memDC->LineTo(ToScreenX(width, left, p2.x), ToScreenY(height, top, p2.y));
			memDC->LineTo(ToScreenX(width, left, p3.x), ToScreenY(height, top, p3.y));
			memDC->LineTo(ToScreenX(width, left, p1.x), ToScreenY(height, top, p1.y));
			memDC->EndPath();
			memDC->StrokeAndFillPath();
			memDC->SelectObject(prevBrush);
			brush.DeleteObject();
		}
	}
	else
	{
		dotResultParallel = meshData[4];
		if (dotResultParallel <= 0)
		{
			rgbRate = (int)round(255 * meshData[0]);
			brush.CreateSolidBrush(RGB(0, rgbRate, 0));
			prevBrush = memDC->SelectObject(&brush);
			memDC->BeginPath();
			memDC->MoveTo(ToScreenX(width, left, p1.x), ToScreenY(height, top, p1.y));
			memDC->LineTo(ToScreenX(width, left, p2.x), ToScreenY(height, top, p2.y));
			memDC->LineTo(ToScreenX(width, left, p3.x), ToScreenY(height, top, p3.y));
			memDC->LineTo(ToScreenX(width, left, p1.x), ToScreenY(height, top, p1.y));
			memDC->EndPath();
			memDC->StrokeAndFillPath();
			memDC->SelectObject(prevBrush);
			brush.DeleteObject();
		}
	}
}
void CubeLineDraw(int projNum, float meshData[5], CDC* memDC, float width, float height, float left, float top, MyVertex p1, MyVertex p2, MyVertex p3)
{
	float dotResult1, dotResult2, dotResult3, dotResultParallel;
	if (projNum == 0)
	{
		dotResult1 = meshData[1];
		dotResult2 = meshData[2];
		dotResult3 = meshData[3];
		if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
		{
			memDC->MoveTo(ToScreenX(width, left, p1.x), ToScreenY(height, top, p1.y));
			memDC->LineTo(ToScreenX(width, left, p2.x), ToScreenY(height, top, p2.y));
			memDC->LineTo(ToScreenX(width, left, p3.x), ToScreenY(height, top, p3.y));
			memDC->LineTo(ToScreenX(width, left, p1.x), ToScreenY(height, top, p1.y));
		}
	}
	else
	{
		dotResultParallel = meshData[4];
		if (dotResultParallel <= 0)
		{
			memDC->MoveTo(ToScreenX(width, left, p1.x), ToScreenY(height, top, p1.y));
			memDC->LineTo(ToScreenX(width, left, p2.x), ToScreenY(height, top, p2.y));
			memDC->LineTo(ToScreenX(width, left, p3.x), ToScreenY(height, top, p3.y));
			memDC->LineTo(ToScreenX(width, left, p1.x), ToScreenY(height, top, p1.y));
		}
	}
}

void DrawSphereLine(int i, CDC* memDC, float width, float height, float left, float top, MyVertex v1, MyVertex v2, MyVertex v3, MyVertex vException)
{
	memDC->MoveTo(ToScreenX(width, left, v1.x), ToScreenY(height, top, v1.y));
	memDC->LineTo(ToScreenX(width, left, v2.x), ToScreenY(height, top, v2.y));
	if (i % 12 == 0)
	{
		memDC->LineTo(ToScreenX(width, left, v3.x), ToScreenY(height, top, v3.y));
	}
	else
	{
		memDC->LineTo(ToScreenX(width, left, vException.x), ToScreenY(height, top, vException.y));
	}
	memDC->LineTo(ToScreenX(width, left, v1.x), ToScreenY(height, top, v1.y));
}
void DrawSphereMesh(int i, int start, CDC* memDC, float width, float height, float left, float top, MyVertex v1, MyVertex v2, MyVertex v3, MyVertex vException, int* array)
{
	CBrush brush;
	CBrush* prevBrush;
	brush.CreateSolidBrush(RGB(0, *(array + (i - start)), 0));
	prevBrush = memDC->SelectObject(&brush);

	memDC->BeginPath();
	memDC->MoveTo(ToScreenX(width, left, v1.x), ToScreenY(height, top, v1.y));
	memDC->LineTo(ToScreenX(width, left, v2.x), ToScreenY(height, top, v2.y));
	if (i % 12 == 0)
	{
		memDC->LineTo(ToScreenX(width, left, v3.x), ToScreenY(height, top, v3.y));
	}
	else
	{
		memDC->LineTo(ToScreenX(width, left, vException.x), ToScreenY(height, top, vException.y));
	}
	memDC->LineTo(ToScreenX(width, left, v1.x), ToScreenY(height, top, v1.y));
	memDC->EndPath();
	memDC->StrokeAndFillPath();
	memDC->SelectObject(prevBrush);
	brush.DeleteObject();
}

void DrawTorusLine(CDC* memDC, float width, float height, float left, float top, MyVertex v1, MyVertex v2, MyVertex v3)
{
	memDC->MoveTo(ToScreenX(width, left, v1.x), ToScreenY(height, top, v1.y));
	memDC->LineTo(ToScreenX(width, left, v2.x), ToScreenY(height, top, v2.y));
	memDC->LineTo(ToScreenX(width, left, v3.x), ToScreenY(height, top, v3.y));
	memDC->LineTo(ToScreenX(width, left, v1.x), ToScreenY(height, top, v1.y));
}
void DrawTorusMesh(int i, int* RGB_array, CDC* memDC, float width, float height, float left, float top, MyVertex v1, MyVertex v2, MyVertex v3)
{
	CBrush torBrush;
	CBrush* prevBrush;
	torBrush.CreateSolidBrush(RGB(0, *(RGB_array + i), 0));
	prevBrush = memDC->SelectObject(&torBrush);

	memDC->BeginPath();
	memDC->MoveTo(ToScreenX(width, left, v1.x), ToScreenY(height, top, v1.y));
	memDC->LineTo(ToScreenX(width, left, v2.x), ToScreenY(height, top, v2.y));
	memDC->LineTo(ToScreenX(width, left, v3.x), ToScreenY(height, top, v3.y));
	memDC->LineTo(ToScreenX(width, left, v1.x), ToScreenY(height, top, v1.y));
	memDC->EndPath();
	memDC->StrokeAndFillPath();
	memDC->SelectObject(prevBrush);
	torBrush.DeleteObject();
}


BOOL isItUpperSide(float NormDirectionVector[3][1], float pointOnPlane[3][1], float point[3][1])
{
	float result = NormDirectionVector[0][0] * (point[0][0] - pointOnPlane[0][0]) + 
		NormDirectionVector[1][0] * (point[1][0] - pointOnPlane[1][0]) + 
		NormDirectionVector[2][0] * (point[2][0] - pointOnPlane[2][0]);

	if (result >= 0) return TRUE;
	else return FALSE;
}