#pragma once
#include "afxwin.h"

#include "resource.h"
// CoInputLineDlg 对话框

class CoInputLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInputLineDlg)

public:
	CoInputLineDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoInputLineDlg();

// 对话框数据
	enum { IDD = IDD_INPUTLINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brBk;//定义一个背景画刷
	CComboBox m_ConLineStyle;
	CEdit m_Edit1;
	CEdit m_Edit2;
	int		m_LineWide;
	int		m_LayerNum;
	COLORREF m_LineCor;
	int		m_LineStyle;
	afx_msg void OnBnClickedButtonCor();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
