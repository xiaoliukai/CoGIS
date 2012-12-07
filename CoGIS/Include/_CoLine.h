
#ifndef __CoLineOper_H
#define __CoLineOper_H

#ifndef _CoLine_EXPORT_
#define LineOper  __declspec(dllimport)
#else
#define LineOper  __declspec(dllexport)
#endif

#include <_MouseOper.h>
#include <CoStructClass.h>
#include <_CoLogic.h>

//---------------------------------------------//
//输入线
class LineOper CoInputLine: public CoBaseTool
{
public:
	CoInputLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	~CoInputLine();
	void LButtonDown (UINT nFlags, CoPnt point);
	void RButtonDown(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	void GetLinePro();
private:
	bool m_bDraw;
	CoPnt m_PtOrigin;
	CoPnt m_PerPoint;
	CoLinePro m_LinePro;
    vector<CoPnt>m_Line;
	CoDB m_DB;
	CString m_ActiveTable;
	CoScreen m_Screen;
};
//---------------------------------------------//
//选择线
class LineOper CoSelectLine:public CoBaseTool
{
public:
	CoSelectLine();
	CoSelectLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen,bool ISDrawPnt);
	virtual ~CoSelectLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp (UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	void DelSelect();
public:
	CoRect m_rect;
	CoPnt m_orignpnt;
	CoPnt m_perpoint;
	static vector<CoPnt>m_Line;//存放当前编辑的线
	static CoLinePro m_LinePro;//存放当前编辑的线属性
	CoDB m_DB;
	CString m_ActiveTB;
	bool m_bDraw;
	bool m_IsDrawPnt;
public:
	static bool m_Selected;//选择成功
	static CView* m_StaticView;
	static CoScreen m_Screen;
	
	inline static void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
	{
		CoCDC dc(m_StaticView,m_Screen);
		dc.XDrawLine(m_Line,m_LinePro);
	}
};

//---------------------------------------------//
//移动线
class LineOper CoMoveLine:public CoBaseTool
{
public:
	CoMoveLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoMoveLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
 	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
 	CoLinePro m_linepro;
 	CoSelectLine m_SelectLine;

	CoDB m_DB;
	CString m_ActiveTB;

	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	bool m_bDraw;

	CoScreen m_Screen;
};

//---------------------------------------------//
//复制线
class LineOper CoCopyLine:public CoBaseTool
{
public:
	CoCopyLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoCopyLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	
	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	bool m_bDraw;

	int index;
	CoScreen m_Screen;
};

//---------------------------------------------//
//剪断线
class LineOper CoCutLine:public CoBaseTool
{
public:
	CoCutLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoCutLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};

//---------------------------------------------//
//修改线属性
class LineOper CoAlterLinePro:public CoBaseTool
{
public:
	CoAlterLinePro(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoAlterLinePro();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};
//---------------------------------------------//
//线上加点
class LineOper CoAddPntLine:public CoBaseTool
{
public:
	CoAddPntLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoAddPntLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};

//---------------------------------------------//
//线上移点
class LineOper CoMovePntLine:public CoBaseTool
{
public:
	CoMovePntLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoMovePntLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;

	bool m_bDraw;
	bool m_Double;
	int m_Pos;
	CoPnt m_perPoint1;
	CoPnt m_perPoint2;
	CoScreen m_Screen;
};

//---------------------------------------------//
//线上删点
class LineOper CoDelPntLine:public CoBaseTool
{
public:
	CoDelPntLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoDelPntLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};

//---------------------------------------------//
//删除线

class LineOper CoDeleteLine:public CoBaseTool
{
public:
	CoDeleteLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoDeleteLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};
//删除所有线
class LineOper CoDleAllLine
{
public:
	CoDleAllLine(CView* ptView,CoDB DB,CString ActiveTable);
	virtual ~CoDleAllLine();
	void DeleteAllLine();
private:
	CView* m_ptView;
	CoDB m_DB;
	CString m_ActiveTB;
};

class LineOper CoDistance:public CoBaseTool
{
public:
	CoDistance(CView* ptView,CoScreen Screen);
	~CoDistance();
	void LButtonDown(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	void RButtonDown(UINT nFlags, CoPnt point);
private:
	bool m_bDraw;
	CoPnt m_PtOrigin;
	CoPnt m_PerPoint;
	CoLinePro m_LinePro;
	vector<CoPnt>m_Line;
	CoDB m_DB;
	CString m_ActiveTable;
	CoScreen m_Screen;
};

class LineOper CoDistanceLine:public CoBaseTool
{
public:
	CoDistanceLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	~CoDistanceLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	CoLinePro m_linepro;
	vector<CoPnt>m_line;
	CoSelectLine m_SelectLine;
	bool m_Selected;
	bool m_bDraw;
	CoLinePro m_LinePro;
	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	CoScreen m_Screen;
};

#ifndef _CoLine_EXPORT_
#ifdef _DEBUG
#pragma comment(lib,"CoLine.lib")
#else
#pragma comment(lib,"CoLine.lib")
#endif
#endif
#endif

