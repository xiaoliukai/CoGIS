#pragma once
#include "resource.h"
#include "CoStructClass.h"
// CoLineProDlg 对话框

class CoLineProDlg : public CDialog
{
	DECLARE_DYNAMIC(CoLineProDlg)

public:
	CoLineProDlg(CWnd* pParent = NULL);   // 标准构造函数
	CoLineProDlg(int MyStyle,CString LineStyle,int LineWide,int LineCor,int LineLayle,CWnd* pParent = NULL);
	virtual ~CoLineProDlg();

// 对话框数据
	enum { IDD = IDD_LINEPRO };
public:
	CBrush m_brBk;//定义一个背景画刷
	CEdit	m_Edit6;
	CEdit	m_Edit5;
	CComboBox	m_Combo;
	CButton	m_SetCor;
	int		m_LineStyle;
	CString	m_EditLineStyle;
	int		m_EditLineWide;
	int		m_EditLineCor;
	int		m_EditLineLayer;
	int		m_EditWide;
	int		m_EditLayer;
	COLORREF m_LineCor;
public:
	CoLinePro m_LinePro;
private:
	bool Tug1;
	bool Tug2;
	bool Tug3;
	bool Tug4;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
