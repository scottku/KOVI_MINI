#include <stdio.h>
#include <cmath>
#include "stdafx.h"
#include "Matrix.h"

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

float* ViewMatrix(float a[3][1] /*ī�޶� ��ġ*/, float b[3][1]  /*��ü ��ġ*/, float c[3][1] /*ī�޶� �þ� ����*/) // ���� (x,y,z) ����ȭ �� �����Ƿ� �ϴ� 1�� �����
{
	float axisZ[4][1] = { {c[0][0]}, {c[1][0]}, {c[2][0]}, {0} }; // ī�޶� �þ� ���� -> ���ο� z��
	float* normZ = MatrixNormalize(axisZ); // z�� ����ȭ
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		axisZ[i][0] = *(normZ + count);
		count++;
	}
	float cameraToMaterial[4][1] = { {b[0][0] - a[0][0]}, {b[1][0] - a[1][0]}, {b[2][0] - a[2][0]}, {0} };

	float axisX[4][1] = { {c[2][0]}, {0}, {-c[0][0]}, {0} }; // Up ����(0,1,0)�� ī�޶� �þ� ����(z')�� ������ ���� ���ο� x��
	float* normX = MatrixNormalize(axisX); // x�� ����ȭ
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		axisX[i][0] = *(normX + count);
		count++;
	}

	float axisY[4][1] = { {-(c[0][0] * c[1][0])}, {(c[0][0] * c[0][0]) + (c[2][0] * c[2][0])}, {-(c[1][0] * c[2][0])}, {0} }; // x' ��� z' ���� ������ ���� ���ο� y��
	float* normY = MatrixNormalize(axisY); // y�� ����ȭ
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		axisY[i][0] = *(normY + count);
		count++;
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

float* ProjectionMatrix(int width, int height, float angle, float n, float f)
{
	//GetClientRect()�� ��Ⱦ�� ���� ��
	n = -n;
	f = -f;
	float a = width / height;
	double distance = 1 / tan((angle/2) * pi / 180);
	float d = (float)distance;
	float projection[4][4] = {};
	projection[0][0] = d / a;
	projection[1][1] = d;
	projection[2][2] = -1;
	projection[3][3] = 1;
	//// �Ÿ��� ���߿� �߰�
	//projection[2][2] = (n + f) / (n - f);
	//projection[2][3] = (2 * n * f) / (n - f);
	//projection[3][2] = -1;

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