
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

extern int figureNum;
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
	v_torusFigure = {};
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
	// �׸��� �غ�
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

	// �޸� DC�� �׸���
	CBrush bgBrush(RGB(0, 0, 255));
	CBrush* pOldBrush = memDC.SelectObject(&bgBrush);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), /*WHITENESS*/ PATCOPY);
	memDC.SelectObject(pOldBrush);
	DeleteObject(bgBrush);

	CPen newPen;
	newPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* oldPen = memDC.SelectObject(&newPen);

	CBrush newBrush(RGB(255, 0, 0));
	CBrush* oldBrush = memDC.SelectObject(&newBrush);

	// ���� ��ǥ�� �����ͼ� ���⼭ �ٽ� �׷����� ī�޶� ȸ���� �ɰŰ���
	for (auto figure : v_cubeFigure)
	{
		int count = 0;
		MyVertex cub[8] = {};
		MyVertex cubCopy[8] = {};
		for (int i = 0; i < 8; i++)
		{
			cub[i] = figure.cube[i];
			cubCopy[i] = figure.cubeCopy[i];
			count++;
		}
		if (figure.isClicked == TRUE)
		{
		#pragma region 1�� ������
			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();

			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();

			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();
	#pragma endregion
		#pragma region 2�� ������
			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();

			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();

			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();
	#pragma endregion
		#pragma region 3�� ������
			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();

			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();

			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();
	#pragma endregion
		#pragma region 4�� ������
			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();

			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();

			memDC.BeginPath();
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
			memDC.EndPath();
			memDC.StrokeAndFillPath();
	#pragma endregion
		}
		else
		{
		#pragma region 1�� ������
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));

			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));

			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[0].x), ToScreenY(rect.Height(), rect.top, cub[0].y));
	#pragma endregion
		#pragma region 2�� ������
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));

			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));

			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[7].x), ToScreenY(rect.Height(), rect.top, cub[7].y));
	#pragma endregion
		#pragma region 3�� ������
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));

			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));

			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[3].x), ToScreenY(rect.Height(), rect.top, cub[3].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[2].x), ToScreenY(rect.Height(), rect.top, cub[2].y));
	#pragma endregion
		#pragma region 4�� ������
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));

			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[1].x), ToScreenY(rect.Height(), rect.top, cub[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));

			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[6].x), ToScreenY(rect.Height(), rect.top, cub[6].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[4].x), ToScreenY(rect.Height(), rect.top, cub[4].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, cub[5].x), ToScreenY(rect.Height(), rect.top, cub[5].y));
	#pragma endregion
		}
	}

	for (auto figure : v_sphereFigure)
	{
		// vector�κ��� �� ��ǥ �޾ƿ���
		int count = 0;
		MyVertex sph[230] = {};
		MyVertex sphCopy[230] = {};
		for (int i = 0; i < 230; i++) {
			sph[i] = figure.sphere[i];
			sphCopy[i] = figure.sphereCopy[i];
			count++;
		}

		// �޸� �߶󳻱�
		float vFst[4][1] = {}; // ��꿡 �� ���� ����� ����
		float vSec[4][1] = {}; // ��꿡 �� ���� ����� ����
		int isVisableDot1[12] = {};
		int isVisable[216] = {};
		int isVisableDot2[12] = {};// ���� ���̴� �κи� üũ�� ���̹Ƿ� ���� �Ⱥ��̴� �������� 0���� �ٲ���� ��ȹ
		int countInt = 0;
		float cameraToPolygon1[3][1] = {}; // ī�޶� -> ���� ����
		float cameraToPolygon2[3][1] = {}; // ī�޶� -> ���� ����
		float cameraToPolygon3[3][1] = {}; // ī�޶� -> ���� ����
		float vPolygon1[3][1] = {}; // ī�޶� -> ���� ���� ���� �ӽ� �迭
		float vPolygon2[3][1] = {}; // ī�޶� -> ���� ���� ���� �ӽ� �迭
		float vPolygon3[3][1] = {}; // ī�޶� -> ���� ���� ���� �ӽ� �迭
		#pragma region ù��° �ﰢ ������
		for (int i = 1; i < 13; i++) // ���� ���� ������ ���� 12���� ���� ������ ��
		{
			if ((i % 12) != 0)
			{
				vFst[0][0] = -sphCopy[0].x + sphCopy[i].x;
				vFst[1][0] = -sphCopy[0].y + sphCopy[i].y;
				vFst[2][0] = -sphCopy[0].z + sphCopy[i].z;
				vSec[0][0] = -sphCopy[i].x + sphCopy[i + 1].x;
				vSec[1][0] = -sphCopy[i].y + sphCopy[i + 1].y;
				vSec[2][0] = -sphCopy[i].z + sphCopy[i + 1].z;
				cameraToPolygon1[0][0] = sphCopy[0].x;
				cameraToPolygon1[1][0] = sphCopy[0].y;
				cameraToPolygon1[2][0] = sphCopy[0].z;
				cameraToPolygon2[0][0] = sphCopy[i].x;
				cameraToPolygon2[1][0] = sphCopy[i].y;
				cameraToPolygon2[2][0] = sphCopy[i].z;
				cameraToPolygon3[0][0] = sphCopy[i + 1].x;
				cameraToPolygon3[1][0] = sphCopy[i + 1].y;
				cameraToPolygon3[2][0] = sphCopy[i + 1].z;
			}
			else
			{
				vFst[0][0] = -sphCopy[0].x + sphCopy[i].x;
				vFst[1][0] = -sphCopy[0].y + sphCopy[i].y;
				vFst[2][0] = -sphCopy[0].z + sphCopy[i].z;
				vSec[0][0] = -sphCopy[i].x + sphCopy[i - 11].x;
				vSec[1][0] = -sphCopy[i].y + sphCopy[i - 11].y;
				vSec[2][0] = -sphCopy[i].z + sphCopy[i - 11].z;
				cameraToPolygon1[0][0] = sphCopy[0].x;
				cameraToPolygon1[1][0] = sphCopy[0].y;
				cameraToPolygon1[2][0] = sphCopy[0].z;
				cameraToPolygon2[0][0] = sphCopy[i].x;
				cameraToPolygon2[1][0] = sphCopy[i].y;
				cameraToPolygon2[2][0] = sphCopy[i].z;
				cameraToPolygon3[0][0] = sphCopy[i - 11].x;
				cameraToPolygon3[1][0] = sphCopy[i - 11].y;
				cameraToPolygon3[2][0] = sphCopy[i - 11].z;
			}
			vFst[3][0] = 1; vSec[3][0] = 1;

			float cross[3][1] = {};
			float* cPtr = CrossProduct(vFst, vSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}
			for (int j = 0; j < 3; j++)
			{
				vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
				vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
				vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
			}

			float result1 = DotProduct(vPolygon1, cross);
			float result2 = DotProduct(vPolygon2, cross);
			float result3 = DotProduct(vPolygon3, cross);

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
			if ((i % 12) == 0)
			{
				vFst[0][0] = -sphCopy[i].x + sphCopy[i + 12].x;
				vFst[1][0] = -sphCopy[i].y + sphCopy[i + 12].y;
				vFst[2][0] = -sphCopy[i].z + sphCopy[i + 12].z;
				vSec[0][0] = -sphCopy[i + 12].x + sphCopy[i + 1].x;
				vSec[1][0] = -sphCopy[i + 12].y + sphCopy[i + 1].y;
				vSec[2][0] = -sphCopy[i + 12].z + sphCopy[i + 1].z;
				cameraToPolygon1[0][0] = sphCopy[i].x;
				cameraToPolygon1[1][0] = sphCopy[i].y;
				cameraToPolygon1[2][0] = sphCopy[i].z;
				cameraToPolygon2[0][0] = sphCopy[i + 12].x;
				cameraToPolygon2[1][0] = sphCopy[i + 12].y;
				cameraToPolygon2[2][0] = sphCopy[i + 12].z;
				cameraToPolygon3[0][0] = sphCopy[i + 1].x;
				cameraToPolygon3[1][0] = sphCopy[i + 1].y;
				cameraToPolygon3[2][0] = sphCopy[i + 1].z;
			}
			else
			{
				vFst[0][0] = -sphCopy[i].x + sphCopy[i + 12].x;
				vFst[1][0] = -sphCopy[i].y + sphCopy[i + 12].y;
				vFst[2][0] = -sphCopy[i].z + sphCopy[i + 12].z;
				vSec[0][0] = -sphCopy[i + 12].x + sphCopy[i + 13].x;
				vSec[1][0] = -sphCopy[i + 12].y + sphCopy[i + 13].y;
				vSec[2][0] = -sphCopy[i + 12].z + sphCopy[i + 13].z;
				cameraToPolygon1[0][0] = sphCopy[i].x;
				cameraToPolygon1[1][0] = sphCopy[i].y;
				cameraToPolygon1[2][0] = sphCopy[i].z;
				cameraToPolygon2[0][0] = sphCopy[i + 12].x;
				cameraToPolygon2[1][0] = sphCopy[i + 12].y;
				cameraToPolygon2[2][0] = sphCopy[i + 12].z;
				cameraToPolygon3[0][0] = sphCopy[i + 13].x;
				cameraToPolygon3[1][0] = sphCopy[i + 13].y;
				cameraToPolygon3[2][0] = sphCopy[i + 13].z;
			}
			vFst[3][0] = 1; vSec[3][0] = 1;

			float cross[3][1] = {};
			float* cPtr = CrossProduct(vFst, vSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}
			for (int j = 0; j < 3; j++)
			{
				vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
				vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
				vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
			}

			float result1 = DotProduct(vPolygon1, cross);
			float result2 = DotProduct(vPolygon2, cross);
			float result3 = DotProduct(vPolygon3, cross);

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
			if ((i % 12) != 0)
			{
				vFst[0][0] = -sphCopy[i].x + sphCopy[229].x;
				vFst[1][0] = -sphCopy[i].y + sphCopy[229].y;
				vFst[2][0] = -sphCopy[i].z + sphCopy[229].z;
				vSec[0][0] = -sphCopy[i].x + sphCopy[i + 1].x;
				vSec[1][0] = -sphCopy[i].y + sphCopy[i + 1].y;
				vSec[2][0] = -sphCopy[i].z + sphCopy[i + 1].z;
				cameraToPolygon1[0][0] = sphCopy[i].x;
				cameraToPolygon1[1][0] = sphCopy[i].y;
				cameraToPolygon1[2][0] = sphCopy[i].z;
				cameraToPolygon2[0][0] = sphCopy[229].x;
				cameraToPolygon2[1][0] = sphCopy[229].y;
				cameraToPolygon2[2][0] = sphCopy[229].z;
				cameraToPolygon3[0][0] = sphCopy[i + 1].x;
				cameraToPolygon3[1][0] = sphCopy[i + 1].y;
				cameraToPolygon3[2][0] = sphCopy[i + 1].z;
			}
			else
			{
				vFst[0][0] = -sphCopy[i].x + sphCopy[229].x;
				vFst[1][0] = -sphCopy[i].y + sphCopy[229].y;
				vFst[2][0] = -sphCopy[i].z + sphCopy[229].z;
				vSec[0][0] = -sphCopy[i].x + sphCopy[i - 11].x;
				vSec[1][0] = -sphCopy[i].y + sphCopy[i - 11].y;
				vSec[2][0] = -sphCopy[i].z + sphCopy[i - 11].z;
				cameraToPolygon1[0][0] = sphCopy[i].x;
				cameraToPolygon1[1][0] = sphCopy[i].y;
				cameraToPolygon1[2][0] = sphCopy[i].z;
				cameraToPolygon2[0][0] = sphCopy[229].x;
				cameraToPolygon2[1][0] = sphCopy[229].y;
				cameraToPolygon2[2][0] = sphCopy[229].z;
				cameraToPolygon3[0][0] = sphCopy[i - 11].x;
				cameraToPolygon3[1][0] = sphCopy[i - 11].y;
				cameraToPolygon3[2][0] = sphCopy[i - 11].z;
			}
			vFst[3][0] = 1; vSec[3][0] = 1;

			float cross[3][1] = {};
			float* cPtr = CrossProduct(vFst, vSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}
			for (int j = 0; j < 3; j++)
			{
				vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
				vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
				vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
			}

			float result1 = DotProduct(vPolygon1, cross);
			float result2 = DotProduct(vPolygon2, cross);
			float result3 = DotProduct(vPolygon3, cross);

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
			
		for (int i = 1; i < 13; i++)
		{
			if (isVisableDot1[i - 1] == 0) continue;
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
			if (i % 12 == 0)
			{
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
			}
			else
			{
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
			}
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[0].x), ToScreenY(rect.Height(), rect.top, sph[0].y));
		}
		for (int i = 1; i < 217; i++)
		{
			if (isVisable[i - 1] == 0) continue;
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 12].x), ToScreenY(rect.Height(), rect.top, sph[i + 12].y));
			if (i % 12 == 0)
			{
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
			}
			else
			{
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 13].x), ToScreenY(rect.Height(), rect.top, sph[i + 13].y));
			}
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
		}
		for(int i = 217; i < 229; i++)
		{
			if (isVisableDot2[i - 217] == 0) continue;
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[229].x), ToScreenY(rect.Height(), rect.top, sph[229].y));
			if (i % 12 == 0)
			{
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i - 11].x), ToScreenY(rect.Height(), rect.top, sph[i - 11].y));
			}
			else
			{
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i + 1].x), ToScreenY(rect.Height(), rect.top, sph[i + 1].y));
			}
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, sph[i].x), ToScreenY(rect.Height(), rect.top, sph[i].y));
		}
		#pragma endregion

		#pragma region �ι�° �ﰢ ������ -> ���� ������ ���������̶��� ���̻� ���� �ʿ� ����
		countInt = 0;
		for (int i = 1; i < 217; i++)
		{
			if ((i % 12) == 0)
			{
				vFst[0][0] = -sphCopy[i + 1].x + sphCopy[i - 11].x;
				vFst[1][0] = -sphCopy[i + 1].y + sphCopy[i - 11].y;
				vFst[2][0] = -sphCopy[i + 1].z + sphCopy[i - 11].z;
				vSec[0][0] = -sphCopy[i - 11].x + sphCopy[i].x;
				vSec[1][0] = -sphCopy[i - 11].y + sphCopy[i].y;
				vSec[2][0] = -sphCopy[i - 11].z + sphCopy[i].z;
				cameraToPolygon1[0][0] = sphCopy[i].x;
				cameraToPolygon1[1][0] = sphCopy[i].y;
				cameraToPolygon1[2][0] = sphCopy[i].z;
				cameraToPolygon2[0][0] = sphCopy[i - 11].x;
				cameraToPolygon2[1][0] = sphCopy[i - 11].y;
				cameraToPolygon2[2][0] = sphCopy[i - 11].z;
				cameraToPolygon3[0][0] = sphCopy[i + 1].x;
				cameraToPolygon3[1][0] = sphCopy[i + 1].y;
				cameraToPolygon3[2][0] = sphCopy[i + 1].z;
			}
			else
			{
				vFst[0][0] = -sphCopy[i + 13].x + sphCopy[i + 1].x;
				vFst[1][0] = -sphCopy[i + 13].y + sphCopy[i + 1].y;
				vFst[2][0] = -sphCopy[i + 13].z + sphCopy[i + 1].z;
				vSec[0][0] = -sphCopy[i + 1].x + sphCopy[i].x;
				vSec[1][0] = -sphCopy[i + 1].y + sphCopy[i].y;
				vSec[2][0] = -sphCopy[i + 1].z + sphCopy[i].z;
				cameraToPolygon1[0][0] = sphCopy[i].x;
				cameraToPolygon1[1][0] = sphCopy[i].y;
				cameraToPolygon1[2][0] = sphCopy[i].z;
				cameraToPolygon2[0][0] = sphCopy[i + 1].x;
				cameraToPolygon2[1][0] = sphCopy[i + 1].y;
				cameraToPolygon2[2][0] = sphCopy[i + 1].z;
				cameraToPolygon3[0][0] = sphCopy[i + 13].x;
				cameraToPolygon3[1][0] = sphCopy[i + 13].y;
				cameraToPolygon3[2][0] = sphCopy[i + 13].z;
			}
			vFst[3][0] = 1; vSec[3][0] = 1;

			float cross[3][1] = {};
			float* cPtr = CrossProduct(vFst, vSec);
			int count = 0;
			for (int j = 0; j < 3; j++)
			{
				cross[j][0] = *(cPtr + count);
				count++;
			}
			for (int j = 0; j < 3; j++)
			{
				vPolygon1[j][0] = -camera[j][0] + cameraToPolygon1[j][0];
				vPolygon2[j][0] = -camera[j][0] + cameraToPolygon2[j][0];
				vPolygon3[j][0] = -camera[j][0] + cameraToPolygon3[j][0];
			}

			float result1 = DotProduct(vPolygon1, cross);
			float result2 = DotProduct(vPolygon2, cross);
			float result3 = DotProduct(vPolygon3, cross);

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
		#pragma endregion
	}

	for (auto figure : v_torusFigure)
	{
		#pragma region ��ǥ�� ��ȯ �� �׸���
		// ���鳢�� �׸���
		float dotFst[4][1] = {};
		float dotSec[4][1] = {};
		int myInt[144] = {};
		int mySecInt[144] = {};
		int countInt = 0;
		int fstResult = 0; // ó�� �ﰢ�� �׸� �� i=0 �� �� ���� ��
		int secResult = 0; // �ι�° �ﰢ�� �׸� �� i=0 �� �� ���� ��
		float cameraToPolygon1[3][1] = {}; // ī�޶� -> ���� ����
		float cameraToPolygon2[3][1] = {}; // ī�޶� -> ���� ����
		float cameraToPolygon3[3][1] = {}; // ī�޶� -> ���� ����
		float vPolygon1[3][1] = {}; // ī�޶� -> ���� ���� ���� �ӽ� �迭
		float vPolygon2[3][1] = {}; // ī�޶� -> ���� ���� ���� �ӽ� �迭
		float vPolygon3[3][1] = {}; // ī�޶� -> ���� ���� ���� �ӽ� �迭
		// �迭���� �޾ƿ� �����ͷ� vertex ��������
		int count = 0;
		MyVertex tor[144] = {};
		MyVertex torCopy[144] = {};
		for (int i = 0; i < 144; i++)			{
			tor[i] = figure.torus[i];
			torCopy[i] = figure.torusCopy[i];
			count++;
		}

		#pragma region ù��° �ﰢ ������ 
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
		// i = 0 �϶��� ���� �׷��ֱ� -> 0�϶��� �ǳʶٰ� �׷�������.
		if (fstResult == 1)
		{
			// ������ �׸���
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[1].x), ToScreenY(rect.Height(), rect.top, tor[1].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[12].x), ToScreenY(rect.Height(), rect.top, tor[12].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			// ������ �׸���
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
					// ������ �׸���
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// ������ �׸���
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
					// ������ �׸���
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// ������ �׸���
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
					// ������ �׸���
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// ������ �׸���
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
					// ������ �׸���
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 1].x), ToScreenY(rect.Height(), rect.top, tor[i + 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i + 12].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// ������ �׸���
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
		#pragma region �ι�° �ﰢ ������ �׸���
		// �ι�° �׸��� �ﰢ����
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
		// i = 0 �϶��� ���� �׷��ֱ� -> 0�϶��� �ǳʶٰ� �׷�������.
		if (secResult == 1)
		{
			// ������ �׸���
			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[11].x), ToScreenY(rect.Height(), rect.top, tor[11].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[132].x), ToScreenY(rect.Height(), rect.top, tor[132].y));
			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[0].x), ToScreenY(rect.Height(), rect.top, tor[0].y));
			// ������ �׸���
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
				// ������ �׸���
				memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 11].x), ToScreenY(rect.Height(), rect.top, tor[i + 11].y));
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
				memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
				// ������ �׸���
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
					// ������ �׸���
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 132].x), ToScreenY(rect.Height(), rect.top, tor[i + 132].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// ������ �׸���
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
					// ������ �׸���
					memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 1].x), ToScreenY(rect.Height(), rect.top, tor[i - 1].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 12].x), ToScreenY(rect.Height(), rect.top, tor[i - 12].y));
					memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
					// ������ �׸���
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

