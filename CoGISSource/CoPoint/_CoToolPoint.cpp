#include "StdAfx.h"
#include "_CoToolPoint.h"
#include <_CoDLG.H>
#include <_CoDB.h>
#include "math.h"
#define pi 3.1415926

//=========================================
//输入点
CoInPutPnt::CoInPutPnt(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveDB = ActiveTB;
	GtePointPro();

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoInPutPnt::~CoInPutPnt()
{
	
}

void CoInPutPnt::LButtonDown(UINT nFlags, CoPnt point)
{

	CoCDC dc(m_ptView,m_Screen);
	switch(m_PointPro.PntStyle)
	{
	case 0:
		dc.DrawCirclePnt(point,m_PointPro);
		break;
	case 1:
		dc.DrawTrianglePnt(point,m_PointPro);
		break;
	case 2:
		dc.DrawSquarePnt(point,m_PointPro);
		break;
	default:
		break;
	}
	//在此调用存储点的函数
	CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	CoFeatureset feature;
	feature.Open(&conn,m_ActiveDB);
	feature.PointAdd(point,m_PointPro);
	feature.Close();
}

void CoInPutPnt::GtePointPro()
{
	//在此调用对画框类获取点参数
	if (!InputPointDLG(m_PointPro))
	{
		m_PointPro.PntColor = RGB(0,0,0);
		m_PointPro.PntLayer = 0;
		m_PointPro.PntRadio = 1;
		m_PointPro.PntStyle = 0;
	}
	 
}

//=============================================
//选择点
CoPnt SelectPoint::m_pnt;
CoPntPro SelectPoint::m_PntPro;
CView* SelectPoint::m_StaticView= NULL;
CoScreen SelectPoint::m_Screen;

SelectPoint::SelectPoint()
{

}

SelectPoint::SelectPoint(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_StaticView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	m_bDraw = FALSE;
	m_Selected = FALSE;


	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

SelectPoint::~SelectPoint()
{
	
}

void SelectPoint::LButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void SelectPoint::LButtonUp(UINT nFlags, CoPnt point)
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
		recorset.GetPoint(m_pnt,m_PntPro);
		CPoint A,B;
		A.x = long(m_pnt.x-m_PntPro.PntRadio);
		A.y = long(m_pnt.y-m_PntPro.PntRadio);
		B.x = long(m_pnt.x+m_PntPro.PntRadio);
		B.y = long(m_pnt.y+m_PntPro.PntRadio);
		if (math.IsPntInRect(m_pnt,m_rect))
		{
			SetTimer(m_ptView->m_hWnd,1,500,TimerProc);
			if (MessageBox(m_ptView->m_hWnd,"选择该点吗?","提示",MB_YESNO | MB_ICONQUESTION)==IDYES)
			{
				KillTimer(m_ptView->m_hWnd,1);
				m_ptView->InvalidateRect(CRect(A,B),TRUE);
				m_Selected = TRUE;
				break;
			}
			KillTimer(m_ptView->m_hWnd,1);
			m_ptView->InvalidateRect(CRect(A,B),TRUE);
		}
		recorset.MoveNext();
		m_pnt.x = m_pnt.y = 0;
	}
	
}

void SelectPoint::MouseMove(UINT nFlags, CoPnt point)
{
	if (m_bDraw)
	{
		CoCDC dc(m_ptView,m_Screen);
		dc.XDrawRectNULLFill(m_ptOrigin,m_perPoint);
		dc.XDrawRectNULLFill(m_ptOrigin,point);
		m_perPoint = point;
	}
	
}

//////////////////////////////////////////////////////////////////////////

MovePoint::MovePoint(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	SelectPoint obj(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectPnt = obj;
	m_Selected = FALSE;
	m_bDraw = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

MovePoint::~MovePoint()
{

}

void MovePoint::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonDown(nFlags,point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = point;
	}
}

void MovePoint::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonUp(nFlags,point);
	else
	{

		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.PointUpdate(m_Point,m_PointPro);
		m_ptView->Invalidate(TRUE);
		m_Point.x = m_Point.y = 0;
		m_bDraw = FALSE;
		m_Selected = FALSE;
		m_SelectPnt.m_Selected = FALSE;
	}

	m_Selected = m_SelectPnt.m_Selected;
	if (m_Selected)
	{
		this->m_Point=m_SelectPnt.m_pnt;
		this->m_PointPro = m_SelectPnt.m_PntPro;
		m_perPoint = m_Point;
	}

}

