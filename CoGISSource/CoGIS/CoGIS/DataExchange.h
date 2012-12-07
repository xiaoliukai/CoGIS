#ifndef _DATAEXCHANGE_H_
#define _DATAEXCHANGE_H_
#include "_CoDB.h"
#include "_MouseOper.h"

extern vector<AllTalble> theTables;//存放当前工程中的所有表
extern CString m_CurrentOper;//显示操作状态变量
extern CoBaseTool* m_BaseOper;
extern int m_OverAllOper;
extern CoDB m_DB;
void setIniState();//设置初始状态
bool isPntActive();//如果有激活的点文件
CString getPntAct();//得到激活的点文件
bool isLineActive();//如果有激活的线文件
CString getLineAct();//得到激活的线文件
bool isAreaActive();//如果有激活的区文件
CString getAreaAct();//得到激活的区文件
bool isNoteActive();//如果有激活的注释文件
CString getNoteAct();//得到激活的注释文件
void GetConnect(CoConnect& conn);//连接数据库
void AddTables(CString temItem,bool isopen,bool isactive,CString filetype);//增加当前工程的表
void setOpenMark(CString temItem);//设置打开标记
void setCloseMark(CString temItem);//设置关闭标记
bool setActiveMark(CString temItem,CString&reItem);//设置激活标记
void remItemMark(CString temItem);//删除一条记录
#endif