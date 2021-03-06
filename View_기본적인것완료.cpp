//
//// MFCApplication3View.cpp : CMFCApplication3View 클래스의 구현
////
//
//#include "stdafx.h"
//// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
//// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
//#ifndef SHARED_HANDLERS
//#include "MFCApplication3.h"
//#endif
//
//#include "MFCApplication3Doc.h"
//#include "MFCApplication3View.h"
//#include "MainFrm.h"
//#include "Figure.h"
//
//
//// 만든 파일들
//#include "Matrix.h"
////////////////
//
//extern int figureNum;
//extern int projNum;
//extern int frameNum;
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
//
//
//// CMFCApplication3View
//
//IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)
//
//BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
//	// 표준 인쇄 명령입니다.
//	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_PAINT()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
//	ON_WM_MOUSEMOVE()
//	ON_WM_ERASEBKGND()
//	ON_WM_HOTKEY()
//	ON_WM_RBUTTONUP()
//END_MESSAGE_MAP()
//
//// CMFCApplication3View 생성/소멸
//
//CMFCApplication3View::CMFCApplication3View()
//{
//	// TODO: 여기에 생성 코드를 추가합니다.
//	v_torusFigure = {};
//	cameraX = 0;
//	cameraY = 0;
//	cameraZ = -100;
//	cameraRotateX = 5;
//	cameraRotateY = 5;
//	rotateXCount = 0;
//	rotateYCount = 0;
//	lookX = 0;
//	lookY = 0;
//	lookZ = -1;
//	moveDirX.x = 0;
//	moveDirX.y = 0;
//	width = 0;
//	left = 0;
//	top = 0;
//	height = 0;
//	lightDirX = -1;
//	lightDirY = -2;
//	lightDirZ = -3;
//	camera[0][0] = cameraX;
//	camera[1][0] = cameraY;
//	camera[2][0] = cameraZ;
//	look[0][0] = lookX;
//	look[1][0] = lookY;
//	look[2][0] = lookZ;
//}
//
//CMFCApplication3View::~CMFCApplication3View()
//{
//
//}
//
//BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: CREATESTRUCT cs를 수정하여 여기에서
//	//  Window 클래스 또는 스타일을 수정합니다.
//
//	return CView::PreCreateWindow(cs);
//}
//
//// CMFCApplication3View 그리기
//
//void CMFCApplication3View::OnDraw(CDC* /*pDC*/)
//{
//	CMFCApplication3Doc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
//}
//
//
//// CMFCApplication3View 인쇄
//
//BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
//{
//	// 기본적인 준비
//	return DoPreparePrinting(pInfo);
//}
//
//void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
//}
//
//void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: 인쇄 후 정리 작업을 추가합니다.
//}
//
//
//// CMFCApplication3View 진단
//
//#ifdef _DEBUG
//void CMFCApplication3View::AssertValid() const
//{
//	CView::AssertValid();
//}
//
//void CMFCApplication3View::Dump(CDumpContext& dc) const
//{
//	CView::Dump(dc);
//}
//
//CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
//	return (CMFCApplication3Doc*)m_pDocument;
//}
//#endif //_DEBUG
//
//
//// CMFCApplication3View 메시지 처리기
//void CMFCApplication3View::OnPaint()
//{
//	// 그리기 준비
//	CPaintDC cdc(this);
//	CRect rect;
//	GetClientRect(&rect);
//	width = rect.Width();
//	height = rect.Height();
//	left = rect.left;
//	top = rect.top;
//
//	CDC memDC;
//	CBitmap myBitmap;
//	CBitmap* pOldBitmap;
//
//	memDC.CreateCompatibleDC(&cdc);
//	myBitmap.CreateCompatibleBitmap(&cdc, rect.Width(), rect.Height());
//	pOldBitmap = memDC.SelectObject(&myBitmap);
//
//	// 메모리 DC에 그리기
//	CBrush bgBrush(RGB(0, 0, 255));
//	CBrush* pOldBrush = memDC.SelectObject(&bgBrush);
//	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), /*WHITENESS*/ PATCOPY);
//	memDC.SelectObject(pOldBrush);
//	DeleteObject(bgBrush);
//
//	CPen newPen;
//	newPen.CreatePen(PS_SOLID, 0.5, RGB(255, 255, 255));
//	CPen* oldPen = memDC.SelectObject(&newPen);
//
//#pragma region 뷰 & 투영행렬 만들기 + 역행렬까지
//	look[0][0] = lookX; look[1][0] = lookY; look[2][0] = lookZ;
//	float view[4][4] = {};
//	camera[0][0] = cameraX; camera[1][0] = cameraY; camera[2][0] = cameraZ;
//	float* viewPtr = ViewMatrix(camera, look);
//	int viewCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			view[i][j] = *(viewPtr + viewCount);
//			viewCount++;
//		}
//	}
//	// 뷰 역행렬
//	float viewReverse[4][4] = {};
//	viewPtr = MatrixReverse(view);
//	viewCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			viewReverse[i][j] = *(viewPtr + viewCount);
//			viewCount++;
//		}
//	}
//	////////////
//	// 투영 행렬
//	float proj[4][4] = {};
//	float* pPtr = ProjectionMatrix(width, height, 90, 2, 15);
//	int prjCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			proj[i][j] = *(pPtr + prjCount);
//			prjCount++;
//		}
//	}
//	// 투영 역행렬
//	float projReverse[4][4] = {};
//	pPtr = MatrixReverse(proj);
//	prjCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			projReverse[i][j] = *(pPtr + prjCount);
//			prjCount++;
//		}
//	}
//	//////////////
//
//	// 빛 방향에 대한 방향벡터 생성
//	float lightDirection41[4][1] = { { lightDirX },{ lightDirY },{ lightDirZ },{ 1 } };
//	float* lPtr = MatrixNormalize(lightDirection41);
//	float lightDirection[3][1] = {};
//	int ldCount = 0;
//	for (int i = 0; i < 3; i++)
//	{
//		lightDirection[i][0] = *(lPtr + ldCount);
//		ldCount++;
//	}
//	//////////////////////////////
//
//#pragma endregion
//
//	for (auto& figure : v_cubeFigure)
//	{
//		int count = 0;
//		MyVertex cub[8] = {};
//		MyVertex cub_original[8] = {};
//		for (int i = 0; i < 8; i++)
//		{
//			cub[i] = figure.cube[i];
//			cub_original[i] = figure.cube[i];
//			count++;
//		}
//
//		if (figure.length != figure.originLength) // 크기 변경이 된 친구라면?
//		{
//			MyVertex* makingCube = pCube(figure.length, figure.cubeOrigin.x, figure.cubeOrigin.y, figure.cubeOrigin.z); // 다시 만들어서 넣어줌
//			int cubeCount = 0;
//			for (int i = 0; i < 8; i++)
//			{
//				cub[i] = *(makingCube + cubeCount);
//				cub_original[i] = *(makingCube + cubeCount);
//				cubeCount++;
//			}
//		}
//
//		////// 테스트 : 카메라 좌표계에서 x, y축으로 평행이동 시키기
//		if (figure.moveY != 0)
//		{
//			for (int i = 0; i < 8; i++)
//			{
//				cub[i].y += figure.moveY;
//			}
//		}
//		if (figure.moveX != 0)
//		{
//			for (int i = 0; i < 8; i++)
//			{
//				cub[i].x += figure.moveX;
//			}
//		}
//		if (figure.moveZ != 0)
//		{
//			for (int i = 0; i < 8; i++)
//			{
//				cub[i].z += figure.moveZ;
//			}
//		}
//		////////////////////////////////////////////////////////////
//
//		float* fPtr;
//		float sample[4][1] = {};
//		// sphere 각 점들을 뷰 행렬 변환 시킴
//		for (int i = 0; i < 8; i++)
//		{
//			sample[0][0] = cub[i].x;
//			sample[1][0] = cub[i].y;
//			sample[2][0] = cub[i].z;
//			sample[3][0] = 1;
//			fPtr = MatrixMulti(view, sample);
//
//			int cubCount = 0;
//			cub[i].x = *(fPtr + cubCount);
//			cubCount++;
//			cub[i].y = *(fPtr + cubCount);
//			cubCount++;
//			cub[i].z = *(fPtr + cubCount);
//			cubCount++;
//		}
//
//		////// 테스트 : 카메라 좌표계에서 회전시키기
//		float originInView[4][1] = {};
//		originInView[0][0] = figure.cubeOrigin.x; originInView[1][0] = figure.cubeOrigin.y; originInView[2][0] = figure.cubeOrigin.z; originInView[3][0] = 1;
//		fPtr = MatrixMulti(view, originInView);
//		int sampleCount = 0;
//		for (int i = 0; i < 3; i++) // 뷰 좌표계에서의 큐브의 중심을 구하기
//		{
//			originInView[i][0] = *(fPtr + sampleCount);
//			sampleCount++;
//		}
//
//		for (int i = 0; i < 8; i++) // 뷰 좌표계에서의 큐브 중심을 원점으로 옮기면서 나머지 점들도 다 동일하게 옮겨줌
//		{
//			cub[i].x -= originInView[0][0];
//			cub[i].y -= originInView[1][0];
//			cub[i].z -= originInView[2][0];
//		}
//
//		for (int i = 0; i < 8; i++) // 해당 점들을 축을 기준으로 회전
//		{
//			float sample[4][1] = { { cub[i].x },{ cub[i].y },{ cub[i].z },{ 1 } };
//			float* rotPtr = MatrixRotate(sample, figure.rotX, figure.rotY, 0);
//			sampleCount = 0;
//			for (int j = 0; j < 4; j++)
//			{
//				sample[j][0] = *(rotPtr + sampleCount);
//				sampleCount++;
//			}
//			cub[i].x = sample[0][0]; cub[i].y = sample[1][0]; cub[i].z = sample[2][0];
//		}
//
//		for (int i = 0; i < 8; i++) // 다시 큐브의 중심을 원점에서 원래의 중심으로 복구
//		{
//			cub[i].x += originInView[0][0];
//			cub[i].y += originInView[1][0];
//			cub[i].z += originInView[2][0];
//		}
//		////////////////////////////////////////////
//
//		////// 테스트 : z가 -1보다 큰 친구들은 화면에서 지우기 -> 카메라 뒤쪽 절두체에서 투영되는 친구들 제거
//		BOOL insideFrustum = TRUE;
//		for (int i = 0; i < 8; i++)
//		{
//			if (cub[i].z > -1)
//			{
//				insideFrustum = FALSE;
//				break;
//			}
//		}
//		if (!insideFrustum) continue;
//		//////////////////////////////////////////////////////
//
//		// sphere 각 점들을 투영 시킴
//		if (projNum == 0)
//		{
//			for (int i = 0; i < 8; i++)
//			{
//				sample[0][0] = cub[i].x;
//				sample[1][0] = cub[i].y;
//				sample[2][0] = cub[i].z;
//				sample[3][0] = 1;
//				fPtr = MatrixMulti(proj, sample);
//				int cubCount = 0;
//
//				cub[i].x = *(fPtr + cubCount);
//				cubCount++;
//				cub[i].y = *(fPtr + cubCount);
//				cubCount++;
//				cub[i].z = *(fPtr + cubCount);
//				cubCount++;
//
//				cub[i].x /= cub[i].z;
//				cub[i].y /= cub[i].z;
//			}
//		}
//		else
//		{
//			for (int i = 0; i < 8; i++)
//			{
//				cub[i].x /= ((width / height) * -originInView[2][0]);
//				cub[i].y /= -originInView[2][0];
//			}
//		}
//
//		/////////// 테스트 : 화면 밖으로 모든 점이 나가버리면 안그리게 할 것
//		float pointOfView[2][1] = {};
//		bool outOfView[8] = {};
//		for (int i = 0; i < 8; i++)
//		{
//			pointOfView[0][0] = ToScreenX(width, left, cub[i].x); pointOfView[1][0] = ToScreenY(height, top, cub[i].y);
//			if (pointOfView[0][0] < 0 || pointOfView[0][0] > width || pointOfView[1][0] < 0 || pointOfView[1][0] > height)
//				outOfView[i] = TRUE;
//			else outOfView[i] = FALSE;
//		}
//		bool totalOut = FALSE;
//		for (int i = 0; i < 8; i++)
//		{
//			if (outOfView[i]) totalOut = TRUE;
//			else
//			{
//				totalOut = FALSE;
//				break;
//			}
//		}
//		if (totalOut) continue;
//		////////////////////////////////////////////////////////////////////
//
//		//위치가 이동되었으니 월드좌표계의 좌표들도 변했을 것-> 현재 받아둔 좌표를 뒤로 돌려서 새로운 월드좌표를 받아야 함
//		MyVertex newCubeWC[8] = {};
//		float tempVertex[4][1] = {};
//		for (int i = 0; i < 8; i++)
//		{
//			float* tempPtr;
//			int tempCount = 0;
//			if (projNum == 0)
//			{
//				tempVertex[0][0] = cub[i].x * cub[i].z; tempVertex[1][0] = cub[i].y * cub[i].z; tempVertex[2][0] = cub[i].z; tempVertex[3][0] = 1;
//				tempPtr = MatrixMulti(projReverse, tempVertex);
//				int tempCount = 0;
//				for (int j = 0; j < 4; j++) // 투영 역행렬 = 카메라 좌표계
//				{
//					tempVertex[j][0] = *(tempPtr + tempCount);
//					tempCount++;
//				}
//			}
//			else
//			{
//				tempVertex[0][0] = cub[i].x * (width / height) * -originInView[2][0];
//				tempVertex[1][0] = cub[i].y * -originInView[2][0];
//				tempVertex[2][0] = cub[i].z; tempVertex[3][0] = 1;
//			}
//
//			tempPtr = MatrixMulti(viewReverse, tempVertex);
//			tempCount = 0;
//			for (int j = 0; j < 4; j++) // 뷰 역행렬 = 월드 좌표계
//			{
//				tempVertex[j][0] = *(tempPtr + tempCount);
//				tempCount++;
//			}
//			// 새로운 월드 좌표계 저장
//			newCubeWC[i].x = tempVertex[0][0]; newCubeWC[i].y = tempVertex[1][0]; newCubeWC[i].z = tempVertex[2][0];
//			figure.cube_justForClick[i].x = tempVertex[0][0]; figure.cube_justForClick[i].y = tempVertex[1][0]; figure.cube_justForClick[i].z = tempVertex[2][0];
//		}
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		float brightness1[4][1] = {};
//		float brightness2[4][1] = {};
//		float brightNorm[3][1] = {};
//		float dotProd, dotResult1, dotResult2, dotResult3;
//		float originToVertex1[3][1], originToVertex2[3][1], originToVertex3[3][1];
//		int rgbRate;
//		float* bPtr;
//		int bCount;
//		CBrush rectBrush;
//		CBrush* prevBrush;
//		if (frameNum == 1)
//		{
//			if (figure.isClicked)
//			{
//#pragma region 1번 꼭짓점 - 면
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//#pragma endregion
//#pragma region 2번 꼭짓점
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[3].x; originToVertex3[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[3].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//#pragma endregion
//#pragma region 3번 꼭짓점
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[6].x; originToVertex3[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[6].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//#pragma endregion
//#pragma region 4번 꼭짓점
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[6].x; originToVertex3[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[6].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//#pragma endregion
//			}
//			else
//			{
//#pragma region 1번 꼭짓점 - 선
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//				}
//#pragma endregion
//#pragma region 2번 꼭짓점
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[3].x; originToVertex3[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[3].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//				}
//
//#pragma endregion
//#pragma region 3번 꼭짓점
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[6].x; originToVertex3[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[6].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//				}
//
//#pragma endregion
//#pragma region 4번 꼭짓점
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[6].x; originToVertex3[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[6].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//				}
//#pragma endregion
//			}
//		}
//		else
//		{
//			if (figure.isClicked)
//			{
//#pragma region 1번 꼭짓점 - 선
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//				}
//#pragma endregion
//#pragma region 2번 꼭짓점
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[3].x; originToVertex3[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[3].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//				}
//
//#pragma endregion
//#pragma region 3번 꼭짓점
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[6].x; originToVertex3[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[6].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//				}
//
//#pragma endregion
//#pragma region 4번 꼭짓점
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[6].x; originToVertex3[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[6].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//				}
//
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//				}
//#pragma endregion
//			}
//			else
//			{
//#pragma region 1번 꼭짓점 - 면
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[0].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[0].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[0].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[0].x; originToVertex1[1][0] = -cameraY + newCubeWC[0].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[0].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//#pragma endregion
//#pragma region 2번 꼭짓점
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[7].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[7].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[7].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[7].x; originToVertex1[1][0] = -cameraY + newCubeWC[7].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[7].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[3].x; originToVertex3[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[3].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//#pragma endregion
//#pragma region 3번 꼭짓점
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[3].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[3].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[3].z;
//				brightness2[0][0] = -newCubeWC[3].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[3].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[3].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[1].x; originToVertex3[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[1].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[2].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[2].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[2].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[3].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[3].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[3].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[2].x; originToVertex1[1][0] = -cameraY + newCubeWC[2].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[2].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[3].x; originToVertex2[1][0] = -cameraY + newCubeWC[3].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[3].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[6].x; originToVertex3[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[6].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//#pragma endregion
//#pragma region 4번 꼭짓점
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[6].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[6].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[6].z;
//				brightness2[0][0] = -newCubeWC[6].x + newCubeWC[1].x; brightness2[1][0] = -newCubeWC[6].y + newCubeWC[1].y;
//				brightness2[2][0] = -newCubeWC[6].z + newCubeWC[1].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[6].x; originToVertex3[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[6].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[1].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[1].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[1].z;
//				brightness2[0][0] = -newCubeWC[1].x + newCubeWC[4].x; brightness2[1][0] = -newCubeWC[1].y + newCubeWC[4].y;
//				brightness2[2][0] = -newCubeWC[1].z + newCubeWC[4].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[1].x; originToVertex2[1][0] = -cameraY + newCubeWC[1].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[1].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//
//				brightness1[0][0] = -newCubeWC[5].x + newCubeWC[4].x; brightness1[1][0] = -newCubeWC[5].y + newCubeWC[4].y;
//				brightness1[2][0] = -newCubeWC[5].z + newCubeWC[4].z;
//				brightness2[0][0] = -newCubeWC[4].x + newCubeWC[6].x; brightness2[1][0] = -newCubeWC[4].y + newCubeWC[6].y;
//				brightness2[2][0] = -newCubeWC[4].z + newCubeWC[6].z;
//				originToVertex1[0][0] = -cameraX + newCubeWC[5].x; originToVertex1[1][0] = -cameraY + newCubeWC[5].y;
//				originToVertex1[2][0] = -cameraZ + newCubeWC[5].z;
//				originToVertex2[0][0] = -cameraX + newCubeWC[6].x; originToVertex2[1][0] = -cameraY + newCubeWC[6].y;
//				originToVertex2[2][0] = -cameraZ + newCubeWC[6].z;
//				originToVertex3[0][0] = -cameraX + newCubeWC[4].x; originToVertex3[1][0] = -cameraY + newCubeWC[4].y;
//				originToVertex3[2][0] = -cameraZ + newCubeWC[4].z;
//
//				bPtr = CrossProduct(brightness1, brightness2);
//				bCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					brightNorm[i][0] = *(bPtr + bCount);
//					bCount++;
//				}
//				dotProd = -DotProduct(brightNorm, lightDirection) / vectorLength(brightNorm);
//				if (dotProd < 0)dotProd = 0;
//				dotResult1 = DotProduct(brightNorm, originToVertex1);
//				dotResult2 = DotProduct(brightNorm, originToVertex2);
//				dotResult3 = DotProduct(brightNorm, originToVertex3);
//				if (dotResult1 <= 0 && dotResult2 <= 0 && dotResult3 <= 0)
//				{
//					rgbRate = (int)round(255 * dotProd);
//					rectBrush.CreateSolidBrush(RGB(0, rgbRate, 0));
//					prevBrush = memDC.SelectObject(&rectBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					rectBrush.DeleteObject();
//				}
//#pragma endregion
//			}
//		}
//	}
//
//	for (auto& figure : v_sphereFigure)
//	{
//		// vector로부터 구 좌표 받아오기
//		int count = 0;
//		MyVertex sph[230] = {};
//		for (int i = 0; i < 230; i++) {
//			sph[i] = figure.sphere[i];
//			count++;
//		}
//
//		if (figure.radius != figure.originRadius) // 크기 변경이 된 친구라면?
//		{ // 다시 만들어서 넣어줌
//			MyVertex* makingSphere = pSphere(figure.radius, figure.sphereOrigin.x, figure.sphereOrigin.y, figure.sphereOrigin.z);
//			int sphereCount = 0;
//			for (int i = 0; i < 230; i++)
//			{
//				sph[i] = *(makingSphere + sphereCount);
//				sphereCount++;
//			}
//		}
//
//		////// 테스트 : 카메라 좌표계에서 x, y축으로 평행이동 시키기
//		if (figure.moveY != 0)
//		{
//			for (int i = 0; i < 230; i++)
//			{
//				sph[i].y += figure.moveY;
//			}
//		}
//		if (figure.moveX != 0)
//		{
//			for (int i = 0; i < 230; i++)
//			{
//				sph[i].x += figure.moveX;
//			}
//		}
//		if (figure.moveZ != 0)
//		{
//			for (int i = 0; i < 230; i++)
//			{
//				sph[i].z += figure.moveZ;
//			}
//		}
//		////////////////////////////////////////////////////////////
//
//		float* fPtr;
//		float sample[4][1] = {};
//		// sphere 각 점들을 뷰 행렬 변환 시킴
//		for (int i = 0; i < 230; i++)
//		{
//			sample[0][0] = sph[i].x;
//			sample[1][0] = sph[i].y;
//			sample[2][0] = sph[i].z;
//			sample[3][0] = 1;
//			fPtr = MatrixMulti(view, sample);
//
//			int sphCount = 0;
//			sph[i].x = *(fPtr + sphCount);
//			sphCount++;
//			sph[i].y = *(fPtr + sphCount);
//			sphCount++;
//			sph[i].z = *(fPtr + sphCount);
//			sphCount++;
//		}
//
//		////// 테스트 : 카메라 좌표계에서 회전시키기
//		float originInView[4][1] = {};
//		originInView[0][0] = figure.sphereOrigin.x; originInView[1][0] = figure.sphereOrigin.y; originInView[2][0] = figure.sphereOrigin.z; originInView[3][0] = 1;
//		fPtr = MatrixMulti(view, originInView);
//		int sampleCount = 0;
//		for (int i = 0; i < 3; i++) // 뷰 좌표계에서의 큐브의 중심을 구하기
//		{
//			originInView[i][0] = *(fPtr + sampleCount);
//			sampleCount++;
//		}
//
//		for (int i = 0; i < 230; i++) // 뷰 좌표계에서의 큐브 중심을 원점으로 옮기면서 나머지 점들도 다 동일하게 옮겨줌
//		{
//			sph[i].x -= originInView[0][0];
//			sph[i].y -= originInView[1][0];
//			sph[i].z -= originInView[2][0];
//		}
//
//		for (int i = 0; i < 230; i++) // 해당 점들을 축을 기준으로 회전
//		{
//			float sample[4][1] = { { sph[i].x },{ sph[i].y },{ sph[i].z },{ 1 } };
//			float* rotPtr = MatrixRotate(sample, figure.rotX, figure.rotY, 0);
//			sampleCount = 0;
//			for (int j = 0; j < 4; j++)
//			{
//				sample[j][0] = *(rotPtr + sampleCount);
//				sampleCount++;
//			}
//			sph[i].x = sample[0][0]; sph[i].y = sample[1][0]; sph[i].z = sample[2][0];
//		}
//
//		for (int i = 0; i < 230; i++) // 다시 큐브의 중심을 원점에서 원래의 중심으로 복구
//		{
//			sph[i].x += originInView[0][0];
//			sph[i].y += originInView[1][0];
//			sph[i].z += originInView[2][0];
//		}
//
//		////// 테스트 : z가 -1보다 큰 친구들은 화면에서 지우기 -> 카메라 뒤쪽 절두체에서 투영되는 친구들 제거
//		BOOL insideFrustum = TRUE;
//		for (int i = 0; i < 230; i++)
//		{
//			if (sph[i].z > -1)
//			{
//				insideFrustum = FALSE;
//				break;
//			}
//		}
//		if (!insideFrustum) continue;
//		//////////////////////////////////////////////////////
//
//		float deltaArray[230] = {};
//		// sphere 각 점들을 투영 시킴
//		if (projNum == 0)
//		{
//			for (int i = 0; i < 230; i++)
//			{
//				sample[0][0] = sph[i].x;
//				sample[1][0] = sph[i].y;
//				sample[2][0] = sph[i].z;
//				sample[3][0] = 1;
//				fPtr = MatrixMulti(proj, sample);
//				int sphCount = 0;
//
//				sph[i].x = *(fPtr + sphCount);
//				sphCount++;
//				sph[i].y = *(fPtr + sphCount);
//				sphCount++;
//				sph[i].z = *(fPtr + sphCount);
//				sphCount++;
//
//				sph[i].x /= sph[i].z;
//				sph[i].y /= sph[i].z;
//			}
//		}
//		else
//		{
//			for (int i = 0; i < 230; i++)
//			{
//				sph[i].x /= ((width / height) * -originInView[2][0]);
//				sph[i].y /= -originInView[2][0];
//			}
//		}
//
//#pragma region 화면 밖으로 모든 점이 나가버리면 안그리게 할 것
//		float pointOfView[2][1] = {};
//		bool outOfView[230] = {};
//		for (int i = 0; i < 230; i++)
//		{
//			pointOfView[0][0] = ToScreenX(width, left, sph[i].x); pointOfView[1][0] = ToScreenY(height, top, sph[i].y);
//			if (pointOfView[0][0] < 0 || pointOfView[0][0] > width || pointOfView[1][0] < 0 || pointOfView[1][0] > height)
//				outOfView[i] = TRUE;
//			else outOfView[i] = FALSE;
//		}
//		bool totalOut = FALSE;
//		for (int i = 0; i < 230; i++)
//		{
//			if (outOfView[i]) totalOut = TRUE;
//			else
//			{
//				totalOut = FALSE;
//				break;
//			}
//		}
//		if (totalOut) continue;
//#pragma endregion ////////////////////////////////////////////////////////////////////
//
//		//위치가 이동되었으니 월드좌표계의 좌표들도 변했을 것-> 현재 받아둔 좌표를 다 뒤로 돌려서 새로운 월드좌표를 받아야 함
//		MyVertex newSphereWC[230] = {};
//		float tempVertex[4][1] = {};
//		for (int i = 0; i < 230; i++)
//		{
//			float* tempPtr;
//			int tempCount = 0;
//			if (projNum == 0)
//			{
//				tempVertex[0][0] = sph[i].x * sph[i].z; tempVertex[1][0] = sph[i].y * sph[i].z; tempVertex[2][0] = sph[i].z; tempVertex[3][0] = 1;
//				tempPtr = MatrixMulti(projReverse, tempVertex);
//				tempCount = 0;
//				for (int j = 0; j < 4; j++) // 투영 역행렬 = 카메라 좌표계
//				{
//					tempVertex[j][0] = *(tempPtr + tempCount);
//					tempCount++;
//				}
//			}
//			else
//			{
//				tempVertex[0][0] = sph[i].x *(width / height) * -originInView[2][0];
//				tempVertex[1][0] = sph[i].y * -originInView[2][0];
//				tempVertex[2][0] = sph[i].z; tempVertex[3][0] = 1;
//			}
//
//			tempPtr = MatrixMulti(viewReverse, tempVertex);
//			tempCount = 0;
//			for (int j = 0; j < 4; j++) // 뷰 역행렬 = 월드 좌표계
//			{
//				tempVertex[j][0] = *(tempPtr + tempCount);
//				tempCount++;
//			}
//			// 새로운 월드 좌표계 저장
//			newSphereWC[i].x = tempVertex[0][0]; newSphereWC[i].y = tempVertex[1][0]; newSphereWC[i].z = tempVertex[2][0];
//			figure.sphere_justForClick[i].x = tempVertex[0][0]; figure.sphere_justForClick[i].y = tempVertex[1][0]; figure.sphere_justForClick[i].z = tempVertex[2][0];
//		}
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		// 뒷면 잘라내기
//		float vFst[4][1] = {}; // 계산에 쓸 방향 저장용 벡터
//		float vSec[4][1] = {}; // 계산에 쓸 방향 저장용 벡터
//		float fst2x2[2][1] = {};
//		float sec2x2[2][1] = {};
//		int isVisableDot1[12] = {};
//		int isVisable[216] = {};
//		int isVisableDot2[12] = {};// 눈에 보이는 부분만 체크할 것이므로 눈에 안보이는 정점들은 0으로 바꿔버릴 계획
//		int countInt = 0;
//		float cameraToPolygon1[3][1] = {}; // 카메라 -> 정점 벡터
//		float cameraToPolygon2[3][1] = {}; // 카메라 -> 정점 벡터
//		float cameraToPolygon3[3][1] = {}; // 카메라 -> 정점 벡터
//		float vPolygon1[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
//		float vPolygon2[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
//		float vPolygon3[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
//
//		CBrush sphBrush;
//		CBrush* prevBrush;
//		float lightDotPrd;
//		int rgbTemp1_12[12];
//		int rgbTemp1_216[216];
//		int rgbTemp217_228[12];
//		int rgbTemp1_216_2[216];
//
//#pragma region 첫번째 삼각 폴리곤
//		for (int i = 1; i < 13; i++) // 원의 가장 끝점과 옆의 12개의 점들 사이의 면
//		{
//			float cross[3][1] = {};
//
//			if ((i % 12) != 0)
//			{
//				vFst[0][0] = -newSphereWC[0].x + newSphereWC[i].x;
//				vFst[1][0] = -newSphereWC[0].y + newSphereWC[i].y;
//				vFst[2][0] = -newSphereWC[0].z + newSphereWC[i].z;
//				vSec[0][0] = -newSphereWC[i].x + newSphereWC[i + 1].x;
//				vSec[1][0] = -newSphereWC[i].y + newSphereWC[i + 1].y;
//				vSec[2][0] = -newSphereWC[i].z + newSphereWC[i + 1].z;
//				cameraToPolygon1[0][0] = newSphereWC[0].x;
//				cameraToPolygon1[1][0] = newSphereWC[0].y;
//				cameraToPolygon1[2][0] = newSphereWC[0].z;
//				cameraToPolygon2[0][0] = newSphereWC[i].x;
//				cameraToPolygon2[1][0] = newSphereWC[i].y;
//				cameraToPolygon2[2][0] = newSphereWC[i].z;
//				cameraToPolygon3[0][0] = newSphereWC[i + 1].x;
//				cameraToPolygon3[1][0] = newSphereWC[i + 1].y;
//				cameraToPolygon3[2][0] = newSphereWC[i + 1].z;
//			}
//			else
//			{
//				vFst[0][0] = -newSphereWC[0].x + newSphereWC[i].x;
//				vFst[1][0] = -newSphereWC[0].y + newSphereWC[i].y;
//				vFst[2][0] = -newSphereWC[0].z + newSphereWC[i].z;
//				vSec[0][0] = -newSphereWC[i].x + newSphereWC[i - 11].x;
//				vSec[1][0] = -newSphereWC[i].y + newSphereWC[i - 11].y;
//				vSec[2][0] = -newSphereWC[i].z + newSphereWC[i - 11].z;
//				cameraToPolygon1[0][0] = newSphereWC[0].x;
//				cameraToPolygon1[1][0] = newSphereWC[0].y;
//				cameraToPolygon1[2][0] = newSphereWC[0].z;
//				cameraToPolygon2[0][0] = newSphereWC[i].x;
//				cameraToPolygon2[1][0] = newSphereWC[i].y;
//				cameraToPolygon2[2][0] = newSphereWC[i].z;
//				cameraToPolygon3[0][0] = newSphereWC[i - 11].x;
//				cameraToPolygon3[1][0] = newSphereWC[i - 11].y;
//				cameraToPolygon3[2][0] = newSphereWC[i - 11].z;
//			}
//			vFst[3][0] = 1; vSec[3][0] = 1;
//
//			float* cPtr = CrossProduct(vFst, vSec);
//			int count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				cross[j][0] = *(cPtr + count);
//				count++;
//			}
//
//			float crossBeforeNorm[4][1] = { { cross[0][0] },{ cross[1][0] },{ cross[2][0] },{ 1 } };
//			cPtr = MatrixNormalize(crossBeforeNorm);
//			count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				cross[j][0] = *(cPtr + count);
//				count++;
//			}
//
//			for (int j = 0; j < 3; j++)
//			{
//				if (projNum == 0)
//				{
//					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
//					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
//					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
//				}
//				else break;
//			}
//			if (projNum == 1)
//			{
//				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
//				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
//				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
//			}
//
//			float result1 = DotProduct(vPolygon1, cross);
//			float result2 = DotProduct(vPolygon2, cross);
//			float result3 = DotProduct(vPolygon3, cross);
//			lightDotPrd = -DotProduct(cross, lightDirection);
//			if (lightDotPrd < 0) lightDotPrd = 0;
//			rgbTemp1_12[i - 1] = (int)round(255 * lightDotPrd);
//
//			if (result1 > 0 || result2 > 0 || result3 > 0)
//			{
//				countInt++;
//				continue;
//			}
//			else
//			{
//				isVisableDot1[countInt] = 1;
//				countInt++;
//			}
//		}
//		countInt = 0;
//		for (int i = 1; i < 217; i++)
//		{
//			float cross[3][1] = {};
//
//			if ((i % 12) == 0)
//			{
//				vFst[0][0] = -newSphereWC[i].x + newSphereWC[i + 12].x;
//				vFst[1][0] = -newSphereWC[i].y + newSphereWC[i + 12].y;
//				vFst[2][0] = -newSphereWC[i].z + newSphereWC[i + 12].z;
//				vSec[0][0] = -newSphereWC[i + 12].x + newSphereWC[i + 1].x;
//				vSec[1][0] = -newSphereWC[i + 12].y + newSphereWC[i + 1].y;
//				vSec[2][0] = -newSphereWC[i + 12].z + newSphereWC[i + 1].z;
//				cameraToPolygon1[0][0] = newSphereWC[i].x;
//				cameraToPolygon1[1][0] = newSphereWC[i].y;
//				cameraToPolygon1[2][0] = newSphereWC[i].z;
//				cameraToPolygon2[0][0] = newSphereWC[i + 12].x;
//				cameraToPolygon2[1][0] = newSphereWC[i + 12].y;
//				cameraToPolygon2[2][0] = newSphereWC[i + 12].z;
//				cameraToPolygon3[0][0] = newSphereWC[i + 1].x;
//				cameraToPolygon3[1][0] = newSphereWC[i + 1].y;
//				cameraToPolygon3[2][0] = newSphereWC[i + 1].z;
//			}
//			else
//			{
//				vFst[0][0] = -newSphereWC[i].x + newSphereWC[i + 12].x;
//				vFst[1][0] = -newSphereWC[i].y + newSphereWC[i + 12].y;
//				vFst[2][0] = -newSphereWC[i].z + newSphereWC[i + 12].z;
//				vSec[0][0] = -newSphereWC[i + 12].x + newSphereWC[i + 13].x;
//				vSec[1][0] = -newSphereWC[i + 12].y + newSphereWC[i + 13].y;
//				vSec[2][0] = -newSphereWC[i + 12].z + newSphereWC[i + 13].z;
//				cameraToPolygon1[0][0] = newSphereWC[i].x;
//				cameraToPolygon1[1][0] = newSphereWC[i].y;
//				cameraToPolygon1[2][0] = newSphereWC[i].z;
//				cameraToPolygon2[0][0] = newSphereWC[i + 12].x;
//				cameraToPolygon2[1][0] = newSphereWC[i + 12].y;
//				cameraToPolygon2[2][0] = newSphereWC[i + 12].z;
//				cameraToPolygon3[0][0] = newSphereWC[i + 13].x;
//				cameraToPolygon3[1][0] = newSphereWC[i + 13].y;
//				cameraToPolygon3[2][0] = newSphereWC[i + 13].z;
//			}
//			vFst[3][0] = 1; vSec[3][0] = 1;
//
//			float* cPtr = CrossProduct(vFst, vSec);
//			int count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				cross[j][0] = *(cPtr + count);
//				count++;
//			}
//
//			float crossBeforeNorm[4][1] = { { cross[0][0] },{ cross[1][0] },{ cross[2][0] },{ 1 } };
//			cPtr = MatrixNormalize(crossBeforeNorm);
//			count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				cross[j][0] = *(cPtr + count);
//				count++;
//			}
//
//			for (int j = 0; j < 3; j++)
//			{
//				if (projNum == 0)
//				{
//					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
//					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
//					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
//				}
//				else break;
//			}
//			if (projNum == 1)
//			{
//				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
//				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
//				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
//			}
//
//
//			float result1 = DotProduct(vPolygon1, cross);
//			float result2 = DotProduct(vPolygon2, cross);
//			float result3 = DotProduct(vPolygon3, cross);
//			lightDotPrd = -DotProduct(cross, lightDirection);
//			if (lightDotPrd < 0) lightDotPrd = 0;
//			rgbTemp1_216[i - 1] = (int)round(255 * lightDotPrd);
//
//			if (result1 > 0 || result2 > 0 || result3 > 0)
//			{
//				countInt++;
//				continue;
//			}
//			else
//			{
//				isVisable[countInt] = 1;
//				countInt++;
//			}
//		}
//		countInt = 0;
//		for (int i = 217; i < 229; i++)
//		{
//			float cross[3][1] = {};
//
//			if ((i % 12) != 0)
//			{
//				vFst[0][0] = -newSphereWC[i].x + newSphereWC[229].x;
//				vFst[1][0] = -newSphereWC[i].y + newSphereWC[229].y;
//				vFst[2][0] = -newSphereWC[i].z + newSphereWC[229].z;
//				vSec[0][0] = -newSphereWC[i].x + newSphereWC[i + 1].x;
//				vSec[1][0] = -newSphereWC[i].y + newSphereWC[i + 1].y;
//				vSec[2][0] = -newSphereWC[i].z + newSphereWC[i + 1].z;
//				cameraToPolygon1[0][0] = newSphereWC[i].x;
//				cameraToPolygon1[1][0] = newSphereWC[i].y;
//				cameraToPolygon1[2][0] = newSphereWC[i].z;
//				cameraToPolygon2[0][0] = newSphereWC[229].x;
//				cameraToPolygon2[1][0] = newSphereWC[229].y;
//				cameraToPolygon2[2][0] = newSphereWC[229].z;
//				cameraToPolygon3[0][0] = newSphereWC[i + 1].x;
//				cameraToPolygon3[1][0] = newSphereWC[i + 1].y;
//				cameraToPolygon3[2][0] = newSphereWC[i + 1].z;
//			}
//			else
//			{
//				vFst[0][0] = -newSphereWC[i].x + newSphereWC[229].x;
//				vFst[1][0] = -newSphereWC[i].y + newSphereWC[229].y;
//				vFst[2][0] = -newSphereWC[i].z + newSphereWC[229].z;
//				vSec[0][0] = -newSphereWC[i].x + newSphereWC[i - 11].x;
//				vSec[1][0] = -newSphereWC[i].y + newSphereWC[i - 11].y;
//				vSec[2][0] = -newSphereWC[i].z + newSphereWC[i - 11].z;
//				cameraToPolygon1[0][0] = newSphereWC[i].x;
//				cameraToPolygon1[1][0] = newSphereWC[i].y;
//				cameraToPolygon1[2][0] = newSphereWC[i].z;
//				cameraToPolygon2[0][0] = newSphereWC[229].x;
//				cameraToPolygon2[1][0] = newSphereWC[229].y;
//				cameraToPolygon2[2][0] = newSphereWC[229].z;
//				cameraToPolygon3[0][0] = newSphereWC[i - 11].x;
//				cameraToPolygon3[1][0] = newSphereWC[i - 11].y;
//				cameraToPolygon3[2][0] = newSphereWC[i - 11].z;
//			}
//			vFst[3][0] = 1; vSec[3][0] = 1;
//
//			float* cPtr = CrossProduct(vFst, vSec);
//			int count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				cross[j][0] = *(cPtr + count);
//				count++;
//			}
//
//			float crossBeforeNorm[4][1] = { { cross[0][0] },{ cross[1][0] },{ cross[2][0] },{ 1 } };
//			cPtr = MatrixNormalize(crossBeforeNorm);
//			count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				cross[j][0] = *(cPtr + count);
//				count++;
//			}
//
//			for (int j = 0; j < 3; j++)
//			{
//				if (projNum == 0)
//				{
//					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
//					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
//					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
//				}
//				else break;
//			}
//			if (projNum == 1)
//			{
//				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
//				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
//				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
//			}
//
//			float result1 = DotProduct(vPolygon1, cross);
//			float result2 = DotProduct(vPolygon2, cross);
//			float result3 = DotProduct(vPolygon3, cross);
//			lightDotPrd = -DotProduct(cross, lightDirection);
//			if (lightDotPrd < 0) lightDotPrd = 0;
//			rgbTemp217_228[i - 217] = (int)round(255 * lightDotPrd);
//
//			if (result1 > 0 || result2 > 0 || result3 > 0)
//			{
//				countInt++;
//				continue;
//			}
//			else
//			{
//				isVisableDot2[countInt] = 1;
//				countInt++;
//			}
//		}
//
//		if (frameNum == 1)
//		{
//			if (figure.isClicked == FALSE)
//			{
//				for (int i = 1; i < 13; i++)
//				{
//					if (isVisableDot1[i - 1] == 0) continue;
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
//				}
//				for (int i = 1; i < 217; i++)
//				{
//					if (isVisable[i - 1] == 0) continue;
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 12].x), ToScreenY(rect.Height(), rect.top, sph[i + 12].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//				}
//				for (int i = 217; i < 229; i++)
//				{
//					if (isVisableDot2[i - 217] == 0) continue;
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[229].x), ToScreenY(rect.Height(), rect.top, sph[229].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//				}
//			}
//			else
//			{
//				for (int i = 1; i < 13; i++)
//				{
//					if (isVisableDot1[i - 1] == 0) continue;
//					sphBrush.CreateSolidBrush(RGB(0, rgbTemp1_12[i - 1], 0));
//					prevBrush = memDC.SelectObject(&sphBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					sphBrush.DeleteObject();
//				}
//				for (int i = 1; i < 217; i++)
//				{
//					if (isVisable[i - 1] == 0) continue;
//					sphBrush.CreateSolidBrush(RGB(0, rgbTemp1_216[i - 1], 0));
//					prevBrush = memDC.SelectObject(&sphBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 12].x), ToScreenY(rect.Height(), rect.top, sph[i + 12].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					sphBrush.DeleteObject();
//				}
//				for (int i = 217; i < 229; i++)
//				{
//					if (isVisableDot2[i - 217] == 0) continue;
//					sphBrush.CreateSolidBrush(RGB(0, rgbTemp217_228[i - 217], 0));
//					prevBrush = memDC.SelectObject(&sphBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[229].x), ToScreenY(rect.Height(), rect.top, sph[229].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					sphBrush.DeleteObject();
//				}
//			}
//		}
//		else
//		{
//			if (figure.isClicked)
//			{
//				for (int i = 1; i < 13; i++)
//				{
//					if (isVisableDot1[i - 1] == 0) continue;
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
//				}
//				for (int i = 1; i < 217; i++)
//				{
//					if (isVisable[i - 1] == 0) continue;
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 12].x), ToScreenY(rect.Height(), rect.top, sph[i + 12].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//				}
//				for (int i = 217; i < 229; i++)
//				{
//					if (isVisableDot2[i - 217] == 0) continue;
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[229].x), ToScreenY(rect.Height(), rect.top, sph[229].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//				}
//			}
//			else
//			{
//				for (int i = 1; i < 13; i++)
//				{
//					if (isVisableDot1[i - 1] == 0) continue;
//					sphBrush.CreateSolidBrush(RGB(0, rgbTemp1_12[i - 1], 0));
//					prevBrush = memDC.SelectObject(&sphBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					sphBrush.DeleteObject();
//				}
//				for (int i = 1; i < 217; i++)
//				{
//					if (isVisable[i - 1] == 0) continue;
//					sphBrush.CreateSolidBrush(RGB(0, rgbTemp1_216[i - 1], 0));
//					prevBrush = memDC.SelectObject(&sphBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 12].x), ToScreenY(rect.Height(), rect.top, sph[i + 12].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					sphBrush.DeleteObject();
//				}
//				for (int i = 217; i < 229; i++)
//				{
//					if (isVisableDot2[i - 217] == 0) continue;
//					sphBrush.CreateSolidBrush(RGB(0, rgbTemp217_228[i - 217], 0));
//					prevBrush = memDC.SelectObject(&sphBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[229].x), ToScreenY(rect.Height(), rect.top, sph[229].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					sphBrush.DeleteObject();
//				}
//			}
//		}
//#pragma endregion
//
//#pragma region 두번째 삼각 폴리곤 -> 가장 끝쪽의 꼭짓점들이랑은 더이상 이을 필요 없음
//		countInt = 0;
//		for (int i = 1; i < 217; i++)
//		{
//			float cross[3][1] = {};
//
//			if ((i % 12) == 0)
//			{
//				vFst[0][0] = -newSphereWC[i + 1].x + newSphereWC[i - 11].x;
//				vFst[1][0] = -newSphereWC[i + 1].y + newSphereWC[i - 11].y;
//				vFst[2][0] = -newSphereWC[i + 1].z + newSphereWC[i - 11].z;
//				vSec[0][0] = -newSphereWC[i - 11].x + newSphereWC[i].x;
//				vSec[1][0] = -newSphereWC[i - 11].y + newSphereWC[i].y;
//				vSec[2][0] = -newSphereWC[i - 11].z + newSphereWC[i].z;
//				cameraToPolygon1[0][0] = newSphereWC[i].x;
//				cameraToPolygon1[1][0] = newSphereWC[i].y;
//				cameraToPolygon1[2][0] = newSphereWC[i].z;
//				cameraToPolygon2[0][0] = newSphereWC[i - 11].x;
//				cameraToPolygon2[1][0] = newSphereWC[i - 11].y;
//				cameraToPolygon2[2][0] = newSphereWC[i - 11].z;
//				cameraToPolygon3[0][0] = newSphereWC[i + 1].x;
//				cameraToPolygon3[1][0] = newSphereWC[i + 1].y;
//				cameraToPolygon3[2][0] = newSphereWC[i + 1].z;
//			}
//			else
//			{
//				vFst[0][0] = -newSphereWC[i + 13].x + newSphereWC[i + 1].x;
//				vFst[1][0] = -newSphereWC[i + 13].y + newSphereWC[i + 1].y;
//				vFst[2][0] = -newSphereWC[i + 13].z + newSphereWC[i + 1].z;
//				vSec[0][0] = -newSphereWC[i + 1].x + newSphereWC[i].x;
//				vSec[1][0] = -newSphereWC[i + 1].y + newSphereWC[i].y;
//				vSec[2][0] = -newSphereWC[i + 1].z + newSphereWC[i].z;
//				cameraToPolygon1[0][0] = newSphereWC[i].x;
//				cameraToPolygon1[1][0] = newSphereWC[i].y;
//				cameraToPolygon1[2][0] = newSphereWC[i].z;
//				cameraToPolygon2[0][0] = newSphereWC[i + 1].x;
//				cameraToPolygon2[1][0] = newSphereWC[i + 1].y;
//				cameraToPolygon2[2][0] = newSphereWC[i + 1].z;
//				cameraToPolygon3[0][0] = newSphereWC[i + 13].x;
//				cameraToPolygon3[1][0] = newSphereWC[i + 13].y;
//				cameraToPolygon3[2][0] = newSphereWC[i + 13].z;
//			}
//			vFst[3][0] = 1; vSec[3][0] = 1;
//
//			float* cPtr = CrossProduct(vFst, vSec);
//			int count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				cross[j][0] = *(cPtr + count);
//				count++;
//			}
//
//			float crossBeforeNorm[4][1] = { { cross[0][0] },{ cross[1][0] },{ cross[2][0] },{ 1 } };
//			cPtr = MatrixNormalize(crossBeforeNorm);
//			count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				cross[j][0] = *(cPtr + count);
//				count++;
//			}
//
//			for (int j = 0; j < 3; j++)
//			{
//				if (projNum == 0)
//				{
//					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
//					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
//					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
//				}
//				else break;
//			}
//			if (projNum == 1)
//			{
//				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
//				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
//				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
//			}
//
//			float result1 = DotProduct(vPolygon1, cross);
//			float result2 = DotProduct(vPolygon2, cross);
//			float result3 = DotProduct(vPolygon3, cross);
//			lightDotPrd = -DotProduct(cross, lightDirection);
//			if (lightDotPrd < 0) lightDotPrd = 0;
//			rgbTemp1_216_2[i - 1] = (int)round(255 * lightDotPrd);
//
//			if (result1 > 0 || result2 > 0 || result3 > 0)
//			{
//				countInt++;
//				continue;
//			}
//			else
//			{
//				isVisable[countInt] = 1;
//				countInt++;
//			}
//		}
//
//		for (int i = 1; i < 217; i++)
//		{
//			if (frameNum == 1)
//			{
//				if (figure.isClicked)
//				{
//					if (isVisable[i - 1] == 0) continue;
//					sphBrush.CreateSolidBrush(RGB(0, rgbTemp1_216_2[i - 1], 0));
//					prevBrush = memDC.SelectObject(&sphBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					sphBrush.DeleteObject();
//				}
//				else
//				{
//					if (isVisable[i - 1] == 0) continue;
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//				}
//			}
//			else
//			{
//				if (figure.isClicked)
//				{
//					if (isVisable[i - 1] == 0) continue;
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//				}
//				else
//				{
//					if (isVisable[i - 1] == 0) continue;
//					sphBrush.CreateSolidBrush(RGB(0, rgbTemp1_216_2[i - 1], 0));
//					prevBrush = memDC.SelectObject(&sphBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					if (i % 12 == 0)
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
//					}
//					else
//					{
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
//					}
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					sphBrush.DeleteObject();
//				}
//			}
//
//		}
//#pragma endregion
//	}
//
//	for (auto& figure : v_torusFigure)
//	{
//#pragma region 좌표계 변환 후 그리기
//		// 원들끼리 그리기
//		float dotFst[4][1] = {};
//		float dotSec[4][1] = {};
//		int myInt[144] = {};
//		int mySecInt[144] = {};
//		int countInt = 0;
//		int fstResult = 0; // 처음 삼각형 그릴 때 i=0 일 때 조건 용
//		int secResult = 0; // 두번째 삼각형 그릴 때 i=0 일 때 조건 용
//		float cameraToPolygon1[3][1] = {}; // 카메라 -> 정점 벡터
//		float cameraToPolygon2[3][1] = {}; // 카메라 -> 정점 벡터
//		float cameraToPolygon3[3][1] = {}; // 카메라 -> 정점 벡터
//		float vPolygon1[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
//		float vPolygon2[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
//		float vPolygon3[3][1] = {}; // 카메라 -> 정점 벡터 계산용 임시 배열
//									// 배열에서 받아온 포인터로 vertex 가져오기
//		int count = 0;
//		MyVertex tor[144] = {};
//		for (int i = 0; i < 144; i++) {
//			tor[i] = figure.torus[i];
//			count++;
//		}
//
//		if (figure.torusRadius != figure.originTorusRadius) // 크기 변경이 된 친구라면?
//		{ // 다시 만들어서 넣어줌
//			MyVertex* makingTorus = pTorus(figure.torusOrigin.x, figure.torusOrigin.y, figure.torusOrigin.z, figure.torusLongRadius, figure.torusRadius);
//			int torusCount = 0;
//			for (int i = 0; i < 144; i++)
//			{
//				tor[i] = *(makingTorus + torusCount);
//				torusCount++;
//			}
//		}
//
//		////// 테스트 : 카메라 좌표계에서 x, y축으로 평행이동 시키기
//		if (figure.moveY != 0)
//		{
//			for (int i = 0; i < 144; i++)
//			{
//				tor[i].y += figure.moveY;
//			}
//		}
//		if (figure.moveX != 0)
//		{
//			for (int i = 0; i < 144; i++)
//			{
//				tor[i].x += figure.moveX;
//			}
//		}
//		if (figure.moveZ != 0)
//		{
//			for (int i = 0; i < 144; i++)
//			{
//				tor[i].z += figure.moveZ;
//			}
//		}
//		////////////////////////////////////////////////////////////
//
//#pragma region 뷰 행렬 변환
//
//		float* fPtr;
//		float sample[4][1] = {};
//		// torus 각 점들을 뷰 행렬 변환 시킴
//		for (int i = 0; i < 144; i++)
//		{
//			sample[0][0] = tor[i].x;
//			sample[1][0] = tor[i].y;
//			sample[2][0] = tor[i].z;
//			sample[3][0] = 1;
//			fPtr = MatrixMulti(view, sample);
//
//			int torCount = 0;
//			tor[i].x = *(fPtr + torCount);
//			torCount++;
//			tor[i].y = *(fPtr + torCount);
//			torCount++;
//			tor[i].z = *(fPtr + torCount);
//			torCount++;
//		}
//#pragma endregion
//
//		////// 테스트 : 카메라 좌표계에서 회전시키기
//		float originInView[4][1] = {};
//		originInView[0][0] = figure.torusOrigin.x; originInView[1][0] = figure.torusOrigin.y; originInView[2][0] = figure.torusOrigin.z; originInView[3][0] = 1;
//		fPtr = MatrixMulti(view, originInView);
//		int sampleCount = 0;
//		for (int i = 0; i < 3; i++) // 뷰 좌표계에서의 큐브의 중심을 구하기
//		{
//			originInView[i][0] = *(fPtr + sampleCount);
//			sampleCount++;
//		}
//
//		for (int i = 0; i < 144; i++) // 뷰 좌표계에서의 큐브 중심을 원점으로 옮기면서 나머지 점들도 다 동일하게 옮겨줌
//		{
//			tor[i].x -= originInView[0][0];
//			tor[i].y -= originInView[1][0];
//			tor[i].z -= originInView[2][0];
//		}
//
//		for (int i = 0; i < 144; i++) // 해당 점들을 축을 기준으로 회전
//		{
//			float sample[4][1] = { { tor[i].x },{ tor[i].y },{ tor[i].z },{ 1 } };
//			float* rotPtr = MatrixRotate(sample, figure.rotX, figure.rotY, 0);
//			sampleCount = 0;
//			for (int j = 0; j < 4; j++)
//			{
//				sample[j][0] = *(rotPtr + sampleCount);
//				sampleCount++;
//			}
//			tor[i].x = sample[0][0]; tor[i].y = sample[1][0]; tor[i].z = sample[2][0];
//		}
//
//		for (int i = 0; i < 144; i++) // 다시 큐브의 중심을 원점에서 원래의 중심으로 복구
//		{
//			tor[i].x += originInView[0][0];
//			tor[i].y += originInView[1][0];
//			tor[i].z += originInView[2][0];
//		}
//
//		////// 테스트 : z가 -1보다 큰 친구들은 화면에서 지우기 -> 카메라 뒤쪽 절두체에서 투영되는 친구들 제거
//		BOOL insideFrustum = TRUE;
//		for (int i = 0; i < 144; i++)
//		{
//			if (tor[i].z > -1)
//			{
//				insideFrustum = FALSE;
//				break;
//			}
//		}
//		if (!insideFrustum) continue;
//		//////////////////////////////////////////////////////
//
//		////// 테스트 : 05.17 -> 카메라 기준 가장 먼 곳의 정점부터 그림 그리기
//		// 뷰 좌표 기준 원점까지의 거리를 순서대로 
//		float originToVertexLength[144] = {};
//		int fromFarToNear[144] = {};
//		float vertexSample[3][1] = {};
//		float distance;
//		for (int i = 0; i < 144; i++)
//		{
//			vertexSample[0][0] = tor[i].x;
//			vertexSample[1][0] = tor[i].y;
//			vertexSample[2][0] = tor[i].z;
//			distance = vectorLength(vertexSample);
//			originToVertexLength[i] = distance;
//		} // 각 정점에서 카메라까지의 거리를 체크
//		int num = 0;
//		for (int i = 0; i < 144; i++) // 가장 큰(먼) 것 부터 배열에 넣음
//		{
//			float biggerOne = -1;
//			for (int j = 0; j < 144; j++)
//			{
//				if (originToVertexLength[j] > biggerOne)
//				{
//					biggerOne = originToVertexLength[j];
//					num = j;
//				}
//			}
//			originToVertexLength[num] = -1;
//			fromFarToNear[i] = num;
//		}
//
//		//////////////////////////////////////////////////////////////////////
//
//#pragma region 투영 행렬 변환
//		// 뷰 변환 한 점들 투영 변환
//		if (projNum == 0)
//		{
//			for (int i = 0; i < 144; i++)
//			{
//				sample[0][0] = tor[i].x;
//				sample[1][0] = tor[i].y;
//				sample[2][0] = tor[i].z;
//				sample[3][0] = 1;
//				fPtr = MatrixMulti(proj, sample);
//				int torCount = 0;
//
//				tor[i].x = *(fPtr + torCount);
//				torCount++;
//				tor[i].y = *(fPtr + torCount);
//				torCount++;
//				tor[i].z = *(fPtr + torCount);
//				torCount++;
//
//				tor[i].x /= tor[i].z;
//				tor[i].y /= tor[i].z;
//			}
//		}
//		else
//		{
//			for (int i = 0; i < 144; i++)
//			{
//				tor[i].x /= (width / height) * -originInView[2][0];
//				tor[i].y /= -originInView[2][0];
//			}
//		}
//
//#pragma endregion
//
//		/////////// 테스트 : 화면 밖으로 모든 점이 나가버리면 안그리게 할 것
//		float pointOfView[2][1] = {};
//		bool outOfView[144] = {};
//		for (int i = 0; i < 144; i++)
//		{
//			pointOfView[0][0] = ToScreenX(width, left, tor[i].x); pointOfView[1][0] = ToScreenY(height, top, tor[i].y);
//			if (pointOfView[0][0] < 0 || pointOfView[0][0] > width || pointOfView[1][0] < 0 || pointOfView[1][0] > height)
//				outOfView[i] = TRUE;
//			else outOfView[i] = FALSE;
//		}
//		bool totalOut = FALSE;
//		for (int i = 0; i < 144; i++)
//		{
//			if (outOfView[i]) totalOut = TRUE;
//			else
//			{
//				totalOut = FALSE;
//				break;
//			}
//		}
//		if (totalOut) continue;
//		////////////////////////////////////////////////////////////////////
//
//		//위치가 이동되었으니 월드좌표계의 좌표들도 변했을 것-> 현재 받아둔 좌표를 다 뒤로 돌려서 새로운 월드좌표를 받아야 함
//		MyVertex newTorusWC[144] = {};
//		float tempVertex[4][1] = {};
//		for (int i = 0; i < 144; i++)
//		{
//			float* tempPtr;
//			int tempCount = 0;
//			if (projNum == 0)
//			{
//				tempVertex[0][0] = tor[i].x * tor[i].z; tempVertex[1][0] = tor[i].y * tor[i].z; tempVertex[2][0] = tor[i].z; tempVertex[3][0] = 1;
//				tempPtr = MatrixMulti(projReverse, tempVertex);
//				tempCount = 0;
//				for (int j = 0; j < 4; j++) // 투영 역행렬 = 카메라 좌표계
//				{
//					tempVertex[j][0] = *(tempPtr + tempCount);
//					tempCount++;
//				}
//			}
//			else
//			{
//				tempVertex[0][0] = tor[i].x * (width / height) * 100;
//				tempVertex[1][0] = tor[i].y * 100;
//				tempVertex[2][0] = tor[i].z; tempVertex[3][0] = 1;
//			}
//
//			tempPtr = MatrixMulti(viewReverse, tempVertex);
//			tempCount = 0;
//			for (int j = 0; j < 4; j++) // 뷰 역행렬 = 월드 좌표계
//			{
//				tempVertex[j][0] = *(tempPtr + tempCount);
//				tempCount++;
//			}
//			// 새로운 월드 좌표계 저장
//			newTorusWC[i].x = tempVertex[0][0]; newTorusWC[i].y = tempVertex[1][0]; newTorusWC[i].z = tempVertex[2][0];
//			figure.torus_justForClick[i].x = tempVertex[0][0]; figure.torus_justForClick[i].y = tempVertex[1][0]; figure.torus_justForClick[i].z = tempVertex[2][0];
//		}
//		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		CBrush torBrush;
//		CBrush* prevBrush;
//		float lightDotPrd;
//		int rgbTemp[144];
//		int rgbTemp_2[144];
//
//#pragma region 첫번째 삼각 폴리곤 
//		//for (int i = 0; i < 144; i++)
//		for (auto i : fromFarToNear)
//		{
//			if ((i + 1) % 12 == 0)
//			{
//				if (i >= 132)
//				{
//					dotFst[0][0] = -newTorusWC[i].x + newTorusWC[i - 132].x;
//					dotSec[0][0] = -newTorusWC[i - 132].x + newTorusWC[i - 11].x;
//					dotFst[1][0] = -newTorusWC[i].y + newTorusWC[i - 132].y;
//					dotSec[1][0] = -newTorusWC[i - 132].y + newTorusWC[i - 11].y;
//					dotFst[2][0] = -newTorusWC[i].z + newTorusWC[i - 132].z;
//					dotSec[2][0] = -newTorusWC[i - 132].z + newTorusWC[i - 11].z;
//					cameraToPolygon1[0][0] = newTorusWC[i].x;
//					cameraToPolygon1[1][0] = newTorusWC[i].y;
//					cameraToPolygon1[2][0] = newTorusWC[i].z;
//					cameraToPolygon2[0][0] = newTorusWC[i - 132].x;
//					cameraToPolygon2[1][0] = newTorusWC[i - 132].y;
//					cameraToPolygon2[2][0] = newTorusWC[i - 132].z;
//					cameraToPolygon3[0][0] = newTorusWC[i - 11].x;
//					cameraToPolygon3[1][0] = newTorusWC[i - 11].y;
//					cameraToPolygon3[2][0] = newTorusWC[i - 11].z;
//				}
//				else
//				{
//					dotFst[0][0] = -newTorusWC[i].x + newTorusWC[i + 12].x;
//					dotSec[0][0] = -newTorusWC[i + 12].x + newTorusWC[i - 11].x;
//					dotFst[1][0] = -newTorusWC[i].y + newTorusWC[i + 12].y;
//					dotSec[1][0] = -newTorusWC[i + 12].y + newTorusWC[i - 11].y;
//					dotFst[2][0] = -newTorusWC[i].z + newTorusWC[i + 12].z;
//					dotSec[2][0] = -newTorusWC[i + 12].z + newTorusWC[i - 11].z;
//					cameraToPolygon1[0][0] = newTorusWC[i].x;
//					cameraToPolygon1[1][0] = newTorusWC[i].y;
//					cameraToPolygon1[2][0] = newTorusWC[i].z;
//					cameraToPolygon2[0][0] = newTorusWC[i + 12].x;
//					cameraToPolygon2[1][0] = newTorusWC[i + 12].y;
//					cameraToPolygon2[2][0] = newTorusWC[i + 12].z;
//					cameraToPolygon3[0][0] = newTorusWC[i - 11].x;
//					cameraToPolygon3[1][0] = newTorusWC[i - 11].y;
//					cameraToPolygon3[2][0] = newTorusWC[i - 11].z;
//				}
//			}
//			else
//			{
//				if (i >= 132)
//				{
//					dotFst[0][0] = -newTorusWC[i].x + newTorusWC[i - 132].x;
//					dotSec[0][0] = -newTorusWC[i - 132].x + newTorusWC[i + 1].x;
//					dotFst[1][0] = -newTorusWC[i].y + newTorusWC[i - 132].y;
//					dotSec[1][0] = -newTorusWC[i - 132].y + newTorusWC[i + 1].y;
//					dotFst[2][0] = -newTorusWC[i].z + newTorusWC[i - 132].z;
//					dotSec[2][0] = -newTorusWC[i - 132].z + newTorusWC[i + 1].z;
//					cameraToPolygon1[0][0] = newTorusWC[i].x;
//					cameraToPolygon1[1][0] = newTorusWC[i].y;
//					cameraToPolygon1[2][0] = newTorusWC[i].z;
//					cameraToPolygon2[0][0] = newTorusWC[i - 132].x;
//					cameraToPolygon2[1][0] = newTorusWC[i - 132].y;
//					cameraToPolygon2[2][0] = newTorusWC[i - 132].z;
//					cameraToPolygon3[0][0] = newTorusWC[i + 1].x;
//					cameraToPolygon3[1][0] = newTorusWC[i + 1].y;
//					cameraToPolygon3[2][0] = newTorusWC[i + 1].z;
//				}
//				else
//				{
//					dotFst[0][0] = -newTorusWC[i].x + newTorusWC[i + 12].x;
//					dotSec[0][0] = -newTorusWC[i + 12].x + newTorusWC[i + 1].x;
//					dotFst[1][0] = -newTorusWC[i].y + newTorusWC[i + 12].y;
//					dotSec[1][0] = -newTorusWC[i + 12].y + newTorusWC[i + 1].y;
//					dotFst[2][0] = -newTorusWC[i].z + newTorusWC[i + 12].z;
//					dotSec[2][0] = -newTorusWC[i + 12].z + newTorusWC[i + 1].z;
//					cameraToPolygon1[0][0] = newTorusWC[i].x;
//					cameraToPolygon1[1][0] = newTorusWC[i].y;
//					cameraToPolygon1[2][0] = newTorusWC[i].z;
//					cameraToPolygon2[0][0] = newTorusWC[i + 12].x;
//					cameraToPolygon2[1][0] = newTorusWC[i + 12].y;
//					cameraToPolygon2[2][0] = newTorusWC[i + 12].z;
//					cameraToPolygon3[0][0] = newTorusWC[i + 1].x;
//					cameraToPolygon3[1][0] = newTorusWC[i + 1].y;
//					cameraToPolygon3[2][0] = newTorusWC[i + 1].z;
//				}
//			}
//			dotFst[3][0] = 1;
//			dotSec[3][0] = 1;
//
//			float crsBoth[3][1] = {};
//			float* ptr = CrossProduct(dotFst, dotSec);
//			int count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				crsBoth[j][0] = *(ptr + count);
//				count++;
//			}
//
//			float crossBeforeNorm[4][1] = { { crsBoth[0][0] },{ crsBoth[1][0] },{ crsBoth[2][0] },{ 1 } };
//			ptr = MatrixNormalize(crossBeforeNorm);
//			count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				crsBoth[j][0] = *(ptr + count);
//				count++;
//			}
//
//			for (int j = 0; j < 3; j++)
//			{
//				if (projNum == 0)
//				{
//					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
//					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
//					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
//				}
//				else break;
//			}
//			if (projNum == 1)
//			{
//				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
//				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
//				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
//			}
//
//			float result1 = DotProduct(vPolygon1, crsBoth);
//			float result2 = DotProduct(vPolygon2, crsBoth);
//			float result3 = DotProduct(vPolygon3, crsBoth);
//			lightDotPrd = -DotProduct(crsBoth, lightDirection);
//			if (lightDotPrd < 0)lightDotPrd = 0;
//			rgbTemp[i] = (int)round(255 * lightDotPrd);
//
//			if (i == 0)
//			{
//				if (result1 > 0 || result2 > 0 || result3 > 0)
//				{
//					continue;
//				}
//				else
//				{
//					fstResult = 1;
//					continue;
//				}
//			}
//
//			if (result1 > 0 || result2 > 0 || result3 > 0)
//			{
//				countInt++;
//				continue;
//			}
//			myInt[countInt] = i;
//			countInt++;
//		}
//		// i = 0 일때만 따로 그려주기 -> 0일때는 건너뛰게 그려놓았음.
//		int rgbCount;
//		if (frameNum == 1)
//		{
//			if (fstResult == 1)
//			{
//				if (figure.isClicked == FALSE)
//				{// 선으로 그리기
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//				}
//				else
//				{
//					// 면으로 그리기
//					torBrush.CreateSolidBrush(RGB(0, rgbTemp[0], 0));
//					prevBrush = memDC.SelectObject(&torBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					torBrush.DeleteObject();
//				}
//			}
//			for (auto i : myInt)
//			{
//				if (i == 0) continue;
//				if ((i + 1) % 12 == 0)
//				{
//					if (i >= 132)
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//				else
//				{
//					if (i >= 132)
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//			}
//		}
//		else
//		{
//			if (fstResult == 1)
//			{
//				if (figure.isClicked)
//				{// 선으로 그리기
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//				}
//				else
//				{
//					// 면으로 그리기
//					torBrush.CreateSolidBrush(RGB(0, rgbTemp[0], 0));
//					prevBrush = memDC.SelectObject(&torBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					torBrush.DeleteObject();
//				}
//			}
//			rgbCount = -1;
//			for (auto i : myInt)
//			{
//				rgbCount++;
//				if (i == 0) continue;
//				if ((i + 1) % 12 == 0)
//				{
//					if (i >= 132)
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//				else
//				{
//					if (i >= 132)
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//			}
//		}
//		//////
//#pragma endregion
//#pragma region 두번째 삼각 폴리곤 그리기
//		countInt = 0;
//		//for (int i = 0; i < 144; i++)
//		for (auto i : fromFarToNear)
//		{
//			if ((i + 12) % 12 == 0) // 0, 12, 24, 36, .... , 120, 132
//			{
//				if (i == 0)
//				{
//					dotFst[0][0] = -newTorusWC[i].x + newTorusWC[i + 132].x;
//					dotSec[0][0] = -newTorusWC[i + 132].x + newTorusWC[i + 11].x;
//					dotFst[1][0] = -newTorusWC[i].y + newTorusWC[i + 132].y;
//					dotSec[1][0] = -newTorusWC[i + 132].y + newTorusWC[i + 11].y;
//					dotFst[2][0] = -newTorusWC[i].z + newTorusWC[i + 132].z;
//					dotSec[2][0] = -newTorusWC[i + 132].z + newTorusWC[i + 11].z;
//					cameraToPolygon1[0][0] = newTorusWC[i].x;
//					cameraToPolygon1[1][0] = newTorusWC[i].y;
//					cameraToPolygon1[2][0] = newTorusWC[i].z;
//					cameraToPolygon2[0][0] = newTorusWC[i + 132].x;
//					cameraToPolygon2[1][0] = newTorusWC[i + 132].y;
//					cameraToPolygon2[2][0] = newTorusWC[i + 132].z;
//					cameraToPolygon3[0][0] = newTorusWC[i + 11].x;
//					cameraToPolygon3[1][0] = newTorusWC[i + 11].y;
//					cameraToPolygon3[2][0] = newTorusWC[i + 11].z;
//				}
//				else
//				{
//					dotFst[0][0] = -newTorusWC[i].x + newTorusWC[i - 12].x;
//					dotSec[0][0] = -newTorusWC[i - 12].x + newTorusWC[i + 11].x;
//					dotFst[1][0] = -newTorusWC[i].y + newTorusWC[i - 12].y;
//					dotSec[1][0] = -newTorusWC[i - 12].y + newTorusWC[i + 11].y;
//					dotFst[2][0] = -newTorusWC[i].z + newTorusWC[i - 12].z;
//					dotSec[2][0] = -newTorusWC[i - 12].z + newTorusWC[i + 11].z;
//					cameraToPolygon1[0][0] = newTorusWC[i].x;
//					cameraToPolygon1[1][0] = newTorusWC[i].y;
//					cameraToPolygon1[2][0] = newTorusWC[i].z;
//					cameraToPolygon2[0][0] = newTorusWC[i - 12].x;
//					cameraToPolygon2[1][0] = newTorusWC[i - 12].y;
//					cameraToPolygon2[2][0] = newTorusWC[i - 12].z;
//					cameraToPolygon3[0][0] = newTorusWC[i + 11].x;
//					cameraToPolygon3[1][0] = newTorusWC[i + 11].y;
//					cameraToPolygon3[2][0] = newTorusWC[i + 11].z;
//				}
//			}
//			else
//			{
//				if (i < 12)
//				{
//					dotFst[0][0] = -newTorusWC[i].x + newTorusWC[i + 132].x;
//					dotSec[0][0] = -newTorusWC[i + 132].x + newTorusWC[i - 1].x;
//					dotFst[1][0] = -newTorusWC[i].y + newTorusWC[i + 132].y;
//					dotSec[1][0] = -newTorusWC[i + 132].y + newTorusWC[i - 1].y;
//					dotFst[2][0] = -newTorusWC[i].z + newTorusWC[i + 132].z;
//					dotSec[2][0] = -newTorusWC[i + 132].z + newTorusWC[i - 1].z;
//					cameraToPolygon1[0][0] = newTorusWC[i].x;
//					cameraToPolygon1[1][0] = newTorusWC[i].y;
//					cameraToPolygon1[2][0] = newTorusWC[i].z;
//					cameraToPolygon2[0][0] = newTorusWC[i + 132].x;
//					cameraToPolygon2[1][0] = newTorusWC[i + 132].y;
//					cameraToPolygon2[2][0] = newTorusWC[i + 132].z;
//					cameraToPolygon3[0][0] = newTorusWC[i - 1].x;
//					cameraToPolygon3[1][0] = newTorusWC[i - 1].y;
//					cameraToPolygon3[2][0] = newTorusWC[i - 1].z;
//				}
//				else
//				{
//					dotFst[0][0] = -newTorusWC[i].x + newTorusWC[i - 12].x;
//					dotSec[0][0] = -newTorusWC[i - 12].x + newTorusWC[i - 1].x;
//					dotFst[1][0] = -newTorusWC[i].y + newTorusWC[i - 12].y;
//					dotSec[1][0] = -newTorusWC[i - 12].y + newTorusWC[i - 1].y;
//					dotFst[2][0] = -newTorusWC[i].z + newTorusWC[i - 12].z;
//					dotSec[2][0] = -newTorusWC[i - 12].z + newTorusWC[i - 1].z;
//					cameraToPolygon1[0][0] = newTorusWC[i].x;
//					cameraToPolygon1[1][0] = newTorusWC[i].y;
//					cameraToPolygon1[2][0] = newTorusWC[i].z;
//					cameraToPolygon2[0][0] = newTorusWC[i - 12].x;
//					cameraToPolygon2[1][0] = newTorusWC[i - 12].y;
//					cameraToPolygon2[2][0] = newTorusWC[i - 12].z;
//					cameraToPolygon3[0][0] = newTorusWC[i - 1].x;
//					cameraToPolygon3[1][0] = newTorusWC[i - 1].y;
//					cameraToPolygon3[2][0] = newTorusWC[i - 1].z;
//				}
//			}
//			dotFst[3][0] = 1;
//			dotSec[3][0] = 1;
//
//			float crsBoth[3][1] = {};
//			float* ptr = CrossProduct(dotFst, dotSec);
//			int count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				crsBoth[j][0] = *(ptr + count);
//				count++;
//			}
//
//			float crossBeforeNorm[4][1] = { { crsBoth[0][0] },{ crsBoth[1][0] },{ crsBoth[2][0] },{ 1 } };
//			ptr = MatrixNormalize(crossBeforeNorm);
//			count = 0;
//			for (int j = 0; j < 3; j++)
//			{
//				crsBoth[j][0] = *(ptr + count);
//				count++;
//			}
//
//			for (int j = 0; j < 3; j++)
//			{
//				if (projNum == 0)
//				{
//					vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
//					vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
//					vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
//				}
//				else break;
//			}
//			if (projNum == 1)
//			{
//				vPolygon1[0][0] = lookX; vPolygon1[1][0] = lookY; vPolygon1[2][0] = lookZ;
//				vPolygon2[0][0] = lookX; vPolygon2[1][0] = lookY; vPolygon2[2][0] = lookZ;
//				vPolygon3[0][0] = lookX; vPolygon3[1][0] = lookY; vPolygon3[2][0] = lookZ;
//			}
//
//			float result1 = DotProduct(vPolygon1, crsBoth);
//			float result2 = DotProduct(vPolygon2, crsBoth);
//			float result3 = DotProduct(vPolygon3, crsBoth);
//			lightDotPrd = -DotProduct(crsBoth, lightDirection);
//			if (lightDotPrd < 0) lightDotPrd = 0;
//			rgbTemp[i] = (int)round(255 * lightDotPrd);
//
//
//			if (i == 0)
//			{
//				if (result1 > 0 || result2 > 0 || result3 > 0)
//				{
//					continue;
//				}
//				else
//				{
//					secResult = 1;
//					continue;
//				}
//			}
//
//			if (result1 > 0 || result2 > 0 || result3 > 0)
//			{
//				countInt++;
//				continue;
//			}
//			mySecInt[countInt] = i;
//			countInt++;
//		}
//		// i = 0 일때만 따로 그려주기 -> 0일때는 건너뛰게 그려놓았음.
//		rgbCount = 0;
//		if (frameNum == 1)
//		{
//			if (secResult == 1)
//			{
//				if (figure.isClicked == FALSE)
//				{
//					// 선으로 그리기
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[11].x), ToScreenY(rect.Height(), rect.top, tor[11].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[132].x), ToScreenY(rect.Height(), rect.top, tor[132].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//				}
//				else
//				{
//					// 면으로 그리기
//					torBrush.CreateSolidBrush(RGB(0, rgbTemp[0], 0));
//					prevBrush = memDC.SelectObject(&torBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[11].x), ToScreenY(rect.Height(), rect.top, tor[11].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[132].x), ToScreenY(rect.Height(), rect.top, tor[132].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					torBrush.DeleteObject();
//				}
//			}
//			//////
//			for (auto i : mySecInt)
//			{
//				if (i == 0) continue;
//				if (i % 12 == 0)
//				{
//					if (figure.isClicked == FALSE)
//					{
//						// 선으로 그리기
//						memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 11].x), ToScreenY(rect.Height(), rect.top, tor[i + 11].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//					}
//					else
//					{
//						// 면으로 그리기
//						torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//						prevBrush = memDC.SelectObject(&torBrush);
//						memDC.BeginPath();
//						memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 11].x), ToScreenY(rect.Height(), rect.top, tor[i + 11].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						memDC.EndPath();
//						memDC.StrokeAndFillPath();
//						memDC.SelectObject(prevBrush);
//						torBrush.DeleteObject();
//					}
//				}
//				else
//				{
//					if (i < 12)
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 132].x), ToScreenY(rect.Height(), rect.top, tor[i + 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 132].x), ToScreenY(rect.Height(), rect.top, tor[i + 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//			}
//		}
//		else
//		{
//			if (secResult == 1)
//			{
//				if (figure.isClicked)
//				{
//					// 선으로 그리기
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[11].x), ToScreenY(rect.Height(), rect.top, tor[11].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[132].x), ToScreenY(rect.Height(), rect.top, tor[132].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//				}
//				else
//				{
//					// 면으로 그리기
//					torBrush.CreateSolidBrush(RGB(0, rgbTemp[0], 0));
//					prevBrush = memDC.SelectObject(&torBrush);
//					memDC.BeginPath();
//					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[11].x), ToScreenY(rect.Height(), rect.top, tor[11].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[132].x), ToScreenY(rect.Height(), rect.top, tor[132].y));
//					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					memDC.EndPath();
//					memDC.StrokeAndFillPath();
//					memDC.SelectObject(prevBrush);
//					torBrush.DeleteObject();
//				}
//			}
//			//////
//			for (auto i : mySecInt)
//			{
//				if (i == 0) continue;
//				if (i % 12 == 0)
//				{
//					if (figure.isClicked)
//					{
//						// 선으로 그리기
//						memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 11].x), ToScreenY(rect.Height(), rect.top, tor[i + 11].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//					}
//					else
//					{
//						// 면으로 그리기
//						torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//						prevBrush = memDC.SelectObject(&torBrush);
//						memDC.BeginPath();
//						memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 11].x), ToScreenY(rect.Height(), rect.top, tor[i + 11].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						memDC.EndPath();
//						memDC.StrokeAndFillPath();
//						memDC.SelectObject(prevBrush);
//						torBrush.DeleteObject();
//					}
//				}
//				else
//				{
//					if (i < 12)
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 132].x), ToScreenY(rect.Height(), rect.top, tor[i + 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 132].x), ToScreenY(rect.Height(), rect.top, tor[i + 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//			}
//		}
//
//#pragma endregion
//
//#pragma region 면이 겹쳐보이는것을 해결하기 위해 처음 그린부분 중 앞부분만 다시 그려줌
//		int countFor96 = 0;
//		int whereIs0 = 0;
//		if (frameNum == 1)
//		{
//			if (fstResult == 1)
//			{
//				for (int i = 0; i < 144; i++)
//				{
//					if (fromFarToNear[i] == 0)
//					{
//						whereIs0 = i;
//						break;
//					}
//				}
//
//				if (whereIs0 > 95)
//				{
//					if (figure.isClicked == FALSE)
//					{// 선으로 그리기
//						memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					}
//					else
//					{
//						// 면으로 그리기
//						torBrush.CreateSolidBrush(RGB(0, rgbTemp[0], 0));
//						prevBrush = memDC.SelectObject(&torBrush);
//						memDC.BeginPath();
//						memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//						memDC.EndPath();
//						memDC.StrokeAndFillPath();
//						memDC.SelectObject(prevBrush);
//						torBrush.DeleteObject();
//					}
//				}
//			}
//			for (auto i : myInt)
//			{
//				if (countFor96 < 95)
//				{
//					countFor96++;
//					continue;
//				}
//				if (i == 0) continue;
//				if ((i + 1) % 12 == 0)
//				{
//					if (i >= 132)
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//				else
//				{
//					if (i >= 132)
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked == FALSE)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//			}
//		}
//		else
//		{
//			if (fstResult == 1)
//			{
//				for (int i = 0; i < 144; i++)
//				{
//					if (fromFarToNear[i] == 0)
//					{
//						whereIs0 = i;
//						break;
//					}
//				}
//
//				if (whereIs0 > 95)
//				{
//					if (figure.isClicked)
//					{// 선으로 그리기
//						memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//					}
//					else
//					{
//						// 면으로 그리기
//						torBrush.CreateSolidBrush(RGB(0, rgbTemp[0], 0));
//						prevBrush = memDC.SelectObject(&torBrush);
//						memDC.BeginPath();
//						memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
//						memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
//						memDC.EndPath();
//						memDC.StrokeAndFillPath();
//						memDC.SelectObject(prevBrush);
//						torBrush.DeleteObject();
//					}
//				}
//			}
//			countFor96 = 0;
//			for (auto i : myInt)
//			{
//				if (countFor96 < 95)
//				{
//					countFor96++;
//					continue;
//				}
//				if (i == 0) continue;
//				if ((i + 1) % 12 == 0)
//				{
//					if (i >= 132)
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//				else
//				{
//					if (i >= 132)
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//					else
//					{
//						if (figure.isClicked)
//						{
//							// 선으로 그리기
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//						}
//						else
//						{
//							// 면으로 그리기
//							torBrush.CreateSolidBrush(RGB(0, rgbTemp[i], 0));
//							prevBrush = memDC.SelectObject(&torBrush);
//							memDC.BeginPath();
//							memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
//							memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//							memDC.EndPath();
//							memDC.StrokeAndFillPath();
//							memDC.SelectObject(prevBrush);
//							torBrush.DeleteObject();
//						}
//					}
//				}
//			}
//		}
//#pragma endregion
//#pragma endregion
//	}
//
//	memDC.SelectObject(oldPen);
//	DeleteObject(newPen);
//
//	cdc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
//
//	memDC.SelectObject(pOldBitmap);
//	myBitmap.DeleteObject();
//	memDC.DeleteDC();
//	ReleaseDC(&cdc);
//}
//
//// 클릭하는 곳 좌표를 받아서 그곳에 그림 생성하기
//void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	float az10[4][1];
//	az10[2][0] = 200;
//	az10[0][0] = (point.x - left - width / 2) / (width / 2) * az10[2][0];
//	az10[1][0] = (point.y - top - height / 2) * (-1) / (height / 2) * az10[2][0];
//	az10[3][0] = 1; // 화면을 클릭했을 때 얻어지는 투영면에서의 한 지점
//					// 뷰 행렬
//	look[0][0] = lookX; look[1][0] = lookY; look[2][0] = lookZ;
//	float view[4][4] = {};
//	camera[0][0] = cameraX; camera[1][0] = cameraY; camera[2][0] = cameraZ;
//	float* viewPtr = ViewMatrix(camera, look);
//	int viewCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			view[i][j] = *(viewPtr + viewCount);
//			viewCount++;
//		}
//	}
//	// 투영 행렬
//	float proj[4][4] = {};
//	float* pPtr = ProjectionMatrix(width, height, 90, 2, 15);
//	int prjCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			proj[i][j] = *(pPtr + prjCount);
//			prjCount++;
//		}
//	}
//
//	// TODO: 투영면의 점을 카메라 좌표계로 옮긴다 (투영 역행렬)
//	float projReverse[4][4] = {};
//	pPtr = MatrixReverse(proj);
//	prjCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			projReverse[i][j] = *(pPtr + prjCount);
//			prjCount++;
//		}
//	}
//	// 기존 점을 역행렬과 연산
//	pPtr = MatrixMulti(projReverse, az10);
//	prjCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		az10[i][0] = *(pPtr + prjCount);
//		prjCount++;
//	}
//
//	// TODO: 카메라좌표계의 점을 월드 좌표계로 옮긴다 (뷰 역행렬)
//	float viewReverse[4][4] = {};
//	viewPtr = MatrixReverse(view);
//	viewCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			viewReverse[i][j] = *(viewPtr + viewCount);
//			viewCount++;
//		}
//	}
//
//	// 기존 점을 역행렬과 연산
//	viewPtr = MatrixMulti(viewReverse, az10);
//	viewCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		az10[i][0] = *(viewPtr + viewCount);
//		viewCount++;
//	}
//	// 이제 월드에서의 한 점이 만들어졌다.
//
//	// TODO: 해당 점을 기준으로 도형을 만든다
//	switch (figureNum)
//	{
//	case 0:
//
//#pragma region case1-Cube
//	case 1:
//	{
//		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
//		MyVertex* vPtr = pCube(20, x, y, z);
//		MyVertex cub[8] = {};
//		int count = 0;
//		for (int i = 0; i < 8; i++)
//		{
//			cub[i] = *(vPtr + count);
//			count++;
//		}
//
//		// 해당 점들을 구조체에 넣어서 vector array에 보관
//		CubeInfo Ci;
//		for (int i = 0; i < 8; i++)
//		{
//			Ci.cube[i] = cub[i];
//		}
//		Ci.vertexCount = sizeof(cub) / sizeof(MyVertex);
//		Ci.originLength = 20; Ci.length = 20;
//		Ci.cubeOrigin.x = x; Ci.cubeOrigin.y = y; Ci.cubeOrigin.z = z;
//		v_cubeFigure.push_back(Ci);
//#pragma endregion
//		break;
//	}
//
//#pragma region case2-Sphere
//	case 2:
//	{
//		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
//		MyVertex* vPtr = pSphere(30, x, y, z);
//		MyVertex sph[230] = {};
//		int count = 0;
//		for (int i = 0; i < 230; i++)
//		{
//			sph[i] = *(vPtr + count);
//			count++;
//		}
//
//		// 해당 점들을 구조체에 넣어서 vector array에 보관
//		SphereInfo Si;
//		for (int i = 0; i < 230; i++)
//		{
//			Si.sphere[i] = sph[i];
//		}
//		Si.vertexCount = sizeof(sph) / sizeof(MyVertex);
//		Si.radius = 30; Si.originRadius = 30;
//		Si.sphereOrigin.x = x; Si.sphereOrigin.y = y; Si.sphereOrigin.z = z;
//		v_sphereFigure.push_back(Si);
//#pragma endregion
//		break;
//	}
//#pragma region case3-Torus
//	case 3:
//	{
//		// 해당 점을 넣을 것
//		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
//		MyVertex* vPtr = pTorus(x, y, z, 32, 8);
//		MyVertex tor[144] = {};
//
//		int count = 0;
//		// 만든 Torus 정보 가져오기
//		for (int i = 0; i < 144; i++)
//		{
//			tor[i] = *(vPtr + count);
//			count++;
//		}
//
//		// 해당 점들을 구조체에 넣어서 vector array에 보관
//		TorusInfo ti;
//		for (int i = 0; i < 144; i++)
//		{
//			ti.torus[i] = tor[i];
//		}
//		ti.vertexCount = sizeof(tor) / sizeof(MyVertex);
//		ti.torusLongRadius = 32; ti.originTorusLongRadius = 32;
//		ti.torusRadius = 8; ti.originTorusRadius = 8;
//		ti.torusOrigin.x = x; ti.torusOrigin.y = y; ti.torusOrigin.z = z;
//		v_torusFigure.push_back(ti);
//#pragma endregion
//		break;
//	}
//	}
//
//	Invalidate();
//	CView::OnLButtonDown(nFlags, point);
//}
//
//void CMFCApplication3View::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CView::OnLButtonUp(nFlags, point);
//}
//
//
//void CMFCApplication3View::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CView::OnMouseMove(nFlags, point);
//}
//
//
//BOOL CMFCApplication3View::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	return TRUE;
//
//	return CView::OnEraseBkgnd(pDC);
//}
//
//
//void CMFCApplication3View::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CView::OnHotKey(nHotKeyId, nKey1, nKey2);
//}
//
//
//void CMFCApplication3View::OnRButtonUp(UINT nFlags, CPoint point)
//{
//#pragma region 스크린 좌표계의 점을 월드 좌표계로 이동
//	float az10[4][1];
//	az10[2][0] = 1;
//	az10[0][0] = (point.x - left - width / 2) / (width / 2);
//	az10[1][0] = (point.y - top - height / 2) * (-1) / (height / 2);
//	az10[3][0] = 1; // 화면을 클릭했을 때 얻어지는 투영면에서의 한 지점
//					// 뷰 행렬
//
//	look[0][0] = lookX; look[1][0] = lookY; look[2][0] = lookZ;
//	float view[4][4] = {};
//	camera[0][0] = cameraX; camera[1][0] = cameraY; camera[2][0] = cameraZ;
//	float* viewPtr = ViewMatrix(camera, look);
//	int viewCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			view[i][j] = *(viewPtr + viewCount);
//			viewCount++;
//		}
//	}
//	// 투영 행렬
//	float proj[4][4] = {};
//	float* pPtr = ProjectionMatrix(width, height, 90, 2, 15);
//	int prjCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			proj[i][j] = *(pPtr + prjCount);
//			prjCount++;
//		}
//	}
//
//#pragma endregion
//	BOOL oneFigureChecked = FALSE;
//	// az[4][1]의 좌표는 월드 좌표계의 한 점 -> 각 꼭짓점과 연결해서 각 면의 변들과 외적 -> 외적 방향을 정규화해서 모두 같으면 내부
//	for (auto& figure : v_cubeFigure)
//	{
//		figure.isClicked = FALSE;
//		if (oneFigureChecked) continue;
//
//		MyVertex cub[8] = {};
//		float vertexSample[4][1] = {};
//		int viewCount = 0;
//		float* viewPtr;
//		// 투영 좌표를 기준으로 해보자.
//		for (int i = 0; i < 8; i++)
//		{
//			vertexSample[0][0] = figure.cube_justForClick[i].x;
//			vertexSample[1][0] = figure.cube_justForClick[i].y;
//			vertexSample[2][0] = figure.cube_justForClick[i].z;
//			vertexSample[3][0] = 1;
//			viewPtr = MatrixMulti(view, vertexSample);
//			viewCount = 0;
//			for (int i = 0; i < 4; i++)
//			{
//				vertexSample[i][0] = *(viewPtr + viewCount);
//				viewCount++;
//			}
//			cub[i].x = vertexSample[0][0];
//			cub[i].y = vertexSample[1][0];
//			cub[i].z = vertexSample[2][0];
//		} // 뷰 좌표로 변환시킴
//
//		  //int pCount = 0;
//		  //float* pPtr;
//		if (projNum == 0)
//		{
//			for (int i = 0; i < 8; i++)
//			{
//				vertexSample[0][0] = cub[i].x;
//				vertexSample[1][0] = cub[i].y;
//				vertexSample[2][0] = cub[i].z;
//				vertexSample[3][0] = 1;
//				viewPtr = MatrixMulti(proj, vertexSample);
//				viewCount = 0;
//				for (int i = 0; i < 4; i++)
//				{
//					vertexSample[i][0] = *(viewPtr + viewCount);
//					viewCount++;
//				}
//				cub[i].z = vertexSample[2][0] / vertexSample[2][0];
//				cub[i].x = vertexSample[0][0] / vertexSample[2][0];
//				cub[i].y = vertexSample[1][0] / vertexSample[2][0];
//			} // 투영 좌표로 변환시킴
//		}
//		else
//		{
//			for (int i = 0; i < 8; i++)
//			{
//				cub[i].x /= (width / height) * 100;
//				cub[i].y /= 100;
//			}
//		}
//
//
//
//		MyVertex p1 = {};
//		MyVertex p2 = {};
//		MyVertex p3 = {};
//		MyVertex planeVector[12][3] = {};
//		MyVertex originVector[12][3] = {};
//
//		/////
//#pragma region 각 메쉬에 대한 좌표와 벡터들
//		p1.x = cub[0].x; p1.y = cub[0].y; p1.z = cub[0].z;
//		p2.x = cub[3].x; p2.y = cub[3].y; p2.z = cub[3].z;
//		p3.x = cub[4].x; p3.y = cub[4].y; p3.z = cub[4].z;
//
//		planeVector[0][0].x = -p1.x + p2.x; planeVector[0][0].y = -p1.y + p2.y; planeVector[0][0].z = -p1.z + p2.z;
//		planeVector[0][1].x = -p2.x + p3.x; planeVector[0][1].y = -p2.y + p3.y; planeVector[0][1].z = -p2.z + p3.z;
//		planeVector[0][2].x = -p3.x + p1.x; planeVector[0][2].y = -p3.y + p1.y; planeVector[0][2].z = -p3.z + p1.z;
//
//		originVector[0][0] = p1; originVector[0][1] = p2; originVector[0][2] = p3;
//		/////
//		p1.x = cub[0].x; p1.y = cub[0].y; p1.z = cub[0].z;
//		p2.x = cub[4].x; p2.y = cub[4].y; p2.z = cub[4].z;
//		p3.x = cub[1].x; p3.y = cub[1].y; p3.z = cub[1].z;
//
//		planeVector[1][0].x = -p1.x + p2.x; planeVector[1][0].y = -p1.y + p2.y; planeVector[1][0].z = -p1.z + p2.z;
//		planeVector[1][1].x = -p2.x + p3.x; planeVector[1][1].y = -p2.y + p3.y; planeVector[1][1].z = -p2.z + p3.z;
//		planeVector[1][2].x = -p3.x + p1.x; planeVector[1][2].y = -p3.y + p1.y; planeVector[1][2].z = -p3.z + p1.z;
//
//		originVector[1][0] = p1; originVector[1][1] = p2; originVector[1][2] = p3;
//		/////
//		p1.x = cub[0].x; p1.y = cub[0].y; p1.z = cub[0].z;
//		p2.x = cub[1].x; p2.y = cub[1].y; p2.z = cub[1].z;
//		p3.x = cub[3].x; p3.y = cub[3].y; p3.z = cub[3].z;
//
//		planeVector[2][0].x = -p1.x + p2.x; planeVector[2][0].y = -p1.y + p2.y; planeVector[2][0].z = -p1.z + p2.z;
//		planeVector[2][1].x = -p2.x + p3.x; planeVector[2][1].y = -p2.y + p3.y; planeVector[2][1].z = -p2.z + p3.z;
//		planeVector[2][2].x = -p3.x + p1.x; planeVector[2][2].y = -p3.y + p1.y; planeVector[2][2].z = -p3.z + p1.z;
//
//		originVector[2][0] = p1; originVector[2][1] = p2; originVector[2][2] = p3;
//		/////
//		p1.x = cub[7].x; p1.y = cub[7].y; p1.z = cub[7].z;
//		p2.x = cub[4].x; p2.y = cub[4].y; p2.z = cub[4].z;
//		p3.x = cub[3].x; p3.y = cub[3].y; p3.z = cub[3].z;
//
//		planeVector[3][0].x = -p1.x + p2.x; planeVector[3][0].y = -p1.y + p2.y; planeVector[3][0].z = -p1.z + p2.z;
//		planeVector[3][1].x = -p2.x + p3.x; planeVector[3][1].y = -p2.y + p3.y; planeVector[3][1].z = -p2.z + p3.z;
//		planeVector[3][2].x = -p3.x + p1.x; planeVector[3][2].y = -p3.y + p1.y; planeVector[3][2].z = -p3.z + p1.z;
//
//		originVector[3][0] = p1; originVector[3][1] = p2; originVector[3][2] = p3;
//		/////
//		p1.x = cub[7].x; p1.y = cub[7].y; p1.z = cub[7].z;
//		p2.x = cub[6].x; p2.y = cub[6].y; p2.z = cub[6].z;
//		p3.x = cub[4].x; p3.y = cub[4].y; p3.z = cub[4].z;
//
//		planeVector[4][0].x = -p1.x + p2.x; planeVector[4][0].y = -p1.y + p2.y; planeVector[4][0].z = -p1.z + p2.z;
//		planeVector[4][1].x = -p2.x + p3.x; planeVector[4][1].y = -p2.y + p3.y; planeVector[4][1].z = -p2.z + p3.z;
//		planeVector[4][2].x = -p3.x + p1.x; planeVector[4][2].y = -p3.y + p1.y; planeVector[4][2].z = -p3.z + p1.z;
//
//		originVector[4][0] = p1; originVector[4][1] = p2; originVector[4][2] = p3;
//		/////
//		p1.x = cub[7].x; p1.y = cub[7].y; p1.z = cub[7].z;
//		p2.x = cub[3].x; p2.y = cub[3].y; p2.z = cub[3].z;
//		p3.x = cub[6].x; p3.y = cub[6].y; p3.z = cub[6].z;
//
//		planeVector[5][0].x = -p1.x + p2.x; planeVector[5][0].y = -p1.y + p2.y; planeVector[5][0].z = -p1.z + p2.z;
//		planeVector[5][1].x = -p2.x + p3.x; planeVector[5][1].y = -p2.y + p3.y; planeVector[5][1].z = -p2.z + p3.z;
//		planeVector[5][2].x = -p3.x + p1.x; planeVector[5][2].y = -p3.y + p1.y; planeVector[5][2].z = -p3.z + p1.z;
//
//		originVector[5][0] = p1; originVector[5][1] = p2; originVector[5][2] = p3;
//		/////
//		p1.x = cub[2].x; p1.y = cub[2].y; p1.z = cub[2].z;
//		p2.x = cub[1].x; p2.y = cub[1].y; p2.z = cub[1].z;
//		p3.x = cub[6].x; p3.y = cub[6].y; p3.z = cub[6].z;
//
//		planeVector[6][0].x = -p1.x + p2.x; planeVector[6][0].y = -p1.y + p2.y; planeVector[6][0].z = -p1.z + p2.z;
//		planeVector[6][1].x = -p2.x + p3.x; planeVector[6][1].y = -p2.y + p3.y; planeVector[6][1].z = -p2.z + p3.z;
//		planeVector[6][2].x = -p3.x + p1.x; planeVector[6][2].y = -p3.y + p1.y; planeVector[6][2].z = -p3.z + p1.z;
//
//		originVector[6][0] = p1; originVector[6][1] = p2; originVector[6][2] = p3;
//		/////
//		p1.x = cub[2].x; p1.y = cub[2].y; p1.z = cub[2].z;
//		p2.x = cub[3].x; p2.y = cub[3].y; p2.z = cub[3].z;
//		p3.x = cub[1].x; p3.y = cub[1].y; p3.z = cub[1].z;
//
//		planeVector[7][0].x = -p1.x + p2.x; planeVector[7][0].y = -p1.y + p2.y; planeVector[7][0].z = -p1.z + p2.z;
//		planeVector[7][1].x = -p2.x + p3.x; planeVector[7][1].y = -p2.y + p3.y; planeVector[7][1].z = -p2.z + p3.z;
//		planeVector[7][2].x = -p3.x + p1.x; planeVector[7][2].y = -p3.y + p1.y; planeVector[7][2].z = -p3.z + p1.z;
//
//		originVector[7][0] = p1; originVector[7][1] = p2; originVector[7][2] = p3;
//		/////
//		p1.x = cub[2].x; p1.y = cub[2].y; p1.z = cub[2].z;
//		p2.x = cub[6].x; p2.y = cub[6].y; p2.z = cub[6].z;
//		p3.x = cub[3].x; p3.y = cub[3].y; p3.z = cub[3].z;
//
//		planeVector[8][0].x = -p1.x + p2.x; planeVector[8][0].y = -p1.y + p2.y; planeVector[8][0].z = -p1.z + p2.z;
//		planeVector[8][1].x = -p2.x + p3.x; planeVector[8][1].y = -p2.y + p3.y; planeVector[8][1].z = -p2.z + p3.z;
//		planeVector[8][2].x = -p3.x + p1.x; planeVector[8][2].y = -p3.y + p1.y; planeVector[8][2].z = -p3.z + p1.z;
//
//		originVector[8][0] = p1; originVector[8][1] = p2; originVector[8][2] = p3;
//		/////
//		p1.x = cub[5].x; p1.y = cub[5].y; p1.z = cub[5].z;
//		p2.x = cub[6].x; p2.y = cub[6].y; p2.z = cub[6].z;
//		p3.x = cub[1].x; p3.y = cub[1].y; p3.z = cub[1].z;
//
//		planeVector[9][0].x = -p1.x + p2.x; planeVector[9][0].y = -p1.y + p2.y; planeVector[9][0].z = -p1.z + p2.z;
//		planeVector[9][1].x = -p2.x + p3.x; planeVector[9][1].y = -p2.y + p3.y; planeVector[9][1].z = -p2.z + p3.z;
//		planeVector[9][2].x = -p3.x + p1.x; planeVector[9][2].y = -p3.y + p1.y; planeVector[9][2].z = -p3.z + p1.z;
//
//		originVector[9][0] = p1; originVector[9][1] = p2; originVector[9][2] = p3;
//		/////
//		p1.x = cub[5].x; p1.y = cub[5].y; p1.z = cub[5].z;
//		p2.x = cub[1].x; p2.y = cub[1].y; p2.z = cub[1].z;
//		p3.x = cub[4].x; p3.y = cub[4].y; p3.z = cub[4].z;
//
//		planeVector[10][0].x = -p1.x + p2.x; planeVector[10][0].y = -p1.y + p2.y; planeVector[10][0].z = -p1.z + p2.z;
//		planeVector[10][1].x = -p2.x + p3.x; planeVector[10][1].y = -p2.y + p3.y; planeVector[10][1].z = -p2.z + p3.z;
//		planeVector[10][2].x = -p3.x + p1.x; planeVector[10][2].y = -p3.y + p1.y; planeVector[10][2].z = -p3.z + p1.z;
//
//		originVector[10][0] = p1; originVector[10][1] = p2; originVector[10][2] = p3;
//		/////
//		p1.x = cub[5].x; p1.y = cub[5].y; p1.z = cub[5].z;
//		p2.x = cub[4].x; p2.y = cub[4].y; p2.z = cub[4].z;
//		p3.x = cub[6].x; p3.y = cub[6].y; p3.z = cub[6].z;
//
//		planeVector[11][0].x = -p1.x + p2.x; planeVector[11][0].y = -p1.y + p2.y; planeVector[11][0].z = -p1.z + p2.z;
//		planeVector[11][1].x = -p2.x + p3.x; planeVector[11][1].y = -p2.y + p3.y; planeVector[11][1].z = -p2.z + p3.z;
//		planeVector[11][2].x = -p3.x + p1.x; planeVector[11][2].y = -p3.y + p1.y; planeVector[11][2].z = -p3.z + p1.z;
//
//		originVector[11][0] = p1; originVector[11][1] = p2; originVector[11][2] = p3;
//		/////
//#pragma endregion
//
//		float vertexToVertex1[2][1] = {};
//		float vertexToPoint1[2][1] = {};
//		float resultBeforeNorm1[4][1] = {};
//		float result1[4][1] = {};
//		float* crsPtr;
//		float* normPtr;
//		int count;
//		float finalResult[3][3] = {};
//		for (int i = 0; i < 12; i++)
//		{
//			for (int k = 0; k < 3; k++)
//			{
//				vertexToVertex1[0][0] = planeVector[i][k].x; vertexToVertex1[1][0] = planeVector[i][k].y;
//				vertexToPoint1[0][0] = (-1) * originVector[i][k].x + az10[0][0]; vertexToPoint1[1][0] = (-1) * originVector[i][k].y + az10[1][0];
//
//				crsPtr = CrossProduct2X2(vertexToVertex1, vertexToPoint1);
//				count = 0;
//				for (int j = 0; j < 3; j++)
//				{
//					resultBeforeNorm1[j][0] = *(crsPtr + count);
//					count++;
//				}
//				normPtr = MatrixNormalize(resultBeforeNorm1);
//				count = 0;
//				for (int j = 0; j < 3; j++)
//				{
//					result1[j][0] = *(normPtr + count);
//					count++;
//				}
//				finalResult[k][0] = result1[0][0];  finalResult[k][1] = result1[1][0]; finalResult[k][2] = result1[2][0];
//			}
//
//			if (finalResult[0][0] == finalResult[1][0] && finalResult[0][0] == finalResult[2][0])
//			{
//				if (finalResult[0][1] == finalResult[1][1] && finalResult[0][1] == finalResult[2][1])
//				{
//					if (finalResult[0][2] == finalResult[1][2] && finalResult[0][2] == finalResult[2][2])
//					{
//						figure.isClicked = TRUE;
//						oneFigureChecked = TRUE;
//						break;
//					}
//					else
//					{
//						if (i != 11) continue;
//						else figure.isClicked = FALSE;
//					}
//				}
//				else
//				{
//					if (i != 11) continue;
//					else figure.isClicked = FALSE;
//				}
//			}
//			else
//			{
//				if (i != 11) continue;
//				else figure.isClicked = FALSE;
//			}
//		}
//	}
//
//	for (auto& figure : v_sphereFigure)
//	{
//		figure.isClicked = FALSE;
//		if (oneFigureChecked) continue;
//
//		MyVertex sph[230] = {};
//		float vertexSample[4][1] = {};
//		int viewCount = 0;
//		float* viewPtr;
//		// 뷰 좌표로 변환시킴
//		for (int i = 0; i < 230; i++)
//		{
//			vertexSample[0][0] = figure.sphere_justForClick[i].x;
//			vertexSample[1][0] = figure.sphere_justForClick[i].y;
//			vertexSample[2][0] = figure.sphere_justForClick[i].z;
//			vertexSample[3][0] = 1;
//			viewPtr = MatrixMulti(view, vertexSample);
//			viewCount = 0;
//			for (int i = 0; i < 4; i++)
//			{
//				vertexSample[i][0] = *(viewPtr + viewCount);
//				viewCount++;
//			}
//			sph[i].x = vertexSample[0][0];
//			sph[i].y = vertexSample[1][0];
//			sph[i].z = vertexSample[2][0];
//		}
//
//		//int pCount = 0;
//		//float* pPtr;
//		// 투영 좌표로 변환시킴
//		if (projNum == 0)
//		{
//			for (int i = 0; i < 230; i++)
//			{
//				vertexSample[0][0] = sph[i].x;
//				vertexSample[1][0] = sph[i].y;
//				vertexSample[2][0] = sph[i].z;
//				vertexSample[3][0] = 1;
//				viewPtr = MatrixMulti(proj, vertexSample);
//				viewCount = 0;
//				for (int i = 0; i < 4; i++)
//				{
//					vertexSample[i][0] = *(viewPtr + viewCount);
//					viewCount++;
//				}
//				sph[i].z = vertexSample[2][0] / vertexSample[2][0];
//				sph[i].x = vertexSample[0][0] / vertexSample[2][0];
//				sph[i].y = vertexSample[1][0] / vertexSample[2][0];
//			}
//		}
//		else
//		{
//			for (int i = 0; i < 230; i++)
//			{
//				sph[i].x /= (width / height) * 100;
//				sph[i].y /= 100;
//			}
//		}
//
//
//		MyVertex p1 = {};
//		MyVertex p2 = {};
//		MyVertex p3 = {};
//		MyVertex p4 = {};
//		MyVertex planeVector3[24][3] = {};
//		MyVertex planeVector4[216][4] = {};
//		MyVertex originVector3[24][3] = {};
//		MyVertex originVector4[216][4] = {};
//
//#pragma region 정점과 벡터들 확인
//		// 끝점으로 만들어지는 삼각형 면
//		for (int i = 1; i < 13; i++)
//		{
//			if ((i % 12) == 0)
//			{
//				p1.x = sph[0].x; p1.y = sph[0].y;
//				p2.x = sph[i].x; p2.y = sph[i].y;
//				p3.x = sph[i - 11].x; p3.y = sph[i - 11].y;
//			}
//			else
//			{
//				p1.x = sph[0].x; p1.y = sph[0].y;
//				p2.x = sph[i].x; p2.y = sph[i].y;
//				p3.x = sph[i + 1].x; p3.y = sph[i + 1].y;
//			}
//			planeVector3[i][0].x = -p1.x + p2.x; planeVector3[i][0].y = -p1.y + p2.y; planeVector3[i][0].z = -p1.z + p2.z;
//			planeVector3[i][1].x = -p2.x + p3.x; planeVector3[i][1].y = -p2.y + p3.y; planeVector3[i][1].z = -p2.z + p3.z;
//			planeVector3[i][2].x = -p3.x + p1.x; planeVector3[i][2].y = -p3.y + p1.y; planeVector3[i][2].z = -p3.z + p1.z;
//			originVector3[i][0] = p1; originVector3[i][1] = p2; originVector3[i][2] = p3;
//		}
//		for (int i = 217; i < 229; i++)
//		{
//			if ((i % 12) == 0)
//			{
//				p1.x = sph[229].x; p1.y = sph[229].y;
//				p2.x = sph[i - 11].x; p2.y = sph[i - 11].y;
//				p3.x = sph[i].x; p3.y = sph[i].y;
//			}
//			else
//			{
//				p1.x = sph[229].x; p1.y = sph[229].y;
//				p2.x = sph[i + 1].x; p2.y = sph[i + 1].y;
//				p3.x = sph[i].x; p3.y = sph[i].y;
//			}
//			planeVector3[i - 205][0].x = -p1.x + p2.x; planeVector3[i - 205][0].y = -p1.y + p2.y; planeVector3[i - 205][0].z = -p1.z + p2.z;
//			planeVector3[i - 205][1].x = -p2.x + p3.x; planeVector3[i - 205][1].y = -p2.y + p3.y; planeVector3[i - 205][1].z = -p2.z + p3.z;
//			planeVector3[i - 205][2].x = -p3.x + p1.x; planeVector3[i - 205][2].y = -p3.y + p1.y; planeVector3[i - 205][2].z = -p3.z + p1.z;
//			originVector3[i - 205][0] = p1; originVector3[i - 205][1] = p2; originVector3[i - 205][2] = p3;
//		}
//		// 사각형 면들
//		for (int i = 1; i < 217; i++)
//		{
//			if (i % 12 == 0)
//			{
//				p1.x = sph[i].x; p1.y = sph[i].y;
//				p2.x = sph[i + 12].x; p2.y = sph[i + 12].y;
//				p3.x = sph[i + 1].x; p3.y = sph[i + 1].y;
//				p4.x = sph[i - 11].x; p4.y = sph[i - 11].y;
//			}
//			else
//			{
//				p1.x = sph[i].x; p1.y = sph[i].y;
//				p2.x = sph[i + 12].x; p2.y = sph[i + 12].y;
//				p3.x = sph[i + 13].x; p3.y = sph[i + 13].y;
//				p4.x = sph[i + 1].x; p4.y = sph[i + 1].y;
//			}
//			planeVector4[i - 1][0].x = -p1.x + p2.x; planeVector4[i - 1][0].y = -p1.y + p2.y; planeVector4[i - 1][0].z = -p1.z + p2.z;
//			planeVector4[i - 1][1].x = -p2.x + p3.x; planeVector4[i - 1][1].y = -p2.y + p3.y; planeVector4[i - 1][1].z = -p2.z + p3.z;
//			planeVector4[i - 1][2].x = -p3.x + p4.x; planeVector4[i - 1][2].y = -p3.y + p4.y; planeVector4[i - 1][2].z = -p3.z + p4.z;
//			planeVector4[i - 1][3].x = -p4.x + p1.x; planeVector4[i - 1][3].y = -p4.y + p1.y; planeVector4[i - 1][3].z = -p4.z + p1.z;
//			originVector4[i - 1][0] = p1; originVector4[i - 1][1] = p2; originVector4[i - 1][2] = p3; originVector4[i - 1][3] = p4;
//		}
//#pragma endregion
//
//		float vertexToVertex1[2][1] = {};
//		float vertexToPoint1[2][1] = {};
//		float resultBeforeNorm1[4][1] = {};
//		float result1[4][1] = {};
//		float* crsPtr;
//		float* normPtr;
//		int count;
//		float finalResultTri[3][3] = {};
//		float finalResultRec[4][3] = {};
//
//		for (int i = 0; i < 24; i++)
//		{
//			for (int k = 0; k < 3; k++)
//			{
//				vertexToVertex1[0][0] = planeVector3[i][k].x; vertexToVertex1[1][0] = planeVector3[i][k].y;
//				vertexToPoint1[0][0] = -originVector3[i][k].x + az10[0][0]; vertexToPoint1[1][0] = -originVector3[i][k].y + az10[1][0];
//
//				crsPtr = CrossProduct2X2(vertexToPoint1, vertexToPoint1);
//				count = 0;
//				for (int j = 0; j < 3; j++)
//				{
//					resultBeforeNorm1[j][0] = *(crsPtr + count);
//					count++;
//				}
//				normPtr = MatrixNormalize(resultBeforeNorm1);
//				count = 0;
//				for (int j = 0; j < 4; j++)
//				{
//					result1[j][0] = *(normPtr + count);
//					count++;
//				}
//				finalResultTri[k][0] = result1[0][0]; finalResultTri[k][1] = result1[1][0]; finalResultTri[k][2] = result1[2][0];
//			}
//			if (finalResultTri[0][0] == finalResultTri[1][0] && finalResultTri[0][0] == finalResultTri[2][0])
//			{
//				if (finalResultTri[0][1] == finalResultTri[1][1] && finalResultTri[0][1] == finalResultTri[2][1])
//				{
//					if (finalResultTri[0][2] == finalResultTri[1][2] && finalResultTri[0][2] == finalResultTri[2][2])
//					{
//						figure.isClicked = TRUE;
//						oneFigureChecked = TRUE;
//						break;
//					}
//					else
//					{
//						if (i != 23) continue;
//						else figure.isClicked = FALSE;
//					}
//				}
//				else
//				{
//					if (i != 23) continue;
//					else figure.isClicked = FALSE;
//				}
//			}
//			else
//			{
//				if (i != 23) continue;
//				else figure.isClicked = FALSE;
//			}
//		}
//		for (int i = 0; i < 216; i++)
//		{
//			for (int k = 0; k < 4; k++)
//			{
//				vertexToVertex1[0][0] = planeVector4[i][k].x; vertexToVertex1[1][0] = planeVector4[i][k].y;
//				vertexToPoint1[0][0] = -originVector4[i][k].x + az10[0][0]; vertexToPoint1[1][0] = -originVector4[i][k].y + az10[1][0];
//
//				crsPtr = CrossProduct2X2(vertexToVertex1, vertexToPoint1);
//				count = 0;
//				for (int j = 0; j < 3; j++)
//				{
//					resultBeforeNorm1[j][0] = *(crsPtr + count);
//					count++;
//				}
//				normPtr = MatrixNormalize(resultBeforeNorm1);
//				count = 0;
//				for (int j = 0; j < 4; j++)
//				{
//					result1[j][0] = *(normPtr + count);
//					count++;
//				}
//				finalResultRec[k][0] = result1[0][0]; finalResultRec[k][1] = result1[1][0]; finalResultRec[k][2] = result1[2][0];
//			}
//			if (finalResultRec[0][0] == finalResultRec[1][0] && finalResultRec[1][0] == finalResultRec[2][0] && finalResultRec[2][0] == finalResultRec[3][0])
//			{
//				if (finalResultRec[0][1] == finalResultRec[1][1] && finalResultRec[1][1] == finalResultRec[2][1] && finalResultRec[2][1] == finalResultRec[3][1])
//				{
//					if (finalResultRec[0][2] == finalResultRec[1][2] && finalResultRec[1][2] == finalResultRec[2][2] && finalResultRec[2][2] == finalResultRec[3][2])
//					{
//						figure.isClicked = TRUE;
//						oneFigureChecked = TRUE;
//						break;
//					}
//					else
//					{
//						if (i != 215) continue;
//						else figure.isClicked = FALSE;
//					}
//				}
//				else
//				{
//					if (i != 215) continue;
//					else figure.isClicked = FALSE;
//				}
//			}
//			else
//			{
//				if (i != 215) continue;
//				else figure.isClicked = FALSE;
//			}
//		}
//	}
//
//	for (auto& figure : v_torusFigure)
//	{
//		figure.isClicked = FALSE;
//		if (oneFigureChecked) continue;
//
//		MyVertex tor[144] = {};
//		float vertexSample[4][1] = {};
//		int viewCount = 0;
//		float* viewPtr;
//		// 투영 좌표를 기준으로 해보자.
//		for (int i = 0; i < 144; i++)
//		{
//			vertexSample[0][0] = figure.torus_justForClick[i].x;
//			vertexSample[1][0] = figure.torus_justForClick[i].y;
//			vertexSample[2][0] = figure.torus_justForClick[i].z;
//			vertexSample[3][0] = 1;
//			viewPtr = MatrixMulti(view, vertexSample);
//			viewCount = 0;
//			for (int i = 0; i < 4; i++)
//			{
//				vertexSample[i][0] = *(viewPtr + viewCount);
//				viewCount++;
//			}
//			tor[i].x = vertexSample[0][0];
//			tor[i].y = vertexSample[1][0];
//			tor[i].z = vertexSample[2][0];
//		} // 뷰 좌표로 변환시킴
//
//		  //int pCount = 0;
//		  //float* pPtr;
//		if (projNum == 0)
//		{
//			for (int i = 0; i < 144; i++)
//			{
//				vertexSample[0][0] = tor[i].x;
//				vertexSample[1][0] = tor[i].y;
//				vertexSample[2][0] = tor[i].z;
//				vertexSample[3][0] = 1;
//				viewPtr = MatrixMulti(proj, vertexSample);
//				viewCount = 0;
//				for (int i = 0; i < 4; i++)
//				{
//					vertexSample[i][0] = *(viewPtr + viewCount);
//					viewCount++;
//				}
//				tor[i].z = vertexSample[2][0] / vertexSample[2][0];
//				tor[i].x = vertexSample[0][0] / vertexSample[2][0];
//				tor[i].y = vertexSample[1][0] / vertexSample[2][0];
//			} // 투영 좌표로 변환시킴
//		}
//		else
//		{
//			for (int i = 0; i < 144; i++)
//			{
//				tor[i].x /= (width / height) * 100;
//				tor[i].y /= 100;
//			}
//		}
//
//		MyVertex p1 = {};
//		MyVertex p2 = {};
//		MyVertex p3 = {};
//		MyVertex p4 = {};
//		MyVertex planeVector[144][4] = {};
//		MyVertex originVector[144][4] = {};
//
//#pragma region 정점들과 벡터
//		for (int i = 0; i < 144; i++)
//		{
//			if ((i + 1) % 12 == 0)
//			{
//				if (i >= 132) // i == 143
//				{
//					p1.x = tor[i].x; p1.y = tor[i].y; p1.z = tor[i].z;
//					p2.x = tor[i - 132].x; p2.y = tor[i - 132].y; p2.z = tor[i - 132].z;
//					p3.x = tor[i - 143].x; p3.y = tor[i - 143].y; p3.z = tor[i - 143].z;
//					p4.x = tor[i - 11].x; p4.y = tor[i - 11].y; p4.z = tor[i - 11].z;
//				}
//				else
//				{
//					p1.x = tor[i].x; p1.y = tor[i].y; p1.z = tor[i].z;
//					p2.x = tor[i + 12].x; p2.y = tor[i + 12].y; p2.z = tor[i + 12].z;
//					p3.x = tor[i + 1].x; p3.y = tor[i + 1].y; p3.z = tor[i + 1].z;
//					p4.x = tor[i - 11].x; p4.y = tor[i - 11].y; p4.z = tor[i - 11].z;
//				}
//			}
//			else
//			{
//				if (i >= 132)
//				{
//					p1.x = tor[i].x; p1.y = tor[i].y; p1.z = tor[i].z;
//					p2.x = tor[i - 132].x; p2.y = tor[i - 132].y; p2.z = tor[i - 132].z;
//					p3.x = tor[i - 131].x; p3.y = tor[i - 131].y; p3.z = tor[i - 131].z;
//					p4.x = tor[i + 1].x; p4.y = tor[i + 1].y; p4.z = tor[i + 1].z;
//				}
//				else
//				{
//					p1.x = tor[i].x; p1.y = tor[i].y; p1.z = tor[i].z;
//					p2.x = tor[i + 12].x; p2.y = tor[i + 12].y; p2.z = tor[i + 12].z;
//					p3.x = tor[i + 13].x; p3.y = tor[i + 13].y; p3.z = tor[i + 13].z;
//					p4.x = tor[i + 1].x; p4.y = tor[i + 1].y; p4.z = tor[i + 1].z;
//				}
//
//			}
//			planeVector[i][0].x = -p1.x + p2.x; planeVector[i][0].y = -p1.y + p2.y; planeVector[i][0].z = -p1.z + p2.z;
//			planeVector[i][1].x = -p2.x + p3.x; planeVector[i][1].y = -p2.y + p3.y; planeVector[i][1].z = -p2.z + p3.z;
//			planeVector[i][2].x = -p3.x + p4.x; planeVector[i][2].y = -p3.y + p4.y; planeVector[i][2].z = -p3.z + p4.z;
//			planeVector[i][3].x = -p4.x + p1.x; planeVector[i][3].y = -p4.y + p1.y; planeVector[i][3].z = -p4.z + p1.z;
//			originVector[i][0] = p1; originVector[i][1] = p2; originVector[i][2] = p3; originVector[i][3] = p4;
//		}
//#pragma endregion
//
//		float vertexToVertex[2][1] = {};
//		float vertexToPoint[2][1] = {};
//		float resultBeforeNorm[4][1] = {};
//		float result[4][1] = {};
//		float* crsPtr;
//		float* normPtr;
//		int count;
//		float finalResultRec[4][3] = {};
//		for (int i = 0; i < 144; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				vertexToVertex[0][0] = planeVector[i][j].x; vertexToVertex[1][0] = planeVector[i][j].y;
//				vertexToPoint[0][0] = -originVector[i][j].x + az10[0][0]; vertexToPoint[1][0] = -originVector[i][j].y + az10[1][0];
//				crsPtr = CrossProduct2X2(vertexToVertex, vertexToPoint);
//				count = 0;
//				for (int k = 0; k < 4; k++)
//				{
//					resultBeforeNorm[k][0] = *(crsPtr + count);
//					count++;
//				}
//				normPtr = MatrixNormalize(resultBeforeNorm);
//				count = 0;
//				for (int k = 0; k < 4; k++)
//				{
//					result[k][0] = *(normPtr + count);
//					count++;
//				}
//				finalResultRec[j][0] = result[0][0]; finalResultRec[j][1] = result[1][0]; finalResultRec[j][2] = result[2][0];
//			}
//			if (finalResultRec[0][0] == finalResultRec[1][0] && finalResultRec[1][0] == finalResultRec[2][0] && finalResultRec[2][0] == finalResultRec[3][0])
//			{
//				if (finalResultRec[0][1] == finalResultRec[1][1] && finalResultRec[1][1] == finalResultRec[2][1] && finalResultRec[2][1] == finalResultRec[3][1])
//				{
//					if (finalResultRec[0][2] == finalResultRec[1][2] && finalResultRec[1][2] == finalResultRec[2][2] && finalResultRec[2][2] == finalResultRec[3][2])
//					{
//						figure.isClicked = TRUE;
//						oneFigureChecked = TRUE;
//						break;
//					}
//					else
//					{
//						if (i != 143)continue;
//						else figure.isClicked = FALSE;
//					}
//				}
//				else
//				{
//					if (i != 143)continue;
//					else figure.isClicked = FALSE;
//				}
//			}
//			else
//			{
//				if (i != 143)continue;
//				else figure.isClicked = FALSE;
//			}
//		}
//	}
//
//	Invalidate();
//
//	CView::OnRButtonUp(nFlags, point);
//}
//
//BOOL CMFCApplication3View::PreTranslateMessage(MSG* pMsg)
//{
//	if (pMsg->message == WM_KEYDOWN)
//	{
//		float camAxisX[3][1] = {};
//		float camAxisY[3][1] = {};
//		float camAxisZ[3][1] = {};
//		float* camPtr = MakeNewCoordinate(look);
//		int camCount = 0;
//		for (int i = 0; i < 3; i++)
//		{
//			camAxisX[i][0] = *(camPtr + camCount);
//			camCount++;
//		}
//		for (int i = 0; i < 3; i++)
//		{
//			camAxisY[i][0] = *(camPtr + camCount);
//			camCount++;
//		}
//		for (int i = 0; i < 3; i++)
//		{
//			camAxisZ[i][0] = *(camPtr + camCount);
//			camCount++;
//		}
//		if (pMsg->wParam == VK_RIGHT)
//		{
//			cameraX -= camAxisX[0][0] * 5;
//			cameraY -= camAxisX[1][0] * 5;
//			cameraZ -= camAxisX[2][0] * 5;
//		}
//		if (pMsg->wParam == VK_LEFT)
//		{
//			cameraX += camAxisX[0][0] * 5;
//			cameraY += camAxisX[1][0] * 5;
//			cameraZ += camAxisX[2][0] * 5;
//		}
//		if (pMsg->wParam == VK_UP)
//		{
//			cameraX += camAxisY[0][0] * 5;
//			cameraY += camAxisY[1][0] * 5;
//			cameraZ += camAxisY[2][0] * 5;
//		}
//		if (pMsg->wParam == VK_DOWN)
//		{
//			cameraX -= camAxisY[0][0] * 5;
//			cameraY -= camAxisY[1][0] * 5;
//			cameraZ -= camAxisY[2][0] * 5;
//		}
//		// 카메라 아래로 이동시 경계면에 있는 물체가 조금 이상하게 찍힘
//		float sampleVectorZ[4][1] = {};
//		float sampleVectorY[4][1] = {};
//		float sampleVectorX[4][1] = {};
//		float* newAxisPtr;
//		if (pMsg->wParam == 'W')
//		{
//			if (rotateXCount < 120)
//			{
//				newAxisPtr = vectorRotation(camAxisZ, camAxisX, -15);
//				camCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					camAxisZ[i][0] = *(newAxisPtr + camCount);
//					camCount++;
//				}
//				for (int i = 0; i < 3; i++)
//				{
//					sampleVectorX[i][0] = camAxisX[i][0];
//					sampleVectorZ[i][0] = camAxisZ[i][0];
//				}
//				sampleVectorX[3][0] = 1; sampleVectorZ[3][0] = 1;
//
//				newAxisPtr = CrossProduct(sampleVectorZ, sampleVectorX);
//				camCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					camAxisY[i][0] = *(newAxisPtr + camCount);
//					camCount++;
//				}
//				lookX = camAxisZ[0][0]; lookY = camAxisZ[1][0]; lookZ = camAxisZ[2][0];
//				rotateXCount++;
//			}
//		}
//		if (pMsg->wParam == 'S')
//		{
//			if (rotateXCount > -120)
//			{
//				newAxisPtr = vectorRotation(camAxisZ, camAxisX, 15);
//				camCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					camAxisZ[i][0] = *(newAxisPtr + camCount);
//					camCount++;
//				}
//				lookX = camAxisZ[0][0]; lookY = camAxisZ[1][0]; lookZ = camAxisZ[2][0];
//				rotateXCount--;
//			}
//		}
//		if (pMsg->wParam == 'A')
//		{
//			if (rotateYCount < 120)
//			{
//				////// 카메라 방향 회전
//				newAxisPtr = vectorRotation(camAxisZ, camAxisY, 15);
//				camCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					camAxisZ[i][0] = *(newAxisPtr + camCount);
//					camCount++;
//				}
//				lookX = camAxisZ[0][0]; lookY = camAxisZ[1][0]; lookZ = camAxisZ[2][0];
//				rotateYCount++;
//			}
//		}
//		if (pMsg->wParam == 'D')
//		{
//			if (rotateYCount > -120)
//			{
//				////// 카메라 방향 회전
//				newAxisPtr = vectorRotation(camAxisZ, camAxisY, -15);
//				camCount = 0;
//				for (int i = 0; i < 3; i++)
//				{
//					camAxisZ[i][0] = *(newAxisPtr + camCount);
//					camCount++;
//				}
//				lookX = camAxisZ[0][0]; lookY = camAxisZ[1][0]; lookZ = camAxisZ[2][0];
//				rotateYCount--;
//				//////
//			}
//		}
//		// 선택된 물체 크기 변화
//		if (pMsg->wParam == 'P')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.length += 5;
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.radius += 4;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.torusLongRadius += 8;
//				figure.torusRadius += 4;
//				break;
//			}
//		}
//		if (pMsg->wParam == 'M')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.length -= 5;
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.radius -= 4;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.torusLongRadius -= 8;
//				figure.torusRadius -= 1;
//				break;
//			}
//		}
//		// 선택된 물체 이동
//		if (pMsg->wParam == 'T')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				////////////////////
//				figure.moveX += camAxisY[0][0] * 5;
//				figure.moveY += camAxisY[1][0] * 5;
//				figure.moveZ += camAxisY[2][0] * 5;
//				////////////////////
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX += camAxisY[0][0] * 5;
//				figure.moveY += camAxisY[1][0] * 5;
//				figure.moveZ += camAxisY[2][0] * 5;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX += camAxisY[0][0] * 5;
//				figure.moveY += camAxisY[1][0] * 5;
//				figure.moveZ += camAxisY[2][0] * 5;
//				break;
//			}
//		}
//		if (pMsg->wParam == 'G')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX -= camAxisY[0][0] * 5;
//				figure.moveY -= camAxisY[1][0] * 5;
//				figure.moveZ -= camAxisY[2][0] * 5;
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX -= camAxisY[0][0] * 5;
//				figure.moveY -= camAxisY[1][0] * 5;
//				figure.moveZ -= camAxisY[2][0] * 5;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX -= camAxisY[0][0] * 5;
//				figure.moveY -= camAxisY[1][0] * 5;
//				figure.moveZ -= camAxisY[2][0] * 5;
//				break;
//			}
//		}
//		if (pMsg->wParam == 'F')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX += camAxisX[0][0] * 5;
//				figure.moveY += camAxisX[1][0] * 5;
//				figure.moveZ += camAxisX[2][0] * 5;
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX += camAxisX[0][0] * 5;
//				figure.moveY += camAxisX[1][0] * 5;
//				figure.moveZ += camAxisX[2][0] * 5;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX += camAxisX[0][0] * 5;
//				figure.moveY += camAxisX[1][0] * 5;
//				figure.moveZ += camAxisX[2][0] * 5;
//				break;
//			}
//		}
//		if (pMsg->wParam == 'H')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX -= camAxisX[0][0] * 5;
//				figure.moveY -= camAxisX[1][0] * 5;
//				figure.moveZ -= camAxisX[2][0] * 5;
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX -= camAxisX[0][0] * 5;
//				figure.moveY -= camAxisX[1][0] * 5;
//				figure.moveZ -= camAxisX[2][0] * 5;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.moveX -= camAxisX[0][0] * 5;
//				figure.moveY -= camAxisX[1][0] * 5;
//				figure.moveZ -= camAxisX[2][0] * 5;
//				break;
//			}
//		}
//		// 선택된 물체 회전
//		if (pMsg->wParam == 'I')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotX += 15;
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotX += 15;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotX += 15;
//				break;
//			}
//		}
//		if (pMsg->wParam == 'K')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotX -= 15;
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotX -= 15;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotX -= 15;
//				break;
//			}
//		}
//		if (pMsg->wParam == 'J')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotY -= 15;
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotY -= 15;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotY -= 15;
//				break;
//			}
//		}
//		if (pMsg->wParam == 'L')
//		{
//			BOOL isChecked = FALSE;
//			for (auto& figure : v_cubeFigure)
//			{
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotY += 15;
//				break;
//			}
//			for (auto& figure : v_sphereFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotY += 15;
//				break;
//			}
//			for (auto& figure : v_torusFigure)
//			{
//				if (isChecked) break;
//				if (!figure.isClicked) continue;
//				isChecked = TRUE;
//				figure.rotY += 15;
//				break;
//			}
//		}
//		Invalidate();
//	}
//
//	return CView::PreTranslateMessage(pMsg);
//}
