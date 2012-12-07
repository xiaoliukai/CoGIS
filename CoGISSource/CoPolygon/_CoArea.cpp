#include "StdAfx.h"
#include "_CoArea.h"
#include <_CoDLG.H>
#include <_CoDB.h>

//==========================================================
//输入区
CoInputPoly::CoInputPoly(CView* ptview,CoDB& DB,CString& Table,CoScreen Screen)
{
	m_DB = DB;
	m_Table = Table;
	m_bDraw = FALSE;
    m_ptView= ptview;
	GetPolyPro();
	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoInputPoly::~CoInputPoly()
{
	if(m_Poly.size())
		m_Poly.clear();
}

void CoInputPoly::LButtonDown(UINT nFlags, CoPnt point) 
{
	CoCDC dc(m_ptView,m_Screen);
	m_bDraw = TRUE;
	m_PerPoint = m_ptOrigin=point;
	m_Poly.push_back(point);
	if(m_Poly.size()==2&&m_PolyPro.PolyStyle==3)
		dc.XDrawLine(m_Poly[0],m_Poly[1],m_LinePro);

	if(m_Poly.size()==2&&m_PolyPro.PolyStyle==4)
		dc.XDrawLine(m_Poly[0],m_Poly[1],m_LinePro);
}

void CoInputPoly::MouseMove(UINT nFlags, CoPnt point)
{
	CoLog math;
	int Radio;
	CoPnt Center;
	CoCDC dc(m_ptView,m_Screen);
	if (m_bDraw)
	{
		switch(m_PolyPro.PolyStyle)
		{
		case 0:
			dc.XDrawRectNULLFill(m_ptOrigin,m_PerPoint);
			dc.XDrawRectNULLFill(m_ptOrigin,point);
			break;
		case 1:
			dc.XDrawLine(m_ptOrigin,m_PerPoint,m_LinePro);
			dc.XDrawLine(m_ptOrigin,point,m_LinePro);
			break;

		case 2:
			dc.XDrawEillpseNullFill(m_ptOrigin,m_PerPoint,m_LinePro);
			dc.XDrawEillpseNullFill(m_ptOrigin,point,m_LinePro);
			break;

		case 3:
			if(m_Poly.size()==1)
			{
				dc.XDrawLine(m_ptOrigin,m_PerPoint,m_LinePro);
				dc.XDrawLine(m_ptOrigin,point,m_LinePro);
			}
			else
			{
				dc.XDrawLine(m_Poly[0],m_PerPoint,m_LinePro);
				dc.XDrawLine(m_Poly[0],point,m_LinePro);
                
				dc.XDrawLine(m_Poly[1],m_PerPoint,m_LinePro);
				dc.XDrawLine(m_Poly[1],point,m_LinePro);

				math.InnerCircle_Radius(m_Poly[0],m_Poly[1],m_PerPoint,Radio,Center);
				CoPnt Point1,Point2;
				Point1.x = Center.x-Radio;
				Point1.y = Center.y+Radio;
				Point2.x = Center.x+Radio;
				Point2.y = Center.y-Radio;
				dc.XDrawEillpseNullFill(Point1,Point2,m_LinePro);
				math.InnerCircle_Radius(m_Poly[0],m_Poly[1],point,Radio,Center);
				Point1.x = Center.x-Radio;
				Point1.y = Center.y+Radio;
				Point2.x = Center.x+Radio;
				Point2.y = Center.y-Radio;
				dc.XDrawEillpseNullFill(Point1,Point2,m_LinePro);
			}
			break;

		case 4:
			if(m_Poly.size()==1)
			{
				dc.XDrawLine(m_ptOrigin,m_PerPoint,m_LinePro);
				dc.XDrawLine(m_ptOrigin,point,m_LinePro);
			}
			if(m_Poly.size()==2)
			{
				dc.XDrawLine(m_Poly[0],m_PerPoint,m_LinePro);
				dc.XDrawLine(m_Poly[0],point,m_LinePro);
                
				dc.XDrawLine(m_Poly[1],m_PerPoint,m_LinePro);
				dc.XDrawLine(m_Poly[1],point,m_LinePro);
			}
			break;
		default:
			break;
		}
		m_PerPoint = point;
	}
	
}

void CoInputPoly::RButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = FALSE;
	CoCDC dc(m_ptView,m_Screen);
	if (m_PolyPro.PolyStyle==0)
	{
		if(m_Poly.size()==1)
			m_Poly.push_back(point);

		dc.DrawRect(m_Poly[0],m_Poly[1],m_PolyPro);
	}

	if(m_PolyPro.PolyStyle==1&&m_Poly.size())
	{
		dc.XDrawLine(m_Poly[0],point,m_LinePro);
	    dc.DrawPolygon(m_Poly,m_PolyPro);
	}

	if (m_PolyPro.PolyStyle==2)
	{
		if(m_Poly.size()==1)
			m_Poly.push_back(point);

		dc.DrawEillpse(m_Poly[0],m_Poly[1],m_PolyPro);
	}

	if (m_PolyPro.PolyStyle==3&&m_Poly.size())
	{
		dc.XDrawLine(m_Poly[0],m_Poly[1],m_LinePro);
		dc.XDrawLine(m_Poly[1],m_Poly[2],m_LinePro);
		dc.XDrawLine(m_Poly[0],m_Poly[2],m_LinePro);

		CoLog math;
		int Radio;
	    CoPnt Center,Point1,Point2;
		math.InnerCircle_Radius(m_Poly[0],m_Poly[1],m_Poly[2],Radio,Center);
		Point1.x = Center.x-Radio;
		Point1.y = Center.y+Radio;
		Point2.x = Center.x+Radio;
		Point2.y = Center.y-Radio;
		dc.DrawEillpse(Point1,Point2,m_PolyPro);
	}

	if(m_PolyPro.PolyStyle==4&&m_Poly.size())
	{
		dc.DrawPolygon(m_Poly,m_PolyPro);
	}

	if(m_Poly.size())
	{
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_Table);
		feature.PolygonAdd(m_Poly,m_PolyPro);
		feature.Close();
		m_Poly.clear();
	}
}

