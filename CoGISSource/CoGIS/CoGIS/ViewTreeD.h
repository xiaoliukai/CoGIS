
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTreeD 窗口

class CViewTreeD : public CTreeCtrl
{
// 构造
public:
	CViewTreeD();

// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 实现
public:
	virtual ~CViewTreeD();
//自定义改变子项颜色
protected:
	struct Color_Font
	{
		COLORREF color;
		LOGFONT  logfont;
	};
//保存颜色信息的变量
protected:
	CMap< void*, void*, Color_Font, Color_Font& > m_mapColorFont ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetItemFont(HTREEITEM hItem, LOGFONT& logfont);
	void SetItemBold(HTREEITEM hItem, BOOL bBold);
	void SetItemColor(HTREEITEM hItem, COLORREF color);
	BOOL GetItemFont(HTREEITEM hItem, LOGFONT * plogfont);
	BOOL GetItemBold(HTREEITEM hItem);
	COLORREF GetItemColor(HTREEITEM hItem);
	afx_msg void OnPaint();
};
