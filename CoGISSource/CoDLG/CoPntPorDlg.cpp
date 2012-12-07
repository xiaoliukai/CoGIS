// CoPntPorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoPntPorDlg.h"
#include "afxdialogex.h"


// CoPntPorDlg 对话框

IMPLEMENT_DYNAMIC(CoPntPorDlg, CDialog)

CoPntPorDlg::CoPntPorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoPntPorDlg::IDD, pParent)
{
	m_OrPntStyle = _T("");
	m_OrRadio = 0;
	m_OrPntCor = 0;
	m_OrPntLayler = 0;
	m_Radio = 0;
	m_Layler = 0;
	m_PntStyle = -1;
}

CoPntPorDlg::CoPntPorDlg(int Style,CString PntStyle,int Raido,int PntCor,int PntLayer,CWnd* pParent /* = NULL */)
	: CDialog(CoPntPorDlg::IDD, pParent)
{
	m_OrPntStyle = PntStyle;
	m_Radio =m_OrRadio = Raido;
	m_OrPntCor = PntCor;
	m_Layler =m_OrPntLayler = PntLayer;
	m_PntStyle = Style;
	m_PntCor = PntCor;
	Tug1=Tug2=Tug3=Tug4=FALSE;
}



CoPntPorDlg::~CoPntPorDlg()
{
}

void CoPntPorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_CorPntStyle);
	DDX_Text(pDX, IDC_EDIT1, m_OrPntStyle);
	DDX_Text(pDX, IDC_EDIT2, m_OrRadio);
	DDX_Text(pDX, IDC_EDIT3, m_OrPntCor);
	DDX_Text(pDX, IDC_EDIT4, m_OrPntLayler);
	DDX_Text(pDX, IDC_EDIT5, m_Radio);
	DDX_Text(pDX, IDC_EDIT6, m_Layler);
	DDX_CBIndex(pDX, IDC_COMBO1, m_PntStyle);
}


BEGIN_MESSAGE_MAP(CoPntPorDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CoPntPorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CoPntPorDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CoPntPorDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CoPntPorDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CoPntPorDlg::OnBnClickedCheck4)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoPntPorDlg 消息处理程序


BOOL CoPntPorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);

	//添加背景
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CoPntPorDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog corDlg;
	if (corDlg.DoModal()==IDOK)
	{
		m_PntCor = corDlg.GetColor();
	}
}


void CoPntPorDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(Tug1)
	{
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		Tug1 = false;
	}
	else
	{
		GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
		Tug1 = true;
	}
	UpdateData(FALSE);
}


void CoPntPorDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(Tug2)
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		Tug2 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		Tug2 = true;
	}
	UpdateData(FALSE);
}


void CoPntPorDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(Tug3)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		Tug3 = false;
	}
	else
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		Tug3 = true;
	}
	UpdateData(FALSE);
}


void CoPntPorDlg::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(Tug4)
	{
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		Tug4 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		Tug4 = true;
	}
	UpdateData(FALSE);
}


HBRUSH CoPntPorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
