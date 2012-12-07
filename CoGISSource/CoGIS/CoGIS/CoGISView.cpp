
// CoGISView.cpp : CCoGISView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CoGIS.h"
#endif
#include "MainFrm.h"
#include "CoGISDoc.h"
#include "CoGISView.h"
#include "CoStructClass.h"
#include "DataExchange.h"
//导入自定义头文件
#include "_CoToolPoint.h"
#include "_CoLine.h"
#include "_CoArea.h"
#include "_CoLogic.h"
#include "_CoDLG.H"
#include "_CoDB.h"
#include "_CoOverall.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoGISView

IMPLEMENT_DYNCREATE(CCoGISView, CView)

BEGIN_MESSAGE_MAP(CCoGISView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCoGISView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CESHI, &CCoGISView::OnCeshi)
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_COMMAND(ID_INPUT_POINT, &CCoGISView::OnInputPoint)
	ON_COMMAND(ID_SELECT_POINT, &CCoGISView::OnSelectPoint)
	ON_COMMAND(ID_MOVE_POINT, &CCoGISView::OnMovePoint)
	ON_COMMAND(ID_COPY_POINT, &CCoGISView::OnCopyPoint)
	ON_COMMAND(ID_RE_POINTPRO, &CCoGISView::OnRePointpro)
	ON_COMMAND(ID_DEL_POINT, &CCoGISView::OnDelPoint)
	ON_COMMAND(ID_DELALL_POINT, &CCoGISView::OnDelallPoint)
	ON_COMMAND(ID_INPUT_LINE, &CCoGISView::OnInputLine)
	ON_COMMAND(ID_SELECT_LINE, &CCoGISView::OnSelectLine)
	ON_COMMAND(ID_MOVE_LINE, &CCoGISView::OnMoveLine)
	ON_COMMAND(ID_COPY_LINE, &CCoGISView::OnCopyLine)
	ON_COMMAND(ID_EDIT_LINEPRO, &CCoGISView::OnEditLinepro)
	ON_COMMAND(ID_CUT_LINE, &CCoGISView::OnCutLine)
	ON_COMMAND(ID_ADDPNT_LINE, &CCoGISView::OnAddpntLine)
	ON_COMMAND(ID_MOVEPNT_ONLINE, &CCoGISView::OnMovepntOnline)
	ON_COMMAND(ID_DELPNT_ONLINE, &CCoGISView::OnDelpntOnline)
	ON_COMMAND(ID_DEL_LINE, &CCoGISView::OnDelLine)
	ON_COMMAND(ID_DELALL_LINE, &CCoGISView::OnDelallLine)
	ON_COMMAND(ID_INPUT_POLYGON, &CCoGISView::OnInputPolygon)
	ON_COMMAND(ID_SELECT_POLY, &CCoGISView::OnSelectPoly)
	ON_COMMAND(ID_COPY_POLY, &CCoGISView::OnCopyPoly)
	ON_COMMAND(ID_MOVE_POLY, &CCoGISView::OnMovePoly)
	ON_COMMAND(ID_REPOLY_PRO, &CCoGISView::OnRepolyPro)
	ON_COMMAND(ID_DEL_POLY, &CCoGISView::OnDelPoly)
	ON_COMMAND(ID_DELALL_POLY, &CCoGISView::OnDelallPoly)
	ON_COMMAND(ID_INPUT_TAG, &CCoGISView::OnInputTag)
	ON_COMMAND(ID_SELECT_TAG, &CCoGISView::OnSelectTag)
	ON_COMMAND(ID_MOVE_TAG, &CCoGISView::OnMoveTag)
	ON_COMMAND(ID_COPY_TAG, &CCoGISView::OnCopyTag)
	ON_COMMAND(ID_ALTER_TAGTEXT, &CCoGISView::OnAlterTagtext)
	ON_COMMAND(ID_RE_TAGGPRO, &CCoGISView::OnReTaggpro)
	ON_COMMAND(ID_DEL_TAG, &CCoGISView::OnDelTag)
	ON_COMMAND(ID_DELALL_TAG, &CCoGISView::OnDelallTag)
	ON_COMMAND(ID_TOPO_SELPNT, &CCoGISView::OnTopoSelpnt)
	ON_COMMAND(ID_TOPO_SELLINE, &CCoGISView::OnTopoSelline)
	ON_COMMAND(ID_TOPO_SELPOLY, &CCoGISView::OnTopoSelpoly)
	ON_COMMAND(ID_GET_DISTANCE, &CCoGISView::OnGetDistance)
	ON_COMMAND(ID_ZOON_IN, &CCoGISView::OnZoonIn)
	ON_COMMAND(ID_ZOON_OUT, &CCoGISView::OnZoonOut)
	ON_COMMAND(ID_PAN, &CCoGISView::OnPan)
	ON_COMMAND(ID_MICFW, &CCoGISView::OnMicfw)
	ON_COMMAND(ID_FRASH, &CCoGISView::OnFrash)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_CLEAR_LINE_STATE, &CCoGISView::OnClearLineState)
	ON_COMMAND(ID_CLEAR_AREA_STATE, &CCoGISView::OnClearAreaState)
	ON_COMMAND(ID_ADD_PNT_AREA, &CCoGISView::OnAddPntArea)
	ON_COMMAND(ID_MOVE_PNT_AREA, &CCoGISView::OnMovePntArea)
	ON_COMMAND(ID_DEL_PNT_AREA, &CCoGISView::OnDelPntArea)
	ON_COMMAND(ID_DIS_LINE, &CCoGISView::OnDisLine)
