#ifndef _CoDLG_H_
#define _CoDLG_H_

#include "CoStructClass.h"

#ifndef _CoDLG_EXPORT_
#define DIALOG  __declspec(dllimport)
#else
#define DIALOG  __declspec(dllexport)
#endif
//================================================

//================================================
//输入点对话框
bool DIALOG InputPointDLG(CoPntPro& PointPor);

//================================================
//输入线对话框
bool DIALOG InputLineDLG(CoLinePro& LinePor);

//================================================
//输入区对话框
bool DIALOG InputPolyDLG(CoPolyPro& PolyPor);
//================================================
//输入注记对话框
bool DIALOG InputTagPro(CoTagPro& TagPro);
//================================================
//输入注记文本对话框
bool DIALOG InputTagStr(CoTagPro& TagPro);

//===============================================
//点参数查寻修改
bool DIALOG PointPro(CoPntPro& PointPro);

//===============================================
//线属性查询与修改
bool DIALOG LinePro(CoLinePro& LinePro);

//================================================
//区参数查询与修改
bool DIALOG PolyGonPro(CoPolyPro& PolygonPro);

//================================================
//新建点文件
bool DIALOG NewPointDoc(CString* PntName);

//=================================================
//新建线文件
bool DIALOG NewLineDoc(CString* LineName);

//==================================================
//新建区文件
bool DIALOG NewPolyDoc(CString* PolyName);
//==================================================
//新建区文件
bool DIALOG NewTagDoc(CString* TagName);


bool DIALOG AlterTagProDLG(CoTagPro& TagPro);

bool DIALOG AlterTagStr(CString& TagStr);

 #ifndef _CoDLG_EXPORT_
   #ifdef _DEBUG
  #pragma comment(lib,"CoDLG.lib")
#else
  #pragma comment(lib,"CoDLG.lib")
  #endif
 #endif
#endif
