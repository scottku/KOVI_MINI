// MFCApplication3View.cpp : CMFCApplication3View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"
#include "MainFrm.h"
#include "Figure.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

// 만든 파일들
#include "Matrix.h"
//////////////

extern int figureNum;
extern int projNum;
extern int frameNum;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication3View 생성/소멸

CMFCApplication3View::CMFCApplication3View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	v_torusFigure = {};
	cameraX = 0;
	cameraY = 0;
	cameraZ = -300;
	cameraRotateX = 5;
	cameraRotateY = 5;
	rotateXCount = 0;
	rotateYCount = 0;
	//lookX = -cos(62 * M_PI / 180);
	//lookZ = -sin(62 * M_PI / 180);
	lookX = 0;
	lookY = 0;
	lookZ = -1;
	moveDirX.x = 0;
	moveDirX.y = 0;
	width = 0;
	left = 0;
	top = 0;
	height = 0;
	right = 0;
	bottom = 0;
	lightDirX = -1;
	lightDirY = -2;
	lightDirZ = -3;
	camera[0][0] = cameraX;
	camera[1][0] = cameraY;
	camera[2][0] = cameraZ;
	look[0][0] = lookX;
	look[1][0] = lookY;
	look[2][0] = lookZ;
	fPlane = 326.5;
	nPlane = 1;
	camAxisX[0][0] = -1; camAxisX[1][0] = 0; camAxisX[2][0] = 0;
	camAxisY[0][0] = 0; camAxisY[1][0] = 1; camAxisY[2][0] = 0;
	camAxisZ[0][0] = lookX; camAxisZ[1][0] = lookY; camAxisZ[2][0] = lookZ;
}

CMFCApplication3View::~CMFCApplication3View()
{
	v_cubeFigure.clear();
	v_sphereFigure.clear();
	v_torusFigure.clear();
	vector<CubeInfo>().swap(v_cubeFigure);
	vector<SphereInfo>().swap(v_sphereFigure);
	vector<TorusInfo>().swap(v_torusFigure);
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View 그리기

void CMFCApplication3View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMFCApplication3View 인쇄

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCApplication3View 진단

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View 메시지 처리기
void CMFCApplication3View::OnPaint()
{
	if (figureNum == -1)
	{
		v_cubeFigure.clear();
		v_sphereFigure.clear();
		v_torusFigure.clear();
		figureNum = 0;
		return;
	}

	// 그리기 준비
	CPaintDC cdc(this);
	CRect rect;
	GetClientRect(&rect);
	right = rect.right;
	bottom = rect.bottom;
	width = rect.Width();
	height = rect.Height();
	left = rect.left;
	top = rect.top;

	CDC memDC;
	CDC* memDCPtr = &memDC;
	CBitmap myBitmap;
	CBitmap* pOldBitmap;

	memDC.CreateCompatibleDC(&cdc);
	myBitmap.CreateCompatibleBitmap(&cdc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&myBitmap);

	// 메모리 DC에 그리기
	CBrush bgBrush(RGB(0, 0, 255));
	CBrush* pOldBrush = memDC.SelectObject(&bgBrush);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), /*WHITENESS*/ PATCOPY);
	memDC.SelectObject(pOldBrush);
	DeleteObject(bgBrush);

	CPen newPen;
	newPen.CreatePen(PS_SOLID, 0.5, RGB(255, 255, 255));
	CPen* oldPen = memDC.SelectObject(&newPen);

	#pragma region 절두체 컬링 준비
	// far 평면의 1사분면의 점
	float farPoint1[4][1] = { { fPlane * (width / height) },{ fPlane },{ -fPlane },{ 1 } };
	// far 평면의 3사분면의 점
	float farPoint3[4][1] = { { -fPlane * (width / height) },{ -fPlane },{ -fPlane },{ 1 } };
	// 근평면의 점들
	float nearPoint1[4][1] = { { 1 },{ 1 } ,{ -1 } ,{ 1 } };
	float nearPoint2[4][1] = { { -1 },{ 1 },{ -1 },{ 1 } };
	float nearPoint3[4][1] = { { -1 },{ -1 },{ -1 },{ 1 } };
	float nearPoint4[4][1] = { { 1 },{ -1 },{ -1 },{ 1 } };
	// 해당 점들을 이용해 벡터 생성
	float shortVector3[4][1], longVector3AND12[4][1], shortVector12[4][1], shortVector9[4][1], longVector9AND6[4][1], shortVector6[4][1];
	for (int i = 0; i < 3; i++)
	{
		shortVector3[i][0] = -nearPoint1[i][0] + nearPoint4[i][0];
		longVector3AND12[i][0] = -nearPoint1[i][0] + farPoint1[i][0];
		shortVector12[i][0] = -nearPoint1[i][0] + nearPoint2[i][0];
		shortVector9[i][0] = -nearPoint3[i][0] + nearPoint2[i][0];
		longVector9AND6[i][0] = -nearPoint3[i][0] + farPoint3[i][0];
		shortVector6[i][0] = -nearPoint3[i][0] + nearPoint4[i][0];
	}
	shortVector3[3][0] = longVector3AND12[3][0] = shortVector12[3][0] = shortVector9[3][0] = longVector9AND6[3][0] = shortVector6[3][0] = 1;
	// 평면 6개 중 4개에 대한 법선방향벡터 지정(정면 기준 3시 12시 9시 6시 방향의 면)
	float normOfFrustum3[3][1] = {};
	float normOfFrustum12[3][1] = {};
	float normOfFrustum9[3][1] = {};
	float normOfFrustum6[3][1] = {};

	#pragma region 3시방향 면 법선방향벡터
	float* frustumPtr = CrossProduct(longVector3AND12, shortVector3);
	int frustumCount = 0;
	for (int i = 0; i < 3; i++)
	{
		normOfFrustum3[i][0] = *(frustumPtr + frustumCount);
		frustumCount++;
	}
	frustumPtr = MatrixNormalize(normOfFrustum3);
	frustumCount = 0;
	for (int i = 0; i < 3; i++)
	{
		normOfFrustum3[i][0] = *(frustumPtr + frustumCount);
		frustumCount++;
	}
#pragma endregion
	#pragma region 12시방향 면 법선방향벡터
	frustumPtr = CrossProduct(shortVector12, longVector3AND12);
	frustumCount = 0;
	for (int i = 0; i < 3; i++)
	{
		normOfFrustum12[i][0] = *(frustumPtr + frustumCount);
		frustumCount++;
	}
	frustumPtr = MatrixNormalize(normOfFrustum12);
	frustumCount = 0;
	for (int i = 0; i < 3; i++)
	{
		normOfFrustum12[i][0] = *(frustumPtr + frustumCount);
		frustumCount++;
	}
#pragma endregion
	#pragma region 9시방향 면 법선방향벡터
	frustumPtr = CrossProduct(longVector9AND6, shortVector9);
	frustumCount = 0;
	for (int i = 0; i < 3; i++)
	{
		normOfFrustum9[i][0] = *(frustumPtr + frustumCount);
		frustumCount++;
	}
	frustumPtr = MatrixNormalize(normOfFrustum9);
	frustumCount = 0;
	for (int i = 0; i < 3; i++)
	{
		normOfFrustum9[i][0] = *(frustumPtr + frustumCount);
		frustumCount++;
	}
#pragma endregion
	#pragma region 6시방향 면 법선방향벡터
	frustumPtr = CrossProduct(shortVector6, longVector9AND6);
	frustumCount = 0;
	for (int i = 0; i < 3; i++)
	{
		normOfFrustum6[i][0] = *(frustumPtr + frustumCount);
		frustumCount++;
	}
	frustumPtr = MatrixNormalize(normOfFrustum6);
	frustumCount = 0;
	for (int i = 0; i < 3; i++)
	{
		normOfFrustum6[i][0] = *(frustumPtr + frustumCount);
		frustumCount++;
	}
