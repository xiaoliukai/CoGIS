#include "StdAfx.h"
#include "_CoLine.h"
#include <_CoDLG.H>
#include <_CoDB.h>
//----------------------------------------------------------
CoInputLine::CoInputLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_DB = DB;
	m_ptView = ptView;
	m_ActiveTable = ActiveTable;
	m_bDraw = FALSE;
	GetLinePro();

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}
CoInputLine::~CoInputLine()
{

}
void CoInputLine::LButtonDown (UINT nFlags, CoPnt point)
{
	m_bDraw = TRUE;
	m_PerPoint = m_PtOrigin=point;
	m_Line.push_back(point);
}
void CoInputLine::MouseMove(UINT nFlags, CoPnt point)
{
	//橡皮线
	CoCDC dc(m_ptView,m_Screen);
	if (m_bDraw)
	{
		dc.XDrawLine(m_PtOrigin,m_PerPoint,m_LinePro);
		dc.XDrawLine(m_PtOrigin,point,m_LinePro);
		m_PerPoint = point;
	}
}

void CoInputLine::RButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = FALSE;
	//保存线
	CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	CoFeatureset feature;
	if (m_Line.size())
	{
		feature.Open(&conn,m_ActiveTable);
		feature.LineAdd(m_Line,m_LinePro);
		m_Line.clear();
	}
}

void CoInputLine::GetLinePro()
{
	if (InputLineDLG(m_LinePro)==FALSE)
	{
		m_LinePro.LineColor = RGB(0,0,0);
		m_LinePro.LineLayer = 0;
		m_LinePro.LineStyle = 0;
		m_LinePro.LineWidth = 1;
	}
}

//----------------------------------------------------------
CView* CoSelectLine::m_StaticView = NULL;
CoScreen CoSelectLine::m_Screen;
vector<CoPnt> CoSelectLine::m_Line;
CoLinePro CoSelectLine::m_LinePro;
bool CoSelectLine::m_Selected = FALSE;
CoSelectLine::CoSelectLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen,bool ISDrawPnt)
{
	m_IsDrawPnt = ISDrawPnt;
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;
	m_bDraw = FALSE;
	m_StaticView = ptView;


	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoSelectLine::CoSelectLine()
{

}

CoSelectLine::~CoSelectLine()
{
	
}
void CoSelectLine::LButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = TRUE;
	m_orignpnt = m_perpoint = point;	
}

void CoSelectLine::LButtonUp(UINT nFlags, CoPnt point)
{
	m_bDraw = FALSE;
	CoCDC dc(m_ptView,m_Screen);
	dc.XDrawRectNULLFill(m_orignpnt,point);
	if (m_orignpnt.x>point.x)
	{
		m_rect.xmax = m_orignpnt.x;
		m_rect.xmin = point.x;
	}
	else
	{
		m_rect.xmin = m_orignpnt.x;
		m_rect.xmax = point.x;
	}
	
	if (m_orignpnt.y>point.y)
	{
		m_rect.ymax = m_orignpnt.y;
		m_rect.ymin = point.y;
	}
	else
	{
		m_rect.ymin = m_orignpnt.y;
		m_rect.ymax = point.y;
	}
	CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	CoFeatureset feature;
	feature.Open(&conn,m_ActiveTB);
	CoRecorset recorset;
	recorset.Open(&feature,m_rect);
	CoLog math;
	while(!recorset.CoEOF())
	{
		if(m_Line.size())
			m_Line.clear();
		recorset.GetLine(m_Line,m_LinePro);
		if (math.ISLineInRect(m_rect,m_Line))
		{
			SetTimer(m_ptView->m_hWnd,1,500,TimerProc);
			if (MessageBox(m_ptView->m_hWnd,"选择该线吗?","提示",MB_YESNO | MB_ICONQUESTION)==IDYES)
			{
				dc.DrawLine(m_Line,m_LinePro);
				m_Selected = TRUE;//选择成功
				KillTimer(m_ptView->m_hWnd,1);
				if(m_IsDrawPnt)
					dc.DrawPoint(m_Line);
				break;
			}
			KillTimer(m_ptView->m_hWnd,1);
			//dc.CoInvalidateRect(TRUE,m_Line);
		}
		if(m_IsDrawPnt)
			dc.DrawPoint(m_Line);
		recorset.MoveNext();
		m_Line.clear();
	}
}

void CoSelectLine::MouseMove(UINT nFlags, CoPnt point)
{
	if (m_bDraw)
	{
		CoCDC dc(m_ptView,m_Screen);
		dc.XDrawRectNULLFill(m_orignpnt,m_perpoint);
		dc.XDrawRectNULLFill(m_orignpnt,point);
		m_perpoint = point;
	}
	
}
void CoSelectLine::DelSelect()
{
	m_Selected = FALSE;
	if(m_Line.size())
		m_Line.clear();
}
//////////////////////////////////////////////////////////////////////////

