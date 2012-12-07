// CoNewPntDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoNewPntDlg.h"
#include "afxdialogex.h"


// CoNewPntDlg 对话框

IMPLEMENT_DYNAMIC(CoNewPntDlg, CDialog)

CoNewPntDlg::CoNewPntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoNewPntDlg::IDD, pParent)
{
	m_PntName = _T("");
}

CoNewPntDlg::~CoNewPntDlg()
{
}

void CoNewPntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_PntName);
}


BEGIN_MESSAGE_MAP(CoNewPntDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoNewPntDlg 消息处理程序


BOOL CoNewPntDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//添加背景
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


HBRUSH CoNewPntDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