#pragma endregion

	// 만약 평행 투영이면 다른 법선방향벡터를 사용해야함
	float normOfParallel3[3][1] = { { -1 },{ 0 },{ 0 } };
	float pointOn3AND12[3][1] = { { width / 2 },{ height / 2 },{ -1 } };
	float normOfParallel12[3][1] = { { 0 },{ -1 },{ 0 } };
	float normOfParallel9[3][1] = { { 1 },{ 0 },{ 0 } };
	float pointOn9AND6[3][1] = { { -width / 2 },{ -height / 2 },{ -1 } };
	float normOfParallel6[3][1] = { { 0 },{ 1 },{ 0 } };
	float pointOnFar[3][1] = { { width / 2 },{ height / 2 },{ -300 } };


	// 공통으로 사용하는 앞면의 법선방향벡터
	float normOfNear[3][1] = { { 0 },{ 0 },{ -1 } };
	// 공통으로 사용하는 뒷면의 법선방향벡터
	float normOfFar[3][1] = { { 0 },{ 0 },{ 1 } };
	#pragma endregion

	#pragma region 연산에 사용할 뷰 & 투영행렬 미리 제작 + 역행렬까지
	look[0][0] = lookX; look[1][0] = lookY; look[2][0] = lookZ;
	float view[4][4] = {};
	camera[0][0] = cameraX; camera[1][0] = cameraY; camera[2][0] = cameraZ;
	float* viewPtr = ViewMatrix(camera, camAxisZ, camAxisX, camAxisY);
	int viewCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			view[i][j] = *(viewPtr + viewCount);
			viewCount++;
		}
	}
	// 뷰 역행렬
	float viewReverse[4][4] = {};
	viewPtr = MatrixReverse(view);
	viewCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			viewReverse[i][j] = *(viewPtr + viewCount);
			viewCount++;
		}
	}
	// 투영 행렬
	float proj[4][4] = {};
	float* pPtr;
	if (projNum == 0)
	{
		pPtr = ProjectionMatrix(width, height, 90);
	}
	else
	{
		pPtr = ProjectionMatrixParallel(right, left, bottom, top, nPlane, fPlane);
	}
	int prjCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			proj[i][j] = *(pPtr + prjCount);
			prjCount++;
		}
	}
	// 투영 역행렬
	float projReverse[4][4] = {};
	pPtr = MatrixReverse(proj);
	prjCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			projReverse[i][j] = *(pPtr + prjCount);
			prjCount++;
		}
	}
	// 빛 방향에 대한 방향벡터 생성
	float lightDirection41[4][1] = { { lightDirX },{ lightDirY },{ lightDirZ },{ 1 } };
	float* lPtr = MatrixNormalize(lightDirection41);
	float lightDirection[3][1] = {};
	int ldCount = 0;
	for (int i = 0; i < 3; i++)
	{
		lightDirection[i][0] = *(lPtr + ldCount);
		ldCount++;
	}
	#pragma endregion

	for (auto& figure : v_cubeFigure)
	{
		int count = 0;
		MyVertex cub[8] = {};
		MyVertex cub_original[8] = {};
		for (int i = 0; i < 8; i++)
		{
			cub[i] = figure.cube[i];
			cub_original[i] = figure.cube[i];
			count++;
		}

		#pragma region 도형의 크기, 회전, 이동
		if (figure.length != figure.originLength) // 크기 변경이 된 친구라면?
		{
			MyVertex* makingCube = pCube(figure.length, figure.cubeOrigin.x, figure.cubeOrigin.y, figure.cubeOrigin.z); // 다시 만들어서 넣어줌
			int cubeCount = 0;
			for (int i = 0; i < 8; i++)
			{
				cub[i] = *(makingCube + cubeCount);
				cub_original[i] = *(makingCube + cubeCount);
				cubeCount++;
			}
		}

		////// 월드 좌표계에서 회전시키기
		float originInView[4][1] = {};
		originInView[0][0] = figure.cubeOrigin.x; originInView[1][0] = figure.cubeOrigin.y; originInView[2][0] = figure.cubeOrigin.z; originInView[3][0] = 1;
		float* fPtr = MatrixMulti(view, originInView);
		int sampleCount = 0;

		for (int i = 0; i < 8; i++) // 월드 좌표계에서의 큐브 중심을 원점으로 옮기면서 나머지 점들도 다 동일하게 옮겨줌
		{
			cub[i].x -= originInView[0][0];
			cub[i].y -= originInView[1][0];
			cub[i].z -= originInView[2][0];
		}

		for (int i = 0; i < 8; i++) // 해당 점들을 축을 기준으로 회전
		{
			float sample[4][1] = { { cub[i].x },{ cub[i].y },{ cub[i].z },{ 1 } };
			float* rotPtr = MatrixRotate(sample, figure.rotX, figure.rotY, 0);
			sampleCount = 0;
			for (int j = 0; j < 4; j++)
			{
				sample[j][0] = *(rotPtr + sampleCount);
				sampleCount++;
			}
			cub[i].x = sample[0][0]; cub[i].y = sample[1][0]; cub[i].z = sample[2][0];
		}

		for (int i = 0; i < 8; i++) // 다시 큐브의 중심을 원점에서 원래의 중심으로 복구
		{
			cub[i].x += originInView[0][0];
			cub[i].y += originInView[1][0];
			cub[i].z += originInView[2][0];
		}

		////// 월드 좌표계에서 x, y축으로 평행이동 시키기
		if (figure.moveY != 0)
		{
			for (int i = 0; i < 8; i++)
			{
				cub[i].y += figure.moveY;
				figure.cubeOrigin_moved.y += figure.moveY;
			}
		}
		if (figure.moveX != 0)
		{
			for (int i = 0; i < 8; i++)
			{
				cub[i].x += figure.moveX;
				figure.cubeOrigin_moved.x += figure.moveX;
			}
		}
		if (figure.moveZ != 0)
		{
			for (int i = 0; i < 8; i++)
			{
				cub[i].z += figure.moveZ;
				figure.cubeOrigin_moved.z += figure.moveZ;
			}
		}
		#pragma endregion

		MyVertex newCubeWC[8] = {};
		float tempVertex[4][1] = {};
		for (int i = 0; i < 8; i++)
		{
			newCubeWC[i].x = cub[i].x; newCubeWC[i].y = cub[i].y; newCubeWC[i].z = cub[i].z;
		}

		float sample[4][1] = {};
		// sphere 각 점들을 뷰 행렬 변환 시킴
		for (int i = 0; i < 8; i++)
		{
			sample[0][0] = cub[i].x;
			sample[1][0] = cub[i].y;
			sample[2][0] = cub[i].z;
			sample[3][0] = 1;
			fPtr = MatrixMulti(view, sample);

			int cubCount = 0;
			cub[i].x = *(fPtr + cubCount);
			cubCount++;
			cub[i].y = *(fPtr + cubCount);
			cubCount++;
			cub[i].z = *(fPtr + cubCount);
			cubCount++;
		}

		#pragma region 절두체 컬링
		if (projNum == 0)
		{
			BOOL isItUpper[8] = {};
			for (int i = 0; i < 8; i++)
			{
				float vertexOfCube[3][1] = { { cub[i].x },{ cub[i].y },{ cub[i].z } };
				BOOL result1 = isItUpperSide(normOfFrustum3, nearPoint1, vertexOfCube);
				BOOL result2 = isItUpperSide(normOfFrustum12, nearPoint1, vertexOfCube);
				BOOL result3 = isItUpperSide(normOfFrustum9, nearPoint3, vertexOfCube);
				BOOL result4 = isItUpperSide(normOfFrustum6, nearPoint3, vertexOfCube);
				BOOL result5 = isItUpperSide(normOfNear, nearPoint3, vertexOfCube);
				//BOOL result6 = isItUpperSide(normOfFar, farPoint3, vertexOfCube);
				//if (result1 && result2 && result3 && result4 && result5 && result6) isItUpper[i] = TRUE;
				if (result1 && result2 && result3 && result4 && result5) isItUpper[i] = TRUE;
				else isItUpper[i] = FALSE;
			}
			BOOL bDrawBlock = FALSE;
			for (int i = 0; i < 8; i++)
			{
				if (isItUpper[i]) break;
				if (i == 7) bDrawBlock = TRUE;
			}
			if (bDrawBlock)
			{
				figure.isFront = FALSE;
				continue;
			}
		}
		else
		{
			BOOL isItUpper[8] = {};
			for (int i = 0; i < 8; i++)
			{
				float vertexOfCube[3][1] = { { cub[i].x },{ cub[i].y },{ cub[i].z } };
				BOOL result1 = isItUpperSide(normOfParallel3, pointOn3AND12, vertexOfCube);
				BOOL result2 = isItUpperSide(normOfParallel12, pointOn3AND12, vertexOfCube);
				BOOL result3 = isItUpperSide(normOfParallel9, pointOn9AND6, vertexOfCube);
				BOOL result4 = isItUpperSide(normOfParallel6, pointOn9AND6, vertexOfCube);
				BOOL result5 = isItUpperSide(normOfNear, pointOn3AND12, vertexOfCube);
				//BOOL result6 = isItUpperSide(normOfFar, pointOnFar, vertexOfCube);
				//if (result1 && result2 && result3 && result4 && result5 && result6) isItUpper[i] = TRUE;
				if (result1 && result2 && result3 && result4 && result5) isItUpper[i] = TRUE;
				else isItUpper[i] = FALSE;
			}
			BOOL bDrawBlock = FALSE;
			for (int i = 0; i < 8; i++)
			{
				if (isItUpper[i]) break;
				if (i == 7) bDrawBlock = TRUE;
			}
			if (bDrawBlock)
			{
				figure.isFront = FALSE;
				continue;
			}
		}
		figure.isFront = TRUE;
		#pragma endregion

		// sphere 각 점들을 투영 시킴
		for (int i = 0; i < 8; i++)
		{
			sample[0][0] = cub[i].x;
			sample[1][0] = cub[i].y;
			sample[2][0] = cub[i].z;
			sample[3][0] = 1;
			fPtr = MatrixMulti(proj, sample);
			int cubCount = 0;

			cub[i].x = *(fPtr + cubCount);
			cubCount++;
			cub[i].y = *(fPtr + cubCount);
			cubCount++;
			cub[i].z = *(fPtr + cubCount);
			cubCount++;
			if (projNum == 0)
			{
				cub[i].x /= cub[i].z;
				cub[i].y /= cub[i].z;
			}
		}

		// picking을 위해 스크린에 찍힌 점들의 값을 미리 저장
		for (int i = 0; i < 8; i++)
		{
			figure.cube_justForClick[i].x = ToScreenX(width, left, cub[i].x);
			figure.cube_justForClick[i].y = ToScreenY(height, top, cub[i].y);
			figure.cube_justForClick[i].z = 0;
		}

		float brightness1[4][1] = {};
		float brightness2[4][1] = {};
		float brightNorm[3][1] = {};
		float dotProd, dotResult1, dotResult2, dotResult3, dotResultParallel;
		float originToVertex1[3][1], originToVertex2[3][1], originToVertex3[3][1];
		int rgbRate;
		float* bPtr;
		int bCount;
		CBrush rectBrush;
		CBrush* prevBrush;
		if (frameNum == 1)
		{
			if (figure.isClicked)
			{
#pragma region 1번 꼭짓점 - 면
				float* frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[3], newCubeWC[4], camera, look, lightDirection);
				float meshData[5] = {};
				int count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[3], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[4], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[4], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[1], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[1], cub[3]);
#pragma endregion
#pragma region 2번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[4], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[4], cub[3]);

				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[6], newCubeWC[4], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[6], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[3], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[3], cub[6]);
#pragma endregion
#pragma region 3번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[1], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[1], cub[6]);

				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[3], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[3], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[6], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[6], cub[3]);
#pragma endregion
#pragma region 4번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[6], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[6], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[1], newCubeWC[4], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[1], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[4], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[4], cub[6]);
#pragma endregion
			}
			else
			{
#pragma region 1번 꼭짓점 - 선
				float* frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[3], newCubeWC[4], camera, look, lightDirection);
				float meshData[5] = {};
				int count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[3], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[4], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[4], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[1], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[1], cub[3]);
#pragma endregion
#pragma region 2번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[4], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[4], cub[3]);

				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[6], newCubeWC[4], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[6], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[3], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[3], cub[6]);
#pragma endregion
#pragma region 3번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[1], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[1], cub[6]);

				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[3], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[3], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[6], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[6], cub[3]);
#pragma endregion
#pragma region 4번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[6], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[6], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[1], newCubeWC[4], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[1], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[4], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[4], cub[6]);
#pragma endregion
			}
		}
		else
		{
			if (figure.isClicked)
			{
#pragma region 1번 꼭짓점 - 선
				float* frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[3], newCubeWC[4], camera, look, lightDirection);
				float meshData[5] = {};
				int count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[3], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[4], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[4], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[1], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[1], cub[3]);
#pragma endregion
#pragma region 2번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[4], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[4], cub[3]);

				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[6], newCubeWC[4], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[6], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[3], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[3], cub[6]);
#pragma endregion
#pragma region 3번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[1], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[1], cub[6]);

				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[3], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[3], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[6], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[6], cub[3]);
#pragma endregion
#pragma region 4번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[6], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[6], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[1], newCubeWC[4], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[1], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[4], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeLineDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[4], cub[6]);
#pragma endregion
			}
			else
			{
#pragma region 1번 꼭짓점 - 면
				float* frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[3], newCubeWC[4], camera, look, lightDirection);
				float meshData[5] = {};
				int count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[3], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[4], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[4], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[0], newCubeWC[1], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[0], cub[1], cub[3]);
#pragma endregion
#pragma region 2번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[4], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[4], cub[3]);

				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[6], newCubeWC[4], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[6], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[7], newCubeWC[3], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[7], cub[3], cub[6]);
#pragma endregion
#pragma region 3번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[1], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[1], cub[6]);

				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[3], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[3], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[2], newCubeWC[6], newCubeWC[3], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[2], cub[6], cub[3]);
#pragma endregion
#pragma region 4번 꼭짓점
				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[6], newCubeWC[1], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[6], cub[1]);

				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[1], newCubeWC[4], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[1], cub[4]);

				frontPtr = Cube_isitFront(newCubeWC[5], newCubeWC[4], newCubeWC[6], camera, look, lightDirection);
				count = 0;
				for (int i = 0; i < 5; i++)
				{
					meshData[i] = *(frontPtr + count);
					count++;
				}
				CubeMeshDraw(projNum, meshData, memDCPtr, width, height, left, top, cub[5], cub[4], cub[6]);
