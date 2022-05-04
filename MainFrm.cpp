
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
	float a[4][4] = { { 1,2,3,4 },{ 5,6,7,8 },{ 9,10,11,12 },{ 13,14,15,16 } };
	float b[4][4] = { { 1,2,3,4 },{ 5,6,7,8 },{ 9,10,11,12 },{ 13,14,15,16 } };

	float cp[4][4]; // 4x4 ����� ����
	float cm[4][4]; // 4x4 ����� ����
	float cMul[4][4]; // 4x4 ����� ����

	float* ptrCp = MatrixPlus(a, b);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cp[i][j] = *(ptrCp+count);
			count++;
		}
	}

	float* ptrCm = MatrixMinus(a, b);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cm[i][j] = *(ptrCm + count);
			count++;
		}
	}

	float* ptrCMul = MatrixMulti(a, b);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cMul[i][j] = *(ptrCMul + count);
			count++;
		}
	}

	CString strTmp = _T("");
	strTmp.Format(_T("%f + %f = %f"), cp[0][0], cp[2][0], cp[0][0] + cp[2][0]);
	AfxMessageBox(strTmp);
	strTmp.Format(_T("%f + %f = %f"), cm[0][0], cm[2][0], cm[0][0] + cm[2][0]);
	AfxMessageBox(strTmp);
	strTmp.Format(_T("%f + %f = %f"), cMul[0][0], cMul[2][0], cMul[0][0] + cMul[2][0]);
	AfxMessageBox(strTmp);
	//AfxMessageBox(_T("�ﰢ��!"));
}


void CMainFrame::OnButtonCube()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	float a[4][1] = { {2}, {4}, {6}, {0} };
	float* scaleA = MatrixScale(a, 2, 3, 4);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		a[i][0] = *(scaleA + count);
		count++;
	}

	CString strTmp = _T("");
	strTmp.Format(_T("%f - %f - %f - %f"), a[0][0], a[1][0], a[2][0], a[3][0]);
	AfxMessageBox(strTmp);
	//AfxMessageBox(_T("������ü!"));
}


void CMainFrame::OnButtonSphe()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	float a[4][1] = { { 1 },{ 1 },{ 1 },{ 0 } };
	float* rotateA = MatrixRotate(a, 90, 90, 90);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		a[i][0] = *(rotateA + count);
		count++;
	}

	CString strTmp = _T("");
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), a[0][0], a[1][0], a[2][0], a[3][0]);
	AfxMessageBox(strTmp);
	//AfxMessageBox(_T("��!"));
}


void CMainFrame::OnButtonToroid()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	float a[4][1] = { {0}, {0}, {0}, {1} };
	float* transA = MatrixTranslate(a, 5, 10, 15);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		a[i][0] = *(transA + count);
		count++;
	}

	CString strTmp = _T("");
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), a[0][0], a[1][0], a[2][0], a[3][0]);
	AfxMessageBox(strTmp);
	//AfxMessageBox(_T("��ȯü!"));
}


void CMainFrame::OnMenuType()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	float a[4][4] = { {1,0,3,7}, {4,2,0,1}, {7,7,3,0}, {5,0,6,8} };
	float b[4][4] = {};
	float* ptrB = MatrixReverse(a);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			b[i][j] = *(ptrB + count);
			count++;
		}
	}

	CString strTmp = _T("");
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), b[0][0], b[1][0], b[2][0], b[3][0]);
	AfxMessageBox(strTmp);
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), b[0][1], b[1][1], b[2][1], b[3][1]);
	AfxMessageBox(strTmp);
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), b[0][2], b[1][2], b[2][2], b[3][2]);
	AfxMessageBox(strTmp);
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), b[0][3], b[1][3], b[2][3], b[3][3]);
	AfxMessageBox(strTmp);
	//AfxMessageBox(_T("Ÿ��!"));
}


