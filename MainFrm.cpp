
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "MFCApplication3.h"

#include "MainFrm.h"

#include "Matrix.h"

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
	AfxMessageBox(_T("������ü!"));
}


void CMainFrame::OnButtonSphe()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("��!"));
}


void CMainFrame::OnButtonToroid()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("��ȯü!"));
}


void CMainFrame::OnMenuType()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("Ÿ��!"));
}


void CMainFrame::OnProjectionPar()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("���� ����!"));
}


void CMainFrame::OnProjectionPers()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("���� ����!"));
}
