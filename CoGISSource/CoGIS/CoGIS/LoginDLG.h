#pragma once


// LoginDLG 对话框

class LoginDLG : public CDialog
{
	DECLARE_DYNAMIC(LoginDLG)

public:
	LoginDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginDLG();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_pwd;
	CBrush m_brBk;//定义一个背景画刷
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_serverName;
	CString m_sa;
	CString m_gis;
};