#pragma endregion
			}
		}
	}

	for (auto& figure : v_sphereFigure)
	{
		// vector로부터 구 좌표 받아오기
		int count = 0;
		MyVertex sph[230] = {};
		for (int i = 0; i < 230; i++) {
			sph[i] = figure.sphere[i];
			count++;
		}
		#pragma region 도형의 크기, 회전, 이동 변환
		if (figure.radius != figure.originRadius) // 크기 변경이 된 친구라면?
		{ // 다시 만들어서 넣어줌
			MyVertex* makingSphere = pSphere(figure.radius, figure.sphereOrigin.x, figure.sphereOrigin.y, figure.sphereOrigin.z);
			int sphereCount = 0;
			for (int i = 0; i < 230; i++)
			{
				sph[i] = *(makingSphere + sphereCount);
				sphereCount++;
			}
		}

		////// 월드 좌표계에서 회전시키기
		float originInView[4][1] = {};
		originInView[0][0] = figure.sphereOrigin.x; originInView[1][0] = figure.sphereOrigin.y; originInView[2][0] = figure.sphereOrigin.z; originInView[3][0] = 1;
		float* fPtr = MatrixMulti(view, originInView);
		int sampleCount = 0;

		for (int i = 0; i < 230; i++) // 월드 좌표계에서의 큐브 중심을 원점으로 옮기면서 나머지 점들도 다 동일하게 옮겨줌
		{
			sph[i].x -= originInView[0][0];
			sph[i].y -= originInView[1][0];
			sph[i].z -= originInView[2][0];
		}

		for (int i = 0; i < 230; i++) // 해당 점들을 축을 기준으로 회전
		{
			float sample[4][1] = { { sph[i].x },{ sph[i].y },{ sph[i].z },{ 1 } };
			float* rotPtr = MatrixRotate(sample, figure.rotX, figure.rotY, 0);
			sampleCount = 0;
			for (int j = 0; j < 4; j++)
			{
				sample[j][0] = *(rotPtr + sampleCount);
				sampleCount++;
			}
			sph[i].x = sample[0][0]; sph[i].y = sample[1][0]; sph[i].z = sample[2][0];
		}

		for (int i = 0; i < 230; i++) // 다시 큐브의 중심을 원점에서 원래의 중심으로 복구
		{
			sph[i].x += originInView[0][0];
			sph[i].y += originInView[1][0];
			sph[i].z += originInView[2][0];
		}

		////// 월드 좌표계에서 x, y축으로 평행이동 시키기
		if (figure.moveY != 0)
		{
			for (int i = 0; i < 230; i++)
			{
				sph[i].y += figure.moveY;
				figure.sphereOrigin_moved.y += figure.moveY;
			}
		}
		if (figure.moveX != 0)
		{
			for (int i = 0; i < 230; i++)
			{
				sph[i].x += figure.moveX;
				figure.sphereOrigin_moved.x += figure.moveX;
			}
		}
		if (figure.moveZ != 0)
		{
			for (int i = 0; i < 230; i++)
			{
				sph[i].z += figure.moveZ;
				figure.sphereOrigin_moved.z += figure.moveZ;
			}
		}
		#pragma endregion

		////// 변경된 월드좌표 저장
		MyVertex newSphereWC[230] = {};
		float tempVertex[4][1] = {};
		for (int i = 0; i < 230; i++)
		{
			newSphereWC[i].x = sph[i].x; newSphereWC[i].y = sph[i].y; newSphereWC[i].z = sph[i].z;
		}
		//////

		float sample[4][1] = {};
		// sphere 각 점들을 뷰 행렬 변환 시킴
		for (int i = 0; i < 230; i++)
		{
			sample[0][0] = sph[i].x;
			sample[1][0] = sph[i].y;
			sample[2][0] = sph[i].z;
			sample[3][0] = 1;
			fPtr = MatrixMulti(view, sample);

			int sphCount = 0;
			sph[i].x = *(fPtr + sphCount);
			sphCount++;
			sph[i].y = *(fPtr + sphCount);
			sphCount++;
			sph[i].z = *(fPtr + sphCount);
			sphCount++;
		}

		#pragma region 절두체 컬링
		if (projNum == 0)
		{
			BOOL isItUpper[230] = {};
			for (int i = 0; i < 230; i++)
			{
				float vertexOfCube[3][1] = { { sph[i].x },{ sph[i].y },{ sph[i].z } };
				BOOL result1 = isItUpperSide(normOfFrustum3, nearPoint1, vertexOfCube);
				BOOL result2 = isItUpperSide(normOfFrustum12, nearPoint1, vertexOfCube);
				BOOL result3 = isItUpperSide(normOfFrustum9, nearPoint3, vertexOfCube);
				BOOL result4 = isItUpperSide(normOfFrustum6, nearPoint3, vertexOfCube);
				BOOL result5 = isItUpperSide(normOfNear, nearPoint3, vertexOfCube);
				//BOOL result6 = isItUpperSide(normOfFar, farPoint3, vertexOfCube);
				//if (result1 && result2 && result3 && result4 && result5 && result6) isItUpper[i] = TRUE;
				if (result1 && result2 && result3 && result4 && result5) isItUpper[i] = TRUE;
				else isItUpper[i] = FALSE;
			}
			BOOL bDrawBlock = FALSE;
			for (int i = 0; i < 230; i++)
			{
				if (isItUpper[i]) break;
				if (i == 229) bDrawBlock = TRUE;
			}
			if (bDrawBlock)
			{
				figure.isFront = FALSE;
				continue;
			}
		}
		else
		{
			BOOL isItUpper[230] = {};
			for (int i = 0; i < 230; i++)
			{
				float vertexOfCube[3][1] = { { sph[i].x },{ sph[i].y },{ sph[i].z } };
				BOOL result1 = isItUpperSide(normOfParallel3, pointOn3AND12, vertexOfCube);
				BOOL result2 = isItUpperSide(normOfParallel12, pointOn3AND12, vertexOfCube);
				BOOL result3 = isItUpperSide(normOfParallel9, pointOn9AND6, vertexOfCube);
				BOOL result4 = isItUpperSide(normOfParallel6, pointOn9AND6, vertexOfCube);
				BOOL result5 = isItUpperSide(normOfNear, pointOn3AND12, vertexOfCube);
				//BOOL result6 = isItUpperSide(normOfFar, pointOnFar, vertexOfCube);
				//if (result1 && result2 && result3 && result4 && result5 && result6) isItUpper[i] = TRUE;
				if (result1 && result2 && result3 && result4 && result5) isItUpper[i] = TRUE;
				else isItUpper[i] = FALSE;
			}
			BOOL bDrawBlock = FALSE;
			for (int i = 0; i < 230; i++)
			{
				if (isItUpper[i]) break;
				if (i == 229) bDrawBlock = TRUE;
			}
			if (bDrawBlock)
			{
				figure.isFront = FALSE;
				continue;
			}
		}
		figure.isFront = TRUE;
		#pragma endregion

		float deltaArray[230] = {};
		// sphere 각 점들을 투영 시킴
		for (int i = 0; i < 230; i++)
		{
			sample[0][0] = sph[i].x;
			sample[1][0] = sph[i].y;
			sample[2][0] = sph[i].z;
			sample[3][0] = 1;
			fPtr = MatrixMulti(proj, sample);
			int sphCount = 0;

			sph[i].x = *(fPtr + sphCount);
			sphCount++;
			sph[i].y = *(fPtr + sphCount);
			sphCount++;
			sph[i].z = *(fPtr + sphCount);
			sphCount++;
			if (projNum == 0)
			{
				sph[i].x /= sph[i].z;
				sph[i].y /= sph[i].z;
			}
		}

		// picking을 위해 미리 스크린 좌표 저장
		for (int i = 0; i < 230; i++)
		{
			figure.sphere_justForClick[i].x = ToScreenX(width, left, sph[i].x);
			figure.sphere_justForClick[i].y = ToScreenY(height, top, sph[i].y);
		}

		// 백스페이스 컬링
		float vFst[4][1] = {}; // 계산에 쓸 방향 저장용 벡터
		float vSec[4][1] = {}; // 계산에 쓸 방향 저장용 벡터
		float fst2x2[2][1] = {};
		float sec2x2[2][1] = {};
		int isVisableDot1[12] = {};
		int isVisable[216] = {};
		int isVisableDot2[12] = {};// 눈에 보이는 부분만 체크할 것이므로 눈에 안보이는 정점들은 0으로 바꿔버릴 계획
		int countInt = 0;
		float cameraToPolygon1[3][1] = {}; // 카메라 -> 정점 벡터
		float cameraToPolygon2[3][1] = {}; // 카메라 -> 정점 벡터
		float cameraToPolygon3[3][1] = {}; // 카메라 -> 정점 벡터
		float vPolygon1[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
		float vPolygon2[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
		float vPolygon3[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열

		CBrush sphBrush;
		CBrush* prevBrush;
		float lightDotPrd;
		int rgbTemp1_12[12];
		int rgbTemp1_216[216];
		int rgbTemp217_228[12];
		int rgbTemp1_216_2[216];

#pragma region 첫번째 삼각 폴리곤
		for (int i = 1; i < 13; i++) // 원의 가장 끝점과 옆의 12개의 점들 사이의 면
		{
			float cross[3][1] = {};

			if ((i % 12) != 0)
			{
				MakeVertexToVertexVector(vFst, newSphereWC[i], newSphereWC[0]);
				MakeVertexToVertexVector(vSec, newSphereWC[i + 1], newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon1, newSphereWC[0]);
				MakeVertexToVertexVector(cameraToPolygon2, newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon3, newSphereWC[i + 1]);
			}
			else
			{
				MakeVertexToVertexVector(vFst, newSphereWC[i], newSphereWC[0]);
				MakeVertexToVertexVector(vSec, newSphereWC[i - 11], newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon1, newSphereWC[0]);
				MakeVertexToVertexVector(cameraToPolygon2, newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon3, newSphereWC[i - 11]);
			}
			vFst[3][0] = 1; vSec[3][0] = 1;

			float* cPtr = CrossProduct(vFst, vSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}

			float crossBeforeNorm[4][1] = { { cross[0][0] },{ cross[1][0] },{ cross[2][0] },{ 1 } };
			cPtr = MatrixNormalize(crossBeforeNorm);
			count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}

			for (int j = 0; j < 3; j++)
			{
				if (projNum == 0)
				{
					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
				}
				else break;
			}
			if (projNum == 1)
			{
				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
			}

			float result1 = DotProduct(vPolygon1, cross);
			float result2 = DotProduct(vPolygon2, cross);
			float result3 = DotProduct(vPolygon3, cross);
			lightDotPrd = -DotProduct(cross, lightDirection);
			if (lightDotPrd < 0) lightDotPrd = 0;
			rgbTemp1_12[i - 1] = (int)round(80 + 175 * lightDotPrd);

			if (result1 > 0 || result2 > 0 || result3 > 0)
			{
				countInt++;
				continue;
			}
			else
			{
				isVisableDot1[countInt] = 1;
				countInt++;
			}
		}
		countInt = 0;
		for (int i = 1; i < 217; i++)
		{
			float cross[3][1] = {};

			if ((i % 12) == 0)
			{
				MakeVertexToVertexVector(vFst, newSphereWC[i + 12], newSphereWC[i]);
				MakeVertexToVertexVector(vSec, newSphereWC[i + 1], newSphereWC[i + 12]);
				MakeVertexToVertexVector(cameraToPolygon1, newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon2, newSphereWC[i + 12]);
				MakeVertexToVertexVector(cameraToPolygon3, newSphereWC[i + 1]);
			}
			else
			{
				MakeVertexToVertexVector(vFst, newSphereWC[i + 12], newSphereWC[i]);
				MakeVertexToVertexVector(vSec, newSphereWC[i + 13], newSphereWC[i + 12]);
				MakeVertexToVertexVector(cameraToPolygon1, newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon2, newSphereWC[i + 12]);
				MakeVertexToVertexVector(cameraToPolygon3, newSphereWC[i + 13]);
			}
			vFst[3][0] = 1; vSec[3][0] = 1;

			float* cPtr = CrossProduct(vFst, vSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}

			float crossBeforeNorm[4][1] = { { cross[0][0] },{ cross[1][0] },{ cross[2][0] },{ 1 } };
			cPtr = MatrixNormalize(crossBeforeNorm);
			count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}

			for (int j = 0; j < 3; j++)
			{
				if (projNum == 0)
				{
					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
				}
				else break;
			}
			if (projNum == 1)
			{
				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
			}


			float result1 = DotProduct(vPolygon1, cross);
			float result2 = DotProduct(vPolygon2, cross);
			float result3 = DotProduct(vPolygon3, cross);
			lightDotPrd = -DotProduct(cross, lightDirection);
			if (lightDotPrd < 0) lightDotPrd = 0;
			rgbTemp1_216[i - 1] = (int)round(80 + 175 * lightDotPrd);

			if (result1 > 0 || result2 > 0 || result3 > 0)
			{
				countInt++;
				continue;
			}
			else
			{
				isVisable[countInt] = 1;
				countInt++;
			}
		}
		countInt = 0;
		for (int i = 217; i < 229; i++)
		{
			float cross[3][1] = {};

			if ((i % 12) != 0)
			{
				MakeVertexToVertexVector(vFst, newSphereWC[229], newSphereWC[i]);
				MakeVertexToVertexVector(vSec, newSphereWC[i + 1], newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon1, newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon2, newSphereWC[229]);
				MakeVertexToVertexVector(cameraToPolygon3, newSphereWC[i + 1]);
			}
			else
			{
				MakeVertexToVertexVector(vFst, newSphereWC[229], newSphereWC[i]);
				MakeVertexToVertexVector(vSec, newSphereWC[i - 11], newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon1, newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon2, newSphereWC[229]);
				MakeVertexToVertexVector(cameraToPolygon3, newSphereWC[i - 11]);
			}
			vFst[3][0] = 1; vSec[3][0] = 1;

			float* cPtr = CrossProduct(vFst, vSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}

			float crossBeforeNorm[4][1] = { { cross[0][0] },{ cross[1][0] },{ cross[2][0] },{ 1 } };
			cPtr = MatrixNormalize(crossBeforeNorm);
			count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}

			for (int j = 0; j < 3; j++)
			{
				if (projNum == 0)
				{
					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
				}
				else break;
			}
			if (projNum == 1)
			{
				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
			}

			float result1 = DotProduct(vPolygon1, cross);
			float result2 = DotProduct(vPolygon2, cross);
			float result3 = DotProduct(vPolygon3, cross);
			lightDotPrd = -DotProduct(cross, lightDirection);
			if (lightDotPrd < 0) lightDotPrd = 0;
			rgbTemp217_228[i - 217] = (int)round(80 + 175 * lightDotPrd);

			if (result1 > 0 || result2 > 0 || result3 > 0)
			{
				countInt++;
				continue;
			}
			else
			{
				isVisableDot2[countInt] = 1;
				countInt++;
			}
		}

		if (frameNum == 1)
		{
			if (figure.isClicked == FALSE)
			{
				for (int i = 1; i < 13; i++)
				{
					if (isVisableDot1[i - 1] == 0) continue;
					DrawSphereLine(i, memDCPtr, width, height, left, top, sph[0], sph[i], sph[i - 11], sph[i + 1]);
				}
				for (int i = 1; i < 217; i++)
				{
					if (isVisable[i - 1] == 0) continue;
					DrawSphereLine(i, memDCPtr, width, height, left, top, sph[i], sph[i + 12], sph[i + 1], sph[i + 13]);
				}
				for (int i = 217; i < 229; i++)
				{
					if (isVisableDot2[i - 217] == 0) continue;
					DrawSphereLine(i, memDCPtr, width, height, left, top, sph[i], sph[229], sph[i - 11], sph[i + 1]);
				}
			}
			else
			{
				for (int i = 1; i < 13; i++)
				{
					if (isVisableDot1[i - 1] == 0) continue;
					DrawSphereMesh(i, 1, memDCPtr, width, height, left, top, sph[0], sph[i], sph[i - 11], sph[i + 1], rgbTemp1_12);
				}
				for (int i = 1; i < 217; i++)
				{
					if (isVisable[i - 1] == 0) continue;
					DrawSphereMesh(i, 1, memDCPtr, width, height, left, top, sph[i], sph[i + 12], sph[i + 1], sph[i + 13], rgbTemp1_216);
				}
				for (int i = 217; i < 229; i++)
				{
					if (isVisableDot2[i - 217] == 0) continue;
					DrawSphereMesh(i, 217, memDCPtr, width, height, left, top, sph[i], sph[229], sph[i - 11], sph[i + 1], rgbTemp217_228);
				}
			}
		}
		else
		{
			if (figure.isClicked)
			{
				for (int i = 1; i < 13; i++)
				{
					if (isVisableDot1[i - 1] == 0) continue;
					DrawSphereLine(i, memDCPtr, width, height, left, top, sph[0], sph[i], sph[i - 11], sph[i + 1]);
				}
				for (int i = 1; i < 217; i++)
				{
					if (isVisable[i - 1] == 0) continue;
					DrawSphereLine(i, memDCPtr, width, height, left, top, sph[i], sph[i + 12], sph[i + 1], sph[i + 13]);
				}
				for (int i = 217; i < 229; i++)
				{
					if (isVisableDot2[i - 217] == 0) continue;
					DrawSphereLine(i, memDCPtr, width, height, left, top, sph[i], sph[229], sph[i - 11], sph[i + 1]);
				}
			}
			else
			{
				for (int i = 1; i < 13; i++)
				{
					if (isVisableDot1[i - 1] == 0) continue;
					DrawSphereMesh(i, 1, memDCPtr, width, height, left, top, sph[0], sph[i], sph[i - 11], sph[i + 1], rgbTemp1_12);
				}
				for (int i = 1; i < 217; i++)
				{
					if (isVisable[i - 1] == 0) continue;
					DrawSphereMesh(i, 1, memDCPtr, width, height, left, top, sph[i], sph[i + 12], sph[i + 1], sph[i + 13], rgbTemp1_216);
				}
				for (int i = 217; i < 229; i++)
				{
					if (isVisableDot2[i - 217] == 0) continue;
					DrawSphereMesh(i, 217, memDCPtr, width, height, left, top, sph[i], sph[229], sph[i - 11], sph[i + 1], rgbTemp217_228);
				}
			}
		}
#pragma endregion

#pragma region 두번째 삼각 폴리곤 -> 가장 끝쪽의 꼭짓점들이랑은 더이상 이을 필요 없음
		countInt = 0;
		for (int i = 1; i < 217; i++)
		{
			float cross[3][1] = {};

			if ((i % 12) == 0)
			{
				MakeVertexToVertexVector(vFst, newSphereWC[i - 11], newSphereWC[i + 1]);
				MakeVertexToVertexVector(vSec, newSphereWC[i], newSphereWC[i - 11]);
				MakeVertexToVertexVector(cameraToPolygon1, newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon2, newSphereWC[i - 11]);
				MakeVertexToVertexVector(cameraToPolygon3, newSphereWC[i + 1]);
			}
			else
			{
				MakeVertexToVertexVector(vFst, newSphereWC[i + 1], newSphereWC[i + 13]);
				MakeVertexToVertexVector(vSec, newSphereWC[i], newSphereWC[i + 1]);
				MakeVertexToVertexVector(cameraToPolygon1, newSphereWC[i]);
				MakeVertexToVertexVector(cameraToPolygon2, newSphereWC[i + 1]);
				MakeVertexToVertexVector(cameraToPolygon3, newSphereWC[i + 13]);
			}
			vFst[3][0] = 1; vSec[3][0] = 1;

			float* cPtr = CrossProduct(vFst, vSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}

			float crossBeforeNorm[4][1] = { { cross[0][0] },{ cross[1][0] },{ cross[2][0] },{ 1 } };
			cPtr = MatrixNormalize(crossBeforeNorm);
			count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}

			for (int j = 0; j < 3; j++)
			{
				if (projNum == 0)
				{
					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
				}
				else break;
			}
			if (projNum == 1)
			{
				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
			}

			float result1 = DotProduct(vPolygon1, cross);
			float result2 = DotProduct(vPolygon2, cross);
			float result3 = DotProduct(vPolygon3, cross);
			lightDotPrd = -DotProduct(cross, lightDirection);
			if (lightDotPrd < 0) lightDotPrd = 0;
			rgbTemp1_216_2[i - 1] = (int)round(80 + 175 * lightDotPrd);

			if (result1 > 0 || result2 > 0 || result3 > 0)
			{
				countInt++;
				continue;
			}
			else
			{
				isVisable[countInt] = 1;
				countInt++;
			}
		}

		for (int i = 1; i < 217; i++)
		{
			if (frameNum == 1)
			{
				if (figure.isClicked)
				{
					if (isVisable[i - 1] == 0) continue;
					sphBrush.CreateSolidBrush(RGB(0, rgbTemp1_216_2[i - 1], 0));
					prevBrush = memDC.SelectObject(&sphBrush);
					memDC.BeginPath();
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
					if (i % 12 == 0)
					{
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
					}
					else
					{
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
					}
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
					memDC.EndPath();
					memDC.StrokeAndFillPath();
					memDC.SelectObject(prevBrush);
					sphBrush.DeleteObject();
				}
				else
				{
					if (isVisable[i - 1] == 0) continue;
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
					if (i % 12 == 0)
					{
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
					}
					else
					{
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
					}
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
				}
			}
			else
			{
				if (figure.isClicked)
				{
					if (isVisable[i - 1] == 0) continue;
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
					if (i % 12 == 0)
					{
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
					}
					else
					{
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
					}
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
				}
				else
				{
					if (isVisable[i - 1] == 0) continue;
					sphBrush.CreateSolidBrush(RGB(0, rgbTemp1_216_2[i - 1], 0));
					prevBrush = memDC.SelectObject(&sphBrush);
					memDC.BeginPath();
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
					if (i % 12 == 0)
					{
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
					}
					else
					{
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
					}
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
					memDC.EndPath();
					memDC.StrokeAndFillPath();
					memDC.SelectObject(prevBrush);
					sphBrush.DeleteObject();
				}
			}

		}
