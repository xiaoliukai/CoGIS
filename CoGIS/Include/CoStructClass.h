#ifndef __COSTRUCTCLASS_H_
#define __COSTRUCTCLASS_H_

#include <vector>
using namespace std;

//点坐标
typedef struct
{
	double x;
	double y;
}CoPnt;

//点属性
typedef struct  
{
	long PntID;
	int PntRadio;
	int  PntStyle;
	COLORREF  PntColor;
	int PntLayer;
}CoPntPro;

//线结构体
typedef struct
{
	vector<CoPnt>Line;
}CoLine;

//线属性
typedef struct
{
	long LineID;
	int  LineWidth;
	int  LineStyle;
	COLORREF LineColor;
	int LineLayer;
}CoLinePro;

//区结构体
typedef struct
{
	vector<CoPnt>Poly;
}CoPoly;
//区属性
typedef struct
{
	long PolyID;
    int PolyStyle;
	COLORREF PolyColor;
	int PolyLayer;
    double PolyArea;
	int PolyFillStyle;
}CoPolyPro;
//注记属性
typedef struct
{
	int ID;
	int TagHeight;    //字体高度
	int TagWidth;     //字体宽度
	float TagAngle;  //字体角度
	float TextAngle; //文本角度
	COLORREF TagColor;//字体颜色
	int  TagOffsite;  //字体间距
	CString TagFont;  //字体类型
	CString TagStr;   //字符串
	int	TagLayer; //注记图层
}CoTagPro;

//外接矩形
typedef struct
{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
}CoRect;

typedef struct
{
	int ID;
	CString UserName;//用户名
    CString UserSex;
	CString UserPassword;//用户密码
	CString UserDuties;//职务
	CString UserAddress;//住址
	CString Email;
	CString UserQQ;
}CoUser;

typedef struct
{
	CString szIP;
	CString szDsn;
	CString szName;
	CString szPassword;
}CoDB;

typedef struct
{
	int index;//记录选择物体的类型
	vector<CoPnt>Object;//记录选中的物体
}MyTopo;

typedef struct	//用来记录历史屏幕参数的结构
{
	double blc;	//比例尺
	double sx;	//屏幕左下角的横坐标
	double sy;	//屏幕左下角的纵坐标
    int wScreen;    //屏幕宽
    int hScreen;    //屏幕高
}CoScreen;

typedef struct
{
	HTREEITEM Item;
	CString Text;
	UINT State;
}CoTreeNode;

typedef struct
{
	int ID;
	CString ItemName;
	CString CreateTime;
	CString ModifyTime;
	CString Creater;
	int State;
	int TableType;

}CoDirectory;
//保存所有数据库的表
typedef struct
{
	CString itemnode;
	bool      isOpen;
	bool      isActive;
	CString   fileTyep;
}AllTalble;
//当前激活的表
typedef struct
{
	CString   item;
	bool      isAct;
}AcTable;
	
#endif
