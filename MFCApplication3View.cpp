
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


// 만든 파일들
#include "Matrix.h"
//////////////

extern int figureNum;

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
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_HOTKEY()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication3View 생성/소멸

CMFCApplication3View::CMFCApplication3View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	v_Figure = {};
	RegisterHotKey(m_hWnd, 15000, 0, VK_RIGHT);
	RegisterHotKey(m_hWnd, 15001, 0, VK_LEFT);
	cameraX = -40;
	cameraY = 40;
	cameraZ = 0;
	moveDirX.x = 0;
	moveDirX.y = 0;
	width = 0;
	left = 0;
	top = 0;
	height = 0;
	camera[0][0] = cameraX;
	camera[1][0] = cameraY;
	camera[2][0] = cameraZ;
}

CMFCApplication3View::~CMFCApplication3View()
{
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
	// 그리기 준비
	CPaintDC cdc(this);
	CRect rect;
	GetClientRect(&rect);
	width = rect.Width();
	height = rect.Height();
	left = rect.left;
	top = rect.top;

	CPoint cp = (10, 10);

	CDC memDC;
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
	newPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* oldPen = memDC.SelectObject(&newPen);

	CBrush newBrush(RGB(0, 0, 255));
	CBrush* oldBrush = memDC.SelectObject(&newBrush);

	for (auto figure : v_Figure)
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
		// 배열에서 받아온 포인터로 vertex 가져오기
		int count = 0;
		MyVertex tor[144] = {};
		MyVertex torCopy[144] = {};
		for (int i = 0; i < 144; i++)			{
			tor[i] = figure.torus[i];
			torCopy[i] = figure.torusCopy[i];
			count++;
		}

		#pragma region 첫번째 삼각 폴리곤 
		for (int i = 0; i < 144; i++)
		{
			if ((i + 1) % 12 == 0)
			{
				if (i >= 132)
				{
					dotFst[0][0] = -torCopy[i].x + torCopy[i - 132].x;
					dotSec[0][0] = -torCopy[i].x + torCopy[i - 11].x;
					dotFst[1][0] = -torCopy[i].y + torCopy[i - 132].y;
					dotSec[1][0] = -torCopy[i].y + torCopy[i - 11].y;
					dotFst[2][0] = -torCopy[i].z + torCopy[i - 132].z;
					dotSec[2][0] = -torCopy[i].z + torCopy[i - 11].z;
					cameraToPolygon1[0][0] = torCopy[i].x;
					cameraToPolygon1[1][0] = torCopy[i].y;
					cameraToPolygon1[2][0] = torCopy[i].z;
					cameraToPolygon2[0][0] = torCopy[i - 132].x;
					cameraToPolygon2[1][0] = torCopy[i - 132].y;
					cameraToPolygon2[2][0] = torCopy[i - 132].z;
					cameraToPolygon3[0][0] = torCopy[i - 11].x;
					cameraToPolygon3[1][0] = torCopy[i - 11].y;
					cameraToPolygon3[2][0] = torCopy[i - 11].z;
				}
				else
				{
					dotFst[0][0] = -torCopy[i].x + torCopy[i + 12].x;
					dotSec[0][0] = -torCopy[i].x + torCopy[i - 11].x;
					dotFst[1][0] = -torCopy[i].y + torCopy[i + 12].y;
					dotSec[1][0] = -torCopy[i].y + torCopy[i - 11].y;
					dotFst[2][0] = -torCopy[i].z + torCopy[i + 12].z;
					dotSec[2][0] = -torCopy[i].z + torCopy[i - 11].z;
					cameraToPolygon1[0][0] = torCopy[i].x;
					cameraToPolygon1[1][0] = torCopy[i].y;
					cameraToPolygon1[2][0] = torCopy[i].z;
					cameraToPolygon2[0][0] = torCopy[i + 12].x;
					cameraToPolygon2[1][0] = torCopy[i + 12].y;
					cameraToPolygon2[2][0] = torCopy[i + 12].z;
					cameraToPolygon3[0][0] = torCopy[i - 11].x;
					cameraToPolygon3[1][0] = torCopy[i - 11].y;
					cameraToPolygon3[2][0] = torCopy[i - 11].z;
				}
			}
			else
			{
				if (i >= 132)
				{
					dotFst[0][0] = -torCopy[i].x + torCopy[i - 132].x;
					dotSec[0][0] = -torCopy[i].x + torCopy[i + 1].x;
					dotFst[1][0] = -torCopy[i].y + torCopy[i - 132].y;
					dotSec[1][0] = -torCopy[i].y + torCopy[i + 1].y;
					dotFst[2][0] = -torCopy[i].z + torCopy[i - 132].z;
					dotSec[2][0] = -torCopy[i].z + torCopy[i + 1].z;
					cameraToPolygon1[0][0] = torCopy[i].x;
					cameraToPolygon1[1][0] = torCopy[i].y;
					cameraToPolygon1[2][0] = torCopy[i].z;
					cameraToPolygon2[0][0] = torCopy[i - 132].x;
					cameraToPolygon2[1][0] = torCopy[i - 132].y;
					cameraToPolygon2[2][0] = torCopy[i - 132].z;
					cameraToPolygon3[0][0] = torCopy[i + 1].x;
					cameraToPolygon3[1][0] = torCopy[i + 1].y;
					cameraToPolygon3[2][0] = torCopy[i + 1].z;
				}
				else
				{
					dotFst[0][0] = -torCopy[i].x + torCopy[i + 12].x;
					dotSec[0][0] = -torCopy[i].x + torCopy[i + 1].x;
					dotFst[1][0] = -torCopy[i].y + torCopy[i + 12].y;
					dotSec[1][0] = -torCopy[i].y + torCopy[i + 1].y;
					dotFst[2][0] = -torCopy[i].z + torCopy[i + 12].z;
					dotSec[2][0] = -torCopy[i].z + torCopy[i + 1].z;
					cameraToPolygon1[0][0] = torCopy[i].x;
					cameraToPolygon1[1][0] = torCopy[i].y;
					cameraToPolygon1[2][0] = torCopy[i].z;
					cameraToPolygon2[0][0] = torCopy[i + 12].x;
					cameraToPolygon2[1][0] = torCopy[i + 12].y;
					cameraToPolygon2[2][0] = torCopy[i + 12].z;
					cameraToPolygon3[0][0] = torCopy[i + 1].x;
					cameraToPolygon3[1][0] = torCopy[i + 1].y;
					cameraToPolygon3[2][0] = torCopy[i + 1].z;
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
			for (int j = 0; j < 3; j++)
			{
				vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
				vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
				vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
			}

			float result1 = DotProduct(vPolygon1, crsBoth);
			float result2 = DotProduct(vPolygon2, crsBoth);
			float result3 = DotProduct(vPolygon3, crsBoth);

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
		if (fstResult == 1)
		{
			// 선으로 그리기
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			// 면으로 그리기
			/*memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();*/
		}
		//////
		for (auto i : myInt)
		{
			if (i == 0) continue;
			if ((i + 1) % 12 == 0)
			{
				if (i >= 132)
				{
					// 선으로 그리기
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// 면으로 그리기
					/*memDC.BeginPath();
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.EndPath();
					memDC.StrokeAndFillPath();*/
				}
				else
				{
					// 선으로 그리기
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// 면으로 그리기
					/*memDC.BeginPath();
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.EndPath();
					memDC.StrokeAndFillPath();*/
				}
			}
			else
			{
				if (i >= 132)
				{
					// 선으로 그리기
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// 면으로 그리기
					/*memDC.BeginPath();
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.EndPath();
					memDC.StrokeAndFillPath();*/
				}
				else
				{
					// 선으로 그리기
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// 면으로 그리기
					/*memDC.BeginPath();
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.EndPath();
					memDC.StrokeAndFillPath();*/
				}
			}
		}

		//	if (i >= 132)
		//	{
		//		memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
		//		memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
		//		continue;
		//	}
		//	memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
		//	memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
		//}
#pragma endregion
		#pragma region 두번째 삼각 폴리곤 그리기
		// 두번째 그리는 삼각형들
		countInt = 0;
		for (int i = 0; i < 144; i++)
		{
			if ((i + 12) % 12 == 0) // 0, 12, 24, 36, .... , 120, 132
			{
				if (i == 0)
				{
					dotFst[0][0] = -torCopy[i].x + torCopy[i + 132].x;
					dotSec[0][0] = -torCopy[i].x + torCopy[i + 11].x;
					dotFst[1][0] = -torCopy[i].y + torCopy[i + 132].y;
					dotSec[1][0] = -torCopy[i].y + torCopy[i + 11].y;
					dotFst[2][0] = -torCopy[i].z + torCopy[i + 132].z;
					dotSec[2][0] = -torCopy[i].z + torCopy[i + 11].z;
					cameraToPolygon1[0][0] = torCopy[i].x;
					cameraToPolygon1[1][0] = torCopy[i].y;
					cameraToPolygon1[2][0] = torCopy[i].z;
					cameraToPolygon2[0][0] = torCopy[i + 132].x;
					cameraToPolygon2[1][0] = torCopy[i + 132].y;
					cameraToPolygon2[2][0] = torCopy[i + 132].z;
					cameraToPolygon3[0][0] = torCopy[i + 11].x;
					cameraToPolygon3[1][0] = torCopy[i + 11].y;
					cameraToPolygon3[2][0] = torCopy[i + 11].z;
				}
				else
				{
					dotFst[0][0] = -torCopy[i].x + torCopy[i - 12].x;
					dotSec[0][0] = -torCopy[i].x + torCopy[i + 11].x;
					dotFst[1][0] = -torCopy[i].y + torCopy[i - 12].y;
					dotSec[1][0] = -torCopy[i].y + torCopy[i + 11].y;
					dotFst[2][0] = -torCopy[i].z + torCopy[i - 12].z;
					dotSec[2][0] = -torCopy[i].z + torCopy[i + 11].z;
					cameraToPolygon1[0][0] = torCopy[i].x;
					cameraToPolygon1[1][0] = torCopy[i].y;
					cameraToPolygon1[2][0] = torCopy[i].z;
					cameraToPolygon2[0][0] = torCopy[i - 12].x;
					cameraToPolygon2[1][0] = torCopy[i - 12].y;
					cameraToPolygon2[2][0] = torCopy[i - 12].z;
					cameraToPolygon3[0][0] = torCopy[i + 11].x;
					cameraToPolygon3[1][0] = torCopy[i + 11].y;
					cameraToPolygon3[2][0] = torCopy[i + 11].z;
				}
			}
			else
			{
				if (i < 12)
				{
					dotFst[0][0] = -torCopy[i].x + torCopy[i + 132].x;
					dotSec[0][0] = -torCopy[i].x + torCopy[i - 1].x;
					dotFst[1][0] = -torCopy[i].y + torCopy[i + 132].y;
					dotSec[1][0] = -torCopy[i].y + torCopy[i - 1].y;
					dotFst[2][0] = -torCopy[i].z + torCopy[i + 132].z;
					dotSec[2][0] = -torCopy[i].z + torCopy[i - 1].z;
					cameraToPolygon1[0][0] = torCopy[i].x;
					cameraToPolygon1[1][0] = torCopy[i].y;
					cameraToPolygon1[2][0] = torCopy[i].z;
					cameraToPolygon2[0][0] = torCopy[i + 132].x;
					cameraToPolygon2[1][0] = torCopy[i + 132].y;
					cameraToPolygon2[2][0] = torCopy[i + 132].z;
					cameraToPolygon3[0][0] = torCopy[i - 1].x;
					cameraToPolygon3[1][0] = torCopy[i - 1].y;
					cameraToPolygon3[2][0] = torCopy[i - 1].z;
				}
				else
				{
					dotFst[0][0] = -torCopy[i].x + torCopy[i - 12].x;
					dotSec[0][0] = -torCopy[i].x + torCopy[i - 1].x;
					dotFst[1][0] = -torCopy[i].y + torCopy[i - 12].y;
					dotSec[1][0] = -torCopy[i].y + torCopy[i - 1].y;
					dotFst[2][0] = -torCopy[i].z + torCopy[i - 12].z;
					dotSec[2][0] = -torCopy[i].z + torCopy[i - 1].z;
					cameraToPolygon1[0][0] = torCopy[i].x;
					cameraToPolygon1[1][0] = torCopy[i].y;
					cameraToPolygon1[2][0] = torCopy[i].z;
					cameraToPolygon2[0][0] = torCopy[i - 12].x;
					cameraToPolygon2[1][0] = torCopy[i - 12].y;
					cameraToPolygon2[2][0] = torCopy[i - 12].z;
					cameraToPolygon3[0][0] = torCopy[i - 1].x;
					cameraToPolygon3[1][0] = torCopy[i - 1].y;
					cameraToPolygon3[2][0] = torCopy[i - 1].z;
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

			for (int j = 0; j < 3; j++)
			{
				vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
				vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
				vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
			}

			float result1 = DotProduct(vPolygon1, crsBoth);
			float result2 = DotProduct(vPolygon2, crsBoth);
			float result3 = DotProduct(vPolygon3, crsBoth);

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
		if (secResult == 1)
		{
			// 선으로 그리기
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[11].x), ToScreenY(rect.Height(), rect.top, tor[11].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[132].x), ToScreenY(rect.Height(), rect.top, tor[132].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			// 면으로 그리기
			/*memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[11].x), ToScreenY(rect.Height(), rect.top, tor[11].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[132].x), ToScreenY(rect.Height(), rect.top, tor[132].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();*/
		}
		//////
		for (auto i : mySecInt)
		{
			if (i == 0) continue;
			if (i % 12 == 0)
			{
				// 선으로 그리기
				memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 11].x), ToScreenY(rect.Height(), rect.top, tor[i + 11].y));
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
				// 면으로 그리기
				/*memDC.BeginPath();
				memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 11].x), ToScreenY(rect.Height(), rect.top, tor[i + 11].y));
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
				memDC.EndPath();
				memDC.StrokeAndFillPath();*/

			}
			else
			{
				if (i < 12)
				{
					// 선으로 그리기
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 132].x), ToScreenY(rect.Height(), rect.top, tor[i + 132].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// 면으로 그리기
					/*memDC.BeginPath();
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i -1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 132].x), ToScreenY(rect.Height(), rect.top, tor[i + 132].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.EndPath();
					memDC.StrokeAndFillPath();*/
				}
				else
				{
					// 선으로 그리기
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// 면으로 그리기
					/*memDC.BeginPath();
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.EndPath();
					memDC.StrokeAndFillPath();*/
				}
			}
		}
#pragma endregion
#pragma endregion

	}


	memDC.SelectObject(oldBrush);
	DeleteObject(newBrush);

	memDC.SelectObject(oldPen);
	DeleteObject(newPen);

	cdc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	myBitmap.DeleteObject();
	memDC.DeleteDC();
	ReleaseDC(&cdc);
	#pragma region 기존 코드들
	//CPaintDC dc(this); // device context for painting
	//				   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//				   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	//CDC memDC;
	//CBitmap myBitmap;
	//CBitmap* pOldBitmap;
	//CRect rect;
	//GetClientRect(&rect);

	//memDC.CreateCompatibleDC(&dc);
	//myBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	//pOldBitmap = memDC.SelectObject(&myBitmap);

	//// 메모리 DC에 그리기
	//CBrush bgBrush(RGB(0, 0, 255));
	//CBrush* pOldBrush = memDC.SelectObject(&bgBrush);
	//memDC.PatBlt(0, 0, rect.Width(), rect.Height(), /*WHITENESS*/ PATCOPY);
	//memDC.SelectObject(pOldBrush);
	//DeleteObject(bgBrush);

	//	// 삼각형 그리기 + 칠하기
	//if (myPoint.x != 0 || myPoint.y != 0)
	//{
	//	CBrush TriBrush(RGB(255, 0, 0));
	//	CBrush* OldBrush = memDC.SelectObject(&TriBrush);

	//	memDC.BeginPath();
	//	memDC.MoveTo(C1);
	//	memDC.LineTo(C2);
	//	memDC.LineTo(C3);
	//	memDC.LineTo(C1);
	//	memDC.EndPath();
	//	memDC.StrokeAndFillPath();

	//	memDC.SelectObject(OldBrush);
	//	DeleteObject(TriBrush);
	//}
	//	////////
	///*
	//for (auto shape : m_vShape)
	//{
	//	memDC.Rectangle(shape.ptStart.x, shape.ptStart.y, shape.ptEnd.x, shape.ptEnd.y);
	//}
	//*/
	////////////////////////
	//dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	//memDC.SelectObject(pOldBitmap);
	//myBitmap.DeleteObject();
	//memDC.DeleteDC();
	//ReleaseDC(&dc);
	#pragma endregion
}

// 클릭하는 곳 좌표를 받아서 그곳에 그림 생성하기
void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	float az10[4][1];
	az10[2][0] = 100;
	az10[0][0] = (point.x - left - width / 2) / (width / 2) * az10[2][0];
	az10[1][0] = (point.y - top - height / 2) * (-1) / (height / 2) * az10[2][0];
	az10[3][0] = 1; // 화면을 클릭했을 때 얻어지는 투영면에서의 한 지점
	// 뷰 행렬
	float look[3][1] = { { 1 },{ -1 },{ 0 } };
	float view[4][4] = {}; 
	float* viewPtr = ViewMatrix(camera, look/*뷰 행렬 만드는데 물체 위치가 크게 중요하지 않은 것 같아서 나중에 지울 예정*/, look);
	int viewCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			view[i][j] = *(viewPtr + viewCount);
			viewCount++;
		}
	}
	// 투영 행렬
	float proj[4][4] = {};
	float* pPtr = ProjectionMatrix(width, height, 90, 2, 15);
	int prjCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			proj[i][j] = *(pPtr + prjCount);
			prjCount++;
		}
	}

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

	// TODO: 카메라좌표계의 점을 월드 좌표계로 옮긴다 (뷰 역행렬)
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
	// 이제 로컬에서의 한 점이 만들어졌다.

	//CString str = _T("");
	//str.Format(_T("%f  %f  %f  %f"), az10[0][0], az10[1][0], az10[2][0], az10[3][0]);
	//AfxMessageBox(str);
	//return;
	// TODO: 해당 점을 기준으로 도형을 만든다
	if (figureNum == 3)
	{
		// 해당 점을 넣을 것
		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
		MyVertex* vPtr = pTorus(x, y, z, 15, 8);
		MyVertex tor[144] = {};
		MyVertex torCopy[144] = {};
		int count = 0;
		// 만든 Torus 정보 가져오기
		for (int i = 0; i < 144; i++)
		{
			tor[i] = *(vPtr + count);
			torCopy[i] = *(vPtr + count);
			count++;
		}

		#pragma region 뷰 행렬 변환
		//float look[3][1] = { { 1 },{ -1 },{ 0 } };
		//float view[4][4] = {};
		//float* viewPtr = ViewMatrix(camera, look/*뷰 행렬 만드는데 물체 위치가 크게 중요하지 않은 것 같아서 나중에 지울 예정*/, look);
		//int viewCount = 0;
		//for (int i = 0; i < 4; i++)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		view[i][j] = *(viewPtr + viewCount);
		//		viewCount++;
		//	}
		//}

		float* fPtr;
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
#pragma endregion
		#pragma region 투영 행렬 변환
		//float proj[4][4] = {};
		//float* pPtr = ProjectionMatrix(width, height, 90, 2, 15);
		//count = 0;
		//// 투영 행렬 생성
		//for (int i = 0; i < 4; i++)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		proj[i][j] = *(fPtr + count);
		//		count++;
		//	}
		//}

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

			tor[i].x /= tor[i].z;
			tor[i].y /= tor[i].z;
			tor[i].z /= tor[i].z;

		}
		#pragma endregion
		// 해당 점들을 구조체에 넣어서 vector array에 보관
		TorusInfo ti;
		for (int i = 0; i < 144; i++)
		{
			ti.torus[i] = tor[i];
			ti.torusCopy[i] = torCopy[i];
		}
		ti.vertexCount = sizeof(tor) / sizeof(MyVertex);
		v_Figure.push_back(ti);
	}
	Invalidate();

