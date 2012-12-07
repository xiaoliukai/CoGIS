// CoInputPntDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoInputPntDlg.h"
#include "afxdialogex.h"


// CoInputPntDlg 对话框

IMPLEMENT_DYNAMIC(CoInputPntDlg, CDialog)

CoInputPntDlg::CoInputPntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoInputPntDlg::IDD, pParent)
{
	m_PntStyle = -1;
	m_Radio = 1;
	m_Layer = 0;
	m_PntCor = RGB(0,0,0);
}

CoInputPntDlg::~CoInputPntDlg()
{
}

void CoInputPntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ConPntStyle);
	DDX_CBIndex(pDX, IDC_COMBO1, m_PntStyle);
	DDX_Text(pDX, IDC_EDIT1, m_Radio);
	DDV_MinMaxInt(pDX, m_Radio, 1, 20);
	DDX_Text(pDX, IDC_EDIT2, m_Layer);
}


BEGIN_MESSAGE_MAP(CoInputPntDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CoInputPntDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoInputPntDlg 消息处理程序


void CoInputPntDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog MyCorDlg;
	if (MyCorDlg.DoModal()==IDOK)
	{
		m_PntCor = MyCorDlg.GetColor();
	}
}


BOOL CoInputPntDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ConPntStyle.SetCurSel(0);

	//添加背景
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


HBRUSH CoInputPntDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