CoMoveLine::CoMoveLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;
	CoSelectLine obj(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectLine = obj;
	m_Selected = m_SelectLine.m_Selected;

	m_bDraw = FALSE;
	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}
	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoMoveLine::~CoMoveLine()
{

}

void CoMoveLine::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags,point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = m_perPoint = point;
	}
}

void CoMoveLine::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags,point);
	else
	{
		CoCDC dc(m_ptView,m_Screen);
		dc.DrawLine(m_line,m_linepro);
		m_bDraw = FALSE;
		//存库
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.LineUpdate(m_line,m_linepro);
		m_line.clear();
		m_perLine.clear();
		m_SelectLine.m_Selected = FALSE;
		m_ptView->Invalidate(TRUE);
	}
	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}
}

void CoMoveLine::MouseMove(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags,point);
	else
	{
		if(m_bDraw)
		{
			CoLog math((point.x-m_ptOrigin.x),(point.y-m_ptOrigin.y));
		    CoCDC dc(m_ptView,m_Screen);
		    dc.XDrawLine(m_perLine,m_linepro);
		    math.displayFcn(m_line,1);
		    dc.XDrawLine(m_line,m_linepro);
		    m_perLine = m_line;
			m_ptOrigin.x = point.x;
			m_ptOrigin.y = point.y;
		}
	}
}

// //----------------------------------------------------------
// //复制线
//////////////////////////////////////////////////////////////////////////

CoCopyLine::CoCopyLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;
	CoSelectLine obj(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectLine = obj;
	this->m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}
	m_bDraw = FALSE;
	index = 0;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoCopyLine::~CoCopyLine()
{
	
}

void CoCopyLine::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags,point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = m_perPoint = point;
	}
}

void CoCopyLine::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags,point);
	else
	{
		CoCDC dc(m_ptView,m_Screen);
		dc.DrawLine(m_line,m_linepro);
		m_bDraw = FALSE;
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.LineAdd(m_line,m_linepro);
		m_line.clear();
		m_perLine.clear();
		m_SelectLine.m_Selected = FALSE;
		index = 0;
		m_ptView->Invalidate(TRUE);
	}
	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}
}

void CoCopyLine::MouseMove(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags,point);
	else
	{
		if(m_bDraw)
		{
			CoLog math((point.x-m_ptOrigin.x),(point.y-m_ptOrigin.y));
			CoCDC dc(m_ptView,m_Screen);
			if(index)
				dc.XDrawLine(m_perLine,m_linepro);
			index++;
			math.displayFcn(m_line,1);
			dc.XDrawLine(m_line,m_linepro);
			m_perLine = m_line;
			m_ptOrigin.x = point.x;
			m_ptOrigin.y = point.y;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

CoCutLine::CoCutLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;
	CoSelectLine obj(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectLine = obj;
	this->m_Selected = m_SelectLine.m_Selected;

	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoCutLine::~CoCutLine()
{
	
}

void CoCutLine::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags,point);
	else
	{
		vector<CoPnt>Line2;
		CoLog math;
		if (math.CutLine(point,m_line,Line2))
		{
			CoCDC dc(m_ptView,m_Screen);
			dc.DrawPoint(point);
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.LineUpdate(m_line,m_linepro);
			feature.LineAdd(Line2,m_linepro);
			m_line.clear();
			Line2.clear();
			m_SelectLine.m_Selected = FALSE;
			m_ptView->Invalidate(TRUE);
		}
	}
}

void CoCutLine::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags,point);

	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}
}

void CoCutLine::MouseMove(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////

CoAddPntLine::CoAddPntLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;
	CoSelectLine obj(m_ptView,m_DB,m_ActiveTB,Screen,TRUE);
	m_SelectLine = obj;
	this->m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
	
}

CoAddPntLine::~CoAddPntLine()
{
	
}

void CoAddPntLine::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags,point);
	else
	{
		vector<CoPnt>Line2;
		CoLog math;
		if (math.AddPntInLine(point,m_line))
		{
			CoCDC dc(m_ptView,m_Screen);
			dc.DrawPoint(point);
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.LineUpdate(m_line,m_linepro);
			m_line.clear();
			m_SelectLine.m_Selected = FALSE;
		}
	}
}

void CoAddPntLine::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags,point);
	
	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
		CoCDC dc(m_ptView,m_Screen);
		dc.DrawPoint(m_line);
	}
}