void CoInputPoly::GetPolyPro()
{
  
	if (!InputPolyDLG(m_PolyPro))
	{
	    m_PolyPro.PolyStyle=0;
		m_PolyPro.PolyColor=RGB(0,0,0);
		m_PolyPro.PolyLayer=0;
		m_PolyPro.PolyFillStyle=0;
	}
	m_LinePro.LineColor = RGB(0,0,0);
	m_LinePro.LineStyle = 0;
	m_LinePro.LineWidth = 1;
}

//==========================================================
//选择区
vector<CoPnt> CoSelectPoly::m_Poly;
CoPolyPro CoSelectPoly::m_PolyPro;
CView* CoSelectPoly::m_staticView= NULL;
CoScreen CoSelectPoly::m_Screen;
bool CoSelectPoly::m_Selected = FALSE;
CoSelectPoly::CoSelectPoly()
{

}
CoSelectPoly::CoSelectPoly(CView* ptview,CoDB& DB,CString& Table,CoScreen Screen,bool ISDrawPnt)
{
	m_isDrawPnt = ISDrawPnt;
	m_ptView = ptview;
	m_staticView = ptview;
	m_DB = DB;
	m_ActiveTB = Table;
	m_bDraw = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoSelectPoly::~CoSelectPoly()
{
	
}

void CoSelectPoly::LButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void CoSelectPoly::LButtonUp(UINT nFlags, CoPnt point)
{
	m_bDraw = FALSE;
	CoCDC dc(m_ptView,m_Screen);
	dc.XDrawRectNULLFill(m_ptOrigin,point);
	if (m_ptOrigin.x>point.x)
	{
		m_rect.xmax = m_ptOrigin.x;
		m_rect.xmin = point.x;
	}
	else
	{
		m_rect.xmin = m_ptOrigin.x;
		m_rect.xmax = point.x;
	}
	
	if (m_ptOrigin.y>point.y)
	{
		m_rect.ymax = m_ptOrigin.y;
		m_rect.ymin = point.y;
	}
	else
	{
		m_rect.ymin = m_ptOrigin.y;
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
		if (m_Poly.size())
			m_Poly.clear();
		recorset.GetPolygon(m_Poly,m_PolyPro);
		if (math.RectAndPoly(m_rect,m_Poly))
		{
			SetTimer(m_ptView->m_hWnd,1,500,TimerProc);
			if (MessageBox(m_ptView->m_hWnd,"选择该区吗?","提示",MB_YESNO | MB_ICONQUESTION)==IDYES)
			{
				KillTimer(m_ptView->m_hWnd,1);
				m_Selected = TRUE;
				dc.DrawAllPoly(m_Poly,m_PolyPro);
				if(m_isDrawPnt)
					dc.DrawPoint(m_Poly);
				break;
			}
			KillTimer(m_ptView->m_hWnd,1);
			dc.DrawAllPoly(m_Poly,m_PolyPro);
		}
		if(m_isDrawPnt)
			dc.DrawPoint(m_Poly);
		recorset.MoveNext();
		m_Poly.clear();
	}

}

void CoSelectPoly::MouseMove(UINT nFlags, CoPnt point)
{
	if (m_bDraw)
	{
		CoCDC dc(m_ptView,m_Screen);
		dc.XDrawRectNULLFill(m_ptOrigin,m_perPoint);
		dc.XDrawRectNULLFill(m_ptOrigin,point);
		m_perPoint = point;
	}

}
void CoSelectPoly::DelSelect()//清空状态
{
	m_Selected = FALSE;
	if(m_Poly.size())
		m_Poly.clear();
}
///==========================================================
//移动区
CoMovePoly::CoMovePoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen)
{
	m_ptView=ptView;
	m_DB = DB;
	m_ActiveTB = Table;
	m_bDraw = FALSE;
	CoSelectPoly obj(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectePoly = obj;
	m_Selected = obj.m_Selected;
	if (m_Selected)
	{
		m_Poly =m_perPoly= m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
	}

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoMovePoly::~CoMovePoly()
{

}

void CoMovePoly::LButtonDown(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonDown(nFlags,point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = point;
	}

}

void CoMovePoly::LButtonUp(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonUp(nFlags,point);

	else
	{
		m_bDraw = FALSE;
		//m_SelectePoly.m_Selected = FALSE;
		//m_Selected = FALSE;
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.PolygonUpdate(m_Poly,m_PolyPro);
		m_Poly.clear();
		m_perPoly.clear();
		m_SelectePoly.m_Selected = FALSE;
		m_ptView->Invalidate(TRUE);
	}

	m_Selected = m_SelectePoly.m_Selected;
	if (m_Selected)
	{
		m_Poly =m_perPoly= m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
	}
}

void CoMovePoly::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.MouseMove(nFlags,point);
	if (m_bDraw)
	{
		CoLog math((point.x-m_ptOrigin.x),(point.y-m_ptOrigin.y));
		CoCDC dc(m_ptView,m_Screen);
		dc.XDrawAllPoly(m_perPoly,m_PolyPro);
		math.displayFcn(m_Poly,1);
		dc.XDrawAllPoly(m_Poly,m_PolyPro);
		m_perPoly = m_Poly;
		m_ptOrigin.x = point.x;
		m_ptOrigin.y = point.y;
	}
}

///==========================================================
//复制区
CoCopyPoly::CoCopyPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen)
{
	m_ptView=ptView;
	m_DB = DB;
	m_ActiveTB = Table;
	m_Selected = FALSE;
	m_bDraw = FALSE;
	CoSelectPoly obj(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectePoly = obj;
	//m_Selected = obj.m_Selected;
	//if (m_Selected)
	//{
	//	m_Poly =m_perPoly= m_SelectePoly.m_Poly;
	//	m_PolyPro = m_SelectePoly.m_PolyPro;
	//}
	index =0;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoCopyPoly::~CoCopyPoly()
{
	
}

void CoCopyPoly::LButtonDown(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonDown(nFlags,point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = point;
	}
	
}

void CoCopyPoly::LButtonUp(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonUp(nFlags,point);
	
	if (m_bDraw)
	{
		m_bDraw = FALSE;
		m_SelectePoly.m_Selected = FALSE;
		m_Selected = FALSE;
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.PolygonAdd(m_Poly,m_PolyPro);
		m_ptView->Invalidate(TRUE);
		index = 0;
	}
	
	m_Selected = m_SelectePoly.m_Selected;
	if (m_Selected)
	{
		m_Poly =m_perPoly= m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
	}
}

void CoCopyPoly::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.MouseMove(nFlags,point);
	if (m_bDraw)
	{
		CoLog math((point.x-m_ptOrigin.x),(point.y-m_ptOrigin.y));
		CoCDC dc(m_ptView,m_Screen);
		if(index)
			dc.XDrawAllPoly(m_perPoly,m_PolyPro);
		index++;
		math.displayFcn(m_Poly,1);
		dc.XDrawAllPoly(m_Poly,m_PolyPro);
		m_perPoly = m_Poly;
		m_ptOrigin.x = point.x;
		m_ptOrigin.y = point.y;
	}
}


///==========================================================
//修改区
CoModifyPoly::CoModifyPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen)
{
	m_ptView=ptView;
	m_DB = DB;
	m_ActiveTB = Table;
	CoSelectPoly obj(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectePoly = obj;
	m_Selected = obj.m_Selected;

	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;

		m_SelectePoly.m_Selected = FALSE;
		m_Selected = FALSE;
		if (PolyGonPro(m_PolyPro))
		{
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.PolygonUpdate(m_Poly,m_PolyPro);
			m_ptView->Invalidate(TRUE);
		}
	}

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoModifyPoly::~CoModifyPoly()
{
	
}

void CoModifyPoly::LButtonDown(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonDown(nFlags,point);
	
}

void CoModifyPoly::LButtonUp(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonUp(nFlags,point);
	
	m_Selected = m_SelectePoly.m_Selected;
	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;

		m_SelectePoly.m_Selected = FALSE;
		m_Selected = FALSE;
		if (PolyGonPro(m_PolyPro))
		{
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.PolygonUpdate(m_Poly,m_PolyPro);
			m_ptView->Invalidate(TRUE);
		}
	}
}

