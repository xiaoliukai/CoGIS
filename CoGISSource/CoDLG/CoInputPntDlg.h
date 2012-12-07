#pragma once
#include "afxwin.h"

#include "resource.h"
// CoInputPntDlg 对话框

class CoInputPntDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInputPntDlg)

public:
	CoInputPntDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoInputPntDlg();

// 对话框数据
	enum { IDD = IDD_INPUTPNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brBk;//定义一个背景画刷
	CComboBox m_ConPntStyle;
	int		m_PntStyle;
	int		m_Radio;
	int		m_Layer;
	COLORREF m_PntCor;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
