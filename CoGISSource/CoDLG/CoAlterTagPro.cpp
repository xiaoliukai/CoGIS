// CoAlterTagPro.cpp : 实现文件
//

#include "stdafx.h"
#include "CoAlterTagPro.h"
#include "afxdialogex.h"


// CoAlterTagPro 对话框

IMPLEMENT_DYNAMIC(CoAlterTagPro, CDialog)

CoAlterTagPro::CoAlterTagPro(CWnd* pParent /*=NULL*/)
	: CDialog(CoAlterTagPro::IDD, pParent)
{

}

CoAlterTagPro::CoAlterTagPro(CoTagPro& TagPro,CWnd* pParent /* = NULL */)
	: CDialog(CoAlterTagPro::IDD, pParent)
{
	m_TagHight = m_lTagHeight=TagPro.TagHeight;
	m_TagWide =m_lTagWidth =TagPro.TagWidth;
	m_TagAngle = m_lTagAngle=TagPro.TagAngle;
	m_TextAngle = m_lTextAngle=TagPro.TextAngle;
	m_TagOffsite = m_lTagOffsite=TagPro.TagOffsite;
	m_TagFont = m_lTagFont=TagPro.TagFont ;
	m_TagColor = m_lFontCor=TagPro.TagColor;
	m_TagLayer =m_lTagLayer=TagPro.TagLayer;
	tug3 = tug4 = tug5 = tug6 = tug7 = tug8 = tug9 = tug10 = FALSE;

}


CoAlterTagPro::~CoAlterTagPro()
{
}

void CoAlterTagPro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_lColFont);
	DDX_Text(pDX, IDC_EDIT1, m_TagHight);
	DDX_Text(pDX, IDC_EDIT2, m_TagWide);
	DDX_Text(pDX, IDC_EDIT3, m_TagAngle);
	DDX_Text(pDX, IDC_EDIT4, m_TextAngle);
	DDX_Text(pDX, IDC_EDIT5, m_TagOffsite);
	DDX_Text(pDX, IDC_EDIT6, m_TagFont);
	DDX_Text(pDX, IDC_EDIT7, m_TagColor);
	DDX_Text(pDX, IDC_EDIT8, m_TagLayer);
	DDX_Text(pDX, IDC_EDIT9, m_lTagHeight);
	DDX_Text(pDX, IDC_EDIT10, m_lTagWidth);
	DDX_Text(pDX, IDC_EDIT11, m_lTagAngle);
	DDX_Text(pDX, IDC_EDIT12, m_lTextAngle);
	DDX_Text(pDX, IDC_EDIT13, m_lTagOffsite);
	DDX_CBString(pDX, IDC_COMBO1, m_lTagFont);
	DDX_Text(pDX, IDC_EDIT14, m_lTagLayer);
}


BEGIN_MESSAGE_MAP(CoAlterTagPro, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CoAlterTagPro::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK3, &CoAlterTagPro::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CoAlterTagPro::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CoAlterTagPro::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CoAlterTagPro::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CoAlterTagPro::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CoAlterTagPro::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CoAlterTagPro::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CoAlterTagPro::OnBnClickedCheck10)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoAlterTagPro 消息处理程序


BOOL CoAlterTagPro::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT12)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT13)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT14)->EnableWindow(FALSE);

	//添加背景
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject(); 

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CoAlterTagPro::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog corDlg;
	if (corDlg.DoModal()==IDOK)
	{
		m_lFontCor = corDlg.GetColor();
	}
}


void CoAlterTagPro::OnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int index;
	index=m_lColFont.GetCurSel();
	m_lColFont.GetLBText(index,m_lTagFont);
	CDialog::OnOK();
}


void CoAlterTagPro::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(tug3)
	{
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		tug3 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		tug3 = true;
	}
	UpdateData(FALSE);
}


void CoAlterTagPro::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(tug4)
	{
		GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
		tug4 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		tug4 = true;
	}
	UpdateData(FALSE);
}


void CoAlterTagPro::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(tug5)
	{
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		tug5 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		tug5 = true;
	}
	UpdateData(FALSE);
}


void CoAlterTagPro::OnBnClickedCheck6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(tug6)
	{
		GetDlgItem(IDC_EDIT12)->EnableWindow(FALSE);
		tug6 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT12)->EnableWindow(TRUE);
		tug6 = true;
	}
	UpdateData(FALSE);
}


void CoAlterTagPro::OnBnClickedCheck7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(tug7)
	{
		GetDlgItem(IDC_EDIT13)->EnableWindow(FALSE);
		tug7 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT13)->EnableWindow(TRUE);
		tug7 = true;
	}
	UpdateData(FALSE);
}


void CoAlterTagPro::OnBnClickedCheck8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(tug8)
	{
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		tug8 = false;
	}
	else
	{
		GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
		tug8 = true;
	}
	UpdateData(FALSE);
}


void CoAlterTagPro::OnBnClickedCheck9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(tug9)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		tug9 = false;
	}
	else
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		tug9 = true;
	}
	UpdateData(FALSE);
}


void CoAlterTagPro::OnBnClickedCheck10()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(tug10)
	{
		GetDlgItem(IDC_EDIT14)->EnableWindow(FALSE);
		tug10 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT14)->EnableWindow(TRUE);
		tug10 = true;
	}
	UpdateData(FALSE);
}


HBRUSH CoAlterTagPro::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