void CoModifyPoly::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.MouseMove(nFlags,point);
}
//边界加点
CoAddPntPoly::CoAddPntPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen)
{
	m_ptView=ptView;
	m_ActiveTB = Table;
	m_DB=DB;
	CoSelectPoly obj(m_ptView,m_DB,m_ActiveTB,Screen,TRUE);
	m_SelectePoly = obj;
	m_Selected = obj.m_Selected;
	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
	}

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}
CoAddPntPoly::~CoAddPntPoly()
{

}

void CoAddPntPoly::LButtonDown(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonDown(nFlags,point);
	else
	{
		m_SelectePoly.m_Selected = FALSE;
		CoLog math;
		if (math.AddPntPoly(point,m_Poly))
		{
			CoCDC dc(m_ptView,m_Screen);
			dc.DrawPoint(point);
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.PolygonUpdate(m_Poly,m_PolyPro);
			//	m_ptView->Invalidate(TRUE);
		}
	}
}

void CoAddPntPoly::LButtonUp(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonUp(nFlags,point);

	m_Selected = m_SelectePoly.m_Selected;
	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
	}
}

void CoAddPntPoly::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.MouseMove(nFlags,point);
}

// 区边界删点 [2/7/2011 shlh]
CoDelPntPoly::CoDelPntPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen)

