
// MFCApplication3View.cpp : CMFCApplication3View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"
#include "MainFrm.h"
#include "Figure.h"


// ���� ���ϵ�
#include "Matrix.h"
//////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// ǥ�� �μ� ����Դϴ�.
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

// CMFCApplication3View ����/�Ҹ�

CMFCApplication3View::CMFCApplication3View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	RegisterHotKey(m_hWnd, 15000, 0, VK_RIGHT);
	RegisterHotKey(m_hWnd, 15001, 0, VK_LEFT);
	cameraX = -40;
	cameraY = 40;
	cameraZ = 0;
	moveDirX.x = 0;
	moveDirX.y = 0;
}

CMFCApplication3View::~CMFCApplication3View()
{
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View �׸���

void CMFCApplication3View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMFCApplication3View �μ�

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCApplication3View ����

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View �޽��� ó����


void CMFCApplication3View::OnPaint()
{
	float x = 10; float y = 0; float z = 0;
	float* ptr = pTorus(x, y, z, 15, 8);
	float tor[144][3] = {};
	int count = 0;
	// ���� Torus ���� ��������
	for (int i = 0; i < 144; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tor[i][j] = *(ptr + count);
			count++;
		}
	}
	// �׸��� �غ�
	CPaintDC cdc(this);
	CRect rect;
	GetClientRect(&rect);

	CPoint cp = (10, 10);

	CDC memDC;
	CBitmap myBitmap;
	CBitmap* pOldBitmap;

	memDC.CreateCompatibleDC(&cdc);
	myBitmap.CreateCompatibleBitmap(&cdc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&myBitmap);

	// �޸� DC�� �׸���
	CBrush bgBrush(RGB(0, 0, 255));
	CBrush* pOldBrush = memDC.SelectObject(&bgBrush);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), /*WHITENESS*/ PATCOPY);
	memDC.SelectObject(pOldBrush);
	DeleteObject(bgBrush);

	CPen newPen;
	newPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* oldPen = memDC.SelectObject(&newPen);

#pragma region �� ��� ��ȯ
	float camera[3][1] = { { cameraX },{ cameraY },{ cameraZ } };
	float look[3][1] = { { 1 },{ -1 },{ 0 } };
	float view[4][4] = {};
	float* viewPtr = ViewMatrix(camera, look/*�� ��� ����µ� ��ü ��ġ�� ũ�� �߿����� ���� �� ���Ƽ� ���߿� ���� ����*/, look);
	int viewCount = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			view[i][j] = *(viewPtr + viewCount);
			viewCount++;
		}
	}

	ptr = 0;
	float sample[4][1] = {};
	// torus �� ������ �� ��� ��ȯ ��Ŵ
	for (int i = 0; i < 144; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sample[j][0] = tor[i][j];
		}
		sample[3][0] = 1;
		ptr = MatrixMulti(view, sample);
		int torCount = 0;
		for (int j = 0; j < 3; j++)
		{
			tor[i][j] = *(ptr + torCount);
			torCount++;
		}
	}
#pragma endregion
#pragma region ���� ��� ��ȯ
	float proj[4][4] = {};
	ptr = ProjectionMatrix(rect.Width(), rect.Height(), 90, 2, 15);
	count = 0;
	// ���� ��� ����
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			proj[i][j] = *(ptr + count);
			count++;
		}
	}

	// �� ��ȯ �� ���� ���� ��ȯ
	for (int i = 0; i < 144; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sample[j][0] = tor[i][j];
		}
		sample[3][0] = 1;
		ptr = MatrixMulti(proj, sample);
		int torCount = 0;
		for (int j = 0; j < 3; j++)
		{
			tor[i][j] = *(ptr + torCount);
			if (j == 2)
			{
				tor[i][0] /= tor[i][2];
				tor[i][1] /= tor[i][2];
			}
			torCount++;
		}
	}
#pragma endregion
#pragma region ��ǥ�� ��ȯ �� �׸���
	// ���鳢�� �׸���
	for (int i = 0; i < 144; i++)
	{
		if ((i + 1) % 12 == 0)
		{
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i][0]), ToScreenY(rect.Height(), rect.top, tor[i][1]));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11][0]), ToScreenY(rect.Height(), rect.top, tor[i - 11][1]));
			continue;
		}
		memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i][0]), ToScreenY(rect.Height(), rect.top, tor[i][1]));
		memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1][0]), ToScreenY(rect.Height(), rect.top, tor[i + 1][1]));
	}
	// ������ �����ϱ�
	for (int i = 0; i < 144; i++)
	{
		if (i >= 132)
		{
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i][0]), ToScreenY(rect.Height(), rect.top, tor[i][1]));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132][0]), ToScreenY(rect.Height(), rect.top, tor[i - 132][1]));
			continue;
		}
		memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i][0]), ToScreenY(rect.Height(), rect.top, tor[i][1]));
		memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12][0]), ToScreenY(rect.Height(), rect.top, tor[i + 12][1]));
	}
#pragma endregion

	memDC.SelectObject(oldPen);
	DeleteObject(newPen);

	cdc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	myBitmap.DeleteObject();
	memDC.DeleteDC();
	ReleaseDC(&cdc);
	#pragma region ���� �ڵ��
	//CPaintDC dc(this); // device context for painting
	//				   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	//				   // �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.

	//CDC memDC;
	//CBitmap myBitmap;
	//CBitmap* pOldBitmap;
	//CRect rect;
	//GetClientRect(&rect);

	//memDC.CreateCompatibleDC(&dc);
	//myBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	//pOldBitmap = memDC.SelectObject(&myBitmap);

	//// �޸� DC�� �׸���
	//CBrush bgBrush(RGB(0, 0, 255));
	//CBrush* pOldBrush = memDC.SelectObject(&bgBrush);
	//memDC.PatBlt(0, 0, rect.Width(), rect.Height(), /*WHITENESS*/ PATCOPY);
	//memDC.SelectObject(pOldBrush);
	//DeleteObject(bgBrush);

	//	// �ﰢ�� �׸��� + ĥ�ϱ�
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


void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (moveDirX.x == 0 && moveDirX.y == 0)
	{
		moveDirX.x = point.x;
		moveDirX.y = point.y;
		return;
	}
	else
	{
		if (point.x > moveDirX.x)
		{
			cameraZ += 1;
		}
		else 
		{
			cameraZ -= 1;
		}
		//if (point.y > moveDirX.y)
		//{
		//	cameraY -= 1;
		//}
		//else
		//{
		//	cameraY += 1;
		//}
		moveDirX.x = point.x;
		moveDirX.y = point.y;
	}

	Invalidate();

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CMFCApplication3View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
