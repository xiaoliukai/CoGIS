#include "StdAfx.h"
#include "_CoDLG.H"
#include "CoNewPntDlg.h"
#include "CoNewLineDlg.h"
#include "CoNewPolyDlg.h"
#include "CoInputPntDlg.h"
#include "CoInputLineDlg.h"
#include "CoInPutPolyDlg.h"
#include "CoPntPorDlg.h"
#include "CoLineProDlg.h"
#include "CoPolyProDlg.h"

#include "CoInputTagDlg.h"
#include "CoInPutTagStrDlg.h"
#include "CoNewTagDlg.h"
#include "CoAlterTagPro.h"
#include "CoAlterTagStr.h"
//=================================================

//================================================
//输入点对话框
bool DIALOG InputPointDLG(CoPntPro& PointPor)
{
	
	CoInputPntDlg PntDlg;
	if (PntDlg.DoModal()==IDOK)
	{
		PointPor.PntStyle = PntDlg.m_PntStyle;
		PointPor.PntRadio = PntDlg.m_Radio;
		PointPor.PntLayer = PntDlg.m_Layer;
		PointPor.PntColor = PntDlg.m_PntCor;
		return TRUE;
	}
	return FALSE;
}

//================================================
//输入线对话框
bool DIALOG InputLineDLG(CoLinePro& LinePor)
{
	CoInputLineDlg LineDlg;
	if (LineDlg.DoModal()==IDOK)
	{
		LinePor.LineColor = LineDlg.m_LineCor;
		LinePor.LineStyle = LineDlg.m_LineStyle;
		LinePor.LineWidth = LineDlg.m_LineWide;
		LinePor.LineLayer = LineDlg.m_LayerNum;
		return TRUE;
	}
	return FALSE;
}

//================================================
//输入区对话框
bool DIALOG InputPolyDLG(CoPolyPro& PolyPor)
{
	
	CoInPutPolyDlg PolyDlg;
	if (PolyDlg.DoModal()==IDOK)
	{
		PolyPor.PolyFillStyle = PolyDlg.m_FillStyle;
		PolyPor.PolyColor = PolyDlg.m_PolyFillCor;
		PolyPor.PolyStyle = PolyDlg.m_PolyStyle;
		PolyPor.PolyLayer = PolyDlg.m_PolyLayer;
		return TRUE;
	}
	return FALSE;
}
//输入注记对话框
bool DIALOG InputTagPro(CoTagPro& TagPro)
{
	
	CoInputTagDlg TagDlg;
	if (TagDlg.DoModal()==IDOK)
	{
		TagPro.TagHeight=TagDlg.m_tagheight;    //字体高度
		TagPro.TagWidth=TagDlg.m_tagwidth;     //字体宽度
		TagPro.TagAngle=360-TagDlg.m_tagangle;  //字体角度
		TagPro.TextAngle=TagDlg.m_textangle; //文本角度
		TagPro.TagColor=TagDlg.m_tagcolor;//字体颜色
		TagPro.TagOffsite=TagDlg.m_tagoffsite;  //字体间距
		TagPro.TagFont=TagDlg.m_tagfont;  //字体类型
		TagPro.TagLayer=TagDlg.m_taglayer; //注记图层
		return TRUE;
	}
	return FALSE;
}
//================================================
//输入注记字符串对话框
bool DIALOG InputTagStr(CoTagPro& TagPro)
{
	
	CoInPutTagStrDlg StrDlg;
	if (StrDlg.DoModal()==IDOK)
	{
		TagPro.TagStr=StrDlg.m_tagstr;
		return TRUE;
	}
	return FALSE;
}
//===============================================
//点参数查寻修改
bool DIALOG PointPro(CoPntPro& PointPro)
{
	
	CString style;
	switch(PointPro.PntStyle)
	{
	case 0:
		style = "圆点";
		break;
	case 1:
		style = "三角点";
		break;
	case 2:
		style = "放点";
		break;
	default:
		break;
	}
	CoPntPorDlg dlg(PointPro.PntStyle,style,PointPro.PntRadio,
		PointPro.PntColor,PointPro.PntLayer,AfxGetMainWnd());
	if (dlg.DoModal()==IDOK)
	{
		PointPro.PntStyle = dlg.m_PntStyle;
		PointPro.PntRadio = dlg.m_Radio;
		PointPro.PntColor = dlg.m_PntCor;
		PointPro.PntLayer = dlg.m_Layler;
		return TRUE;
	}
	return FALSE;
}