{
	m_ptView=ptView;
	m_ActiveTB = Table;
	m_DB=DB;
	CoSelectPoly obj(m_ptView,m_DB,m_ActiveTB,Screen,TRUE);
	m_SelectePoly = obj;
	m_Selected = obj.m_Selected;
	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
	}

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoDelPntPoly::~CoDelPntPoly()
{
	if(m_Poly.size())
		m_Poly.clear();
}

void CoDelPntPoly::LButtonDown(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonDown(nFlags,point);
	else
	{
		CoLog math;
		if (math.DelPntPoly(point,m_Poly))
		{
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.PolygonUpdate(m_Poly,m_PolyPro);
			m_Poly.clear();
			m_SelectePoly.m_Selected = FALSE;
			m_ptView->Invalidate(TRUE);
		}
	}
}

void CoDelPntPoly::LButtonUp(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonUp(nFlags,point);

	m_Selected = m_SelectePoly.m_Selected;
	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
	}
}

void CoDelPntPoly::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.MouseMove(nFlags,point);
}

// 区边界移点 [2/7/2011 shlh]
CoMovePntPoly::CoMovePntPoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen)

{
	m_ptView=ptView;
	m_ActiveTB = Table;
	m_DB=DB;
	CoSelectPoly obj(m_ptView,m_DB,m_ActiveTB,Screen,TRUE);
	m_SelectePoly = obj;
	m_Selected = obj.m_Selected;
	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
	}

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;

	m_Pos = -1;
	m_bDraw = FALSE;
}

CoMovePntPoly::~CoMovePntPoly()
{

}

void CoMovePntPoly::LButtonDown(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonDown(nFlags,point);
	else
	{
		CoLog math;
		m_Pos = math.GetPos(point,m_Poly);
		if(m_Pos>=0)
		{
			int length = m_Poly.size();
			m_bDraw = TRUE;
			if(m_Pos==0)
			{
				m_perPoint1 = m_Poly[m_Pos+1];
				m_perPoint2 = m_Poly[length-1];
			}
			if(m_Pos==length-1)
			{
				m_perPoint1 = m_Poly[0];
				m_perPoint2 = m_Poly[m_Pos-1];
			}
			if((m_Pos!=0)&&(m_Pos!=length-1))
			{
				m_perPoint1 = m_Poly[m_Pos-1];
				m_perPoint2 = m_Poly[m_Pos+1];
			}
		}
	}
}

