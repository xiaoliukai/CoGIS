// CoInPutPolyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoInPutPolyDlg.h"
#include "afxdialogex.h"


// CoInPutPolyDlg 对话框

IMPLEMENT_DYNAMIC(CoInPutPolyDlg, CDialog)

CoInPutPolyDlg::CoInPutPolyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoInPutPolyDlg::IDD, pParent)
{
	m_FillStyle = -1;
	m_PolyStyle = -1;
	m_PolyLayer = 0;
	m_PolyFillCor = RGB(0,0,0);
}

CoInPutPolyDlg::~CoInPutPolyDlg()
{
}

void CoInPutPolyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_ConPolyStle);
	DDX_Control(pDX, IDC_COMBO1, m_ConFillStyle);
	DDX_CBIndex(pDX, IDC_COMBO1, m_FillStyle);
	DDX_CBIndex(pDX, IDC_COMBO2, m_PolyStyle);
	DDX_Text(pDX, IDC_EDIT1, m_PolyLayer);
}


BEGIN_MESSAGE_MAP(CoInPutPolyDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CoInPutPolyDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoInPutPolyDlg 消息处理程序


void CoInPutPolyDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog FillCorDlg;
	if (FillCorDlg.DoModal()==IDOK)
	{
		m_PolyFillCor = FillCorDlg.GetColor();
	}
}


BOOL CoInPutPolyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ConFillStyle.SetCurSel(0);
	m_ConPolyStle.SetCurSel(1);

	//添加背景
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


HBRUSH CoInPutPolyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