#pragma endregion
	}

	for (auto& figure : v_torusFigure)
	{
#pragma region 좌표계 변환 후 그리기
		// 원들끼리 그리기
		float dotFst[4][1] = {};
		float dotSec[4][1] = {};
		int myInt[144] = {};
		int mySecInt[144] = {};
		int countInt = 0;
		int fstResult = 0; // 처음 삼각형 그릴 때 i=0 일 때 조건 용
		int secResult = 0; // 두번째 삼각형 그릴 때 i=0 일 때 조건 용
		float cameraToPolygon1[3][1] = {}; // 카메라 -> 정점 벡터
		float cameraToPolygon2[3][1] = {}; // 카메라 -> 정점 벡터
		float cameraToPolygon3[3][1] = {}; // 카메라 -> 정점 벡터
		float vPolygon1[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
		float vPolygon2[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
		float vPolygon3[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
									
		int count = 0;
		MyVertex tor[144] = {};
		for (int i = 0; i < 144; i++) {
			tor[i] = figure.torus[i];
			count++;
		}
		#pragma region 도형의 크기, 회전, 이동 변환
		if (figure.torusRadius != figure.originTorusRadius) // 크기 변경이 된 친구라면?
		{ // 다시 만들어서 넣어줌
			MyVertex* makingTorus = pTorus(figure.torusOrigin.x, figure.torusOrigin.y, figure.torusOrigin.z, figure.torusLongRadius, figure.torusRadius);
			int torusCount = 0;
			for (int i = 0; i < 144; i++)
			{
				tor[i] = *(makingTorus + torusCount);
				torusCount++;
			}
		}

		////// 월드 좌표계에서 회전시키기
		float originInView[4][1] = {};
		originInView[0][0] = figure.torusOrigin.x; originInView[1][0] = figure.torusOrigin.y; originInView[2][0] = figure.torusOrigin.z; originInView[3][0] = 1;
		float* fPtr = MatrixMulti(view, originInView);
		int sampleCount = 0;

		for (int i = 0; i < 144; i++) // 월드 좌표계에서의 큐브 중심을 원점으로 옮기면서 나머지 점들도 다 동일하게 옮겨줌
		{
			tor[i].x -= originInView[0][0];
			tor[i].y -= originInView[1][0];
			tor[i].z -= originInView[2][0];
		}

		for (int i = 0; i < 144; i++) // 해당 점들을 축을 기준으로 회전
		{
			float sample[4][1] = { { tor[i].x },{ tor[i].y },{ tor[i].z },{ 1 } };
			float* rotPtr = MatrixRotate(sample, figure.rotX, figure.rotY, 0);
			sampleCount = 0;
			for (int j = 0; j < 4; j++)
			{
				sample[j][0] = *(rotPtr + sampleCount);
				sampleCount++;
			}
			tor[i].x = sample[0][0]; tor[i].y = sample[1][0]; tor[i].z = sample[2][0];
		}

		for (int i = 0; i < 144; i++) // 다시 큐브의 중심을 원점에서 원래의 중심으로 복구
		{
			tor[i].x += originInView[0][0];
			tor[i].y += originInView[1][0];
			tor[i].z += originInView[2][0];
		}

		////// 월드 좌표계에서 x, y축으로 평행이동 시키기
		if (figure.moveY != 0)
		{
			for (int i = 0; i < 144; i++)
			{
				tor[i].y += figure.moveY;
				figure.torusOrigin_moved.y += figure.moveY;
			}
		}
		if (figure.moveX != 0)
		{
			for (int i = 0; i < 144; i++)
			{
				tor[i].x += figure.moveX;
				figure.torusOrigin_moved.x += figure.moveX;
			}
		}
		if (figure.moveZ != 0)
		{
			for (int i = 0; i < 144; i++)
			{
				tor[i].z += figure.moveZ;
				figure.torusOrigin_moved.z += figure.moveZ;
			}
		}
		#pragma endregion

		////// 변경된 월드좌표 저장
		MyVertex newTorusWC[144] = {};
		float tempVertex[4][1] = {};
		for (int i = 0; i < 144; i++)
		{
			newTorusWC[i].x = tor[i].x; newTorusWC[i].y = tor[i].y; newTorusWC[i].z = tor[i].z;
		}

		float sample[4][1] = {};
		// torus 각 점들을 뷰 행렬 변환 시킴
		for (int i = 0; i < 144; i++)
		{
			sample[0][0] = tor[i].x;
			sample[1][0] = tor[i].y;
			sample[2][0] = tor[i].z;
			sample[3][0] = 1;
			fPtr = MatrixMulti(view, sample);

			int torCount = 0;
			tor[i].x = *(fPtr + torCount);
			torCount++;
			tor[i].y = *(fPtr + torCount);
			torCount++;
			tor[i].z = *(fPtr + torCount);
			torCount++;
		}

		#pragma region 절두체 컬링
		if (projNum == 0)
		{
			BOOL isItUpper[144] = {};
			for (int i = 0; i < 144; i++)
			{
				float vertexOfCube[3][1] = { { tor[i].x },{ tor[i].y },{ tor[i].z } };
				BOOL result1 = isItUpperSide(normOfFrustum3, nearPoint1, vertexOfCube);
				BOOL result2 = isItUpperSide(normOfFrustum12, nearPoint1, vertexOfCube);
				BOOL result3 = isItUpperSide(normOfFrustum9, nearPoint3, vertexOfCube);
				BOOL result4 = isItUpperSide(normOfFrustum6, nearPoint3, vertexOfCube);
				BOOL result5 = isItUpperSide(normOfNear, nearPoint3, vertexOfCube);
				//BOOL result6 = isItUpperSide(normOfFar, farPoint3, vertexOfCube);
				//if (result1 && result2 && result3 && result4 && result5 && result6) isItUpper[i] = TRUE;
				if (result1 && result2 && result3 && result4 && result5) isItUpper[i] = TRUE;
				else isItUpper[i] = FALSE;
			}
			BOOL bDrawBlock = FALSE;
			for (int i = 0; i < 144; i++)
			{
				if (isItUpper[i]) break;
				if (i == 143) bDrawBlock = TRUE;
			}
			if (bDrawBlock)
			{
				figure.isFront = FALSE;
				continue;
			}
		}
		else
		{
			BOOL isItUpper[144] = {};
			for (int i = 0; i < 144; i++)
			{
				float vertexOfCube[3][1] = { { tor[i].x },{ tor[i].y },{ tor[i].z } };
				BOOL result1 = isItUpperSide(normOfParallel3, pointOn3AND12, vertexOfCube);
				BOOL result2 = isItUpperSide(normOfParallel12, pointOn3AND12, vertexOfCube);
				BOOL result3 = isItUpperSide(normOfParallel9, pointOn9AND6, vertexOfCube);
				BOOL result4 = isItUpperSide(normOfParallel6, pointOn9AND6, vertexOfCube);
				BOOL result5 = isItUpperSide(normOfNear, pointOn3AND12, vertexOfCube);
				//BOOL result6 = isItUpperSide(normOfFar, pointOnFar, vertexOfCube);
				//if (result1 && result2 && result3 && result4 && result5 && result6) isItUpper[i] = TRUE;
				if (result1 && result2 && result3 && result4 && result5) isItUpper[i] = TRUE;
				else isItUpper[i] = FALSE;
			}
			BOOL bDrawBlock = FALSE;
			for (int i = 0; i < 144; i++)
			{
				if (isItUpper[i]) break;
				if (i == 143) bDrawBlock = TRUE;
			}
			if (bDrawBlock)
			{
				figure.isFront = FALSE;
				continue;
			}
		}
		figure.isFront = TRUE;
		#pragma endregion

		////// 카메라 기준 가장 먼 곳의 정점부터 그림 그리기
		// 뷰 좌표 기준 원점까지의 거리를 순서대로 
		float originToVertexLength[144] = {};
		int fromFarToNear[144] = {};
		float vertexSample[3][1] = {};
		float distance;
		for (int i = 0; i < 144; i++)
		{
			vertexSample[0][0] = tor[i].x;
			vertexSample[1][0] = tor[i].y;
			vertexSample[2][0] = tor[i].z;
			distance = vectorLength(vertexSample);
			originToVertexLength[i] = distance;
		} // 각 정점에서 카메라까지의 거리를 체크
		int num = 0;
		for (int i = 0; i < 144; i++) // 가장 큰(먼) 것 부터 배열에 넣음
		{
			float biggerOne = -1;
			for (int j = 0; j < 144; j++)
			{
				if (originToVertexLength[j] > biggerOne)
				{
					biggerOne = originToVertexLength[j];
					num = j;
				}
			}
			originToVertexLength[num] = -1;
			fromFarToNear[i] = num;
		}

		// 뷰 변환 한 점들 투영 변환
		for (int i = 0; i < 144; i++)
		{
			sample[0][0] = tor[i].x;
			sample[1][0] = tor[i].y;
			sample[2][0] = tor[i].z;
			sample[3][0] = 1;
			fPtr = MatrixMulti(proj, sample);
			int torCount = 0;

			tor[i].x = *(fPtr + torCount);
			torCount++;
			tor[i].y = *(fPtr + torCount);
			torCount++;
			tor[i].z = *(fPtr + torCount);
			torCount++;
			if (projNum == 0)
			{
				tor[i].x /= tor[i].z;
				tor[i].y /= tor[i].z;
			}
		}

		// picking을 위해 미리 스크린 좌표들을 저장
		for (int i = 0; i < 144; i++)
		{
			figure.torus_justForClick[i].x = ToScreenX(width, left, tor[i].x);
			figure.torus_justForClick[i].y = ToScreenY(height, top, tor[i].y);
		}

		CBrush torBrush;
		CBrush* prevBrush;
		float lightDotPrd;
		int rgbTemp[144];
		int rgbTemp_2[144];

#pragma region 첫번째 삼각 폴리곤 
		//for (int i = 0; i < 144; i++)
		for (auto i : fromFarToNear)
		{
			if ((i + 1) % 12 == 0)
			{
				if (i >= 132)
				{
					MakeVertexToVertexVector(dotFst, newTorusWC[i - 132], newTorusWC[i]);
					MakeVertexToVertexVector(dotSec, newTorusWC[i - 11], newTorusWC[i - 132]);
					MakeVertexToVertexVector(cameraToPolygon1, newTorusWC[i]);
					MakeVertexToVertexVector(cameraToPolygon2, newTorusWC[i - 132]);
					MakeVertexToVertexVector(cameraToPolygon3, newTorusWC[i - 11]);
				}
				else
				{
					MakeVertexToVertexVector(dotFst, newTorusWC[i + 12], newTorusWC[i]);
					MakeVertexToVertexVector(dotSec, newTorusWC[i - 11], newTorusWC[i + 12]);
					MakeVertexToVertexVector(cameraToPolygon1, newTorusWC[i]);
					MakeVertexToVertexVector(cameraToPolygon2, newTorusWC[i + 12]);
					MakeVertexToVertexVector(cameraToPolygon3, newTorusWC[i - 11]);
				}
			}
			else
			{
				if (i >= 132)
				{
					MakeVertexToVertexVector(dotFst, newTorusWC[i - 132], newTorusWC[i]);
					MakeVertexToVertexVector(dotSec, newTorusWC[i + 1], newTorusWC[i - 132]);
					MakeVertexToVertexVector(cameraToPolygon1, newTorusWC[i]);
					MakeVertexToVertexVector(cameraToPolygon2, newTorusWC[i - 132]);
					MakeVertexToVertexVector(cameraToPolygon3, newTorusWC[i + 1]);
				}
				else
				{
					MakeVertexToVertexVector(dotFst, newTorusWC[i + 12], newTorusWC[i]);
					MakeVertexToVertexVector(dotSec, newTorusWC[i + 1], newTorusWC[i + 12]);
					MakeVertexToVertexVector(cameraToPolygon1, newTorusWC[i]);
					MakeVertexToVertexVector(cameraToPolygon2, newTorusWC[i + 12]);
					MakeVertexToVertexVector(cameraToPolygon3, newTorusWC[i + 1]);
				}
			}
			dotFst[3][0] = 1;
			dotSec[3][0] = 1;

			float crsBoth[3][1] = {};
			float* ptr = CrossProduct(dotFst, dotSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				crsBoth[j][0] = *(ptr + count);
				count++;
			}

			float crossBeforeNorm[4][1] = { { crsBoth[0][0] },{ crsBoth[1][0] },{ crsBoth[2][0] },{ 1 } };
			ptr = MatrixNormalize(crossBeforeNorm);
			count = 0;
			for (int j = 0; j < 3; j++)
			{
				crsBoth[j][0] = *(ptr + count);
				count++;
			}

			for (int j = 0; j < 3; j++)
			{
				if (projNum == 0)
				{
					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
				}
				else break;
			}
			if (projNum == 1)
			{
				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
			}

			float result1 = DotProduct(vPolygon1, crsBoth);
			float result2 = DotProduct(vPolygon2, crsBoth);
			float result3 = DotProduct(vPolygon3, crsBoth);
			lightDotPrd = -DotProduct(crsBoth, lightDirection);
			if (lightDotPrd < 0)lightDotPrd = 0;
			rgbTemp[i] = (int)round(80 + 175 * lightDotPrd);

			if (i == 0)
			{
				if (result1 > 0 || result2 > 0 || result3 > 0)
				{
					continue;
				}
				else
				{
					fstResult = 1;
					continue;
				}
			}

			if (result1 > 0 || result2 > 0 || result3 > 0)
			{
				countInt++;
				continue;
			}
			myInt[countInt] = i;
			countInt++;
		}
		// i = 0 일때만 따로 그려주기 -> 0일때는 건너뛰게 그려놓았음.
		int rgbCount;
		if (frameNum == 1)
		{
			if (fstResult == 1)
			{
				if (figure.isClicked == FALSE)
				{// 선으로 그리기
					DrawTorusLine(memDCPtr, width, height, left, top, tor[0], tor[1], tor[12]);
				}
				else
				{
					// 면으로 그리기
					DrawTorusMesh(0, rgbTemp, memDCPtr, width, height, left, top, tor[0], tor[1], tor[12]);

				}
			}
			for (auto i : myInt)
			{
				if (i == 0) continue;
				if ((i + 1) % 12 == 0)
				{
					if (i >= 132)
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i - 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i - 132]);
						}
					}
					else
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i + 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i + 12]);
						}
					}
				}
				else
				{
					if (i >= 132)
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i - 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i - 132]);
						}
					}
					else
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i + 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i + 12]);
						}
					}
				}
			}
		}
		else
		{
			if (fstResult == 1)
			{
				if (figure.isClicked)
				{// 선으로 그리기
					DrawTorusLine(memDCPtr, width, height, left, top, tor[0], tor[1], tor[12]);
				}
				else
				{
					// 면으로 그리기
					DrawTorusMesh(0, rgbTemp, memDCPtr, width, height, left, top, tor[0], tor[1], tor[12]);
				}
			}
			rgbCount = -1;
			for (auto i : myInt)
			{
				rgbCount++;
				if (i == 0) continue;
				if ((i + 1) % 12 == 0)
				{
					if (i >= 132)
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i - 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i - 132]);
						}
					}
					else
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i + 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i + 12]);
						}
					}
				}
				else
				{
					if (i >= 132)
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i - 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i - 132]);
						}
					}
					else
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i + 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i + 12]);
						}
					}
				}
			}
		}
		//////