void CoMovePntPoly::LButtonUp(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonUp(nFlags,point);
	if (m_bDraw)
	{
		m_bDraw=FALSE;
		m_Poly[m_Pos]=point;
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.PolygonUpdate(m_Poly,m_PolyPro);
		m_Poly.clear();
		m_SelectePoly.m_Selected = FALSE;
		m_ptView->Invalidate(TRUE);
	}

	m_Selected = m_SelectePoly.m_Selected;
	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
	}
}

void CoMovePntPoly::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.MouseMove(nFlags,point);
	if (m_bDraw)
	{
		CoLinePro Linero;
		Linero.LineColor = m_PolyPro.PolyColor;
		Linero.LineStyle=0;
		Linero.LineWidth=0;
		CoCDC dc(m_ptView,m_Screen);
		int length = m_Poly.size();
		if (m_Pos==0)
		{
			dc.XDrawLine(m_Poly[m_Pos+1],m_perPoint1,Linero);
			dc.XDrawLine(m_Poly[m_Pos+1],point,Linero);

			dc.XDrawLine(m_Poly[length-1],m_perPoint2,Linero);
			dc.XDrawLine(m_Poly[length-1],point,Linero);

		}
		if (m_Pos==length-1)
		{
			dc.XDrawLine(m_Poly[0],m_perPoint1,Linero);
			dc.XDrawLine(m_Poly[0],point,Linero);

			dc.XDrawLine(m_Poly[m_Pos-1],m_perPoint2,Linero);
			dc.XDrawLine(m_Poly[m_Pos-1],point,Linero);
		}
		if((m_Pos!=0)&&(m_Pos!=length-1))
		{
			dc.XDrawLine(m_Poly[m_Pos-1],m_perPoint1,Linero);
			dc.XDrawLine(m_Poly[m_Pos-1],point,Linero);

			dc.XDrawLine(m_Poly[m_Pos+1],m_perPoint2,Linero);
			dc.XDrawLine(m_Poly[m_Pos+1],point,Linero);
		}
	}
	m_perPoint1 = m_perPoint2=point;
}

///==========================================================
//合并区
CoCombPoly::CoCombPoly(CView* ptView)
{
	m_ptView=ptView;
}

CoCombPoly::~CoCombPoly()
{

}

void CoCombPoly::LButtonDown(UINT nFlags, CoPnt point)
{

}

///==========================================================
//挑子区
CoSubPoly::CoSubPoly(CView* ptView)
{
    m_ptView=ptView;
}

CoSubPoly::~CoSubPoly()
{

}

void CoSubPoly::LButtonDown(UINT nFlags, CoPnt point)
{

}

///==========================================================
//删除选中区
CoDeletePoly::CoDeletePoly(CView* ptView,CoDB& DB,CString& Table,CoScreen Screen)
{
	m_ptView=ptView;
	m_DB = DB;
	m_ActiveTB = Table;

	CoSelectPoly obj(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectePoly = obj;
	m_Selected = obj.m_Selected;

	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
		m_SelectePoly.m_Selected = FALSE;
		m_Selected = FALSE;

		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		if (MessageBox(m_ptView->m_hWnd,"删除后将无法恢复，确定删除该区吗?","警告",MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			feature.PolygonDelete(m_PolyPro.PolyID);
			m_ptView->Invalidate(TRUE);
		}
	}
	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoDeletePoly::~CoDeletePoly()
{
	
}

void CoDeletePoly::LButtonDown(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonDown(nFlags,point);
	
}

void CoDeletePoly::LButtonUp(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.LButtonUp(nFlags,point);
	
	m_Selected = m_SelectePoly.m_Selected;
	if (m_Selected)
	{
		m_Poly = m_SelectePoly.m_Poly;
		m_PolyPro = m_SelectePoly.m_PolyPro;
		m_SelectePoly.m_Selected = FALSE;
		m_Selected = FALSE;

		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		if (MessageBox(m_ptView->m_hWnd,"删除后将无法恢复，确定删除该区吗?","警告",MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			feature.PolygonDelete(m_PolyPro.PolyID);
		    m_ptView->Invalidate(TRUE);
		}
	}
}

void CoDeletePoly::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectePoly.MouseMove(nFlags,point);
}


//===============================================
//删除所有区
CoDeleteAllPoly::CoDeleteAllPoly(CView* ptView,CoDB& DB,CString& Table)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = Table;
}

CoDeleteAllPoly::~CoDeleteAllPoly()
{

}

void CoDeleteAllPoly::DelAllPoly()
{
	CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	CoFeatureset feature;
	feature.Open(&conn,m_ActiveTB);
	if (MessageBox(m_ptView->m_hWnd,"删除后将无法恢复，确定删除所有区吗?","警告",MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		feature.DeleteAll();
		m_ptView->Invalidate(TRUE);
	}
}
