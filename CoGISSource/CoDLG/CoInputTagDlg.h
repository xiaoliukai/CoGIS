#pragma once

#include "resource.h"
// CoInputTagDlg 对话框

class CoInputTagDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInputTagDlg)

public:
	CoInputTagDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoInputTagDlg();

// 对话框数据
	enum { IDD = IDD_INPUTTAG };
public:
	CBrush m_brBk;//定义一个背景画刷
	CComboBox	m_font;
	long	m_tagheight;
	long	m_taglayer;
	long	m_tagoffsite;
	long	m_tagangle;
	long	m_textangle;
	CString	m_tagfont;
	long	m_tagwidth;
	long	m_tagcolor;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedColor();
	virtual void OnOk();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
