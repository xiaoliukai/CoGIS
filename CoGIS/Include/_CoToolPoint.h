#ifndef __CoToolPoint_H
#define __CoToolPoint_H

#ifndef _CoToolPoint_EXPORT_
#define PointOper  __declspec(dllimport)
#else
#define PointOper  __declspec(dllexport)
#endif

#include <_MouseOper.h>
#include "CoStructClass.h"
#include <_CoLogic.h>

//==================================
//实现输入点
class PointOper CoInPutPnt:public CoBaseTool
{
public:
	CoInPutPnt(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~CoInPutPnt();
	void LButtonDown(UINT nFlags, CoPnt point);
	void GtePointPro();

private:
	CoPnt m_Point;
	CoPntPro m_PointPro;
	CoDB m_DB;
	CString m_ActiveDB;
	CoScreen m_Screen;
};

//=========================================
//选择点
class PointOper SelectPoint:public CoBaseTool
{
public:
	SelectPoint();
	SelectPoint(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~SelectPoint();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);

public:
	CoRect m_rect;
	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	static CoPnt m_pnt;//存放当前编辑的点；
	static CoPntPro m_PntPro;//存放当前编辑的点属性
	static CoScreen m_Screen;
	CoDB m_DB;
	CString m_ActiveTB;
	bool m_bDraw;
	bool m_Selected;
public:
	static CView* m_StaticView;
	
	inline static void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
	{
		CoCDC dc(m_StaticView,m_Screen);
		dc.XDrawAllPnt(m_pnt,m_PntPro);
	}
};
// ===========================================
// 移动点
class PointOper MovePoint:public CoBaseTool
{
public:
	MovePoint(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~MovePoint();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	CoPnt m_Point;
	CoPntPro m_PointPro;
	SelectPoint m_SelectPnt;

	CoDB m_DB;
	CString m_ActiveTB;

	bool m_bDraw;
	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	CoScreen m_Screen;
};

// =========================================
// 复制点
class PointOper CopyPoint:public CoBaseTool
{
public:
	CopyPoint(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~CopyPoint();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	CoPnt m_Point;
	CoPntPro m_PointPro;
	SelectPoint m_SelectPnt;

	int index;
	
	CoDB m_DB;
	CString m_ActiveTB;
	
	bool m_bDraw;
	CoPnt m_ptOrigin;
	CoPnt m_perPoint;

	CoScreen m_Screen;
};

//===========================================
// 修改点参数
class PointOper ModifyPntPro:public CoBaseTool
{
public:
	ModifyPntPro(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~ModifyPntPro();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	CoPnt m_Point;
	CoPntPro m_PointPro;
	SelectPoint m_SelectPnt;
	
	CoDB m_DB;
	CString m_ActiveTB;

	CoScreen m_Screen;
};

// =========================================
// 删除点
class PointOper DeletePoint:public CoBaseTool
{
public:
	DeletePoint(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~DeletePoint();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	CoPnt m_Point;
	CoPntPro m_PointPro;
	SelectPoint m_SelectPnt;
	
	CoDB m_DB;
	CString m_ActiveTB;

	CoScreen m_Screen;
};


// // =========================================
// // 删除所有点
class PointOper DelAllPoint
{
public:
	DelAllPoint(CView* ptView,CoDB& DB,CString ActiveTB);
	~DelAllPoint();
	void CoDellAllPnt();
private:
	CoDB m_DB;
	CString m_ActiveTB;
	CView* m_ptView;
};

//==================================================
//注释操作

class PointOper CoInputTag:public CoBaseTool
{
public:
	CoInputTag(CView* ptview,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~CoInputTag();
	void LButtonDown (UINT nFlags, CoPnt point);
	
	long GetTagStr();
	void GetTagPro();
private:
	CoDB m_DB;
	CString m_ActiveTB;

	CoPnt    m_tagpnt;
	CoTagPro m_tagpro;	

	CoScreen m_Screen;
};
//==================================================
//选择注释

class PointOper CoSelectTag:public CoBaseTool
{
public:
	CoSelectTag();
	CoSelectTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~CoSelectTag();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	
public:
	CoRect m_rect;
	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	static CoPnt m_pnt;//存放当前编辑的注释点；
	static CoTagPro m_TagPro;//存放当前编辑的点属性
	static CoScreen m_Screen;
	CoDB m_DB;
	CString m_ActiveTB;
	bool m_bDraw;
	bool m_Selected;
public:
	static CView* m_StaticView;
	static int Tug;
	inline static void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
	{
		if(Tug==3)
			Tug = 0;
		else
			Tug += 1;
		CoCDC dc(m_StaticView,m_Screen);
		dc.XDrawText(m_pnt,m_TagPro,Tug);
	}
};

//==================================================
//移动注释点
class PointOper CoMoveTag:public CoBaseTool
{
public:
	CoMoveTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~CoMoveTag();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	CoPnt m_tagPnt;
	CoTagPro m_TagPro;
	CoSelectTag m_SelectTag;
	
	CoDB m_DB;
	CString m_ActiveTB;

	CoScreen m_Screen;
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//复制注释点
class PointOper CoCopyTag:public CoBaseTool
{
public:
	CoCopyTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~CoCopyTag();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	CoPnt m_tagPnt;
	CoTagPro m_TagPro;
	CoSelectTag m_SelectTag;
	
	CoDB m_DB;
	CString m_ActiveTB;

	CoScreen m_Screen;
};

//////////////////////////////////////////////////////////////////////////
//选中删除注释点
class PointOper CoDelTag:public CoBaseTool
{
public:
	CoDelTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~CoDelTag();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	CoPnt m_tagPnt;
	CoTagPro m_TagPro;
	CoSelectTag m_SelectTag;
	
	CoDB m_DB;
	CString m_ActiveTB;

	CoScreen m_Screen;	
};

//////////////////////////////////////////////////////////////////////////
//修改注释点参数
class PointOper CoAlterTagPro:public CoBaseTool
{
public:
	CoAlterTagPro(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~CoAlterTagPro();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	CoPnt m_tagPnt;
	CoTagPro m_TagPro;
	CoSelectTag m_SelectTag;
	
	CoDB m_DB;
	CString m_ActiveTB;

	CoScreen m_Screen;
};

//////////////////////////////////////////////////////////////////////////
///修改注释文本
class PointOper CoAlterTag:public CoBaseTool
{
public:
	CoAlterTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen);
	~CoAlterTag();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	CoPnt m_tagPnt;
	CoTagPro m_TagPro;
	CoSelectTag m_SelectTag;
	
	CoDB m_DB;
	CString m_ActiveTB;

	CoScreen m_Screen;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class PointOper CoDelAllTag
{
public:
	CoDelAllTag(CView* ptView,CoDB DB,CString ActiveTB);
	~CoDelAllTag();
	void DelAllTag();

private:
	CoDB m_DB;
	CString m_ActiveTB;
	CView* m_ptView;
};


#ifndef _CoToolPoint_EXPORT_
#ifdef _DEBUG
#pragma comment(lib,"CoPoint.lib")
#else
#pragma comment(lib,"CoPoint.lib")
#endif
#endif
#endif