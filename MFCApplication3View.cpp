
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

	CBrush newBrush(RGB(0, 0, 255));
	CBrush* oldBrush = memDC.SelectObject(&newBrush);

	for (auto figure : v_Figure)
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
	// ���� ���ÿ����� �� ���� ���������.

	//CString str = _T("");
	//str.Format(_T("%f  %f  %f  %f"), az10[0][0], az10[1][0], az10[2][0], az10[3][0]);
	//AfxMessageBox(str);
	//return;
	// TODO: �ش� ���� �������� ������ �����
	if (figureNum == 3)
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

		#pragma region �� ��� ��ȯ
		//float look[3][1] = { { 1 },{ -1 },{ 0 } };
		//float view[4][4] = {};
		//float* viewPtr = ViewMatrix(camera, look/*�� ��� ����µ� ��ü ��ġ�� ũ�� �߿����� ���� �� ���Ƽ� ���߿� ���� ����*/, look);
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
		//float proj[4][4] = {};
		//float* pPtr = ProjectionMatrix(width, height, 90, 2, 15);
		//count = 0;
		//// ���� ��� ����
		//for (int i = 0; i < 4; i++)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		proj[i][j] = *(fPtr + count);
		//		count++;
		//	}
		//}

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
		v_Figure.push_back(ti);
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
#pragma region 1��и� Ŭ���������� �޽����ڽ��� �������ϴ� �ڵ�
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