END_MESSAGE_MAP()

// CCoGISView 构造/析构

CCoGISView::CCoGISView()
{
	// TODO: 在此处添加构造代码
	m_BaseOper = NULL;
	m_CoScreen.sx=0;
	m_CoScreen.sy=0;
	m_CoScreen.blc=1;
	m_MapMode = 1;
	m_OverAllOper = 0;//整体操作
	ShStatae=0;//设置状态显示
	m_CurrentOper=_T("无操作");
	//初始显示表设置
	setIniState();//设置激活表的状态
}

CCoGISView::~CCoGISView()
{
}

BOOL CCoGISView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCoGISView 绘制
void CCoGISView::OnDraw(CDC* pDC)
{
	CCoGISDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	if (ShStatae)
	{
		ShowState();
	}
	ShStatae=1;
	DisPaly();
}


// CCoGISView 打印


void CCoGISView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCoGISView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCoGISView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCoGISView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}
// CCoGISView 诊断

#ifdef _DEBUG
void CCoGISView::AssertValid() const
{
	CView::AssertValid();
}

void CCoGISView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCoGISDoc* CCoGISView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCoGISDoc)));
	return (CCoGISDoc*)m_pDocument;
}
#endif //_DEBUG


// CCoGISView 消息处理程序
//鼠标相应函数
void CCoGISView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	/*ClientToScreen(&point);
	OnContextMenu(this, point);*/
}

void CCoGISView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CCoGISView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//实时显示坐标位置
	CoPnt MyPoint;
	VPtoDP(point.x,point.y,&MyPoint.x,&MyPoint.y);
	//==========================================================
	//显示屏幕坐标
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CMFCStatusBar&pStatus = pFrame->GetStatusBar();
	CString str;
	str.Format(_T("x=%3f,y=%3f"),MyPoint.x,MyPoint.y);
	pStatus.SetPaneText(pStatus.CommandToIndex(IDS_MOUSE_POINT), str,TRUE);
	CView::OnMouseMove(nFlags, point);
	//光标显示
	if(m_OverAllOper==1)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_FD); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==2)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_SX); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==3)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_YD); 
		SetCursor(hCursor);
	}
	//=======重载新的操作========
	if (m_BaseOper)
		m_BaseOper->MouseMove(nFlags,MyPoint);
}

void CCoGISView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_OverAllOper==1)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_FD); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==2)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_SX); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==3)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_YD); 
		SetCursor(hCursor);
	}
	CoPnt MyPoint;
	VPtoDP(point.x,point.y,&MyPoint.x,&MyPoint.y);
	if(m_BaseOper)
		m_BaseOper->LButtonDown(nFlags,MyPoint);
	CView::OnLButtonDown(nFlags, point);
}