// Ŭ���ϴ� �� ��ǥ�� �޾Ƽ� �װ��� �׸� �����ϱ�
void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	float az10[4][1];
	az10[2][0] = 100;
	az10[0][0] = (point.x - left - width / 2) / (width / 2) * az10[2][0];
	az10[1][0] = (point.y - top - height / 2) * (-1) / (height / 2) * az10[2][0];
	az10[3][0] = 1; // ȭ���� Ŭ������ �� ������� �����鿡���� �� ����
	// �� ���
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
	// ���� ���
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

	// TODO: �������� ���� ī�޶� ��ǥ��� �ű�� (���� �����)
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
		// ���� ���� ����İ� ����
	pPtr = MatrixMulti(projReverse, az10);
	prjCount = 0;
	for (int i = 0; i < 4; i++)
	{
		az10[i][0] = *(pPtr + prjCount);
		prjCount++;
	}

	// TODO: ī�޶���ǥ���� ���� ���� ��ǥ��� �ű�� (�� �����)
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

		// ���� ���� ����İ� ����
	viewPtr = MatrixMulti(viewReverse, az10);
	viewCount = 0;
	for (int i = 0; i < 4; i++)
	{
		az10[i][0] = *(viewPtr + viewCount);
		viewCount++;
	}
	// ���� ���忡���� �� ���� ���������.

	// TODO: �ش� ���� �������� ������ �����
	switch (figureNum)
	{
	case 0:

	#pragma region case1-Cube
	case 1:
	{
		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
		MyVertex* vPtr = pCube(x, y, z);
		MyVertex cub[8] = {};
		MyVertex cubCopy[8] = {};
		int count = 0;
		for (int i = 0; i < 8; i++)
		{
			cub[i] = *(vPtr + count);
			cubCopy[i] = *(vPtr + count);
			count++;
		}

		float* fPtr;
		float sample[4][1] = {};
		// sphere �� ������ �� ��� ��ȯ ��Ŵ
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

		// sphere �� ������ ���� ��Ŵ
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

			cub[i].x /= cub[i].z;
			cub[i].y /= cub[i].z;
			cub[i].z /= cub[i].z;

		}

		// �ش� ������ ����ü�� �־ vector array�� ����
		CubeInfo Ci;
		for (int i = 0; i < 8; i++)
		{
			Ci.cube[i] = cub[i];
			Ci.cubeCopy[i] = cubCopy[i];
		}
		Ci.vertexCount = sizeof(cub) / sizeof(MyVertex);
		v_cubeFigure.push_back(Ci);
	#pragma endregion
		break;
	}

	#pragma region case2-Sphere
	case 2:
	{
		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
		MyVertex* vPtr = pSphere(x, y, z);
		MyVertex sph[230] = {};
		MyVertex sphCopy[230] = {};
		int count = 0;
		for (int i = 0; i < 230; i++)
		{
			sph[i] = *(vPtr + count);
			sphCopy[i] = *(vPtr + count);
			count++;
		}

		float* fPtr;
		float sample[4][1] = {};
		// sphere �� ������ �� ��� ��ȯ ��Ŵ
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

		// sphere �� ������ ���� ��Ŵ
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

			sph[i].x /= sph[i].z;
			sph[i].y /= sph[i].z;
			sph[i].z /= sph[i].z;

		}

		// �ش� ������ ����ü�� �־ vector array�� ����
		SphereInfo Si;
		for (int i = 0; i < 230; i++)
		{
			Si.sphere[i] = sph[i];
			Si.sphereCopy[i] = sphCopy[i];
		}
		Si.vertexCount = sizeof(sph) / sizeof(MyVertex);
		v_sphereFigure.push_back(Si);