void MovePoint::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectPnt.MouseMove(nFlags,point);
	if (m_bDraw)
	{
		CoCDC dc(m_ptView,m_Screen);
		dc.XDrawAllPnt(m_perPoint,m_PointPro);
		vector<CoPnt>CoPoint;
		CoPoint.push_back(m_Point);
		CoLog math((point.x-m_ptOrigin.x),(point.y- m_ptOrigin.y));
		math.displayFcn(CoPoint,1);
		m_Point = CoPoint[0];
		CoPoint.clear();
		dc.XDrawAllPnt(m_Point,m_PointPro);
		m_perPoint.x = m_Point.x;
		m_ptOrigin.x = point.x;
		m_perPoint.y = m_Point.y;
		m_ptOrigin.y = point.y;
	}
}

//////////////////////////////////////////////////////////////////////////

CopyPoint::CopyPoint(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	SelectPoint obj(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectPnt = obj;
	m_Selected = FALSE;
	m_bDraw = FALSE;
	index = 0;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CopyPoint::~CopyPoint()
{
	
}

void CopyPoint::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonDown(nFlags,point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = point;
	}
}

void CopyPoint::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonUp(nFlags,point);
	else
	{
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.PointAdd(m_Point,m_PointPro);
		m_ptView->Invalidate(TRUE);
		m_Point.x = m_Point.y = 0;
		m_bDraw = FALSE;
		m_Selected = FALSE;
		m_SelectPnt.m_Selected = FALSE;
		index = 0;
	}
	
	m_Selected = m_SelectPnt.m_Selected;
	if (m_Selected)
	{
		this->m_Point=m_SelectPnt.m_pnt;
		this->m_PointPro = m_SelectPnt.m_PntPro;
		m_perPoint.x = m_Point.x;
		m_perPoint.y = m_Point.y;
	}
	
}

void CopyPoint::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectPnt.MouseMove(nFlags,point);
	if (m_bDraw)
	{
		CoCDC dc(m_ptView,m_Screen);
		if(index)
			dc.XDrawAllPnt(m_perPoint,m_PointPro);
		index++;
		vector<CoPnt>CoPoint;
		CoPoint.push_back(m_Point);
		CoLog math((point.x-m_ptOrigin.x),(point.y- m_ptOrigin.y));
		math.displayFcn(CoPoint,1);
		m_Point = CoPoint[0];
		CoPoint.clear();
		dc.XDrawAllPnt(m_Point,m_PointPro);
		m_perPoint.x = m_Point.x;
		m_perPoint.y= m_Point.y;
		m_ptOrigin.x = point.x;
		m_ptOrigin.y = point.y;
	}
}

//////////////////////////////////////////////////////////////////////////

DeletePoint::DeletePoint(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	SelectPoint obj(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectPnt = obj;
	m_Selected = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

DeletePoint::~DeletePoint()
{
	
}

void DeletePoint::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonDown(nFlags,point);
}

void DeletePoint::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonUp(nFlags,point);
	
	m_Selected = m_SelectPnt.m_Selected;
	if (m_Selected)
	{
		this->m_Point=m_SelectPnt.m_pnt;
		this->m_PointPro = m_SelectPnt.m_PntPro;
		if (MessageBox(m_ptView->m_hWnd,"删除后将无法恢复，确定删除该点吗?","警告",MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.PointDelete(m_PointPro.PntID);
			m_ptView->Invalidate(TRUE);
			m_Point.x = m_Point.y = 0;
			m_Selected = FALSE;
			m_SelectPnt.m_Selected = FALSE;
		}
	}
	
}

void DeletePoint::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectPnt.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////

DelAllPoint::DelAllPoint(CView* ptView,CoDB& DB,CString ActiveTB)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
}

DelAllPoint::~DelAllPoint()
{

}