#pragma endregion
#pragma region 두번째 삼각 폴리곤 그리기
		countInt = 0;
		//for (int i = 0; i < 144; i++)
		for (auto i : fromFarToNear)
		{
			if ((i + 12) % 12 == 0) // 0, 12, 24, 36, .... , 120, 132
			{
				if (i == 0)
				{
					MakeVertexToVertexVector(dotFst, newTorusWC[i + 132], newTorusWC[i]);
					MakeVertexToVertexVector(dotSec, newTorusWC[i + 11], newTorusWC[i + 132]);
					MakeVertexToVertexVector(cameraToPolygon1, newTorusWC[i]);
					MakeVertexToVertexVector(cameraToPolygon2, newTorusWC[i + 132]);
					MakeVertexToVertexVector(cameraToPolygon3, newTorusWC[i + 11]);
				}
				else
				{
					MakeVertexToVertexVector(dotFst, newTorusWC[i - 12], newTorusWC[i]);
					MakeVertexToVertexVector(dotSec, newTorusWC[i + 11], newTorusWC[i - 12]);
					MakeVertexToVertexVector(cameraToPolygon1, newTorusWC[i]);
					MakeVertexToVertexVector(cameraToPolygon2, newTorusWC[i - 12]);
					MakeVertexToVertexVector(cameraToPolygon3, newTorusWC[i + 11]);
				}
			}
			else
			{
				if (i < 12)
				{
					MakeVertexToVertexVector(dotFst, newTorusWC[i + 132], newTorusWC[i]);
					MakeVertexToVertexVector(dotSec, newTorusWC[i - 1], newTorusWC[i + 132]);
					MakeVertexToVertexVector(cameraToPolygon1, newTorusWC[i]);
					MakeVertexToVertexVector(cameraToPolygon2, newTorusWC[i + 132]);
					MakeVertexToVertexVector(cameraToPolygon3, newTorusWC[i - 1]);
				}
				else
				{
					MakeVertexToVertexVector(dotFst, newTorusWC[i - 12], newTorusWC[i]);
					MakeVertexToVertexVector(dotSec, newTorusWC[i - 1], newTorusWC[i - 12]);
					MakeVertexToVertexVector(cameraToPolygon1, newTorusWC[i]);
					MakeVertexToVertexVector(cameraToPolygon2, newTorusWC[i - 12]);
					MakeVertexToVertexVector(cameraToPolygon3, newTorusWC[i - 1]);
				}
			}
			dotFst[3][0] = 1;
			dotSec[3][0] = 1;

			float crsBoth[3][1] = {};
			float* ptr = CrossProduct(dotFst, dotSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				crsBoth[j][0] = *(ptr + count);
				count++;
			}

			float crossBeforeNorm[4][1] = { { crsBoth[0][0] },{ crsBoth[1][0] },{ crsBoth[2][0] },{ 1 } };
			ptr = MatrixNormalize(crossBeforeNorm);
			count = 0;
			for (int j = 0; j < 3; j++)
			{
				crsBoth[j][0] = *(ptr + count);
				count++;
			}

			for (int j = 0; j < 3; j++)
			{
				if (projNum == 0)
				{
					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
				}
				else break;
			}
			if (projNum == 1)
			{
				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
			}

			float result1 = DotProduct(vPolygon1, crsBoth);
			float result2 = DotProduct(vPolygon2, crsBoth);
			float result3 = DotProduct(vPolygon3, crsBoth);
			lightDotPrd = -DotProduct(crsBoth, lightDirection);
			if (lightDotPrd < 0) lightDotPrd = 0;
			rgbTemp[i] = (int)round(80 + 175 * lightDotPrd);

			if (i == 0)
			{
				if (result1 > 0 || result2 > 0 || result3 > 0)
				{
					continue;
				}
				else
				{
					secResult = 1;
					continue;
				}
			}

			if (result1 > 0 || result2 > 0 || result3 > 0)
			{
				countInt++;
				continue;
			}
			mySecInt[countInt] = i;
			countInt++;
		}
		// i = 0 일때만 따로 그려주기 -> 0일때는 건너뛰게 그려놓았음.
		rgbCount = 0;
		if (frameNum == 1)
		{
			if (secResult == 1)
			{
				if (figure.isClicked == FALSE)
				{
					// 선으로 그리기
					DrawTorusLine(memDCPtr, width, height, left, top, tor[0], tor[11], tor[132]);
				}
				else
				{
					// 면으로 그리기
					DrawTorusMesh(0, rgbTemp, memDCPtr, width, height, left, top, tor[0], tor[11], tor[132]);
				}
			}
			//////
			for (auto i : mySecInt)
			{
				if (i == 0) continue;
				if (i % 12 == 0)
				{
					if (figure.isClicked == FALSE)
					{
						// 선으로 그리기
						DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 11], tor[i - 12]);
					}
					else
					{
						// 면으로 그리기
						DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 11], tor[i - 12]);
					}
				}
				else
				{
					if (i < 12)
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 1], tor[i + 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 1], tor[i + 132]);
						}
					}
					else
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 1], tor[i - 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 1], tor[i - 12]);
						}
					}
				}
			}
		}
		else
		{
			if (secResult == 1)
			{
				if (figure.isClicked)
				{
					// 선으로 그리기
					DrawTorusLine(memDCPtr, width, height, left, top, tor[0], tor[11], tor[132]);
				}
				else
				{
					// 면으로 그리기
					DrawTorusMesh(0, rgbTemp, memDCPtr, width, height, left, top, tor[0], tor[11], tor[132]);
				}
			}
			//////
			for (auto i : mySecInt)
			{
				if (i == 0) continue;
				if (i % 12 == 0)
				{
					if (figure.isClicked)
					{
						// 선으로 그리기
						DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 11], tor[i - 12]);
					}
					else
					{
						// 면으로 그리기
						DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 11], tor[i - 12]);
					}
				}
				else
				{
					if (i < 12)
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 1], tor[i + 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 1], tor[i + 132]);
						}
					}
					else
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 1], tor[i - 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 1], tor[i - 12]);
						}
					}
				}
			}
		}

#pragma endregion

