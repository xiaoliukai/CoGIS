#pragma once
#include "resource.h"

// CoNewPntDlg 对话框

class CoNewPntDlg : public CDialog
{
	DECLARE_DYNAMIC(CoNewPntDlg)

public:
	CoNewPntDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoNewPntDlg();

// 对话框数据
	enum { IDD = IDD_NEWPNTITEM };
	CBrush m_brBk;//定义一个背景画刷
	CString	m_PntName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