void DelAllPoint::CoDellAllPnt()
{
	CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	CoFeatureset feature;
	feature.Open(&conn,m_ActiveTB);
	if (MessageBox(m_ptView->m_hWnd,"删除后将无法恢复，确定删除该点吗?","警告",MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		feature.DeleteAll();
		m_ptView->Invalidate(TRUE);
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//修改点参数
ModifyPntPro::ModifyPntPro(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	SelectPoint obj(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectPnt = obj;
	m_Selected = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

ModifyPntPro::~ModifyPntPro()
{
	
}

void ModifyPntPro::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonDown(nFlags,point);
}

void ModifyPntPro::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonUp(nFlags,point);
	
	m_Selected = m_SelectPnt.m_Selected;
	if (m_Selected)
	{
		this->m_Point=m_SelectPnt.m_pnt;
		this->m_PointPro = m_SelectPnt.m_PntPro;

		if (PointPro(m_PointPro))
		{
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.PointUpdate(m_Point,m_PointPro);
			m_ptView->Invalidate(TRUE);
		}
		m_Point.x = m_Point.y = 0;
		m_Selected = FALSE;
		m_SelectPnt.m_Selected = FALSE;
	}
	
}

void ModifyPntPro::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectPnt.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////


CoInputTag::CoInputTag(CView* ptview,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView=ptview;
	m_DB=DB;
	m_ActiveTB=ActiveTB;
	GetTagPro();

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}
CoInputTag::~CoInputTag()
{
}
void CoInputTag::LButtonDown (UINT nFlags, CoPnt point)
{
	if(GetTagStr()==0)
		return;
	CoCDC dc(m_ptView,m_Screen);
	dc.DrawText(point,m_tagpro);
	CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	CoFeatureset feature;
	feature.Open(&conn,m_ActiveTB);
	feature.TagAdd(point,m_tagpro);
}
long CoInputTag::GetTagStr()
{
	//字符串对话框
	if(InputTagStr(m_tagpro)==FALSE)
		return 0;
	else
		return 1;
}
void CoInputTag::GetTagPro()
{
	//字体对话框
	if(InputTagPro(m_tagpro)==FALSE)
	{
		 m_tagpro.TagHeight=20;    //字体高度
		 m_tagpro.TagWidth=10;     //字体宽度
		 m_tagpro.TagAngle=0;  //字体角度
		 m_tagpro.TextAngle=0; //文本角度
		 m_tagpro.TagColor=RGB(0,0,0);//字体颜色
		 m_tagpro.TagOffsite=1;  //字体间距
		 m_tagpro.TagFont="华文楷体";  //字体类型
		 m_tagpro.TagLayer=0; //注记图层
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//=============================================
//选择注释点

CoPnt CoSelectTag::m_pnt;
CoTagPro CoSelectTag::m_TagPro;
CView* CoSelectTag::m_StaticView= NULL;
int CoSelectTag::Tug=0;
CoScreen CoSelectTag::m_Screen;
CoSelectTag::CoSelectTag()
{

}

CoSelectTag::CoSelectTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_StaticView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	m_bDraw = FALSE;
	m_Selected = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoSelectTag::~CoSelectTag()
{
	
}

void CoSelectTag::LButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void CoSelectTag::LButtonUp(UINT nFlags, CoPnt point)
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
		recorset.GetTag(m_pnt,m_TagPro);
		if (math.IsPntInRect(m_pnt,m_rect))
		{
			
			//SetTimer(m_ptView->m_hWnd,1,300,TimerProc);
			//temdc.Ellipse(m_rect.xmin,m_rect.ymin,m_rect.xmax,m_rect.ymax);
			if (MessageBox(m_ptView->m_hWnd,"选择该注释点吗?","提示",MB_YESNO | MB_ICONQUESTION)==IDYES)
			{
				//KillTimer(m_ptView->m_hWnd,1);
				m_ptView->Invalidate(TRUE);
				m_Selected = TRUE;
				break;
			}
			//KillTimer(m_ptView->m_hWnd,1);
			m_ptView->Invalidate(TRUE);
		}
		recorset.MoveNext();
		m_pnt.x = m_pnt.y = 0;
	}
	
}

void CoSelectTag::MouseMove(UINT nFlags, CoPnt point)
{
	if (m_bDraw)
	{
		CoCDC dc(m_ptView,m_Screen);
		dc.XDrawRectNULLFill(m_ptOrigin,m_perPoint);
		dc.XDrawRectNULLFill(m_ptOrigin,point);
		m_perPoint = point;
	}
	
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CoMoveTag::CoMoveTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	CoSelectTag obj(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectTag = obj;
	m_Selected = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoMoveTag::~CoMoveTag()
{
	
}

void CoMoveTag::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonDown(nFlags,point);
}

void CoMoveTag::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonUp(nFlags,point);
	else
	{
		
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.TagUpdate(point,m_TagPro);
		m_ptView->Invalidate(TRUE);
		m_tagPnt.x = m_tagPnt.y = 0;
		m_Selected = FALSE;
		m_SelectTag.m_Selected = FALSE;
	}
	
	m_Selected = m_SelectTag.m_Selected;
	if (m_Selected)
	{
		this->m_tagPnt=m_SelectTag.m_pnt;
		this->m_TagPro = m_SelectTag.m_TagPro;
	}
	
}

void CoMoveTag::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectTag.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CoCopyTag::CoCopyTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	CoSelectTag obj(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectTag = obj;
	m_Selected = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoCopyTag::~CoCopyTag()
{
	
}

void CoCopyTag::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonDown(nFlags,point);
}

void CoCopyTag::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonUp(nFlags,point);
	else
	{
		
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.TagAdd(point,m_TagPro);
		m_ptView->Invalidate(TRUE);
		m_tagPnt.x = m_tagPnt.y = 0;
		m_Selected = FALSE;
		m_SelectTag.m_Selected = FALSE;
	}
	
	m_Selected = m_SelectTag.m_Selected;
	if (m_Selected)
	{
		this->m_tagPnt=m_SelectTag.m_pnt;
		this->m_TagPro = m_SelectTag.m_TagPro;
	}
	
}

void CoCopyTag::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectTag.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////

CoAlterTagPro::CoAlterTagPro(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	CoSelectTag obj(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectTag = obj;
	m_Selected = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoAlterTagPro::~CoAlterTagPro()
{
	
}

void CoAlterTagPro::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonDown(nFlags,point);
}

void CoAlterTagPro::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonUp(nFlags,point);
	
	m_Selected = m_SelectTag.m_Selected;
	if (m_Selected)
	{
		this->m_tagPnt=m_SelectTag.m_pnt;
		this->m_TagPro = m_SelectTag.m_TagPro;
		if (AlterTagProDLG(m_TagPro))
		{
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.TagUpdate(m_tagPnt,m_TagPro);
			m_ptView->Invalidate(TRUE);
		}
		m_tagPnt.x = m_tagPnt.y = 0;
		m_Selected = FALSE;
		m_SelectTag.m_Selected = FALSE;
	}
	
}

void CoAlterTagPro::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectTag.MouseMove(nFlags,point);
}


//////////////////////////////////////////////////////////////////////////

CoAlterTag::CoAlterTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	CoSelectTag obj(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectTag = obj;
	m_Selected = FALSE;

	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoAlterTag::~CoAlterTag()
{
	
}

void CoAlterTag::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonDown(nFlags,point);
}

void CoAlterTag::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonUp(nFlags,point);
	
	m_Selected = m_SelectTag.m_Selected;
	if (m_Selected)
	{
		this->m_tagPnt=m_SelectTag.m_pnt;
		this->m_TagPro = m_SelectTag.m_TagPro;
		CString TagStr;
		if (AlterTagStr(TagStr))
		{
			m_TagPro.TagStr = TagStr;
			CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
			CoFeatureset feature;
			feature.Open(&conn,m_ActiveTB);
			feature.TagUpdate(m_tagPnt,m_TagPro);
			m_ptView->Invalidate(TRUE);
		}
		m_tagPnt.x = m_tagPnt.y = 0;
		m_Selected = FALSE;
		m_SelectTag.m_Selected = FALSE;
	}
	
}

