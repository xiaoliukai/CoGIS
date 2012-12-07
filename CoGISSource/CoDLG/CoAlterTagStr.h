#pragma once

#include "resource.h"
// CoAlterTagStr 对话框

class CoAlterTagStr : public CDialog
{
	DECLARE_DYNAMIC(CoAlterTagStr)

public:
	CoAlterTagStr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoAlterTagStr();

// 对话框数据
	enum { IDD = IDD_MICALTERTAGSTR };
public:
	CBrush m_brBk;//定义一个背景画刷
	CString	m_TagStr;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