void CCoGISView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_OverAllOper==1)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_FD); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==2)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_SX); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==3)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_YD); 
		SetCursor(hCursor);
	}
	CoPnt MyPoint;
	VPtoDP(point.x,point.y,&MyPoint.x,&MyPoint.y);
	if(m_BaseOper)
		m_BaseOper->LButtonUp(nFlags,MyPoint);
	CView::OnLButtonUp(nFlags, point);
}

void CCoGISView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CoPnt MyPoint;
	VPtoDP(point.x,point.y,&MyPoint.x,&MyPoint.y);
	if (m_BaseOper)
		m_BaseOper->RButtonDown(nFlags,MyPoint);
	CView::OnRButtonDown(nFlags, point);
}
//响应鼠标滚轮放大缩小
BOOL CCoGISView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DelectMouseOper();
	m_CurrentOper =_T("滚轮放大缩小");
	ShowState();
	CoPnt MyPnt;
	VPtoDP(pt.x,pt.y,&MyPnt.x,&MyPnt.y);
	CoZoom Zoom(this,m_CoScreen);
	Zoom.MouseWheel(nFlags,zDelta,MyPnt);
	m_CoScreen=Zoom.m_Screen;

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CCoGISView::OnCeshi()
{
}



//===========点菜单的相关操作============//
//输入点
void CCoGISView::OnInputPoint()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("输入点");
		ShowState();
		m_BaseOper = new CoInPutPnt(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到点文件,请新建或激活已有的点文件！","提示",MB_OK |MB_ICONASTERISK);
}

//选择点
void CCoGISView::OnSelectPoint()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("选择点");
		ShowState();
		m_BaseOper = new SelectPoint(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到点文件,请新建或激活已有的点文件！","提示",MB_OK |MB_ICONASTERISK);
}

//移动点
void CCoGISView::OnMovePoint()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("移动点");
		ShowState();
		m_BaseOper = new MovePoint(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到点文件,请新建或激活已有的点文件！","提示",MB_OK |MB_ICONASTERISK);

}

//复制点
void CCoGISView::OnCopyPoint()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("复制点");
		ShowState();
		m_BaseOper = new CopyPoint(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到点文件,请新建或激活已有的点文件！","提示",MB_OK |MB_ICONASTERISK);

}

//修改点参数
void CCoGISView::OnRePointpro()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("修改点参数");
		ShowState();
		m_BaseOper = new ModifyPntPro(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到点文件,请新建或激活已有的点文件！","提示",MB_OK |MB_ICONASTERISK);

}

//删除点
void CCoGISView::OnDelPoint()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("删除点");
		ShowState();
		m_BaseOper = new DeletePoint(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到点文件,请新建或激活已有的点文件！","提示",MB_OK |MB_ICONASTERISK);

}

//删除所有点
void CCoGISView::OnDelallPoint()
{
	// TODO: 在此添加命令处理程序代码
	if(isPntActive())
	{
		m_CurrentOper=_T("删除所有点");
		ShowState();
		DelAllPoint del(this,m_DB,getPntAct());
		del.CoDellAllPnt();
	}
	else
		MessageBox("没有找到点文件,请新建或激活已有的点文件！","提示",MB_OK |MB_ICONASTERISK);

}

//==============线菜单相关操作===========//

//输入线
void CCoGISView::OnInputLine()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("输入线");
		ShowState();
		m_BaseOper = new CoInputLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);

}

//选择线
void CCoGISView::OnSelectLine()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("选择线");
		ShowState();
		m_BaseOper = new CoSelectLine(this,m_DB,getLineAct(),m_CoScreen,TRUE);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);

}

//清空选择线状态
void CCoGISView::OnClearLineState()
{
	// TODO: 在此添加命令处理程序代码
	m_CurrentOper ="清除选线";
	ShowState();
	CoSelectLine DelSelect;
	DelSelect.DelSelect();
	Invalidate(TRUE);
}

//移动线
void CCoGISView::OnMoveLine()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("移动线");
		ShowState();
		m_BaseOper = new CoMoveLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//复制线
void CCoGISView::OnCopyLine()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("复制线");
		ShowState();
		m_BaseOper = new CoCopyLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//编辑线参数
