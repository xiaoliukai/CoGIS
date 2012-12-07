
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "FileView.h"
//图层控制头文件
#include "DBPanel.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCToolBar       m_CoGISToolbar;

	CMFCToolBar       m_CoPntToolbar;  //点操作控件
	CMFCToolBar       m_CoLineToolbar; //线操作控件
	CMFCToolBar       m_CoAreaToolbar; //区操作控件
	CMFCToolBar       m_CoNoteToolbar; //注释操作控件
	
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndFileView;

	//图层控制变量
	CDBView m_wndDBView;
public:
	CMFCStatusBar&GetStatusBar ()
	{
		return m_wndStatusBar;
	}

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnTcboard();
private:
	//私有变量
	bool IsShowTCPanel;
public:
	afx_msg void OnUpdateTcboard(CCmdUI *pCmdUI);
};


