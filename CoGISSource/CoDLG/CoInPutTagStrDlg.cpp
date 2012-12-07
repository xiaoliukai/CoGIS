// CoInPutTagStrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoInPutTagStrDlg.h"
#include "afxdialogex.h"


// CoInPutTagStrDlg 对话框

IMPLEMENT_DYNAMIC(CoInPutTagStrDlg, CDialog)

CoInPutTagStrDlg::CoInPutTagStrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoInPutTagStrDlg::IDD, pParent)
{
	m_tagstr = _T("");
}

CoInPutTagStrDlg::~CoInPutTagStrDlg()
{
}

void CoInPutTagStrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_tagstr);
}


BEGIN_MESSAGE_MAP(CoInPutTagStrDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoInPutTagStrDlg 消息处理程序


BOOL CoInPutTagStrDlg::OnInitDialog()
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


HBRUSH CoInPutTagStrDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