void CCoGISView::OnEditLinepro()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("编辑线参数");
		ShowState();
		m_BaseOper = new CoAlterLinePro(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//剪断线
void CCoGISView::OnCutLine()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("剪断线");
		ShowState();
		m_BaseOper = new CoCutLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//线上加点
void CCoGISView::OnAddpntLine()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("线上加点");
		ShowState();
		m_BaseOper = new CoAddPntLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//线上移点
void CCoGISView::OnMovepntOnline()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
		{
			m_CurrentOper=_T("线上移点");
			ShowState();
			m_BaseOper = new CoMovePntLine(this,m_DB,getLineAct(),m_CoScreen);
		}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//线上删点
void CCoGISView::OnDelpntOnline()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("线上删点");
		ShowState();
		m_BaseOper = new CoDelPntLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//删除线
void CCoGISView::OnDelLine()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("删除线");
		ShowState();
		m_BaseOper = new CoDeleteLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//删除所有线
void CCoGISView::OnDelallLine()
{
	// TODO: 在此添加命令处理程序代码
	if(isLineActive())
	{
		m_CurrentOper=_T("删除所有线");
		ShowState();
		CoDleAllLine del(this,m_DB,getLineAct());
		del.DeleteAllLine();
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//==============区菜单相关操作==============//

//输入区
void CCoGISView::OnInputPolygon()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("输入区");
		ShowState();
		m_BaseOper = new CoInputPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);
}

//选择区
void CCoGISView::OnSelectPoly()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("选择区");
		ShowState();
		m_BaseOper = new CoSelectPoly(this,m_DB,getAreaAct(),m_CoScreen,TRUE);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);

}

//复制区
void CCoGISView::OnCopyPoly()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("复制区");
		ShowState();
		m_BaseOper = new CoCopyPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);

}

//移动区
void CCoGISView::OnMovePoly()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("移动区");
		ShowState();
		m_BaseOper = new CoMovePoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);

}

//修改区参数
void CCoGISView::OnRepolyPro()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("修改区参数");
		ShowState();
		m_BaseOper = new CoModifyPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);

}

//清空选区状态
void CCoGISView::OnClearAreaState()
{
	// TODO: 在此添加命令处理程序代码
	m_CurrentOper =_T("清除选区");
	ShowState();
	CoSelectPoly DelSelect;
	DelSelect.DelSelect();
	Invalidate(TRUE);
}

//边界加点
void CCoGISView::OnAddPntArea()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if (isAreaActive())
	{
		m_CurrentOper =_T("边界加点");
		ShowState();
		m_BaseOper=new CoAddPntPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);
}

//边界移点
void CCoGISView::OnMovePntArea()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if (isAreaActive())
	{
		m_CurrentOper =_T("边界移点");
		ShowState();
		m_BaseOper=new CoMovePntPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);
}

//边界删点
void CCoGISView::OnDelPntArea()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if (isAreaActive())
	{
		m_CurrentOper =_T("边界删点");
		ShowState();
		m_BaseOper=new CoDelPntPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);
}
//删除区
void CCoGISView::OnDelPoly()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("删除区");
		ShowState();
		m_BaseOper = new CoDeletePoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);

}

//删除所有区
void CCoGISView::OnDelallPoly()
{
	// TODO: 在此添加命令处理程序代码
	if(isAreaActive())
	{
		m_CurrentOper=_T("删除所有区");
		ShowState();
		CoDeleteAllPoly DelAll(this,m_DB,getAreaAct());
		DelAll.DelAllPoly();
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);
}

//==============注释菜单相关操作============//

//输入注释
void CCoGISView::OnInputTag()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("输入注释");
		ShowState();
		m_BaseOper = new CoInputTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到注释文件,请新建或激活已有的注释文件！","提示",MB_OK |MB_ICONASTERISK);
}

//选择注释
void CCoGISView::OnSelectTag()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("选择注释");
		ShowState();
		m_BaseOper = new CoSelectTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到注释文件,请新建或激活已有的注释文件！","提示",MB_OK |MB_ICONASTERISK);
}

//移动注释
void CCoGISView::OnMoveTag()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("移动注释");
		ShowState();
		m_BaseOper = new CoMoveTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到注释文件,请新建或激活已有的注释文件！","提示",MB_OK |MB_ICONASTERISK);
}

