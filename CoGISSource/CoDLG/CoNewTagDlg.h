#pragma once

#include "resource.h"
// CoNewTagDlg 对话框

class CoNewTagDlg : public CDialog
{
	DECLARE_DYNAMIC(CoNewTagDlg)

public:
	CoNewTagDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoNewTagDlg();

// 对话框数据
	enum { IDD = IDD_NEWFONTITEM };
	CBrush m_brBk;//定义一个背景画刷
	CString	m_TagName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
