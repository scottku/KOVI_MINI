
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:
	float p1[4][1], p2[4][1], p3[4][1], p4[4][1], p5[4][1], p6[4][1], p7[4][1], p8[4][1];

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnButtonTri();
	afx_msg void OnButtonCube();
	afx_msg void OnButtonSphe();
	afx_msg void OnButtonToroid();
	afx_msg void OnMenuType();
	afx_msg void OnProjectionPar();
	afx_msg void OnProjectionPers();
};