#pragma endregion
		break;
	}
	#pragma region case3-Torus
	case 3 :
	{
		// �ش� ���� ���� ��
		float x = az10[0][0]; float y = az10[1][0]; float z = az10[2][0];
		MyVertex* vPtr = pTorus(x, y, z, 15, 8);
		MyVertex tor[144] = {};
		MyVertex torCopy[144] = {};
		int count = 0;
		// ���� Torus ���� ��������
		for (int i = 0; i < 144; i++)
		{
			tor[i] = *(vPtr + count);
			torCopy[i] = *(vPtr + count);
			count++;
		}

#pragma region �� ��� ��ȯ\
		
		float* fPtr;
		float sample[4][1] = {};
		// torus �� ������ �� ��� ��ȯ ��Ŵ
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
#pragma region ���� ��� ��ȯ
		// �� ��ȯ �� ���� ���� ��ȯ
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
		// �ش� ������ ����ü�� �־ vector array�� ����
		TorusInfo ti;
		for (int i = 0; i < 144; i++)
		{
			ti.torus[i] = tor[i];
			ti.torusCopy[i] = torCopy[i];
		}
		ti.vertexCount = sizeof(tor) / sizeof(MyVertex);
		v_torusFigure.push_back(ti);
#pragma endregion
		break;
	}
	}

	Invalidate();

