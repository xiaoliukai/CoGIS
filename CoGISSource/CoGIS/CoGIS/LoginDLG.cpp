// LoginDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "CoGIS.h"
#include "LoginDLG.h"
#include "afxdialogex.h"


// LoginDLG 对话框

IMPLEMENT_DYNAMIC(LoginDLG, CDialog)

LoginDLG::LoginDLG(CWnd* pParent /*=NULL*/)
	: CDialog(LoginDLG::IDD, pParent)
	, m_pwd(_T(""))
	, m_serverName(_T("127.0.0.1"))
	, m_sa(_T("sa"))
	, m_gis(_T("CoGISDB"))
{

}

LoginDLG::~LoginDLG()
{
}

void LoginDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PWD, m_pwd);
	DDX_Text(pDX, IDC_EDIT_NAME_SERVER, m_serverName);
	DDX_Text(pDX, IDC_EDIT_NAME_SJKZH, m_sa);
	DDX_Text(pDX, IDC_EDIT_NAME_GIS, m_gis);
}


BEGIN_MESSAGE_MAP(LoginDLG, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// LoginDLG 消息处理程序


BOOL LoginDLG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_LOGIN); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject(); 
	return TRUE; 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


HBRUSH LoginDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd == this) 
	{ 
		return m_brBk; 
	} 
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