//===============================================
//线属性查询与修改
bool DIALOG LinePro(CoLinePro& LinePro)
{
	
	CString style;
	switch(LinePro.LineStyle)
	{
	case 0:
		style = "实线";
			break;
	case 1:
		style = "虚线";
			break;
	case 2:
		style = "点线";
			break;
	case 3:
		style = "点划线";
			break;
	case 4:
		style = "双点划线";
			break;
	case 5:
		style = "空画笔";
			break;
	default:
		break;
	}

	CoLineProDlg dlg(LinePro.LineStyle,style,
		LinePro.LineWidth,LinePro.LineColor,LinePro.LineLayer,AfxGetMainWnd());
	if (dlg.DoModal()==IDOK)
	{
		LinePro.LineStyle = dlg.m_LineStyle;
		LinePro.LineWidth = dlg.m_EditWide;
		LinePro.LineColor = dlg.m_LineCor;
		LinePro.LineLayer = dlg.m_EditLayer;
		return TRUE;
	}
	return FALSE;
}

//================================================
//区参数查询与修改
bool DIALOG PolyGonPro(CoPolyPro& PolygonPro)
{
	
	CString style;
	CString FillStyle;
	switch(PolygonPro.PolyStyle)
	{
	case 0:
		style = "矩形区";
		break;
	case 1:
		style = "多边形区";
		break;
	case 2:
		style = "椭圆区";
		break;
	case 3:
		style = "三角形内接圆";
		break;
	case 4:
		style = "三角形";
		break;
	default:
		break;
	}
	switch(PolygonPro.PolyFillStyle)
	{
	case 0:
		FillStyle = "水平线";
		break;
	case 1:
		FillStyle = "竖直线";
		break;
	case 2:
		FillStyle = "下斜线";
		break;
	case 3:
		FillStyle = "上斜线";
		break;
	case 4:
		FillStyle = "十字形";
		break;
	case 5:
		FillStyle = "交叉线";
		break;
	case 6:
		FillStyle = "无图案";
		break;
	default:
		break;
	}

	CoPolyPro MyPolyPro= PolygonPro;
	CoPolyProDLG dlg(MyPolyPro,style,FillStyle,AfxGetMainWnd());

	if (dlg.DoModal()==IDOK)
	{
		PolygonPro.PolyStyle = dlg.m_PolyStyle;
		PolygonPro.PolyFillStyle = dlg.m_FillStyle;
		PolygonPro.PolyColor = dlg.m_FillCor;
		PolygonPro.PolyLayer = dlg.m_Layer;
		PolygonPro.PolyArea = dlg.m_Area;
		return TRUE;
	}
	return FALSE;
}

//================================================
//新建点文件
bool DIALOG NewPointDoc(CString* PntName)
{
	
	CoNewPntDlg newPoint;
	if (newPoint.DoModal()==IDOK)
	{
		*PntName = newPoint.m_PntName;
		return TRUE;
	}
	return FALSE;
}

//=================================================
//新建线文件
bool DIALOG NewLineDoc(CString* LineName)
{
	
	CoNewLineDlg NewLine;
	if (NewLine.DoModal()==IDOK)
	{
		*LineName= NewLine.m_NewLine;
		return TRUE;
	}
	return FALSE;
}

//==================================================
//新建区文件
bool DIALOG NewPolyDoc(CString* PolyName)
{
	
	CoNewPolyDlg NewPoly;
	if (NewPoly.DoModal()==IDOK)
	{
		*PolyName = NewPoly.m_NewPolyItem;
		return TRUE;
	}
	return FALSE;
}

//新建字体文件
bool DIALOG NewTagDoc(CString* TagName)
{
	
	CoNewTagDlg NewTag;
	if (NewTag.DoModal()==IDOK)
	{
		*TagName = NewTag.m_TagName;
		return TRUE;
	}
	return FALSE;	
}


bool DIALOG AlterTagProDLG(CoTagPro& TagPro)
{
	
	CoAlterTagPro dlg(TagPro,AfxGetMainWnd());
	if (dlg.DoModal()==IDOK)
	{
		TagPro.TagAngle = dlg.m_lTagAngle;
		TagPro.TagColor = dlg.m_lFontCor;
		TagPro.TagFont = dlg.m_lTagFont;
		TagPro.TagHeight = dlg.m_lTagHeight;
		TagPro.TagWidth = dlg.m_lTagWidth;
		TagPro.TagLayer = dlg.m_lTagLayer;
		TagPro.TagOffsite = dlg.m_lTagOffsite;
		TagPro.TextAngle = dlg.m_lTextAngle;
		return TRUE;
	}
	return FALSE;
}

bool DIALOG AlterTagStr(CString& TagStr)
{
	
	CoAlterTagStr dlg;
	if (dlg.DoModal()==IDOK)
	{
		TagStr = dlg.m_TagStr;
		return TRUE;
	}
	return FALSE;
}