void CoAddPntLine::MouseMove(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////

CoMovePntLine::CoMovePntLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;
	CoSelectLine obj(m_ptView,m_DB,m_ActiveTB,Screen,TRUE);
	m_SelectLine = obj;
	this->m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}
	m_bDraw = FALSE;
	m_Pos = 0;

	m_Double = TRUE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
	
}

CoMovePntLine::~CoMovePntLine()
{
	
}

void CoMovePntLine::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags,point);
	else
	{
		/*vector<CoPnt>Line2;
		CoLog math;
		m_Pos = math.GetPos(point,m_line);
		if(m_Pos)
		{
			m_bDraw = TRUE;
			m_perPoint1 = m_line[m_Pos-1];
			m_perPoint2 = m_line[m_Pos+1];
		}*/
		CoLog math;
		m_Pos = math.GetPos(point,m_line);
		if(m_Pos>=0)
		{
			m_bDraw = TRUE;
			if(m_Pos==0)
			{
				m_Double = FALSE;
				m_perPoint1 = m_line[m_Pos+1];
			}
			if(m_Pos==m_line.size()-1)
			{
				m_Double = FALSE;
				m_perPoint1 = m_line[m_Pos-1];
			}
			if(m_Double)
			{
				m_perPoint1 = m_line[m_Pos-1];
				m_perPoint2 = m_line[m_Pos+1];
			}
		}
	}
}

void CoMovePntLine::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags,point);
	
	if(m_bDraw)
	{
		//m_ptView->Invalidate(TRUE);
		m_bDraw = FALSE;
		m_line[m_Pos] = point;
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.LineUpdate(m_line,m_linepro);
		m_line.clear();
		m_SelectLine.m_Selected = FALSE;
		m_Double = TRUE;//+
		m_ptView->Invalidate(TRUE);//+
	}
	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line =m_perLine= m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}
}

void CoMovePntLine::MouseMove(UINT nFlags, CoPnt point)
{
	CoCDC dc(m_ptView,m_Screen);
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags,point);
	if (m_bDraw)
	{
		/*dc.XDrawLine(m_line[m_Pos-1],m_perPoint1,m_linepro);
		dc.XDrawLine(m_line[m_Pos-1],point,m_linepro);

		dc.XDrawLine(m_line[m_Pos+1],m_perPoint2,m_linepro);
		dc.XDrawLine(m_line[m_Pos+1],point,m_linepro);
	
		m_perPoint1 = m_perPoint2 = point;*/
		if(m_Double)
		{
			dc.XDrawLine(m_line[m_Pos-1],m_perPoint1,m_linepro);
			dc.XDrawLine(m_line[m_Pos-1],point,m_linepro);

			dc.XDrawLine(m_line[m_Pos+1],m_perPoint2,m_linepro);
			dc.XDrawLine(m_line[m_Pos+1],point,m_linepro);
		}
		else
		{
			if(m_Pos==0)
			{
				dc.XDrawLine(m_line[m_Pos+1],m_perPoint1,m_linepro);
				dc.XDrawLine(m_line[m_Pos+1],point,m_linepro);
			}
			else
			{
				dc.XDrawLine(m_line[m_Pos-1],m_perPoint1,m_linepro);
				dc.XDrawLine(m_line[m_Pos-1],point,m_linepro);
			}
		}

		m_perPoint1 = m_perPoint2 = point;
	}
}

//////////////////////////////////////////////////////////////////////////

CoDelPntLine::CoDelPntLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;
	CoSelectLine obj(m_ptView,m_DB,m_ActiveTB,Screen,TRUE);
	m_SelectLine = obj;
	this->m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line = m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoDelPntLine::~CoDelPntLine()
{
	
}

void CoDelPntLine::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags,point);
	else
	{
		CoLog math;
		if (math.DeletePntLine(point,m_line))
		{
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.LineUpdate(m_line,m_linepro);
			m_line.clear();
			m_SelectLine.m_Selected = FALSE;
			m_ptView->Invalidate(TRUE);
		}
	}
}

void CoDelPntLine::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags,point);
	/*else
		m_ptView->Invalidate(TRUE);*/
	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line = m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
	}
}

void CoDelPntLine::MouseMove(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////

CoDeleteLine::CoDeleteLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;
	CoSelectLine obj(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectLine = obj;
	this->m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line = m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;

		m_line = m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;

		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		if (MessageBox(m_ptView->m_hWnd,"删除后将无法恢复，确定删除吗？","警告",MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			feature.LineDelete(m_linepro.LineID);
			m_ptView->Invalidate(TRUE);
		}
		m_line.clear();
		m_SelectLine.m_Selected = FALSE;
		m_Selected = FALSE;
	}

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoDeleteLine::~CoDeleteLine()
{
	
}

void CoDeleteLine::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags,point);
}