void CoAlterTag::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectTag.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////

CoDelTag::CoDelTag(CView* ptView,CoDB& DB,CString ActiveTB,CoScreen Screen)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	CoSelectTag obj(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectTag = obj;
	m_Selected = FALSE;


	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoDelTag::~CoDelTag()
{
	
}

void CoDelTag::LButtonDown(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonDown(nFlags,point);
}

void CoDelTag::LButtonUp(UINT nFlags, CoPnt point)
{
	if (!m_Selected)
		m_SelectTag.LButtonUp(nFlags,point);

	m_Selected = m_SelectTag.m_Selected;
	if (m_Selected)
	{
		this->m_tagPnt=m_SelectTag.m_pnt;
		this->m_TagPro = m_SelectTag.m_TagPro;
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		if (MessageBox(m_ptView->m_hWnd,"选择该注释点吗?","提示",MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			feature.TagDelete(m_TagPro.ID);
			m_ptView->Invalidate(TRUE);
		}
		m_tagPnt.x = m_tagPnt.y = 0;
		m_Selected = FALSE;
		m_SelectTag.m_Selected = FALSE;
	}
}

void CoDelTag::MouseMove(UINT nFlags, CoPnt point)
{
	if(!m_Selected)
		m_SelectTag.MouseMove(nFlags,point);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CoDelAllTag::CoDelAllTag(CView* ptView,CoDB DB,CString ActiveTB)
{
	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
}
CoDelAllTag::~CoDelAllTag()
{

}

void CoDelAllTag::DelAllTag()
{
	if (MessageBox(m_ptView->m_hWnd,"删除后将无法恢复，确定删除所有注释吗？","警告",MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
		CoFeatureset feature;
		feature.Open(&conn,m_ActiveTB);
		feature.DeleteAll();
		m_ptView->Invalidate(TRUE);
	}

}