void CMainFrame::OnProjectionPar()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	float camera[3][1] = { {0}, {0}, {500} };
	float material[3][1] = { {0}, {1}, {0} };
	float material4[4][1] = { {0}, {1}, {0}, {1} };
	float look[3][1] = { {0}, {0}, {-1} };
	float b[4][4] = {};
	float* ptrB = ViewMatrix(camera, material, look);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			b[i][j] = *(ptrB + count);
			count++;
		}
	}

	CString strTmp = _T("");
	/*strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), b[0][0], b[1][0], b[2][0], b[3][0]);
	AfxMessageBox(strTmp);
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), b[0][1], b[1][1], b[2][1], b[3][1]);
	AfxMessageBox(strTmp);
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), b[0][2], b[1][2], b[2][2], b[3][2]);
	AfxMessageBox(strTmp);
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), b[0][3], b[1][3], b[2][3], b[3][3]);
	AfxMessageBox(strTmp);*/

	float change[4][1];
	float* ptr = MatrixMulti(b, material4);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
			change[i][0] = *(ptr + count);
			count++;
	}
	strTmp.Format(_T("(%f) - (%f) - (%f) - (%f)"), change[0][0], change[1][0], change[2][0], change[3][0]);
	AfxMessageBox(strTmp);
	//AfxMessageBox(_T("���� ����!"));
}