#pragma region 나중에 도형을 배열에 넣게되면 하나씩 빼서 써먹어봅시다
	//bool direction1, direction2, direction3; // 직선 기준으로 오른쪽에 있는지 왼쪽에 있는지 판별해줄 boolean
	//bool isInside = FALSE;
	//int figureCount = 0;
	//float a = (point.x - left - width / 2) / (width / 2);
	//float b = (point.y - top - height / 2) / (height / 2) * (-1);

	//for (auto figure : v_Figure)
	//{
	//	if (figure.vertexCount == 144) // Torus
	//	{
	//		MyVertex sample[144] = {};
	//		int count = 0;
	//		for (int i = 0; i < 144; i++)
	//		{
	//			sample[i] = *(figure.vPtr + count);
	//			count++;
	//		}
	//		// sample에다가 정점 정보 다 받아옴
	//		float g1, g2, g3; // 선분의 기울기
	//		for (int i = 0; i < 144; i++)
	//		{
	//			direction1 = FALSE;
	//			direction2 = FALSE;
	//			direction3 = FALSE;
	//			// 첫번째 사각형
	//			// 기울기를 구했으므로 점 (a,b)를 넣어 각 직선 기준 오른쪽에 위치한지 왼쪽에 위치하는지 확인
	//			if ((i + 1) % 12 == 0)
	//			{
	//				if (i >= 132)
	//				{
	//					g1 = (sample[i - 11].y - sample[i].y) / (sample[i - 11].x - sample[i].x);
	//					g2 = (sample[i - 132].y - sample[i - 11].y) / (sample[i - 132].x - sample[i - 11].x);
	//					g3 = (sample[i].y - sample[i - 132].y) / (sample[i].x - sample[i - 132].x);
	//					if (b < g1 * (a - sample[i].x) + sample[i].y) direction1 = TRUE;
	//					if (b < g2 * (a - sample[i - 11].x) + sample[i - 11].y) direction2 = TRUE;
	//					if (b < g3 * (a - sample[i - 132].x) + sample[i - 132].y) direction3 = TRUE;
	//				}
	//				else
	//				{
	//					g1 = (sample[i - 11].y - sample[i].y) / (sample[i - 11].x - sample[i].x);
	//					g2 = (sample[i + 12].y - sample[i - 11].y) / (sample[i + 12].x - sample[i - 11].x);
	//					g3 = (sample[i].y - sample[i + 12].y) / (sample[i].x - sample[i + 12].x);
	//					if (b < g1 * (a - sample[i].x) + sample[i].y) direction1 = TRUE;
	//					if (b < g2 * (a - sample[i - 11].x) + sample[i - 11].y) direction2 = TRUE;
	//					if (b < g3 * (a - sample[i + 12].x) + sample[i + 12].y) direction3 = TRUE;
	//				}
	//			}
	//			else
	//			{
	//				if (i >= 132)
	//				{
	//					g1 = (sample[i + 1].y - sample[i].y) / (sample[i + 1].x - sample[i].x);
	//					g2 = (sample[i - 132].y - sample[i + 1].y) / (sample[i - 132].x - sample[i + 1].x);
	//					g3 = (sample[i].y - sample[i - 132].y) / (sample[i].x - sample[i - 132].x);
	//					if (b < g1 * (a - sample[i].x) + sample[i].y) direction1 = TRUE;
	//					if (b < g2 * (a - sample[i + 1].x) + sample[i + 1].y) direction2 = TRUE;
	//					if (b < g3 * (a - sample[i - 132].x) + sample[i - 132].y) direction3 = TRUE;
	//				}
	//				else
	//				{
	//					g1 = (sample[i + 1].y - sample[i].y) / (sample[i + 1].x - sample[i].x);
	//					g2 = (sample[i + 12].y - sample[i + 1].y) / (sample[i + 12].x - sample[i + 1].x);
	//					g3 = (sample[i].y - sample[i + 12].y) / (sample[i].x - sample[i + 12].x);
	//					if (b < g1 * (a - sample[i].x) + sample[i].y) direction1 = TRUE;
	//					if (b < g2 * (a - sample[i + 1].x) + sample[i + 1].y) direction2 = TRUE;
	//					if (b < g3 * (a - sample[i + 12].x) + sample[i + 12].y) direction3 = TRUE;
	//				}
	//			}
	//			// 방향이 전부 TRUE이거나 FALSE이면 면 안쪽에 있음.
	//			if ((g1 == TRUE && g2 == TRUE && g3 == TRUE) || (g1 == FALSE && g2 == FALSE && g3 == FALSE))
	//			{
	//				isInside = TRUE;
	//				break;
	//			}
	//		}
	//	}
	//	figureCount++;
	//}

	//if (isInside)
	//{
	//	AfxMessageBox(_T("It's Inside!"));
	//}
