
// MainFrm.cpp : CMainFrame 클래스의 구현
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
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
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
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

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


// CMainFrame 메시지 처리기



void CMainFrame::OnButtonTri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	figureNum = -1;
	Invalidate();
	//AfxMessageBox(_T("삼각형!"));
}


void CMainFrame::OnButtonCube()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	figureNum = 1;
	//AfxMessageBox(_T("정육면체!"));
}


void CMainFrame::OnButtonSphe()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	figureNum = 2;
	//AfxMessageBox(_T("구!"));
}


void CMainFrame::OnButtonToroid() // 현재 원환체 그리기 코드
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	figureNum = 3;

	#pragma region 이전 코드
//	float x = 10; float y = 0; float z = 0;
//	Vertex* vPtr = pTorus(x, y, z, 15, 8);
//	Vertex tor[144] = {};
//	int count = 0;
//	// 만든 Torus 정보 가져오기
//	for (int i = 0; i < 144; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			tor[i] = *(vPtr + count);
//			count++;
//		}
//	}
//	// 그리기 준비
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
//	// 메모리 DC에 그리기
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
//#pragma region 뷰 행렬 변환
//	float camera[3][1] = { { -40 },{ 40 },{ 0 } };
//	float look[3][1] = { { 1 },{ -1 },{ 0 } };
//	float view[4][4] = {};
//	float* viewPtr = ViewMatrix(camera, look/*뷰 행렬 만드는데 물체 위치가 크게 중요하지 않은 것 같아서 나중에 지울 예정*/, look);
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
//	// torus 각 점들을 뷰 행렬 변환 시킴
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
//#pragma region 투영 행렬 변환
//	float proj[4][4] = {};
//	fPtr = ProjectionMatrix(rect.Width(), rect.Height(), 90, 2, 15);
//	count = 0;
//	// 투영 행렬 생성
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			proj[i][j] = *(fPtr + count);
//			count++;
//		}
//	}
//
//	// 뷰 변환 한 점들 투영 변환
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
//#pragma region 좌표계 변환 후 그리기
//	// 원들끼리 그리기
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
//	// 옆끼리 연결하기
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
	//AfxMessageBox(_T("원환체!"));
}


void CMainFrame::OnMenuType() 
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (frameNum == 0) frameNum = 1;
	else frameNum = 0;

	Invalidate();
}


void CMainFrame::OnProjectionPar()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	projNum = 1;
	Invalidate();
}


void CMainFrame::OnProjectionPers()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	projNum = 0;
	Invalidate();
}