//复制注释
void CCoGISView::OnCopyTag()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("复制注释");
		ShowState();
		m_BaseOper = new CoCopyTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到注释文件,请新建或激活已有的注释文件！","提示",MB_OK |MB_ICONASTERISK);
}

//修改注释文本
void CCoGISView::OnAlterTagtext()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("修改注释文本");
		ShowState();
		m_BaseOper = new CoAlterTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到注释文件,请新建或激活已有的注释文件！","提示",MB_OK |MB_ICONASTERISK);
}

//修改注释参数
void CCoGISView::OnReTaggpro()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("修改注释参数");
		ShowState();
		m_BaseOper = new CoAlterTagPro(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到注释文件,请新建或激活已有的注释文件！","提示",MB_OK |MB_ICONASTERISK);
}

//删除注释
void CCoGISView::OnDelTag()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("删除注释");
		ShowState();
		m_BaseOper = new CoDelTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到注释文件,请新建或激活已有的注释文件！","提示",MB_OK |MB_ICONASTERISK);
}

//删除所有注释
void CCoGISView::OnDelallTag()
{
	// TODO: 在此添加命令处理程序代码
	if(isNoteActive())
	{
		m_CurrentOper=_T("删除所有注释");
		ShowState();
		CoDelAllTag DelAllTag(this,m_DB,getNoteAct());
		DelAllTag.DelAllTag();
	}
	else
		MessageBox("没有找到注释文件,请新建或激活已有的注释文件！","提示",MB_OK |MB_ICONASTERISK);
}

//============空间分析菜单相关操作============//

//选择点
void CCoGISView::OnTopoSelpnt()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper =_T("拓扑选点");
		ShowState();
		m_BaseOper = new CoTopo(this,m_DB,getPntAct(),1,m_CoScreen);
	}

	else
		MessageBox("没有找到点文件,请新建或激活已有的点文件！","提示",MB_OK |MB_ICONASTERISK);
}

//选择线
void CCoGISView::OnTopoSelline()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper =_T("拓扑选线");
		ShowState();
		m_BaseOper = new CoTopo(this,m_DB,getLineAct(),2,m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}

//选择区
void CCoGISView::OnTopoSelpoly()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper =_T("拓扑选区");
		ShowState();
		m_BaseOper = new CoTopo(this,m_DB,getAreaAct(),3,m_CoScreen);
	}
	else
		MessageBox("没有找到区文件,请新建或激活已有的区文件！","提示",MB_OK |MB_ICONASTERISK);
}

//自定义距离量算
void CCoGISView::OnGetDistance()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	m_CurrentOper=_T("距离量算");
	ShowState();
	m_BaseOper = new CoDistance(this,m_CoScreen);
}
//已知线段量算
void CCoGISView::OnDisLine()
{
	// TODO: 在此添加命令处理程序代码
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper =_T("已知线段量算");
		ShowState();
		m_BaseOper = new CoDistanceLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("没有找到线文件,请新建或激活已有的线文件！","提示",MB_OK |MB_ICONASTERISK);
}
//=============整体操作相关菜单响应===========//

//放大
void CCoGISView::OnZoonIn()
{
	// TODO: 在此添加命令处理程序代码
	m_CurrentOper =_T("放大");
	ShowState();
	DelectMouseOper();
	m_OverAllOper = 1;
	m_BaseOper = new CoZoonIn(this,m_CoScreen);

}

//缩小
void CCoGISView::OnZoonOut()
{
	// TODO: 在此添加命令处理程序代码
	m_CurrentOper =_T("缩小");
	ShowState();
	DelectMouseOper();
	m_OverAllOper = 2;
	m_BaseOper = new CoZoonOut(this,m_CoScreen);
}

//移动
void CCoGISView::OnPan()
{
	// TODO: 在此添加命令处理程序代码
	m_CurrentOper =_T("移动");
	ShowState();
	DelectMouseOper();
	m_OverAllOper = 3;
	m_BaseOper = new CoPan(this,m_CoScreen);
}

//复位
void CCoGISView::OnMicfw()
{
	// TODO: 在此添加命令处理程序代码
	m_CurrentOper =_T("复位");
	ShowState();
	DelectMouseOper();
	m_OverAllOper=0;
	m_CoScreen.sx=0;
	m_CoScreen.sy=0;
	m_CoScreen.blc=1;
	DisPaly();
	Invalidate(TRUE);
}