#pragma endregion
#pragma region 1사분면 클릭했을때만 메시지박스가 나오게하는 코드
	/*CPoint a1, a2, a3, a4;
	bool b1, b2, b3, b4;
	a1.x = (1420 - left - width / 2) / (width / 2); a1.y = (0 - top - height / 2) * (-1) / (height / 2);
	a2.x = (1420 - left - width / 2) / (width / 2); a2.y = (326 - top - height / 2) * (-1) / (height / 2);
	a3.x = (710 - left - width / 2) / (width / 2); a3.y = (326 - top - height / 2) * (-1) / (height / 2);
	a4.x = (710 - left - width / 2) / (width / 2); a4.y = (0 - top - height / 2) * (-1) / (height / 2);

	if (point.x <= 1420) b1 = TRUE;
	else b1 = FALSE;

	if (point.x >= 710) b2 = TRUE;
	else b2 = FALSE;

	if (point.y >= 0) b3 = TRUE;
	else b3 = FALSE;

	if (point.y <= 326) b4 = TRUE;
	else b4 = FALSE;

	if (b1 == TRUE && b2 == TRUE && b3 == TRUE && b4 == TRUE)
	AfxMessageBox(_T("It is inside!"));*/
#pragma endregion

	CView::OnLButtonDown(nFlags, point);
}