void CMainFrame::OnProjectionPers()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CClientDC cdc(this);
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

	//memDC.Rectangle(100, 100, 400, 400);

	// �ﰢ�� �׸��� + ĥ�ϱ�

	//CBrush TriBrush(RGB(255, 0, 0));
	//CBrush* OldBrush = memDC.SelectObject(&TriBrush);
	CPen newPen;
	newPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* oldPen = memDC.SelectObject(&newPen);

	float pt1[4][1] = { {-10}, {40}, {10}, {1} };
	float pt2[4][1] = { {-10}, {20}, {10}, {1} };
	float pt3[4][1] = { {10}, {20}, {10}, {1} };
	float pt4[4][1] = { {10}, {40}, {10}, {1} };
	float pt5[4][1] = { { -10 },{ 40 },{ -10 },{ 1 } };
	float pt6[4][1] = { { -10 },{ 20 },{ -10 },{ 1 } };
	float pt7[4][1] = { { 10 },{ 20 },{ -10 },{ 1 } };
	float pt8[4][1] = { { 10 },{ 40 },{ -10 },{ 1 } };

	float camera[3][1] = { {0}, {0}, {40} };
	float look[3][1] = { {0},{0},{-1} };
	float view[4][4] = {};
	float* ptr = ViewMatrix(camera, pt1, look);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			view[i][j] = *(ptr + count);
			count++;
		}
	}

	#pragma region �� ��� ��ȯ
	ptr = MatrixMulti(view, pt1);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt1[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixMulti(view, pt2);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt2[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixMulti(view, pt3);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt3[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixMulti(view, pt4);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt4[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixMulti(view, pt5);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt5[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixMulti(view, pt6);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt6[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixMulti(view, pt7);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt7[i][0] = *(ptr + count);
		count++;
	}
	ptr = MatrixMulti(view, pt8);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt8[i][0] = *(ptr + count);
		count++;
	}
	#pragma endregion
	#pragma region ������ĺ�ȯ
	float proj[4][4] = {};
	ptr = ProjectionMatrix(rect.Width(), rect.Height(), 90, 2, 15);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			proj[i][j] = *(ptr + count);
			count++;
		}
	}

	ptr = MatrixMulti(proj, pt1);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt1[i][0] = *(ptr + count);
		count++;
	}
	pt1[0][0] /= pt1[2][0];
	pt1[1][0] /= pt1[2][0];

	ptr = MatrixMulti(proj, pt2);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt2[i][0] = *(ptr + count);
		count++;
	}
	pt2[0][0] /= pt2[2][0];
	pt2[1][0] /= pt2[2][0];

	ptr = MatrixMulti(proj, pt3);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt3[i][0] = *(ptr + count);
		count++;
	}
	pt3[0][0] /= pt3[2][0];
	pt3[1][0] /= pt3[2][0];

	ptr = MatrixMulti(proj, pt4);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt4[i][0] = *(ptr + count);
		count++;
	}
	pt4[0][0] /= pt4[2][0];
	pt4[1][0] /= pt4[2][0];

	ptr = MatrixMulti(proj, pt5);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt5[i][0] = *(ptr + count);
		count++;
	}
	pt5[0][0] /= pt5[2][0];
	pt5[1][0] /= pt5[2][0];

	ptr = MatrixMulti(proj, pt6);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt6[i][0] = *(ptr + count);
		count++;
	}
	pt6[0][0] /= pt6[2][0];
	pt6[1][0] /= pt6[2][0];

	ptr = MatrixMulti(proj, pt7);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt7[i][0] = *(ptr + count);
		count++;
	}
	pt7[0][0] /= pt7[2][0];
	pt7[1][0] /= pt7[2][0];

	ptr = MatrixMulti(proj, pt8);
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		pt8[i][0] = *(ptr + count);
		count++;
	}
	pt8[0][0] /= pt8[2][0];
	pt8[1][0] /= pt8[2][0];
	#pragma endregion
	/*memDC.BeginPath();
	memDC.MoveTo(pt1[0][0] * (rect.Width() / 2) + rect.left + rect.Width() / 2, (-1) * pt1[1][0] * (rect.Height() / 2) + rect.top + rect.Height() / 2);
	memDC.LineTo(pt2[0][0] * (rect.Width() / 2) + rect.left + rect.Width() / 2, (-1) * pt2[1][0] * (rect.Height() / 2) + rect.top + rect.Height() / 2);
	memDC.LineTo(pt4[0][0] * (rect.Width() / 2) + rect.left + rect.Width() / 2, (-1) * pt4[1][0] * (rect.Height() / 2) + rect.top + rect.Height() / 2);
	memDC.LineTo(pt1[0][0] * (rect.Width() / 2) + rect.left + rect.Width() / 2, (-1) * pt1[1][0] * (rect.Height() / 2) + rect.top + rect.Height() / 2);
	memDC.EndPath();
	memDC.StrokeAndFillPath();*/
	#pragma region ����ü �׸���
	//memDC.BeginPath();
	// �ո�
	memDC.MoveTo(pt1[0][0] * (rect.Width() / 2) + rect.left + rect.Width() / 2, (-1) * pt1[1][0] * (rect.Height() / 2) + rect.top + rect.Height() / 2);
	memDC.LineTo(pt2[0][0] * (rect.Width() / 2) + rect.left + rect.Width() / 2, (-1) * pt2[1][0] * (rect.Height() / 2) + rect.top + rect.Height() / 2);
	memDC.LineTo(pt3[0][0] * (rect.Width() / 2) + rect.left + rect.Width() / 2, (-1) * pt3[1][0] * (rect.Height() / 2) + rect.top + rect.Height() / 2);
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt4[0][0]), ToScreenY(rect.Height(), rect.top, pt4[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt1[0][0]), ToScreenY(rect.Height(), rect.top, pt1[1][0]));
	//
	// �޸�
	memDC.MoveTo(ToScreenX(rect.Width(), rect.left, pt5[0][0]), ToScreenY(rect.Height(), rect.top, pt5[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt8[0][0]), ToScreenY(rect.Height(), rect.top, pt8[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt7[0][0]), ToScreenY(rect.Height(), rect.top, pt7[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt6[0][0]), ToScreenY(rect.Height(), rect.top, pt6[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt5[0][0]), ToScreenY(rect.Height(), rect.top, pt5[1][0]));
	//
	// ������ ����
	memDC.MoveTo(ToScreenX(rect.Width(), rect.left, pt4[0][0]), ToScreenY(rect.Height(), rect.top, pt4[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt3[0][0]), ToScreenY(rect.Height(), rect.top, pt3[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt7[0][0]), ToScreenY(rect.Height(), rect.top, pt7[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt8[0][0]), ToScreenY(rect.Height(), rect.top, pt8[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt4[0][0]), ToScreenY(rect.Height(), rect.top, pt4[1][0]));
	//
	// ���� ����
	memDC.MoveTo(ToScreenX(rect.Width(), rect.left, pt1[0][0]), ToScreenY(rect.Height(), rect.top, pt1[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt5[0][0]), ToScreenY(rect.Height(), rect.top, pt5[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt6[0][0]), ToScreenY(rect.Height(), rect.top, pt6[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt2[0][0]), ToScreenY(rect.Height(), rect.top, pt2[1][0]));
	memDC.LineTo(ToScreenX(rect.Width(), rect.left, pt1[0][0]), ToScreenY(rect.Height(), rect.top, pt1[1][0]));
	#pragma endregion
	//
	//memDC.LineTo(pt1[0][0] * (rect.Width() / 2) + rect.left + rect.Width() / 2, (-1) * pt1[1][0] * (rect.Height() / 2) + rect.top + rect.Height() / 2);
	//memDC.EndPath();
	//memDC.StrokeAndFillPath();

	//memDC.SelectObject(OldBrush);
	//DeleteObject(TriBrush);
	
	cdc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	myBitmap.DeleteObject();
	memDC.DeleteDC();
	ReleaseDC(&cdc);

	//AfxMessageBox(_T("���� ����!"));
}
