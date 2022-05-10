
// MFCApplication3View.h : CMFCApplication3View 클래스의 인터페이스
//

#pragma once
#include "MFCApplication3Doc.h"
using namespace std;
#include <vector>
#include "Figure.h"
#include "MainFrm.h"
struct MyShape
{
	CPoint ptStart;
	CPoint ptEnd;
};

//typedef struct Vertex
//{
//	float x, y, z;
//	float vertexNormal[4][1];
//} Vertex;

typedef struct TorusInfo
{
	MyVertex torus[144];
	MyVertex torusCopy[144];
	int vertexCount;
} TorusInfo;

class CMFCApplication3View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View);

// 특성입니다.
public:
	CMFCApplication3Doc* GetDocument() const;

// 작업입니다.
public:
	// 테스트용
	float camera[3][1];
	float cameraX;
	float cameraY;
	float cameraZ;
	float width;
	float height;
	float left;
	float top;
	CPoint moveDirX;
	vector<TorusInfo> v_Figure;
	///////////
	CPoint myPoint;
	CPoint C1;
	CPoint C2;
	CPoint C3;
	BOOL m_bDrag;
	MyShape m_shCur;
	vector<MyShape> m_vShape;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCApplication3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFCApplication3View.cpp의 디버그 버전
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