//刷新
void CCoGISView::OnFrash()
{
	// TODO: 在此添加命令处理程序代码
	Invalidate(TRUE);
}

/*===========Start设置菜单==============*/

/*===========end设置菜单==============*/


void CCoGISView::DelectMouseOper()
{
	if (m_BaseOper != NULL)
	{
		delete m_BaseOper;
		m_BaseOper = NULL;
	}
	m_OverAllOper= 0;
}

//显示状态函数
void CCoGISView::ShowState()
{
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CMFCStatusBar&pStatus = pFrame->GetStatusBar();
	pStatus.SetPaneText(pStatus.CommandToIndex(ID_INDICATOR_NUM), m_CurrentOper,TRUE);
}

//屏幕坐标转换函数 int to double
void CCoGISView::VPtoDP(int x,int y,double* X,double* Y)
{
	*X=m_CoScreen.sx+x*m_CoScreen.blc;
	if(m_MapMode==1)
		*Y=m_CoScreen.sy+m_CoScreen.blc*(m_CoScreen.hScreen-y);
	else
		*Y=m_CoScreen.sy+m_CoScreen.blc*(y+m_CoScreen.hScreen);
}

void CCoGISView::DPtoVP(double x,double y,int* X,int* Y)
{
	*X=(int)((x-m_CoScreen.sx)/m_CoScreen.blc);
	if(m_MapMode==1)
		*Y=m_CoScreen.hScreen-(int)((y-m_CoScreen.sy)/m_CoScreen.blc);
	else
		*Y=(int)((y-m_CoScreen.sy)/m_CoScreen.blc)-m_CoScreen.hScreen;
}

double CCoGISView::VLtoDL(int l)
{
	return m_CoScreen.blc*l;
}

int CCoGISView::DLtoVL(double l)
{
	return (int)(l/m_CoScreen.blc);
}

//屏幕窗口变化函数
void CCoGISView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	m_CoScreen.wScreen = cx;//视图屏幕的宽度
	m_CoScreen.hScreen = cy;//视图屏幕的高度
}

//用于重绘的函数
void CCoGISView::DisPaly()
{
	if(m_OverAllOper == 1)
	{
		CoZoonIn obj;
		m_CoScreen = obj.m_Screen;
	}

	if(m_OverAllOper==2)
	{
		CoZoonOut obj;
		m_CoScreen = obj.m_Screen;
	}

	if(m_OverAllOper==3)
	{
		CoPan obj;
		m_CoScreen = obj.m_Screen;
	}
	CString type;
	CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	CoFeatureset feature;
	CoRecorset MicReco;
	CString str;
	int lengh = theTables.size();
	CoCDC dc(this,m_CoScreen);
	for(int i=lengh-1;i>=0;i--)
	{
		if (theTables[i].isOpen==true)
		{
			feature.Open(&conn,theTables[i].itemnode);
			str.Format("SELECT ID FROM [%s]",theTables[i].itemnode);
			MicReco.Open(&feature,str);
			type=theTables[i].itemnode.Right(4);
			while (!MicReco.CoEOF())
			{
				if (type==".COP")
				{
					if (MicReco.GetPoint(m_Point,m_PntPro))
					{
						dc.DrawAllPnt(m_Point,m_PntPro);
						m_Point.x = m_Point.y = 0;
					}
				}
				if(type==".COL")
				{
					if (MicReco.GetLine(m_Line,m_LinePro))
					{
						dc.DrawLine(m_Line,m_LinePro);
						m_Line.clear();
					}
				}
				if (type==".COA")
				{
					if (MicReco.GetPolygon(m_Poly,m_PolyPro))
					{
						dc.DrawAllPoly(m_Poly,m_PolyPro);
						m_Poly.clear();
					}
				}
				if (type==".CON")
				{
					if (MicReco.GetTag(m_TagPnt,m_TagPro))
					{
						dc.DrawText(m_TagPnt,m_TagPro);
						m_TagPnt.x = m_TagPnt.y = 0;
					}
				}
				MicReco.MoveNext();
			}
		}
	}
}