#pragma region ���߿� ������ �迭�� �ְԵǸ� �ϳ��� ���� ��Ծ�ô�
	//bool direction1, direction2, direction3; // ���� �������� �����ʿ� �ִ��� ���ʿ� �ִ��� �Ǻ����� boolean
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
	//		// sample���ٰ� ���� ���� �� �޾ƿ�
	//		float g1, g2, g3; // ������ ����
	//		for (int i = 0; i < 144; i++)
	//		{
	//			direction1 = FALSE;
	//			direction2 = FALSE;
	//			direction3 = FALSE;
	//			// ù��° �簢��
	//			// ���⸦ �������Ƿ� �� (a,b)�� �־� �� ���� ���� �����ʿ� ��ġ���� ���ʿ� ��ġ�ϴ��� Ȯ��
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
	//			// ������ ���� TRUE�̰ų� FALSE�̸� �� ���ʿ� ����.
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

	CView::OnLButtonDown(nFlags, point);
}

void CMFCApplication3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
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
			//cameraY -= 1;
			camera[1][0] -= 1;
		}
		else
		{
			//cameraY += 1;
			camera[1][0] += 1;
		}
		moveDirX.x = point.x;
		moveDirX.y = point.y;
	}

	Invalidate();
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
#pragma region ��ũ�� ��ǥ��δ� �����
	//for (auto figure : v_cubeFigure)
	//{
	//	MyVertex cub[8] = {};
	//	for (int i = 0; i < 8; i++)
	//	{
	//		cub[i] = figure.cube[i];
	//	}
	//	CPoint cpointVector[12][3] = {};
	//	CPoint originVector[12][3] = {};
	//	
	//	CPoint p1 = (ToScreenX(width, left, cub[0].x), ToScreenY(height, top, cub[0].y));
	//	CPoint p2 = (ToScreenX(width, left, cub[3].x), ToScreenY(height, top, cub[3].y));
	//	CPoint p3 = (ToScreenX(width, left, cub[4].x), ToScreenY(height, top, cub[4].y));

	//	cpointVector[0][0] = -p1 + p2; cpointVector[0][1] = -p2 + p3, cpointVector[0][2] = -p3 + p1;
	//	originVector[0][0] = p1; originVector[0][1] = p2; originVector[0][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[0].x), ToScreenY(height, top, cub[0].y));
	//	p2 = (ToScreenX(width, left, cub[4].x), ToScreenY(height, top, cub[4].y));
	//	p3 = (ToScreenX(width, left, cub[1].x), ToScreenY(height, top, cub[1].y));

	//	cpointVector[1][0] = -p1 + p2; cpointVector[1][1] = -p2 + p3, cpointVector[1][2] = -p3 + p1;
	//	originVector[1][0] = p1; originVector[1][1] = p2; originVector[1][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[0].x), ToScreenY(height, top, cub[0].y));
	//	p2 = (ToScreenX(width, left, cub[1].x), ToScreenY(height, top, cub[1].y));
	//	p3 = (ToScreenX(width, left, cub[3].x), ToScreenY(height, top, cub[3].y));

	//	cpointVector[2][0] = -p1 + p2; cpointVector[2][1] = -p2 + p3, cpointVector[2][2] = -p3 + p1;
	//	originVector[2][0] = p1; originVector[2][1] = p2; originVector[2][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[7].x), ToScreenY(height, top, cub[7].y));
	//	p2 = (ToScreenX(width, left, cub[4].x), ToScreenY(height, top, cub[4].y));
	//	p3 = (ToScreenX(width, left, cub[3].x), ToScreenY(height, top, cub[3].y));

	//	cpointVector[3][0] = -p1 + p2; cpointVector[3][1] = -p2 + p3, cpointVector[3][2] = -p3 + p1;
	//	originVector[3][0] = p1; originVector[3][1] = p2; originVector[3][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[7].x), ToScreenY(height, top, cub[7].y));
	//	p2 = (ToScreenX(width, left, cub[6].x), ToScreenY(height, top, cub[6].y));
	//	p3 = (ToScreenX(width, left, cub[4].x), ToScreenY(height, top, cub[4].y));

	//	cpointVector[4][0] = -p1 + p2; cpointVector[4][1] = -p2 + p3, cpointVector[4][2] = -p3 + p1;
	//	originVector[4][0] = p1; originVector[4][1] = p2; originVector[4][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[7].x), ToScreenY(height, top, cub[7].y));
	//	p2 = (ToScreenX(width, left, cub[3].x), ToScreenY(height, top, cub[3].y));
	//	p3 = (ToScreenX(width, left, cub[6].x), ToScreenY(height, top, cub[6].y));

	//	cpointVector[5][0] = -p1 + p2; cpointVector[5][1] = -p2 + p3, cpointVector[5][2] = -p3 + p1;
	//	originVector[5][0] = p1; originVector[5][1] = p2; originVector[5][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[2].x), ToScreenY(height, top, cub[2].y));
	//	p2 = (ToScreenX(width, left, cub[1].x), ToScreenY(height, top, cub[1].y));
	//	p3 = (ToScreenX(width, left, cub[6].x), ToScreenY(height, top, cub[6].y));

	//	cpointVector[6][0] = -p1 + p2; cpointVector[6][1] = -p2 + p3, cpointVector[6][2] = -p3 + p1;
	//	originVector[6][0] = p1; originVector[6][1] = p2; originVector[6][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[2].x), ToScreenY(height, top, cub[2].y));
	//	p2 = (ToScreenX(width, left, cub[3].x), ToScreenY(height, top, cub[3].y));
	//	p3 = (ToScreenX(width, left, cub[1].x), ToScreenY(height, top, cub[1].y));

	//	cpointVector[7][0] = -p1 + p2; cpointVector[7][1] = -p2 + p3, cpointVector[7][2] = -p3 + p1;
	//	originVector[7][0] = p1; originVector[7][1] = p2; originVector[7][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[2].x), ToScreenY(height, top, cub[2].y));
	//	p2 = (ToScreenX(width, left, cub[3].x), ToScreenY(height, top, cub[3].y));
	//	p3 = (ToScreenX(width, left, cub[6].x), ToScreenY(height, top, cub[6].y));

	//	cpointVector[8][0] = -p1 + p2; cpointVector[8][1] = -p2 + p3, cpointVector[8][2] = -p3 + p1;
	//	originVector[8][0] = p1; originVector[8][1] = p2; originVector[8][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[5].x), ToScreenY(height, top, cub[5].y));
	//	p2 = (ToScreenX(width, left, cub[6].x), ToScreenY(height, top, cub[6].y));
	//	p3 = (ToScreenX(width, left, cub[1].x), ToScreenY(height, top, cub[1].y));

	//	cpointVector[9][0] = -p1 + p2; cpointVector[9][1] = -p2 + p3, cpointVector[9][2] = -p3 + p1;
	//	originVector[9][0] = p1; originVector[9][1] = p2; originVector[9][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[5].x), ToScreenY(height, top, cub[5].y));
	//	p2 = (ToScreenX(width, left, cub[1].x), ToScreenY(height, top, cub[1].y));
	//	p3 = (ToScreenX(width, left, cub[4].x), ToScreenY(height, top, cub[4].y));

	//	cpointVector[10][0] = -p1 + p2; cpointVector[10][1] = -p2 + p3, cpointVector[10][2] = -p3 + p1;
	//	originVector[10][0] = p1; originVector[10][1] = p2; originVector[10][2] = p3;

	//	p1 = (ToScreenX(width, left, cub[5].x), ToScreenY(height, top, cub[5].y));
	//	p2 = (ToScreenX(width, left, cub[4].x), ToScreenY(height, top, cub[4].y));
	//	p3 = (ToScreenX(width, left, cub[6].x), ToScreenY(height, top, cub[6].y));

	//	cpointVector[11][0] = -p1 + p2; cpointVector[11][1] = -p2 + p3, cpointVector[11][2] = -p3 + p1;
	//	originVector[11][0] = p1; originVector[11][1] = p2; originVector[11][2] = p3;
	//	
	//	
	//	for (int i = 0; i < 12; i++)
	//	{	
	//		float result1[3][1] = {};
	//		float result2[3][1] = {};
	//		float result3[3][1] = {};
	//		float lineVector[2][1] = {};
	//		float pointVector[2][1] = {};
	//		// ���� �Ѱ� ���
	//		lineVector[0][0] = cpointVector[i][0].x;  lineVector[1][0] = cpointVector[i][0].y;
	//		pointVector[0][0] = -originVector[i][0].x + point.x; pointVector[1][0] = -originVector[i][0].y + point.y;
	//		float* ptr = CrossProduct2X2(lineVector, pointVector);
	//		int count = 0;
	//		for (int j = 0; j < 3; j++)
	//		{
	//			result1[j][0] = *(ptr + count);
	//			count++;
	//		}
	//		// ���� �Ѱ� ���
	//		lineVector[0][0] = cpointVector[i][1].x;  lineVector[1][0] = cpointVector[i][1].y;
	//		pointVector[0][0] = -originVector[i][1].x + point.x; pointVector[1][0] = -originVector[i][1].y + point.y;
	//		ptr = CrossProduct2X2(lineVector, pointVector);
	//		count = 0;
	//		for (int j = 0; j < 3; j++)
	//		{
	//			result2[j][0] = *(ptr + count);
	//			count++;
	//		}
	//		// ���� �Ѱ� ���
	//		lineVector[0][0] = cpointVector[i][2].x;  lineVector[1][0] = cpointVector[i][2].y;
	//		pointVector[0][0] = -originVector[i][2].x + point.x; pointVector[1][0] = -originVector[i][2].y + point.y;
	//		ptr = CrossProduct2X2(lineVector, pointVector);
	//		count = 0;
	//		for (int j = 0; j < 3; j++)
	//		{
	//			result3[j][0] = *(ptr + count);
	//			count++;
	//		}
	//		// ���� z�� ������ ��� ������ �� ���ο� �ִ�.
	//		if ((result1[2][0] > 0 && result2[2][0] > 0 && result3[2][0] > 0) || (result1[2][0] < 0 && result2[2][0] < 0 && result3[2][0] < 0))
	//		{
	//			if (figure.isClicked == FALSE) figure.isClicked = TRUE;
	//			else figure.isClicked = FALSE;

	//			break;
	//		}
	//		else
	//		{
	//			figure.isClicked = FALSE;
	//		}
	//	}
	//}
