#pragma once

#include "resource.h"
// CoInPutTagStrDlg 对话框

class CoInPutTagStrDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInPutTagStrDlg)

public:
	CoInPutTagStrDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoInPutTagStrDlg();

// 对话框数据
	enum { IDD = IDD_INPUTTAGSTRDLG };
public:
	CBrush m_brBk;//定义一个背景画刷
	CString	m_tagstr;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