#pragma region 면이 겹쳐보이는것을 해결하기 위해 처음 그린부분 중 앞부분만 다시 그려줌 -> 카메라로부터 정점까지의 거리가 가까운 부분
		int countFor96 = 0;
		int whereIs0 = 0;
		if (frameNum == 1)
		{
			if (fstResult == 1)
			{
				for (int i = 0; i < 144; i++)
				{
					if (fromFarToNear[i] == 0)
					{
						whereIs0 = i;
						break;
					}
				}

				if (whereIs0 > 95)
				{
					if (figure.isClicked == FALSE)
					{// 선으로 그리기
						DrawTorusLine(memDCPtr, width, height, left, top, tor[0], tor[1], tor[12]);
					}
					else
					{
						// 면으로 그리기
						DrawTorusMesh(0, rgbTemp, memDCPtr, width, height, left, top, tor[0], tor[1], tor[12]);
					}
				}
			}
			for (auto i : myInt)
			{
				if (countFor96 < 95)
				{
					countFor96++;
					continue;
				}
				if (i == 0) continue;
				if ((i + 1) % 12 == 0)
				{
					if (i >= 132)
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i - 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i - 132]);
						}
					}
					else
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i + 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i + 12]);
						}
					}
				}
				else
				{
					if (i >= 132)
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i - 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i - 132]);
						}
					}
					else
					{
						if (figure.isClicked == FALSE)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i + 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i + 12]);
						}
					}
				}
			}
		}
		else
		{
			if (fstResult == 1)
			{
				for (int i = 0; i < 144; i++)
				{
					if (fromFarToNear[i] == 0)
					{
						whereIs0 = i;
						break;
					}
				}

				if (whereIs0 > 95)
				{
					if (figure.isClicked)
					{// 선으로 그리기
						DrawTorusLine(memDCPtr, width, height, left, top, tor[0], tor[1], tor[12]);
					}
					else
					{
						// 면으로 그리기
						DrawTorusMesh(0, rgbTemp, memDCPtr, width, height, left, top, tor[0], tor[1], tor[12]);
					}
				}
			}
			countFor96 = 0;
			for (auto i : myInt)
			{
				if (countFor96 < 95)
				{
					countFor96++;
					continue;
				}
				if (i == 0) continue;
				if ((i + 1) % 12 == 0)
				{
					if (i >= 132)
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i - 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i - 132]);
						}
					}
					else
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i + 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i - 11], tor[i + 12]);
						}
					}
				}
				else
				{
					if (i >= 132)
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i - 132]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i - 132]);
						}
					}
					else
					{
						if (figure.isClicked)
						{
							// 선으로 그리기
							DrawTorusLine(memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i + 12]);
						}
						else
						{
							// 면으로 그리기
							DrawTorusMesh(i, rgbTemp, memDCPtr, width, height, left, top, tor[i], tor[i + 1], tor[i + 12]);
						}
					}
				}
			}
		}
#pragma endregion
#pragma endregion
	}

	memDC.SelectObject(oldPen);
	DeleteObject(newPen);

	cdc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	myBitmap.DeleteObject();
	memDC.DeleteDC();
	ReleaseDC(&cdc);
}

// 클릭하는 곳 좌표를 받아서 그곳에 그림 생성하기
void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	float az10[4][1];
	if (projNum == 0)
	{
		az10[2][0] = height / 2;
		az10[0][0] = (point.x - left - width / 2) / (width / 2) * az10[2][0];
		az10[1][0] = (point.y - top - height / 2) * (-1) / (height / 2) * az10[2][0];
	}
	else
	{
		az10[2][0] = 1;
		az10[0][0] = (point.x - left - width / 2) / (width / 2);
		az10[1][0] = (point.y - top - height / 2) * (-1) / (height / 2);
	}

	az10[3][0] = 1; // 화면을 클릭했을 때 얻어지는 투영면에서의 한 지점
	
	#pragma region 연산에 사용할 뷰, 투영행렬 제작
	look[0][0] = lookX; look[1][0] = lookY; look[2][0] = lookZ;
	float view[4][4] = {};
	camera[0][0] = cameraX; camera[1][0] = cameraY; camera[2][0] = cameraZ;
	float* viewPtr = ViewMatrix(camera, camAxisZ, camAxisX, camAxisY);
	int viewCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			view[i][j] = *(viewPtr + viewCount);
			viewCount++;
		}
	}
	float proj[4][4] = {};
	float* pPtr;
	int prjCount;
	if (projNum == 0)
	{
		// 투영 행렬
		pPtr = ProjectionMatrix(width, height, 90);
	}
	else
	{
		pPtr = ProjectionMatrixParallel(right, left, bottom, top, nPlane, fPlane);
	}
	prjCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			proj[i][j] = *(pPtr + prjCount);
			prjCount++;
		}
	}
	#pragma endregion

	// TODO: 투영면의 점을 카메라 좌표계로 옮긴다 (투영 역행렬)
	float projReverse[4][4] = {};
	pPtr = MatrixReverse(proj);
	prjCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			projReverse[i][j] = *(pPtr + prjCount);
			prjCount++;
		}
	}
	// 기존 점을 역행렬과 연산
	pPtr = MatrixMulti(projReverse, az10);
	prjCount = 0;
	for (int i = 0; i < 4; i++)
	{
		az10[i][0] = *(pPtr + prjCount);
		prjCount++;
	}

	// 카메라좌표계의 점을 월드 좌표계로 옮긴다 (뷰 역행렬)
	float viewReverse[4][4] = {};
	viewPtr = MatrixReverse(view);
	viewCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			viewReverse[i][j] = *(viewPtr + viewCount);
			viewCount++;
		}
	}

	// 기존 점을 역행렬과 연산
	viewPtr = MatrixMulti(viewReverse, az10);
	viewCount = 0;
	for (int i = 0; i < 4; i++)
	{
		az10[i][0] = *(viewPtr + viewCount);
		viewCount++;
	}
	// 이제 월드에서의 한 점이 만들어졌다.

	static int cubeCount = 0;
	static int sphereCount = 0;
	static int torusCount = 0;

	//
	//CString str = _T("");
	//str.Format(_T("%f, %f, %f"), az10[0][0], az10[1][0], az10[2][0]);
	//AfxMessageBox(str);
	//

	// TODO: 해당 점을 기준으로 도형을 만든다
	switch (figureNum)
	{
	case 0:
	{
		break;
	}
#pragma region case1-Cube
	case 1:
	{
		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
		MyVertex* vPtr = pCube(20, x, y, z);
		MyVertex cub[8] = {};
		int count = 0;
		for (int i = 0; i < 8; i++)
		{
			cub[i] = *(vPtr + count);
			count++;
		}

		// 해당 점들을 구조체에 넣어서 vector array에 보관
		CubeInfo Ci;
		for (int i = 0; i < 8; i++)
		{
			Ci.cube[i] = cub[i];
		}
		Ci.vertexCount = sizeof(cub) / sizeof(MyVertex);
		Ci.originLength = 20; Ci.length = 20;
		Ci.cubeOrigin.x = x; Ci.cubeOrigin.y = y; Ci.cubeOrigin.z = z;
		v_cubeFigure.push_back(Ci);
#pragma endregion
		break;
	}
#pragma region case2-Sphere
	case 2:
	{
		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
		MyVertex* vPtr = pSphere(30, x, y, z);
		MyVertex sph[230] = {};
		int count = 0;
		for (int i = 0; i < 230; i++)
		{
			sph[i] = *(vPtr + count);
			count++;
		}

		// 해당 점들을 구조체에 넣어서 vector array에 보관
		SphereInfo Si;
		for (int i = 0; i < 230; i++)
		{
			Si.sphere[i] = sph[i];
		}
		Si.vertexCount = sizeof(sph) / sizeof(MyVertex);
		Si.radius = 30; Si.originRadius = 30;
		Si.sphereOrigin.x = x; Si.sphereOrigin.y = y; Si.sphereOrigin.z = z;
		v_sphereFigure.push_back(Si);
#pragma endregion
		break;
	}
#pragma region case3-Torus
	case 3:
	{
		// 해당 점을 넣을 것
		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
		MyVertex* vPtr = pTorus(x, y, z, 32, 8);
		MyVertex tor[144] = {};

		int count = 0;
		// 만든 Torus 정보 가져오기
		for (int i = 0; i < 144; i++)
		{
			tor[i] = *(vPtr + count);
			count++;
		}

		// 해당 점들을 구조체에 넣어서 vector array에 보관
		TorusInfo ti;
		for (int i = 0; i < 144; i++)
		{
			ti.torus[i] = tor[i];
		}
		ti.vertexCount = sizeof(tor) / sizeof(MyVertex);
		ti.torusLongRadius = 32; ti.originTorusLongRadius = 32;
		ti.torusRadius = 8; ti.originTorusRadius = 8;
		ti.torusOrigin.x = x; ti.torusOrigin.y = y; ti.torusOrigin.z = z;
		v_torusFigure.push_back(ti);
#pragma endregion
		break;
	}
	}

	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

BOOL CMFCApplication3View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;

	return CView::OnEraseBkgnd(pDC);
}

