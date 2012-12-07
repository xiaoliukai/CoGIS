
#pragma once

#include "ViewTreeD.h"

class CDBViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CDBView : public CDockablePane
{
// 构造
public:

	CDBView();

	void AdjustLayout();
	void OnChangeVisualStyle();

// 特性
protected:

	CViewTreeD m_wndFileView;
	CImageList m_FileViewImages;
	CDBViewToolBar m_wndToolBar;
	HTREEITEM tempItem;

protected:
	void FillDBTCView();

// 实现
public:
	virtual ~CDBView();
public:
	CString m_ProjectItem;
	HTREEITEM hRoot;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);//右键菜单相应函数
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNewPnt();//新建点文件
	afx_msg void OnNewLine();//新建线文件
	afx_msg void OnNewArea();//新建区文件
	afx_msg void OnNewNote();//新建注释文件
	afx_msg void OnOpenItem();//打开文件
	afx_msg void OnCloseItem();//关闭文件
	afx_msg void OnActiveItem();//激活文件
	afx_msg void OnDelItem();//删除文件
	afx_msg void OnLoadDB();//从数据库中载入文件
	DECLARE_MESSAGE_MAP()

public:
	HTREEITEM FindTreeItem(HTREEITEM item,CString& strText)   ;
	void DelViewState();
};

