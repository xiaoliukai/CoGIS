#pragma once

#include "resource.h"
// CoNewPolyDlg 对话框

class CoNewPolyDlg : public CDialog
{
	DECLARE_DYNAMIC(CoNewPolyDlg)

public:
	CoNewPolyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoNewPolyDlg();

// 对话框数据
	enum { IDD = IDD_NEWPOLYITEM };
	CBrush m_brBk;//定义一个背景画刷
	CString	m_NewPolyItem;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