void CMFCApplication3View::OnRButtonUp(UINT nFlags, CPoint point)
{
#pragma region //스크린 좌표계의 점을 투영 좌표계로 이동
	float az10[4][1];
	az10[2][0] = 1;
	az10[0][0] = point.x;
	az10[1][0] = point.y;
	az10[3][0] = 1; // 화면을 클릭했을 때 얻어지는 스크린에서의 한 지점

#pragma endregion
	BOOL oneFigureChecked = FALSE;
	// az[4][1]의 좌표는 스크린 좌표계의 한 점 -> 각 꼭짓점과 연결해서 각 면의 변들과 외적 -> 외적 방향을 정규화해서 모두 같으면 내부
	for (auto& figure : v_cubeFigure)
	{
		figure.isClicked = FALSE;
		if (!figure.isFront) continue;
		if (oneFigureChecked) continue;

		MyVertex cub[8] = {};
		float vertexSample[4][1] = {};
		int viewCount = 0;
		float* viewPtr;

		// 기존에 미리 저장해둔 스크린 좌표들을 가져옴
		for (int i = 0; i < 8; i++)
		{
			cub[i].x = figure.cube_justForClick[i].x;
			cub[i].y = figure.cube_justForClick[i].y;
		}
		////

		MyVertex p1 = {};
		MyVertex p2 = {};
		MyVertex p3 = {};
		MyVertex planeVector[12][3] = {};
		MyVertex originVector[12][3] = {};

		/////
#pragma region 각 메쉬에 대한 좌표와 벡터들
		MakeMeshVectors(planeVector[0], originVector[0], cub[0], cub[3], cub[4]);
		MakeMeshVectors(planeVector[1], originVector[1], cub[0], cub[4], cub[1]);
		MakeMeshVectors(planeVector[2], originVector[2], cub[0], cub[1], cub[3]);
		MakeMeshVectors(planeVector[3], originVector[3], cub[7], cub[4], cub[3]);
		MakeMeshVectors(planeVector[4], originVector[4], cub[7], cub[6], cub[4]);
		MakeMeshVectors(planeVector[5], originVector[5], cub[7], cub[3], cub[6]);
		MakeMeshVectors(planeVector[6], originVector[6], cub[2], cub[1], cub[6]);
		MakeMeshVectors(planeVector[7], originVector[7], cub[2], cub[3], cub[1]);
		MakeMeshVectors(planeVector[8], originVector[8], cub[2], cub[6], cub[3]);
		MakeMeshVectors(planeVector[9], originVector[9], cub[5], cub[6], cub[1]);
		MakeMeshVectors(planeVector[10], originVector[10], cub[5], cub[1], cub[4]);
		MakeMeshVectors(planeVector[11], originVector[11], cub[5], cub[4], cub[6]);
#pragma endregion

		float vertexToVertex1[2][1] = {};
		float vertexToPoint1[2][1] = {};
		float resultBeforeNorm1[4][1] = {};
		float result1[4][1] = {};
		float* crsPtr;
		float* normPtr;
		int count;
		float finalResult[3][3] = {};
		for (int i = 0; i < 12; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				vertexToVertex1[0][0] = planeVector[i][k].x; vertexToVertex1[1][0] = planeVector[i][k].y;
				vertexToPoint1[0][0] = (-1) * originVector[i][k].x + az10[0][0]; vertexToPoint1[1][0] = (-1) * originVector[i][k].y + az10[1][0];

				crsPtr = CrossProduct2X2(vertexToVertex1, vertexToPoint1);
				count = 0;
				for (int j = 0; j < 3; j++)
				{
					resultBeforeNorm1[j][0] = *(crsPtr + count);
					count++;
				}
				normPtr = MatrixNormalize(resultBeforeNorm1);
				count = 0;
				for (int j = 0; j < 3; j++)
				{
					result1[j][0] = *(normPtr + count);
					count++;
				}
				finalResult[k][0] = result1[0][0];  finalResult[k][1] = result1[1][0]; finalResult[k][2] = result1[2][0];
			}

			if (finalResult[0][2] == 0 || finalResult[1][2] == 0 || finalResult[2][2] == 0)
			{
				figure.isClicked = TRUE;
				oneFigureChecked = TRUE;
				break;
			}

			if (finalResult[0][2] == finalResult[1][2] && finalResult[0][2] == finalResult[2][2])
			{
				figure.isClicked = TRUE;
				oneFigureChecked = TRUE;
				break;
			}
			else
			{
				if (i == 11) figure.isClicked = FALSE;
			}
		}
	}

	for (auto& figure : v_sphereFigure)
	{
		figure.isClicked = FALSE;
		if (!figure.isFront) continue;
		if (oneFigureChecked) continue;

		MyVertex sph[230] = {};
		float vertexSample[4][1] = {};
		int viewCount = 0;
		float* viewPtr;

		for (int i = 0; i < 230; i++)
		{
			sph[i].x = figure.sphere_justForClick[i].x;
			sph[i].y = figure.sphere_justForClick[i].y;
		}

		MyVertex p1 = {};
		MyVertex p2 = {};
		MyVertex p3 = {};
		MyVertex p4 = {};
		MyVertex planeVector3[24][3] = {};
		MyVertex planeVector4[216][4] = {};
		MyVertex originVector3[24][3] = {};
		MyVertex originVector4[216][4] = {};

#pragma region 정점과 벡터들 확인
		// 끝점으로 만들어지는 삼각형 면
		for (int i = 1; i < 13; i++)
		{
			if ((i % 12) == 0)
			{
				p1.x = sph[0].x; p1.y = sph[0].y;
				p2.x = sph[i].x; p2.y = sph[i].y;
				p3.x = sph[i - 11].x; p3.y = sph[i - 11].y;
			}
			else
			{
				p1.x = sph[0].x; p1.y = sph[0].y;
				p2.x = sph[i].x; p2.y = sph[i].y;
				p3.x = sph[i + 1].x; p3.y = sph[i + 1].y;
			}
			planeVector3[i - 1][0].x = -p1.x + p2.x; planeVector3[i - 1][0].y = -p1.y + p2.y; planeVector3[i - 1][0].z = -p1.z + p2.z;
			planeVector3[i - 1][1].x = -p2.x + p3.x; planeVector3[i - 1][1].y = -p2.y + p3.y; planeVector3[i - 1][1].z = -p2.z + p3.z;
			planeVector3[i - 1][2].x = -p3.x + p1.x; planeVector3[i - 1][2].y = -p3.y + p1.y; planeVector3[i - 1][2].z = -p3.z + p1.z;
			originVector3[i - 1][0] = p1; originVector3[i - 1][1] = p2; originVector3[i - 1][2] = p3;
		}
		for (int i = 217; i < 229; i++)
		{
			if ((i % 12) == 0)
			{
				p1.x = sph[229].x; p1.y = sph[229].y;
				p2.x = sph[i - 11].x; p2.y = sph[i - 11].y;
				p3.x = sph[i].x; p3.y = sph[i].y;
			}
			else
			{
				p1.x = sph[229].x; p1.y = sph[229].y;
				p2.x = sph[i + 1].x; p2.y = sph[i + 1].y;
				p3.x = sph[i].x; p3.y = sph[i].y;
			}
			planeVector3[i - 205][0].x = -p1.x + p2.x; planeVector3[i - 205][0].y = -p1.y + p2.y; planeVector3[i - 205][0].z = -p1.z + p2.z;
			planeVector3[i - 205][1].x = -p2.x + p3.x; planeVector3[i - 205][1].y = -p2.y + p3.y; planeVector3[i - 205][1].z = -p2.z + p3.z;
			planeVector3[i - 205][2].x = -p3.x + p1.x; planeVector3[i - 205][2].y = -p3.y + p1.y; planeVector3[i - 205][2].z = -p3.z + p1.z;
			originVector3[i - 205][0] = p1; originVector3[i - 205][1] = p2; originVector3[i - 205][2] = p3;
		}
		// 사각형 면들
		for (int i = 1; i < 217; i++)
		{
			if (i % 12 == 0)
			{
				p1.x = sph[i].x; p1.y = sph[i].y;
				p2.x = sph[i + 12].x; p2.y = sph[i + 12].y;
				p3.x = sph[i + 1].x; p3.y = sph[i + 1].y;
				p4.x = sph[i - 11].x; p4.y = sph[i - 11].y;
			}
			else
			{
				p1.x = sph[i].x; p1.y = sph[i].y;
				p2.x = sph[i + 12].x; p2.y = sph[i + 12].y;
				p3.x = sph[i + 13].x; p3.y = sph[i + 13].y;
				p4.x = sph[i + 1].x; p4.y = sph[i + 1].y;
			}
			planeVector4[i - 1][0].x = -p1.x + p2.x; planeVector4[i - 1][0].y = -p1.y + p2.y; planeVector4[i - 1][0].z = -p1.z + p2.z;
			planeVector4[i - 1][1].x = -p2.x + p3.x; planeVector4[i - 1][1].y = -p2.y + p3.y; planeVector4[i - 1][1].z = -p2.z + p3.z;
			planeVector4[i - 1][2].x = -p3.x + p4.x; planeVector4[i - 1][2].y = -p3.y + p4.y; planeVector4[i - 1][2].z = -p3.z + p4.z;
			planeVector4[i - 1][3].x = -p4.x + p1.x; planeVector4[i - 1][3].y = -p4.y + p1.y; planeVector4[i - 1][3].z = -p4.z + p1.z;
			originVector4[i - 1][0] = p1; originVector4[i - 1][1] = p2; originVector4[i - 1][2] = p3; originVector4[i - 1][3] = p4;
		}
#pragma endregion

		float vertexToVertex1[2][1] = {};
		float vertexToPoint1[2][1] = {};
		float resultBeforeNorm1[4][1] = {};
		float result1[4][1] = {};
		float* crsPtr;
		float* normPtr;
		int count;
		float finalResultTri[3][3] = {};
		float finalResultRec[4][3] = {};

		for (int i = 0; i < 24; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				vertexToVertex1[0][0] = planeVector3[i][k].x; vertexToVertex1[1][0] = planeVector3[i][k].y;
				vertexToPoint1[0][0] = -originVector3[i][k].x + az10[0][0]; vertexToPoint1[1][0] = -originVector3[i][k].y + az10[1][0];

				crsPtr = CrossProduct2X2(vertexToVertex1, vertexToPoint1);
				count = 0;
				for (int j = 0; j < 3; j++)
				{
					resultBeforeNorm1[j][0] = *(crsPtr + count);
					count++;
				}
				normPtr = MatrixNormalize(resultBeforeNorm1);
				count = 0;
				for (int j = 0; j < 4; j++)
				{
					result1[j][0] = *(normPtr + count);
					count++;
				}
				finalResultTri[k][0] = result1[0][0]; finalResultTri[k][1] = result1[1][0]; finalResultTri[k][2] = result1[2][0];
			}

			if (finalResultTri[0][2] == 0 || finalResultTri[1][2] == 0 || finalResultTri[2][2] == 0)
			{
				figure.isClicked = TRUE;
				oneFigureChecked = TRUE;
				break;
			}

			if (finalResultTri[0][2] == finalResultTri[1][2] && finalResultTri[0][2] == finalResultTri[2][2])
			{
				figure.isClicked = TRUE;
				oneFigureChecked = TRUE;
				break;
			}
			else
			{
				if (i == 23) figure.isClicked = FALSE;
			}
		}
		for (int i = 0; i < 216; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				vertexToVertex1[0][0] = planeVector4[i][k].x; vertexToVertex1[1][0] = planeVector4[i][k].y;
				vertexToPoint1[0][0] = -originVector4[i][k].x + az10[0][0]; vertexToPoint1[1][0] = -originVector4[i][k].y + az10[1][0];

				crsPtr = CrossProduct2X2(vertexToVertex1, vertexToPoint1);
				count = 0;
				for (int j = 0; j < 3; j++)
				{
					resultBeforeNorm1[j][0] = *(crsPtr + count);
					count++;
				}
				normPtr = MatrixNormalize(resultBeforeNorm1);
				count = 0;
				for (int j = 0; j < 4; j++)
				{
					result1[j][0] = *(normPtr + count);
					count++;
				}
				finalResultRec[k][0] = result1[0][0]; finalResultRec[k][1] = result1[1][0]; finalResultRec[k][2] = result1[2][0];
			}

			if (finalResultRec[0][2] == 0 || finalResultRec[1][2] == 0 || finalResultRec[2][2] == 0 || finalResultRec[3][2] == 0)
			{
				figure.isClicked = TRUE;
				oneFigureChecked = TRUE;
				break;
			}

			if (finalResultRec[0][2] == finalResultRec[1][2] && finalResultRec[1][2] == finalResultRec[2][2] && finalResultRec[2][2] == finalResultRec[3][2])
			{
				figure.isClicked = TRUE;
				oneFigureChecked = TRUE;
				break;
			}
		}
	}

	for (auto& figure : v_torusFigure)
	{
		figure.isClicked = FALSE;
		if (!figure.isFront) continue;
		if (oneFigureChecked) continue;

		MyVertex tor[144] = {};
		float vertexSample[4][1] = {};
		int viewCount = 0;
		float* viewPtr;

		for (int i = 0; i < 144; i++)
		{
			tor[i].x = figure.torus_justForClick[i].x;
			tor[i].y = figure.torus_justForClick[i].y;
		}

		MyVertex p1 = {};
		MyVertex p2 = {};
		MyVertex p3 = {};
		MyVertex p4 = {};
		MyVertex planeVector[144][4] = {};
		MyVertex originVector[144][4] = {};

#pragma region 정점들과 벡터
		for (int i = 0; i < 144; i++)
		{
			if ((i + 1) % 12 == 0)
			{
				if (i >= 132) // i == 143
				{
					p1.x = tor[i].x; p1.y = tor[i].y; p1.z = tor[i].z;
					p2.x = tor[i - 132].x; p2.y = tor[i - 132].y; p2.z = tor[i - 132].z;
					p3.x = tor[i - 143].x; p3.y = tor[i - 143].y; p3.z = tor[i - 143].z;
					p4.x = tor[i - 11].x; p4.y = tor[i - 11].y; p4.z = tor[i - 11].z;
				}
				else
				{
					p1.x = tor[i].x; p1.y = tor[i].y; p1.z = tor[i].z;
					p2.x = tor[i + 12].x; p2.y = tor[i + 12].y; p2.z = tor[i + 12].z;
					p3.x = tor[i + 1].x; p3.y = tor[i + 1].y; p3.z = tor[i + 1].z;
					p4.x = tor[i - 11].x; p4.y = tor[i - 11].y; p4.z = tor[i - 11].z;
				}
			}
			else
			{
				if (i >= 132)
				{
					p1.x = tor[i].x; p1.y = tor[i].y; p1.z = tor[i].z;
					p2.x = tor[i - 132].x; p2.y = tor[i - 132].y; p2.z = tor[i - 132].z;
					p3.x = tor[i - 131].x; p3.y = tor[i - 131].y; p3.z = tor[i - 131].z;
					p4.x = tor[i + 1].x; p4.y = tor[i + 1].y; p4.z = tor[i + 1].z;
				}
				else
				{
					p1.x = tor[i].x; p1.y = tor[i].y; p1.z = tor[i].z;
					p2.x = tor[i + 12].x; p2.y = tor[i + 12].y; p2.z = tor[i + 12].z;
					p3.x = tor[i + 13].x; p3.y = tor[i + 13].y; p3.z = tor[i + 13].z;
					p4.x = tor[i + 1].x; p4.y = tor[i + 1].y; p4.z = tor[i + 1].z;
				}

			}
			planeVector[i][0].x = -p1.x + p2.x; planeVector[i][0].y = -p1.y + p2.y; planeVector[i][0].z = -p1.z + p2.z;
			planeVector[i][1].x = -p2.x + p3.x; planeVector[i][1].y = -p2.y + p3.y; planeVector[i][1].z = -p2.z + p3.z;
			planeVector[i][2].x = -p3.x + p4.x; planeVector[i][2].y = -p3.y + p4.y; planeVector[i][2].z = -p3.z + p4.z;
			planeVector[i][3].x = -p4.x + p1.x; planeVector[i][3].y = -p4.y + p1.y; planeVector[i][3].z = -p4.z + p1.z;
			originVector[i][0] = p1; originVector[i][1] = p2; originVector[i][2] = p3; originVector[i][3] = p4;
		}
#pragma endregion

		float vertexToVertex[2][1] = {};
		float vertexToPoint[2][1] = {};
		float resultBeforeNorm[4][1] = {};
		float result[4][1] = {};
		float* crsPtr;
		float* normPtr;
		int count;
		float finalResultRec[4][3] = {};
		for (int i = 0; i < 144; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				vertexToVertex[0][0] = planeVector[i][j].x; vertexToVertex[1][0] = planeVector[i][j].y;
				vertexToPoint[0][0] = -originVector[i][j].x + az10[0][0]; vertexToPoint[1][0] = -originVector[i][j].y + az10[1][0];
				crsPtr = CrossProduct2X2(vertexToVertex, vertexToPoint);
				count = 0;
				for (int k = 0; k < 4; k++)
				{
					resultBeforeNorm[k][0] = *(crsPtr + count);
					count++;
				}
				normPtr = MatrixNormalize(resultBeforeNorm);
				count = 0;
				for (int k = 0; k < 4; k++)
				{
					result[k][0] = *(normPtr + count);
					count++;
				}
				finalResultRec[j][0] = result[0][0]; finalResultRec[j][1] = result[1][0]; finalResultRec[j][2] = result[2][0];
			}

			if (finalResultRec[0][2] == 0 || finalResultRec[1][2] == 0 || finalResultRec[2][2] == 0 || finalResultRec[3][2] == 0)
			{
				figure.isClicked = TRUE;
				oneFigureChecked = TRUE;
				break;
			}

			if (finalResultRec[0][2] == finalResultRec[1][2] && finalResultRec[1][2] == finalResultRec[2][2] && finalResultRec[2][2] == finalResultRec[3][2])
			{
				figure.isClicked = TRUE;
				oneFigureChecked = TRUE;
				break;
			}
		}
	}

	Invalidate();

	CView::OnRButtonUp(nFlags, point);
}