#pragma endregion

	#pragma region ��ũ�� ��ǥ���� ���� ���� ��ǥ��� �̵�
	float az10[4][1];
	az10[2][0] = 100;
	az10[0][0] = (point.x - left - width / 2) / (width / 2) * az10[2][0];
	az10[1][0] = (point.y - top - height / 2) * (-1) / (height / 2) * az10[2][0];
	az10[3][0] = 1; // ȭ���� Ŭ������ �� ������� �����鿡���� �� ����
	// �� ���
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
	// ���� ���
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

	// TODO: �������� ���� ī�޶� ��ǥ��� �ű�� (���� �����)
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
	// ���� ���� ����İ� ����
	pPtr = MatrixMulti(projReverse, az10);
	prjCount = 0;
	for (int i = 0; i < 4; i++)
	{
		az10[i][0] = *(pPtr + prjCount);
		prjCount++;
	}

	// TODO: ī�޶���ǥ���� ���� ���� ��ǥ��� �ű�� (�� �����)
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

	// ���� ���� ����İ� ����
	viewPtr = MatrixMulti(viewReverse, az10);
	viewCount = 0;
	for (int i = 0; i < 4; i++)
	{
		az10[i][0] = *(viewPtr + viewCount);
		viewCount++;
	}
	#pragma endregion
	// az[4][1]�� ��ǥ�� ���� ��ǥ���� �� �� -> �� �������� �����ؼ� �� ���� ����� ���� -> ���� ������ ����ȭ�ؼ� ��� ������ ����
	for (auto figure : v_cubeFigure)
	{
		MyVertex cub[8] = {};
		for (int i = 0; i < 8; i++)
		{
			cub[i] = figure.cubeCopy[i];
		}
		MyVertex p1 = {};
		MyVertex p2 = {};
		MyVertex p3 = {};
		MyVertex planeVector[12][3] = {};
		MyVertex originVector[12][3] = {};
		/////
		#pragma region �� �޽��� ���� ��ǥ�� ���͵�
		p1.x = cub[0].x; p1.y = cub[0].y; p1.z = cub[0].z;
		p2.x = cub[3].x; p2.y = cub[3].y; p2.z = cub[3].z;
		p3.x = cub[4].x; p3.y = cub[4].y; p3.z = cub[4].z;

		planeVector[0][0].x = -p1.x + p2.x; planeVector[0][0].y = -p1.y + p2.y; planeVector[0][0].z = -p1.z + p2.z;
		planeVector[0][1].x = -p2.x + p3.x; planeVector[0][1].y = -p2.y + p3.y; planeVector[0][1].z = -p2.z + p3.z;
		planeVector[0][2].x = -p3.x + p1.x; planeVector[0][2].y = -p3.y + p1.y; planeVector[0][2].z = -p3.z + p1.z;

		originVector[0][0] = p1; originVector[0][1] = p2; originVector[0][2] = p3;
		/////
		p1.x = cub[0].x; p1.y = cub[0].y; p1.z = cub[0].z;
		p2.x = cub[4].x; p2.y = cub[4].y; p2.z = cub[4].z;
		p3.x = cub[1].x; p3.y = cub[1].y; p3.z = cub[1].z;

		planeVector[1][0].x = -p1.x + p2.x; planeVector[1][0].y = -p1.y + p2.y; planeVector[1][0].z = -p1.z + p2.z;
		planeVector[1][1].x = -p2.x + p3.x; planeVector[1][1].y = -p2.y + p3.y; planeVector[1][1].z = -p2.z + p3.z;
		planeVector[1][2].x = -p3.x + p1.x; planeVector[1][2].y = -p3.y + p1.y; planeVector[1][2].z = -p3.z + p1.z;

		originVector[1][0] = p1; originVector[1][1] = p2; originVector[1][2] = p3;
		/////
		p1.x = cub[0].x; p1.y = cub[0].y; p1.z = cub[0].z;
		p2.x = cub[1].x; p2.y = cub[1].y; p2.z = cub[1].z;
		p3.x = cub[3].x; p3.y = cub[3].y; p3.z = cub[3].z;

		planeVector[2][0].x = -p1.x + p2.x; planeVector[2][0].y = -p1.y + p2.y; planeVector[2][0].z = -p1.z + p2.z;
		planeVector[2][1].x = -p2.x + p3.x; planeVector[2][1].y = -p2.y + p3.y; planeVector[2][1].z = -p2.z + p3.z;
		planeVector[2][2].x = -p3.x + p1.x; planeVector[2][2].y = -p3.y + p1.y; planeVector[2][2].z = -p3.z + p1.z;

		originVector[2][0] = p1; originVector[2][1] = p2; originVector[2][2] = p3;
		/////
		p1.x = cub[7].x; p1.y = cub[7].y; p1.z = cub[7].z;
		p2.x = cub[4].x; p2.y = cub[4].y; p2.z = cub[4].z;
		p3.x = cub[3].x; p3.y = cub[3].y; p3.z = cub[3].z;

		planeVector[3][0].x = -p1.x + p2.x; planeVector[3][0].y = -p1.y + p2.y; planeVector[3][0].z = -p1.z + p2.z;
		planeVector[3][1].x = -p2.x + p3.x; planeVector[3][1].y = -p2.y + p3.y; planeVector[3][1].z = -p2.z + p3.z;
		planeVector[3][2].x = -p3.x + p1.x; planeVector[3][2].y = -p3.y + p1.y; planeVector[3][2].z = -p3.z + p1.z;

		originVector[3][0] = p1; originVector[3][1] = p2; originVector[3][2] = p3;
		/////
		p1.x = cub[7].x; p1.y = cub[7].y; p1.z = cub[7].z;
		p2.x = cub[6].x; p2.y = cub[6].y; p2.z = cub[6].z;
		p3.x = cub[4].x; p3.y = cub[4].y; p3.z = cub[4].z;

		planeVector[4][0].x = -p1.x + p2.x; planeVector[4][0].y = -p1.y + p2.y; planeVector[4][0].z = -p1.z + p2.z;
		planeVector[4][1].x = -p2.x + p3.x; planeVector[4][1].y = -p2.y + p3.y; planeVector[4][1].z = -p2.z + p3.z;
		planeVector[4][2].x = -p3.x + p1.x; planeVector[4][2].y = -p3.y + p1.y; planeVector[4][2].z = -p3.z + p1.z;

		originVector[4][0] = p1; originVector[4][1] = p2; originVector[4][2] = p3;
		/////
		p1.x = cub[7].x; p1.y = cub[7].y; p1.z = cub[7].z;
		p2.x = cub[3].x; p2.y = cub[3].y; p2.z = cub[3].z;
		p3.x = cub[6].x; p3.y = cub[6].y; p3.z = cub[6].z;

		planeVector[5][0].x = -p1.x + p2.x; planeVector[5][0].y = -p1.y + p2.y; planeVector[5][0].z = -p1.z + p2.z;
		planeVector[5][1].x = -p2.x + p3.x; planeVector[5][1].y = -p2.y + p3.y; planeVector[5][1].z = -p2.z + p3.z;
		planeVector[5][2].x = -p3.x + p1.x; planeVector[5][2].y = -p3.y + p1.y; planeVector[5][2].z = -p3.z + p1.z;

		originVector[5][0] = p1; originVector[5][1] = p2; originVector[5][2] = p3;
		/////
		p1.x = cub[2].x; p1.y = cub[2].y; p1.z = cub[2].z;
		p2.x = cub[1].x; p2.y = cub[1].y; p2.z = cub[1].z;
		p3.x = cub[6].x; p3.y = cub[6].y; p3.z = cub[6].z;

		planeVector[6][0].x = -p1.x + p2.x; planeVector[6][0].y = -p1.y + p2.y; planeVector[6][0].z = -p1.z + p2.z;
		planeVector[6][1].x = -p2.x + p3.x; planeVector[6][1].y = -p2.y + p3.y; planeVector[6][1].z = -p2.z + p3.z;
		planeVector[6][2].x = -p3.x + p1.x; planeVector[6][2].y = -p3.y + p1.y; planeVector[6][2].z = -p3.z + p1.z;

		originVector[6][0] = p1; originVector[6][1] = p2; originVector[6][2] = p3;
		/////
		p1.x = cub[2].x; p1.y = cub[2].y; p1.z = cub[2].z;
		p2.x = cub[3].x; p2.y = cub[3].y; p2.z = cub[3].z;
		p3.x = cub[1].x; p3.y = cub[1].y; p3.z = cub[1].z;

		planeVector[7][0].x = -p1.x + p2.x; planeVector[7][0].y = -p1.y + p2.y; planeVector[7][0].z = -p1.z + p2.z;
		planeVector[7][1].x = -p2.x + p3.x; planeVector[7][1].y = -p2.y + p3.y; planeVector[7][1].z = -p2.z + p3.z;
		planeVector[7][2].x = -p3.x + p1.x; planeVector[7][2].y = -p3.y + p1.y; planeVector[7][2].z = -p3.z + p1.z;

		originVector[7][0] = p1; originVector[7][1] = p2; originVector[7][2] = p3;
		/////
		p1.x = cub[2].x; p1.y = cub[2].y; p1.z = cub[2].z;
		p2.x = cub[6].x; p2.y = cub[6].y; p2.z = cub[6].z;
		p3.x = cub[3].x; p3.y = cub[3].y; p3.z = cub[3].z;

		planeVector[8][0].x = -p1.x + p2.x; planeVector[8][0].y = -p1.y + p2.y; planeVector[8][0].z = -p1.z + p2.z;
		planeVector[8][1].x = -p2.x + p3.x; planeVector[8][1].y = -p2.y + p3.y; planeVector[8][1].z = -p2.z + p3.z;
		planeVector[8][2].x = -p3.x + p1.x; planeVector[8][2].y = -p3.y + p1.y; planeVector[8][2].z = -p3.z + p1.z;

		originVector[8][0] = p1; originVector[8][1] = p2; originVector[8][2] = p3;
		/////
		p1.x = cub[5].x; p1.y = cub[5].y; p1.z = cub[5].z;
		p2.x = cub[6].x; p2.y = cub[6].y; p2.z = cub[6].z;
		p3.x = cub[1].x; p3.y = cub[1].y; p3.z = cub[1].z;

		planeVector[9][0].x = -p1.x + p2.x; planeVector[9][0].y = -p1.y + p2.y; planeVector[9][0].z = -p1.z + p2.z;
		planeVector[9][1].x = -p2.x + p3.x; planeVector[9][1].y = -p2.y + p3.y; planeVector[9][1].z = -p2.z + p3.z;
		planeVector[9][2].x = -p3.x + p1.x; planeVector[9][2].y = -p3.y + p1.y; planeVector[9][2].z = -p3.z + p1.z;

		originVector[9][0] = p1; originVector[9][1] = p2; originVector[9][2] = p3;
		/////
		p1.x = cub[5].x; p1.y = cub[5].y; p1.z = cub[5].z;
		p2.x = cub[1].x; p2.y = cub[1].y; p2.z = cub[1].z;
		p3.x = cub[4].x; p3.y = cub[4].y; p3.z = cub[4].z;

		planeVector[10][0].x = -p1.x + p2.x; planeVector[10][0].y = -p1.y + p2.y; planeVector[10][0].z = -p1.z + p2.z;
		planeVector[10][1].x = -p2.x + p3.x; planeVector[10][1].y = -p2.y + p3.y; planeVector[10][1].z = -p2.z + p3.z;
		planeVector[10][2].x = -p3.x + p1.x; planeVector[10][2].y = -p3.y + p1.y; planeVector[10][2].z = -p3.z + p1.z;

		originVector[10][0] = p1; originVector[10][1] = p2; originVector[10][2] = p3;
		/////
		p1.x = cub[5].x; p1.y = cub[5].y; p1.z = cub[5].z;
		p2.x = cub[4].x; p2.y = cub[4].y; p2.z = cub[4].z;
		p3.x = cub[6].x; p3.y = cub[6].y; p3.z = cub[6].z;

		planeVector[11][0].x = -p1.x + p2.x; planeVector[11][0].y = -p1.y + p2.y; planeVector[11][0].z = -p1.z + p2.z;
		planeVector[11][1].x = -p2.x + p3.x; planeVector[11][1].y = -p2.y + p3.y; planeVector[11][1].z = -p2.z + p3.z;
		planeVector[11][2].x = -p3.x + p1.x; planeVector[11][2].y = -p3.y + p1.y; planeVector[11][2].z = -p3.z + p1.z;

		originVector[11][0] = p1; originVector[11][1] = p2; originVector[11][2] = p3;
		/////
		#pragma endregion

		for (int i = 0; i < 12; i++)
		{
			/*
			i = 0 ����
			���� ���� (n1, n2, n3): CrossProduct(planeVector[0][0], planeVector[0][1]) -> float���� �ٲ���;
			�� �ϳ� (a, b, c): originVector[0][0];
			����� ������ => n1(x - a) + n2(y - b) + n3(z - c) = 0;
			az[4][1]�� ����ִ� ���� ��ǥ���� �������� ���� ���� => MatrixNormalize(az) 
				=> (i, j, k) => (i * x, j * x, k * x)�� �� �� ����
			����� �����Ŀ� ���� => (n1 * i + n2 * j + n3 * k) * x = ( n1 * a + n2 * b + n3 * c);
			x = ( n1 * a + n2 * b + n3 * c) / (n1 * i + n2 * j + n3 * k);
			���� ��� ���� ���� ���� �� ���� = (i, j, k) * x;
			originVector�� Ȱ���� �� p1, p2, p3�� ���� �� ���� ��, p1 -> p2 ���Ϳ� p1 -> (i, j, k) * x ���͸� �����ϸ� 
				�����ؼ� ���� ������ �������͸� ���� �� ����(Normalize)
			�ش� �������͵��� ������ ��� ������, �ش� ���� �ﰢ�� �޽� ���ʿ� �ִٰ� ������ �� ����
			���ʿ� �ִٸ�, isClicked�� TRUE�� �ٲ� ��.
			*/
		}
	}
	

	/*for (auto figure : v_sphereFigure)
	{

	}
	for (auto figure : v_torusFigure)
	{

	}*/

	CView::OnRButtonUp(nFlags, point);
}