void CMFCApplication3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CView::OnLButtonUp(nFlags, point);
}


void CMFCApplication3View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (moveDirX.x == 0 && moveDirX.y == 0)
	{
		moveDirX.x = point.x;
		moveDirX.y = point.y;
		return;
	}
	else
	{
		/*if (point.x > moveDirX.x)
		{
			cameraZ += 1;
		}
		else 
		{
			cameraZ -= 1;
		}*/
		if (point.y > moveDirX.y)
		{
			cameraY -= 1;
		}
		else
		{
			cameraY += 1;
		}
		moveDirX.x = point.x;
		moveDirX.y = point.y;
	}

	Invalidate();
	CView::OnMouseMove(nFlags, point);
}


BOOL CMFCApplication3View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CBrush bgBrush(RGB(0, 0, 255));

	//CBrush* pOldBrush = pDC->SelectObject(&bgBrush);
	//CRect rect;
	//pDC->GetClipBox(&rect);
	//pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	//pDC->SelectObject(pOldBrush);

	return TRUE;

	return CView::OnEraseBkgnd(pDC);
}


void CMFCApplication3View::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CMFCApplication3View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	C1.x = 0; C1.y = -60;
	C2.x = 40; C2.y = 20;
	C3.x = -40; C3.y = 20;
	float c1Point[4][1] = { {0}, {-60}, {0}, {1} };
	float c2Point[4][1] = { {40}, {20}, {0}, {1} };
	float c3Point[4][1] = { {-40}, {20}, {0}, {1} };
	float* ptr = MatrixRotate(c1Point, 0, 0, 90);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		c1Point[i][0] = *(ptr + count);

		count++;
	}
	ptr = MatrixRotate(c2Point, 0, 0, 90);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		c2Point[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixRotate(c3Point, 0, 0, 90);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		c3Point[i][0] = *(ptr + count);
		count++;
	}
	int x = myPoint.x;
	int y = myPoint.y;
	C1.x = x + c1Point[0][0]; C1.y = y + c1Point[0][1];
	C2.x = x + c2Point[0][0]; C2.y = y + c2Point[0][1];
	C3.x = x + c3Point[0][0]; C3.y = y + c3Point[0][1];

	Invalidate();

	CView::OnRButtonUp(nFlags, point);
}