BOOL CMFCApplication3View::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		#pragma region cube : 원점으로부터 가장 멀리있는 도형부터 그릴 수 있도록 가장 거리가 먼 도형을 앞으로 배치하기
		float farFromOrigin_back[3][1] = {};
		float farFromOrigin_front[3][1] = {};
		int count = 0;
		int length = 0;
		vector<CubeInfo> cube_copy;
		int cubeSize = v_cubeFigure.size();
		for (int k = 0; k < cubeSize; k++)
		{
			count = 0;
			for (int i = 1; i < v_cubeFigure.size(); i++)
			{
				if (v_cubeFigure.size() == 1) break;
				farFromOrigin_front[0][0] = v_cubeFigure.at(count).cubeOrigin.x + v_cubeFigure.at(count).moveX - cameraX;
				farFromOrigin_front[1][0] = v_cubeFigure.at(count).cubeOrigin.y + v_cubeFigure.at(count).moveY - cameraY;
				farFromOrigin_front[2][0] = v_cubeFigure.at(count).cubeOrigin.z + v_cubeFigure.at(count).moveZ - cameraZ;

				farFromOrigin_back[0][0] = v_cubeFigure.at(i).cubeOrigin.x + v_cubeFigure.at(i).moveX - cameraX;
				farFromOrigin_back[1][0] = v_cubeFigure.at(i).cubeOrigin.y + v_cubeFigure.at(i).moveY - cameraY;
				farFromOrigin_back[2][0] = v_cubeFigure.at(i).cubeOrigin.z + v_cubeFigure.at(i).moveZ - cameraZ;

				if (vectorLength(farFromOrigin_back) > vectorLength(farFromOrigin_front))
				{
					count = i;
				}
			}
			cube_copy.push_back(v_cubeFigure.at(count));
			v_cubeFigure.erase(v_cubeFigure.begin() + count);
		}
		for (int i = 0; i < cube_copy.size(); i++)
		{
			v_cubeFigure.push_back(cube_copy.at(i));
		}
		cube_copy.clear();
		vector<CubeInfo>().swap(cube_copy);
#pragma endregion
		#pragma region sphere : 원점으로부터 가장 멀리있는 도형부터 그릴 수 있도록 가장 거리가 먼 도형을 앞으로 배치하기
		count = 0;
		length = 0;
		vector<SphereInfo> sphere_copy;
		int sphereSize = v_sphereFigure.size();
		for (int k = 0; k < sphereSize; k++)
		{
			count = 0;
			for (int i = 1; i < v_sphereFigure.size(); i++)
			{
				if (v_sphereFigure.size() == 1) break;
				farFromOrigin_front[0][0] = v_sphereFigure.at(count).sphereOrigin.x + v_sphereFigure.at(count).moveX - cameraX;
				farFromOrigin_front[1][0] = v_sphereFigure.at(count).sphereOrigin.y + v_sphereFigure.at(count).moveY - cameraY;
				farFromOrigin_front[2][0] = v_sphereFigure.at(count).sphereOrigin.z + v_sphereFigure.at(count).moveZ - cameraZ;

				farFromOrigin_back[0][0] = v_sphereFigure.at(i).sphereOrigin.x + v_sphereFigure.at(i).moveX - cameraX;
				farFromOrigin_back[1][0] = v_sphereFigure.at(i).sphereOrigin.y + v_sphereFigure.at(i).moveY - cameraY;
				farFromOrigin_back[2][0] = v_sphereFigure.at(i).sphereOrigin.z + v_sphereFigure.at(i).moveZ - cameraZ;

				if (vectorLength(farFromOrigin_back) > vectorLength(farFromOrigin_front))
				{
					count = i;
				}
			}
			sphere_copy.push_back(v_sphereFigure.at(count));
			v_sphereFigure.erase(v_sphereFigure.begin() + count);
		}
		for (int i = 0; i < sphere_copy.size(); i++)
		{
			v_sphereFigure.push_back(sphere_copy.at(i));
		}
		sphere_copy.clear();
		vector<SphereInfo>().swap(sphere_copy);
#pragma endregion
		#pragma region torus : 원점으로부터 가장 멀리있는 도형부터 그릴 수 있도록 가장 거리가 먼 도형을 앞으로 배치하기
		count = 0;
		length = 0;
		vector<TorusInfo> torus_copy;
		int torusSize = v_torusFigure.size();
		for (int k = 0; k < torusSize; k++)
		{
			count = 0;
			for (int i = 1; i < v_torusFigure.size(); i++)
			{
				if (v_torusFigure.size() == 1) break;
				farFromOrigin_front[0][0] = v_torusFigure.at(count).torusOrigin.x + v_torusFigure.at(count).moveX - cameraX;
				farFromOrigin_front[1][0] = v_torusFigure.at(count).torusOrigin.y + v_torusFigure.at(count).moveY - cameraY;
				farFromOrigin_front[2][0] = v_torusFigure.at(count).torusOrigin.z + v_torusFigure.at(count).moveZ - cameraZ;

				farFromOrigin_back[0][0] = v_torusFigure.at(i).torusOrigin.x + v_torusFigure.at(i).moveX - cameraX;
				farFromOrigin_back[1][0] = v_torusFigure.at(i).torusOrigin.y + v_torusFigure.at(i).moveY - cameraY;
				farFromOrigin_back[2][0] = v_torusFigure.at(i).torusOrigin.z + v_torusFigure.at(i).moveZ - cameraZ;

				if (vectorLength(farFromOrigin_back) > vectorLength(farFromOrigin_front))
				{
					count = i;
				}
			}
			torus_copy.push_back(v_torusFigure.at(count));
			v_torusFigure.erase(v_torusFigure.begin() + count);
		}
		for (int i = 0; i < torus_copy.size(); i++)
		{
			v_torusFigure.push_back(torus_copy.at(i));
		}
		torus_copy.clear();
		vector<TorusInfo>().swap(torus_copy);
#pragma endregion

		if (pMsg->wParam == VK_RIGHT)
		{
			cameraX -= camAxisX[0][0] * 5;
			cameraY -= camAxisX[1][0] * 5;
			cameraZ -= camAxisX[2][0] * 5;
		}
		if (pMsg->wParam == VK_LEFT)
		{
			cameraX += camAxisX[0][0] * 5;
			cameraY += camAxisX[1][0] * 5;
			cameraZ += camAxisX[2][0] * 5;
		}
		if (pMsg->wParam == VK_UP)
		{
			cameraX += camAxisY[0][0] * 5;
			cameraY += camAxisY[1][0] * 5;
			cameraZ += camAxisY[2][0] * 5;
		}
		if (pMsg->wParam == VK_DOWN)
		{
			cameraX -= camAxisY[0][0] * 5;
			cameraY -= camAxisY[1][0] * 5;
			cameraZ -= camAxisY[2][0] * 5;
		}

		float sampleVectorZ[4][1] = {};
		float sampleVectorY[4][1] = {};
		float sampleVectorX[4][1] = {};
		float* newAxisPtr;
		int camCount = 0;
		if (pMsg->wParam == 'W')
		{
			if (rotateXCount < 120)
			{
				newAxisPtr = vectorRotation(camAxisZ, camAxisX, -15);
				camCount = 0;
				for (int i = 0; i < 3; i++)
				{
					camAxisZ[i][0] = *(newAxisPtr + camCount);
					camCount++;
				}
				lookX = camAxisZ[0][0]; lookY = camAxisZ[1][0]; lookZ = camAxisZ[2][0];

				newAxisPtr = vectorRotation(camAxisY, camAxisX, -15);
				camCount = 0;
				for (int i = 0; i < 3; i++)
				{
					camAxisY[i][0] = *(newAxisPtr + camCount);
					camCount++;
				}
				rotateXCount++;
			}
		}
		if (pMsg->wParam == 'S')
		{
			if (rotateXCount > -120)
			{
				newAxisPtr = vectorRotation(camAxisZ, camAxisX, 15);
				camCount = 0;
				for (int i = 0; i < 3; i++)
				{
					camAxisZ[i][0] = *(newAxisPtr + camCount);
					camCount++;
				}
				lookX = camAxisZ[0][0]; lookY = camAxisZ[1][0]; lookZ = camAxisZ[2][0];

				newAxisPtr = vectorRotation(camAxisY, camAxisX, 15);
				camCount = 0;
				for (int i = 0; i < 3; i++)
				{
					camAxisY[i][0] = *(newAxisPtr + camCount);
					camCount++;
				}
				rotateXCount--;
			}

		}
		if (pMsg->wParam == 'A')
		{
			if (rotateYCount < 120)
			{
				////// 카메라 방향 회전
				newAxisPtr = vectorRotation(camAxisZ, camAxisY, 15);
				camCount = 0;
				for (int i = 0; i < 3; i++)
				{
					camAxisZ[i][0] = *(newAxisPtr + camCount);
					camCount++;
				}
				lookX = camAxisZ[0][0]; lookY = camAxisZ[1][0]; lookZ = camAxisZ[2][0];

				newAxisPtr = vectorRotation(camAxisX, camAxisY, 15);
				camCount = 0;
				for (int i = 0; i < 3; i++)
				{
					camAxisX[i][0] = *(newAxisPtr + camCount);
					camCount++;
				}
				rotateYCount++;
			}
		}
		if (pMsg->wParam == 'D')
		{
			if (rotateYCount > -120)
			{
				////// 카메라 방향 회전
				newAxisPtr = vectorRotation(camAxisZ, camAxisY, -15);
				camCount = 0;
				for (int i = 0; i < 3; i++)
				{
					camAxisZ[i][0] = *(newAxisPtr + camCount);
					camCount++;
				}
				lookX = camAxisZ[0][0]; lookY = camAxisZ[1][0]; lookZ = camAxisZ[2][0];

				newAxisPtr = vectorRotation(camAxisX, camAxisY, -15);
				camCount = 0;
				for (int i = 0; i < 3; i++)
				{
					camAxisX[i][0] = *(newAxisPtr + camCount);
					camCount++;
				}
				rotateYCount--;
			}
		}
		// 선택된 물체 크기 변화
		if (pMsg->wParam == 'P')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.length += 5;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.radius += 4;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.torusLongRadius += 8;
				figure.torusRadius += 4;
				break;
			}
		}
		if (pMsg->wParam == 'M')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.length -= 5;
				if (figure.length < 5) figure.length = 5;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.radius -= 5;
				if (figure.radius < 5) figure.radius = 5;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.torusLongRadius -= 8;
				figure.torusRadius -= 2;
				if (figure.torusLongRadius < 8) figure.torusLongRadius = 8;
				if (figure.torusRadius < 2) figure.torusRadius = 2;
				break;
			}
		}
		// 선택된 물체 이동
		if (pMsg->wParam == 'T')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX += camAxisY[0][0] * 5;
				figure.moveY += camAxisY[1][0] * 5;
				figure.moveZ += camAxisY[2][0] * 5;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX += camAxisY[0][0] * 5;
				figure.moveY += camAxisY[1][0] * 5;
				figure.moveZ += camAxisY[2][0] * 5;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX += camAxisY[0][0] * 5;
				figure.moveY += camAxisY[1][0] * 5;
				figure.moveZ += camAxisY[2][0] * 5;
				break;
			}
		}
		if (pMsg->wParam == 'G')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX -= camAxisY[0][0] * 5;
				figure.moveY -= camAxisY[1][0] * 5;
				figure.moveZ -= camAxisY[2][0] * 5;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX -= camAxisY[0][0] * 5;
				figure.moveY -= camAxisY[1][0] * 5;
				figure.moveZ -= camAxisY[2][0] * 5;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX -= camAxisY[0][0] * 5;
				figure.moveY -= camAxisY[1][0] * 5;
				figure.moveZ -= camAxisY[2][0] * 5;
				break;
			}
		}
		if (pMsg->wParam == 'F')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX += camAxisX[0][0] * 5;
				figure.moveY += camAxisX[1][0] * 5;
				figure.moveZ += camAxisX[2][0] * 5;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX += camAxisX[0][0] * 5;
				figure.moveY += camAxisX[1][0] * 5;
				figure.moveZ += camAxisX[2][0] * 5;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX += camAxisX[0][0] * 5;
				figure.moveY += camAxisX[1][0] * 5;
				figure.moveZ += camAxisX[2][0] * 5;
				break;
			}
		}
		if (pMsg->wParam == 'H')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX -= camAxisX[0][0] * 5;
				figure.moveY -= camAxisX[1][0] * 5;
				figure.moveZ -= camAxisX[2][0] * 5;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX -= camAxisX[0][0] * 5;
				figure.moveY -= camAxisX[1][0] * 5;
				figure.moveZ -= camAxisX[2][0] * 5;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.moveX -= camAxisX[0][0] * 5;
				figure.moveY -= camAxisX[1][0] * 5;
				figure.moveZ -= camAxisX[2][0] * 5;
				break;
			}
		}
		// 선택된 물체 회전
		if (pMsg->wParam == 'I')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotX += 15;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotX += 15;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotX += 15;
				break;
			}
		}
		if (pMsg->wParam == 'K')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotX -= 15;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotX -= 15;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotX -= 15;
				break;
			}
		}
		if (pMsg->wParam == 'J')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotY -= 15;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotY -= 15;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotY -= 15;
				break;
			}
		}
		if (pMsg->wParam == 'L')
		{
			BOOL isChecked = FALSE;
			for (auto& figure : v_cubeFigure)
			{
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotY += 15;
				break;
			}
			for (auto& figure : v_sphereFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotY += 15;
				break;
			}
			for (auto& figure : v_torusFigure)
			{
				if (isChecked) break;
				if (!figure.isClicked) continue;
				isChecked = TRUE;
				figure.rotY += 15;
				break;
			}
		}
		Invalidate();
	}

	return CView::PreTranslateMessage(pMsg);
}