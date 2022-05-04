
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


// 만든 파일들
#include "Matrix.h"
//////////////

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
	RegisterHotKey(m_hWnd, 15000, 0, VK_RIGHT);
	RegisterHotKey(m_hWnd, 15001, 0, VK_LEFT);
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
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	CDC memDC;
	CBitmap myBitmap;
	CBitmap* pOldBitmap;
	CRect rect;
	GetClientRect(&rect);

	memDC.CreateCompatibleDC(&dc);
	myBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&myBitmap);

	// 메모리 DC에 그리기
	CBrush bgBrush(RGB(0, 0, 255));
	CBrush* pOldBrush = memDC.SelectObject(&bgBrush);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), /*WHITENESS*/ PATCOPY);
	memDC.SelectObject(pOldBrush);
	DeleteObject(bgBrush);

		// 삼각형 그리기 + 칠하기
	if (myPoint.x != 0 || myPoint.y != 0)
	{
		CBrush TriBrush(RGB(255, 0, 0));
		CBrush* OldBrush = memDC.SelectObject(&TriBrush);

		memDC.BeginPath();
		memDC.MoveTo(C1);
		memDC.LineTo(C2);
		memDC.LineTo(C3);
		memDC.LineTo(C1);
		memDC.EndPath();
		memDC.StrokeAndFillPath();

		memDC.SelectObject(OldBrush);
		DeleteObject(TriBrush);
	}
		////////
	/*
	for (auto shape : m_vShape)
	{
		memDC.Rectangle(shape.ptStart.x, shape.ptStart.y, shape.ptEnd.x, shape.ptEnd.y);
	}
	*/
	//////////////////////
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	myBitmap.DeleteObject();
	memDC.DeleteDC();
	ReleaseDC(&dc);
}


void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	myPoint = point;
	int x = myPoint.x;
	int y = myPoint.y;
	C1.x = x; C1.y = y - 60;
	C2.x = x + 40; C2.y = y + 20;
	C3.x = x - 40; C3.y = y + 20;
	Invalidate();

	/*
	m_shCur.ptStart.x = point.x;
	m_shCur.ptStart.y = point.y;
	m_bDrag = TRUE;
	*/
	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CString strTmp = _T("");
	strTmp.Format(_T("(%f) + (%f)"), (float)point.x, float(point.y));
	AfxMessageBox(strTmp);


	/*
	if (m_bDrag)
	{
		m_bDrag = FALSE;
		m_shCur.ptEnd = point;
		m_vShape.push_back(m_shCur);
		Invalidate();
	}
	*/
	CView::OnLButtonUp(nFlags, point);
}


void CMFCApplication3View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.




	/*
	if (m_bDrag)
	{
		m_shCur.ptEnd.x = point.x;
		m_shCur.ptEnd.y = point.y;

		Invalidate();
	}
	*/
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
	float c1Point[4][1] = { {0}, {-60}, {1}, {1} };
	float c2Point[4][1] = { {40}, {20}, {1}, {1} };
	float c3Point[4][1] = { {-40}, {20}, {1}, {1} };
	float* ptr = MatrixRotate(c1Point, 0, 0, 30);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		c1Point[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixRotate(c2Point, 0, 0, 30);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		c2Point[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixRotate(c3Point, 0, 0, 30);
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
