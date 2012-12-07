#pragma once

#include "resource.h"
// CoInPutPolyDlg 对话框

class CoInPutPolyDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInPutPolyDlg)

public:
	CoInPutPolyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CoInPutPolyDlg();

// 对话框数据
	enum { IDD = IDD_INPUTPOLY };
public:
	CBrush m_brBk;//定义一个背景画刷
	CComboBox	m_ConPolyStle;
	CComboBox	m_ConFillStyle;
	int		m_FillStyle;
	int		m_PolyStyle;
	int		m_PolyLayer;
	COLORREF m_PolyFillCor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
