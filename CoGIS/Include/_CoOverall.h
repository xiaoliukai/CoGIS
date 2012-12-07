#ifndef _CoOverallTransForm_H
#define _CoOverallTransForm_H

#ifndef _CoOverall_EXPORT_
#define Overall  __declspec(dllimport)
#else
#define Overall  __declspec(dllexport)
#endif

#include <_MouseOper.h>
#include "CoStructClass.h"
#include <vector>
#include <_CoLogic.h>
#include <_CoToolPoint.h>
#include <_CoLine.h>
#include <_CoArea.h>
using namespace std;

class Overall CoTopo:public CoBaseTool  
{
public:
	CoTopo(CView* ptView,CoDB DB,CString ActiveTB,int Style,CoScreen Screen);
	virtual ~CoTopo();
	static vector<MyTopo> m_TopoObject;
	void MyAllTopo(vector<MyTopo>TopoObject);
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void  MouseMove(UINT nFlags, CoPnt point);
private:
	CoDB m_DB;
	CString m_ActiveTB;
	bool m_Selected;
	
	vector<CoPnt>m_line;
	CoSelectLine m_SelectLine;
	
	CoPnt m_Point;
	SelectPoint m_SelectPnt;
	
	
	CoPnt m_ptOrigin;
	CoSelectPoly m_SelectePoly;
	
	int m_SelectStyle;
	CoScreen m_Screen;
};

//放大
class Overall CoZoonIn:public CoBaseTool
{
public:
	CoZoonIn();
	CoZoonIn(CView* ptView,CoScreen Screen);
	~CoZoonIn();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	void VPtoDP(long x,long y,double *X,double *Y);
	void DPtoVP(double x,double y,int* X,int* Y);
private:
	CoPnt m_PtOrigin;
	CoPnt m_perPoint;
	bool m_bDraw;
public:
	static CoScreen m_Screen;
};


//缩小
class Overall CoZoonOut:public CoBaseTool
{
public: 
	CoZoonOut();
	CoZoonOut(CView* ptView,CoScreen Screen);
	~CoZoonOut();
	void LButtonDown(UINT nFlags, CoPnt point);
	void VPtoDP(long x,long y,double *X,double *Y);
public:
	static CoScreen m_Screen;
};


//移动
class Overall CoPan:public CoBaseTool
{
public:
	CoPan();
	CoPan(CView* ptView,CoScreen Screen);
	~CoPan();
	void LButtonDown(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void VPtoDP(long x,long y,double *X,double *Y);
private:
	CoPnt m_PtOrigin;
	bool m_bDraw;
public:
	static CoScreen m_Screen;
};

class Overall CoZoom:public CoBaseTool
{
public:
	CoZoom(CView* ptView,CoScreen Screen);
	~CoZoom();
	void MouseWheel(UINT nFlags, short zDelta, CoPnt pt);
public:
	static CoScreen m_Screen;
};


#ifndef _CoOverall_EXPORT_
#ifdef _DEBUG
#pragma comment(lib,"CoAllFirm.lib")
#else
#pragma comment(lib,"CoAllFirm.lib")
#endif
#endif
#endif