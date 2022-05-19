
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3View.h"
#include "MainFrm.h"

#include "Matrix.h"
#include "Figure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;
int figureNum = 0;
int projNum = 0;
int frameNum = 0;


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_BUTTON_Tri, &CMainFrame::OnButtonTri)
	ON_COMMAND(ID_BUTTON_Cube, &CMainFrame::OnButtonCube)
	ON_COMMAND(ID_BUTTON_Sphe, &CMainFrame::OnButtonSphe)
	ON_COMMAND(ID_BUTTON_Toroid, &CMainFrame::OnButtonToroid)
	ON_COMMAND(ID_MENU_TYPE, &CMainFrame::OnMenuType)
	ON_COMMAND(ID_PROJECTION_PAR, &CMainFrame::OnProjectionPar)
	ON_COMMAND(ID_PROJECTION_PERS, &CMainFrame::OnProjectionPers)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����



void CMainFrame::OnButtonTri()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	figureNum = -1;
	Invalidate();
	//AfxMessageBox(_T("�ﰢ��!"));
}


void CMainFrame::OnButtonCube()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	figureNum = 1;
	//AfxMessageBox(_T("������ü!"));
}


void CMainFrame::OnButtonSphe()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	figureNum = 2;
	//AfxMessageBox(_T("��!"));
}


void CMainFrame::OnButtonToroid() // ���� ��ȯü �׸��� �ڵ�
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	figureNum = 3;

	#pragma region ���� �ڵ�
//	float x = 10; float y = 0; float z = 0;
//	Vertex* vPtr = pTorus(x, y, z, 15, 8);
//	Vertex tor[144] = {};
//	int count = 0;
//	// ���� Torus ���� ��������
//	for (int i = 0; i < 144; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			tor[i] = *(vPtr + count);
//			count++;
//		}
//	}
//	// �׸��� �غ�
//	CClientDC cdc(this);
//	CRect rect;
//	GetClientRect(&rect);
//
//	CPoint cp = (10, 10);
//
//	CDC memDC;
//	CBitmap myBitmap;
//	CBitmap* pOldBitmap;
//
//	memDC.CreateCompatibleDC(&cdc);
//	myBitmap.CreateCompatibleBitmap(&cdc, rect.Width(), rect.Height());
//	pOldBitmap = memDC.SelectObject(&myBitmap);
//
//	// �޸� DC�� �׸���
//	CBrush bgBrush(RGB(0, 0, 255));
//	CBrush* pOldBrush = memDC.SelectObject(&bgBrush);
//	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), /*WHITENESS*/ PATCOPY);
//	memDC.SelectObject(pOldBrush);
//	DeleteObject(bgBrush);
//
//	CPen newPen;
//	newPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
//	CPen* oldPen = memDC.SelectObject(&newPen);
//
//#pragma region �� ��� ��ȯ
//	float camera[3][1] = { { -40 },{ 40 },{ 0 } };
//	float look[3][1] = { { 1 },{ -1 },{ 0 } };
//	float view[4][4] = {};
//	float* viewPtr = ViewMatrix(camera, look/*�� ��� ����µ� ��ü ��ġ�� ũ�� �߿����� ���� �� ���Ƽ� ���߿� ���� ����*/, look);
//	int viewCount = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			view[i][j] = *(viewPtr + viewCount);
//			viewCount++;
//		}
//	}
//
//	float* fPtr;
//	float sample[4][1] = {};
//	// torus �� ������ �� ��� ��ȯ ��Ŵ
//	for (int i = 0; i < 144; i++)
//	{
//		sample[0][0] = tor[i].x;
//		sample[1][0] = tor[i].y;
//		sample[2][0] = tor[i].z;
//		sample[3][0] = 1;
//
//		fPtr = MatrixMulti(view, sample);
//		int torCount = 0;
//
//		tor[i].x = *(fPtr + torCount);
//		torCount++;
//		tor[i].y = *(fPtr + torCount);
//		torCount++;
//		tor[i].z = *(fPtr + torCount);
//		torCount++;
//	}
//#pragma endregion
//#pragma region ���� ��� ��ȯ
//	float proj[4][4] = {};
//	fPtr = ProjectionMatrix(rect.Width(), rect.Height(), 90, 2, 15);
//	count = 0;
//	// ���� ��� ����
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			proj[i][j] = *(fPtr + count);
//			count++;
//		}
//	}
//
//	// �� ��ȯ �� ���� ���� ��ȯ
//	for (int i = 0; i < 144; i++)
//	{
//		sample[0][0] = tor[i].x;
//		sample[1][0] = tor[i].y;
//		sample[2][0] = tor[i].z;
//		sample[3][0] = 1;
//
//		fPtr = MatrixMulti(proj, sample);
//		int torCount = 0;
//		for (int j = 0; j < 3; j++)
//		{
//			tor[i].x = *(fPtr + torCount);
//			torCount++;
//			tor[i].y = *(fPtr + torCount);
//			torCount++;
//			tor[i].z = *(fPtr + torCount);
//			torCount++;
//
//			tor[i].x /= tor[i].z;
//			tor[i].y /= tor[i].z;
//			tor[i].z /= tor[i].z;
//			//if (j == 2)
//			//{
//			//	tor[i][0] /= tor[i][2];
//			//	tor[i][1] /= tor[i][2];
//			//}
//			//torCount++;
//		}
//	}
//#pragma endregion
//#pragma region ��ǥ�� ��ȯ �� �׸���
//	// ���鳢�� �׸���
//	for (int i = 0; i < 144; i++)
//	{
//		if ((i + 1) % 12 == 0)
//		{
//			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 11].x), ToScreenY(rect.Height(), rect.top, tor[i - 11].y));
//			continue;
//		}
//		memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//		memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i+1].x), ToScreenY(rect.Height(), rect.top, tor[i+1].y));
//	}
//	// ������ �����ϱ�
//	for (int i = 0; i < 144; i++)
//	{
//		if (i >= 132)
//		{
//			memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//			memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i - 132].x), ToScreenY(rect.Height(), rect.top, tor[i - 132].y));
//			continue;
//		}
//		memDC.MoveTo(ToScreenX(rect.Width(), rect.left, tor[i].x), ToScreenY(rect.Height(), rect.top, tor[i].y));
//		memDC.LineTo(ToScreenX(rect.Width(), rect.left, tor[i + 12].x), ToScreenY(rect.Height(), rect.top, tor[i +12].y));
//	}
//#pragma endregion
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
#pragma endregion
	//AfxMessageBox(_T("��ȯü!"));
}


void CMainFrame::OnMenuType() 
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (frameNum == 0) frameNum = 1;
	else frameNum = 0;

	Invalidate();
}


void CMainFrame::OnProjectionPar()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	projNum = 1;
	Invalidate();
}


void CMainFrame::OnProjectionPers()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	projNum = 0;
	Invalidate();
}
