#ifndef __CoPolygon_H
#define __CoPolygon_H

#include <_MouseOper.h>
#include "CoStructClass.h"
#include <vector>
#include <_CoLogic.h>
using namespace std;

#ifndef __CoPolygon_EXPORT_
#define PolyOper  __declspec(dllimport)
#else
#define PolyOper  __declspec(dllexport)
#endif

//=============================================
//输入区
class PolyOper CoInputPoly : public CoBaseTool
{
public:
	CoInputPoly(CView* ptview,CoDB& DB,CString& Table,CoScreen Screen);
	~CoInputPoly();

	void LButtonDown(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	void RButtonDown(UINT nFlags, CoPnt point);
	void GetPolyPro(); //获取区属性 
private:
	bool m_bDraw;
	CoPolyPro m_PolyPro;//存属性
	CoPnt m_ptOrigin;
	CoPnt m_PerPoint;
	CoLinePro m_LinePro;
    vector<CoPnt>m_Poly;
	CoDB m_DB;
	CString m_Table;

	CoScreen m_Screen;
};

//=============================================
//选择区
class PolyOper CoSelectPoly : public CoBaseTool
{
public:
	CoSelectPoly();
	CoSelectPoly(CView* ptview,CoDB& DB,CString& Table,CoScreen Screen,bool ISDrawPnt);
    ~CoSelectPoly();

	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);

	void DelSelect();

public:
	bool m_isDrawPnt;
	CoRect m_rect;
	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	bool m_bDraw;
	CoDB m_DB;
	CString m_ActiveTB;
	static vector<CoPnt>m_Poly;
	static CoPolyPro m_PolyPro;
	static CView* m_staticView;
	static CoScreen m_Screen;
	static 	bool m_Selected;

public:
	inline static void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
	{
		static CoPolyPro pro;
		CoCDC dc(m_staticView,m_Screen);
		dc.XDrawAllPoly(m_Poly,m_PolyPro);
	}
};

//=============================================
//移动区
class PolyOper CoMovePoly : public CoBaseTool
{
public:
	CoMovePoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen);
	~CoMovePoly();
	
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	vector<CoPnt> m_Poly;
	CoPolyPro m_PolyPro;
	CoDB m_DB;
	CString m_ActiveTB;
	bool m_Selected;
	bool m_bDraw;

	vector<CoPnt>m_perPoly;
	CoPnt m_ptOrigin;

	CoSelectPoly m_SelectePoly;

	CoScreen m_Screen;
};

//=========================================
//复制区
class PolyOper CoCopyPoly : public CoBaseTool
{
public:
	CoCopyPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen);
	~CoCopyPoly();
	
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	vector<CoPnt> m_Poly;
	CoPolyPro m_PolyPro;
	CoDB m_DB;
	CString m_ActiveTB;
	bool m_Selected;
	bool m_bDraw;
	
	vector<CoPnt>m_perPoly;
	CoPnt m_ptOrigin;
	int index;
	CoSelectPoly m_SelectePoly;

	CoScreen m_Screen;
};

//==========================================
//修改区

class PolyOper CoModifyPoly : public CoBaseTool
{
public:
	CoModifyPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen);
	~CoModifyPoly();
	
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	vector<CoPnt> m_Poly;
	CoPolyPro m_PolyPro;
	CoDB m_DB;
	CString m_ActiveTB;
	bool m_Selected;
	CoSelectPoly m_SelectePoly;

	CoScreen m_Screen;
};

//边界加点
class PolyOper CoAddPntPoly:public CoBaseTool
{
public:
	CoAddPntPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen);
	~CoAddPntPoly();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	vector<CoPnt> m_Poly;
	CoPolyPro m_PolyPro;
	CString m_ActiveTB;
	bool m_Selected;
	CoDB m_DB;
	CoSelectPoly m_SelectePoly;

	CoScreen m_Screen;
};

// 区边界删点 [2/7/2011 shlh]
class PolyOper CoDelPntPoly:public CoBaseTool
{
public:
	CoDelPntPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen);
	~CoDelPntPoly();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	vector<CoPnt> m_Poly;
	CoPolyPro m_PolyPro;
	CString m_ActiveTB;
	bool m_Selected;
	CoSelectPoly m_SelectePoly;
	CoDB m_DB;
	CoScreen m_Screen;
};

// 区边界移点 [2/7/2011 shlh]

class PolyOper CoMovePntPoly:public CoBaseTool
{
public:
	CoMovePntPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen);
	~CoMovePntPoly();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);

private:
	vector<CoPnt> m_Poly;
	CoPolyPro m_PolyPro;
	CString m_ActiveTB;
	bool m_Selected;
	CoSelectPoly m_SelectePoly;
	CoDB m_DB;
	CoScreen m_Screen;
	bool m_bDraw;
	CoPnt m_perPoint1;
	CoPnt m_perPoint2;
	int m_Pos;
};


//==========================================
//合并区
class PolyOper CoCombPoly : public CoBaseTool
{
public:
	CoCombPoly(CView* ptView);
	~CoCombPoly();
	void LButtonDown(UINT nFlags, CoPnt point);
private:
};

//===============================================
//挑子区
class PolyOper CoSubPoly : public CoBaseTool
{
public:
	CoSubPoly(CView* ptView);
	~CoSubPoly();
    void LButtonDown(UINT nFlags, CoPnt point);
private:
	CoPolyPro m_PolyPro;
};

//===============================================
//删除选中区
class PolyOper CoDeletePoly : public CoBaseTool
{
public:
	CoDeletePoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen);
	~CoDeletePoly();
	
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	vector<CoPnt> m_Poly;
	CoPolyPro m_PolyPro;
	CoDB m_DB;
	CString m_ActiveTB;
	bool m_Selected;

	CoSelectPoly m_SelectePoly;

	CoScreen m_Screen;
};

//===============================================
//删除所有区
class PolyOper CoDeleteAllPoly
{
public:
	CoDeleteAllPoly(CView* ptView,CoDB& DB,CString& Table);
	virtual ~CoDeleteAllPoly();
	void DelAllPoly();
private:
	CoDB m_DB;
	CView* m_ptView;
	CString m_ActiveTB;

};

//===============================================

#ifndef __CoPolygon_EXPORT_
#ifdef _DEBUG
#pragma comment(lib,"CoArea.lib")
#else
#pragma comment(lib,"CoArea.lib")
#endif
#endif
#endif