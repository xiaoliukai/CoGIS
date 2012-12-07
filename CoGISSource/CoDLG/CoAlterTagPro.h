#pragma once
#include "resource.h"
#include "CoStructClass.h"
// CoAlterTagPro 对话框

class CoAlterTagPro : public CDialog
{
	DECLARE_DYNAMIC(CoAlterTagPro)

public:
	CoAlterTagPro(CWnd* pParent = NULL);   // 标准构造函数
	CoAlterTagPro(CoTagPro& TagPro,CWnd* pParent = NULL); 
	virtual ~CoAlterTagPro();

// 对话框数据
	enum { IDD = IDD_MICALTER_TAGPRO };
public:
	CBrush m_brBk;//定义一个背景画刷
	CComboBox	m_lColFont;
	int		m_TagHight;
	int		m_TagWide;
	float	m_TagAngle;
	float	m_TextAngle;
	int		m_TagOffsite;
	CString	m_TagFont;
	int		m_TagColor;
	int		m_TagLayer;
	int		m_lTagHeight;
	int		m_lTagWidth;
	float	m_lTagAngle;
	float	m_lTextAngle;
	int		m_lTagOffsite;
	CString	m_lTagFont;
	int		m_lTagLayer;
public:
	COLORREF m_lFontCor;
private:
	bool tug3;
	bool tug4;
	bool tug5;
	bool tug6;
	bool tug7;
	bool tug8;
	bool tug9;
	bool tug10;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	virtual void OnOk();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
