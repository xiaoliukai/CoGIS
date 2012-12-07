#include "stdafx.h"
#include "DataExchange.h"
#include "CoStructClass.h"

vector<AllTalble> theTables;//存放当前工程中的所有表
CoDB m_DB;
//当前操作的四张表
AcTable m_PntTable;
AcTable m_LineTable;
AcTable m_AreaTable;
AcTable m_NoteTable;
//当前的工作目录
CString m_CurrentOper;//显示操作状态变量
CoBaseTool* m_BaseOper;
int m_OverAllOper;

//设置初始状态函数
void setIniState()
{
	m_PntTable.isAct=false;
	m_LineTable.isAct=false;
	m_AreaTable.isAct=false;
	m_NoteTable.isAct=false;
}

//如果有激活的点文件
bool isPntActive()
{
	if(m_PntTable.isAct)
		return true;
	else
		return false;
}

//得到激活的点文件
CString getPntAct()
{
	return m_PntTable.item;
}
//如果有激活的线文件
bool isLineActive()
{
	if (m_LineTable.isAct)
		return true;
	else
		return false;
	
}

//得到激活的线文件
CString getLineAct()
{
	return m_LineTable.item;
}

//如果有激活的区文件
bool isAreaActive()
{
	if (m_AreaTable.isAct)
		return true;
	else
		return false;

}

//得到激活的区文件
CString getAreaAct()
{
	return m_AreaTable.item;
}

//如果有激活的注释文件
bool isNoteActive()
{
	if (m_NoteTable.isAct)
		return true;
	else
		return false;
}

//得到激活的注释文件
CString getNoteAct()
{
	return m_NoteTable.item;
}

//连接数据库函数
void GetConnect(CoConnect& conn)
{
	CoConnect MyConn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	MyConn.Connect();
	conn = MyConn;
}

//增加当前工程的表
void AddTables(CString temItem,bool isopen,bool isactive,CString filetype)
{
	AllTalble tempTalble;
	tempTalble.itemnode=temItem;
	tempTalble.isOpen=isopen;
	tempTalble.isActive=isactive;
	tempTalble.fileTyep=filetype;
	theTables.push_back(tempTalble);
}

//设置打开标记
void setOpenMark(CString temItem)
{
	for (int i=0;i<theTables.size();i++)
		{
			if (theTables[i].itemnode==temItem)
			{
				theTables[i].isOpen=true;
				break;
			}
		}
}

//设置关闭标记
void setCloseMark(CString temItem)
{
	for (int i=0;i<theTables.size();i++)
	{
		if (theTables[i].itemnode==temItem)
		{
			theTables[i].isOpen=false;
			if(theTables[i].isActive)
			{
				if (theTables[i].itemnode==m_PntTable.item)
				{
					m_PntTable.isAct=false;
				}
				if (theTables[i].itemnode==m_LineTable.item)
				{
					m_LineTable.isAct=false;
				}
				if (theTables[i].itemnode==m_AreaTable.item)
				{
					m_AreaTable.isAct=false;
				}
				if (theTables[i].itemnode==m_NoteTable.item)
				{
					m_NoteTable.isAct=false;
				}
				theTables[i].isActive=false;
			}
			break;
		}
	}
}

//设置激活标志
bool setActiveMark(CString temItem,CString&reItem)
{
	for (int i=0;i<theTables.size();i++)
	{
		if (theTables[i].itemnode==temItem)
		{
			theTables[i].isOpen=true;
			theTables[i].isActive=true;
			if (theTables[i].fileTyep==_T("COP"))//如果激活的是点文件
			{
				if(isPntActive())//如果存在激活的点文件
				{
					setOpenMark(m_PntTable.item);
					reItem=m_PntTable.item;//返回之前激活的节点
					m_PntTable.isAct=true;
					m_PntTable.item=temItem;//设置新的激活节点
					return true;
				}
				else
				{
					m_PntTable.isAct=true;
					m_PntTable.item=temItem;
					return false;
				}
			}
			if (theTables[i].fileTyep==_T("COL"))//如果激活的是线文件
			{
				if(isLineActive())//如果存在激活的点文件
				{
					setOpenMark(m_LineTable.item);
					reItem=m_LineTable.item;//返回之前激活的节点
					m_LineTable.isAct=true;
					m_LineTable.item=temItem;//设置新的激活节点
					return true;
				}
				else
				{
					m_LineTable.isAct=true;
					m_LineTable.item=temItem;
					return false;
				}
			}
			if (theTables[i].fileTyep==_T("COA"))//如果激活的是区文件
			{
				if(isAreaActive())//如果存在激活的点文件
				{
					setOpenMark(m_AreaTable.item);
					reItem=m_AreaTable.item;//返回之前激活的节点
					m_AreaTable.isAct=true;
					m_AreaTable.item=temItem;//设置新的激活节点
					return true;
				}
				else
				{
					m_AreaTable.isAct=true;
					m_AreaTable.item=temItem;
					return false;
				}
			}
			if (theTables[i].fileTyep==_T("CON"))//如果激活的是注释文件
			{
				if(isNoteActive())//如果存在激活的点文件
				{
					setOpenMark(m_NoteTable.item);
					reItem=m_NoteTable.item;//返回之前激活的节点
					m_NoteTable.isAct=true;
					m_NoteTable.item=temItem;//设置新的激活节点
					return true;
				}
				else
				{
					m_NoteTable.isAct=true;
					m_NoteTable.item=temItem;
					return false;
				}
			}
		}
	}
}

//删除一条记录
void remItemMark(CString temItem)
{
	if (temItem==m_PntTable.item)
	{
		m_PntTable.isAct=false;
	}
	if (temItem==m_LineTable.item)
	{
		m_LineTable.isAct=false;
	}
	if (temItem==m_AreaTable.item)
	{
		m_AreaTable.isAct=false;
	}
	if (temItem==m_NoteTable.item)
	{
		m_NoteTable.isAct=false;
	}
	//查找这个元素在容器中的位置
	/*AllTalble t_Table;
	for (int i=theTables.size();i>=0;i--)
	{
		if (theTables[i].itemnode==temItem)
		{
			theTables[i].isActive=false;
			theTables[i].isOpen=false;
			break;
		}
	}   */
	//vector<AllTalble> myvector;
	for(vector<AllTalble>::iterator iter=theTables.begin();iter!=theTables.end();)
	{
		if(temItem == (*iter).itemnode)
			iter=theTables.erase(iter);
		else
			++iter;
	} 
}