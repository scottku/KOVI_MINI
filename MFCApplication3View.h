
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

typedef struct TorusInfo
{
	MyVertex torus[144];
	MyVertex torus_justForClick[144] = {};
	int vertexCount;
	float originTorusLongRadius;
	float originTorusRadius;
	float torusLongRadius;
	float torusRadius;
	int moveX = 0;
	int moveY = 0;
	int moveZ = 0;
	int rotX = 0;
	int rotY = 0;
	int rotZ = 0;
	MyVertex torusOrigin;
	MyVertex torusOrigin_moved;
	bool isClicked = FALSE;
	bool isFront = TRUE;
} TorusInfo;

typedef struct SphereInfo
{
	MyVertex sphere[230];
	MyVertex sphere_justForClick[230] = {};
	int vertexCount;
	float originRadius;
	float radius;
	int moveX = 0;
	int moveY = 0;
	int moveZ = 0;
	int rotX = 0;
	int rotY = 0;
	int rotZ = 0;
	MyVertex sphereOrigin;
	MyVertex sphereOrigin_moved;
	bool isClicked = FALSE;
	bool isFront = TRUE;
} SphereInfo;

typedef struct CubeInfo
{
	MyVertex cube[8];
	MyVertex cube_justForClick[8] = {};
	int vertexCount;
	float originLength;
	float length;
	int moveX = 0;
	int moveY = 0;
	int moveZ = 0;
	int rotX = 0;
	int rotY = 0;
	int rotZ = 0;
	MyVertex cubeOrigin;
	MyVertex cubeOrigin_moved;
	bool isFront = TRUE;
	bool isClicked = FALSE;
} CubeInfo;

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
	float look[3][1];
	float lookX;
	float lookY;
	float lookZ;
	float width, height, left, top, right, bottom;
	float fPlane, nPlane;
	float lightDirX;
	float lightDirY;
	float lightDirZ;
	int cameraRotateX;
	int cameraRotateY;
	int rotateXCount;
	int rotateYCount;
	CPoint moveDirX;
	vector<TorusInfo> v_torusFigure;
	vector<SphereInfo> v_sphereFigure;
	vector<CubeInfo> v_cubeFigure;
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // MFCApplication3View.cpp의 디버그 버전
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

