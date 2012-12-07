#pragma once

#include "resource.h"
// CoNewLineDlg 对话框

class CoNewLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CoNewLineDlg)

public:
	CoNewLineDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoNewLineDlg();

// 对话框数据
	enum { IDD = IDD_NEWLINEITEM };
	CBrush m_brBk;//定义一个背景画刷
	CString	m_NewLine;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