void CoDeleteLine::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags,point);
	
	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line = m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;

		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		if (MessageBox(m_ptView->m_hWnd,"删除后将无法恢复，确定删除吗？","警告",MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			feature.LineDelete(m_linepro.LineID);
			m_ptView->Invalidate(TRUE);
		}
		m_line.clear();
		m_SelectLine.m_Selected = FALSE;
		m_Selected = FALSE;
	}
}

void CoDeleteLine::MouseMove(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////

CoDleAllLine::CoDleAllLine(CView* ptView,CoDB DB,CString ActiveTable)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;

}

CoDleAllLine::~CoDleAllLine()
{

}

void CoDleAllLine::DeleteAllLine()
{
	CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	CoFeatureset feature;
	feature.Open(&conn,m_ActiveTB);
	if (MessageBox(m_ptView->m_hWnd,"删除后将无法恢复，确定删除吗？","警告",MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		feature.DeleteAll();
	}
	m_ptView->Invalidate(TRUE);
}

//////////////////////////////////////////////////////////////////////////

CoAlterLinePro::CoAlterLinePro(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTable;
	CoSelectLine obj(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectLine = obj;
	this->m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line = m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;

		m_line = m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
		CoCDC dc(m_ptView,m_Screen);

		if (LinePro(m_linepro))
		{
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.LineUpdate(m_line,m_linepro);
			m_line.clear();
			m_ptView->Invalidate(TRUE);
		}
		m_Selected = FALSE;
		m_SelectLine.m_Selected = FALSE;
	}


	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoAlterLinePro::~CoAlterLinePro()
{
	
}

void CoAlterLinePro::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags,point);
}

void CoAlterLinePro::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags,point);
	
	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line = m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
		CoCDC dc(m_ptView,m_Screen);

		if (LinePro(m_linepro))
		{
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.LineUpdate(m_line,m_linepro);
			m_line.clear();
			m_ptView->Invalidate(TRUE);
		}
		m_Selected = FALSE;
		m_SelectLine.m_Selected = FALSE;
	}
}

void CoAlterLinePro::MouseMove(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags,point);
}
//自定义量算
CoDistance::CoDistance(CView* ptView,CoScreen Screen)
{
	m_ptView = ptView;
	m_LinePro.LineColor = RGB(0,0,0);
	m_LinePro.LineStyle = 0;
	m_LinePro.LineWidth = 1;
	m_bDraw = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoDistance::~CoDistance()
{

}

void CoDistance::LButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = TRUE;
	m_PerPoint = m_PtOrigin=point;
	m_Line.push_back(point);
}


void CoDistance::MouseMove(UINT nFlags, CoPnt point)
{
	//橡皮线
	CoCDC dc(m_ptView,m_Screen);
	if (m_bDraw)
	{
		dc.XDrawLine(m_PtOrigin,m_PerPoint,m_LinePro);
		dc.XDrawLine(m_PtOrigin,point,m_LinePro);
		m_PerPoint = point;
	}

}
void CoDistance::RButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = FALSE;
	CoLog tMath;
	double dis=tMath.DistanceLine(m_Line);
	CString str;
	str.Format("%f mm",dis);
	MessageBox(m_ptView->m_hWnd,str,"两点距离",MB_OK);
	m_ptView->Invalidate(TRUE);
	m_Line.clear();
}

//已知直线量算
CoDistanceLine::CoDistanceLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen)
{
	m_ptView = ptView;
	m_LinePro.LineColor = RGB(0,0,0);
	m_LinePro.LineStyle = 0;
	m_LinePro.LineWidth = 1;
	CoSelectLine obj(m_ptView,DB,ActiveTable,Screen,FALSE);
	m_SelectLine = obj;
	this->m_Selected = m_SelectLine.m_Selected;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoDistanceLine::~CoDistanceLine()
{

}

void CoDistanceLine::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags,point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = m_perPoint = point;
	}
}

void CoDistanceLine::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags,point);

	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line = m_SelectLine.m_Line;
		m_linepro = m_SelectLine.m_LinePro;
		CoLog tMath;
		double dis=tMath.DistanceLine(m_line);
		CString str;
		str.Format("%f mm",dis);
		MessageBox(m_ptView->m_hWnd,str,"两点距离",MB_OK);
		m_Selected = FALSE;
		m_SelectLine.m_Selected = FALSE;
	}
}

void CoDistanceLine::MouseMove(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags,point);
}