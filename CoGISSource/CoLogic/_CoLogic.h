#ifndef _CoLogic_H
#define _CoLogic_H

#ifndef _CoLogic_EXPORT_
#define Logic  __declspec(dllimport)
#else
#define Logic  __declspec(dllexport)
#endif

#include "CoStructClass.h"
#include <vector>
using namespace std;

typedef float Matrix3x3 [3][3];
class _CoLogic  
{
public:
	_CoLogic();
	virtual ~_CoLogic();
};

//=================================================
//逻辑分析
//=================================================
class Logic CoLog
{
public:
	CoLog();
	CoLog(double operx,double opery);
	CoLog(double rotejd);
	~CoLog();

public:
	//从所有的点中找到最大的x
	double GetMax_X(vector<CoPnt>& Point);
	//从所有的点中找到最大的y
	double GetMax_Y(vector<CoPnt>& Point);
	//从所有的点中找到最小的x
	double GetMin_X(vector<CoPnt>& Point);
	//从所有的点中找到最小的y
	double GetMin_Y(vector<CoPnt>& Point);


	CoRect GetMaxRect(CoRect rc1,CoRect rc2);
	CoRect GetPntRect(CoPnt point,CoPntPro pointpro);
	CoRect GetFontRect(CoPnt point,CoTagPro tagpro);

public:
	//返回一个图元的外接矩形
	CoRect GetRect(vector<CoPnt>& Point);
    bool IsPointInLine(CoPnt point,vector<CoPnt>&Line);//点是否在线上
	bool IsPonEqlPon(CoPnt point1,CoPnt point2);//判断两个点是否重合

	//计算三角形的内切圆半径和圆心
	bool InnerCircle_Radius(CoPnt A,CoPnt B,CoPnt C,int& radius,CoPnt& Center);
    //点是否在线上
	bool IsPointInLine(CoPnt point,CoPnt startPoint,CoPnt endPoint);
	//计算两点距离
	double DistancePonToPon(CoPnt point1,CoPnt point2);
	//计算一条线的长度
	double DistanceLine(vector<CoPnt>& pLilne);
	//判断两点是否重合
	bool IsTwoPntEqule(CoPnt point1,CoPnt point2);
	//计算点到线的距离
	double DistancePointToLine(CoPnt point,CoPnt startPoint,CoPnt endPoint);
	//点是否在多边形内部
	bool IsPointInPolygon(CoPnt point,vector<CoPnt>& Poly);
    //判断点严格的落在线上
	bool PointInLine(CoPnt point,CoPnt startPoint,CoPnt endPoint);
	//判断2条线段是否相交
	bool IsTwoLineIntersect(CoPnt startPointA,CoPnt endPointA,CoPnt startPointB,CoPnt endPointB);

	//========================================================
	//剪断线
	bool CutLine(CoPnt point,vector<CoPnt>& Line1,vector<CoPnt>& Line2);
	//线上加点
	bool AddPntInLine(CoPnt point,vector<CoPnt>& Line);
	//得到相关点的位置
	int GetPos(CoPnt point,vector<CoPnt>& Line);
	//线上删点
	bool DeletePntLine(CoPnt point,vector<CoPnt>& Line);
	//边界加点
	bool AddPntPoly(CoPnt point,vector<CoPnt>& Poly);
	//边界删点
	bool DelPntPoly(CoPnt point,vector<CoPnt>& Poly);

	//========================================================
	//矩形与点
	bool IsPntInRect(CoPnt& Point,CoRect& rc);
	//判断一条只有两个点的线是否和一条折线相交
	bool IsTwoLineIntersect(CoPnt startPointA,CoPnt endPointA,vector<CoPnt>& Line);
	//矩形与线
	bool ISLineInRect(CoRect& rc,vector<CoPnt>& Line);
	//矩形与多边形,相离返回FALSE，否则返回TURE
	bool RectAndPoly(CoRect& rc,vector<CoPnt>&Poly);
	//======================================================
	//相等返回1，相交返回2，内含返回3,相离返回4
 	int PolygonAndPolygon(vector<CoPnt>&Polygon1,vector<CoPnt>&Polygon2);
 	//相离返回1，相交返回2，在区内返回3
 	int LineAndPolygon(vector<CoPnt>&Line,vector<CoPnt>&Polygon);
 	//相离返回1，相交返回2，在区内返回3
    int LineAndPolygon(CoPnt pntStart,CoPnt pntEnd,vector<CoPnt>&Polygon);
	//========================================================
	//相等返回1;相交返回2;相离返回3
	int LineAndLine(vector<CoPnt>& Line1,vector<CoPnt>& Line2);

	//////////////////////////////////////////////////////////////////////////
	bool TwoRectDeviat(CoRect& rc1,CoRect& rc2);

	Matrix3x3 matComposite;
	void translate2D(double tx,double ty);//二维图形平移矩阵
	void rote2D(CoPnt pivotPt,double theta);//二维图形旋转变换
	void scale2D(float sx,float sy,CoPnt fixedPt);//二维图形的比例变换
	void Matrix3x3SetIdentity(Matrix3x3 matrix3x3);//设置矩阵对角线元素为1
	void matrix3x3PerMulitiplay(Matrix3x3 m1,Matrix3x3 m2);//两矩阵相乘结果存在m2中
	void displayFcn(vector<CoPnt>&verts,int Oper);//oper为1表示平移，为2表示旋转，为3表示变比
	double m_tranx;
	double m_trany;
	double m_rotejd;
	double m_scax;
	double m_scay;
private:
	void transformVerts2D(vector<CoPnt>& verts);//计算变换后点的坐标

public:
	void CopyPnt(vector<CoPnt>&Point1,vector<CoPnt>&Point2);

	double GetArea(vector<CoPnt>&Poly);
};

//=========================================================
//画图逻辑
//=========================================================
class Logic CoCDC
{
public:
    CoCDC(CView* ptView,CoScreen Screen);
	~CoCDC();

	void DrawLine(CoPnt PointStart,CoPnt PointEnd,CoLinePro LinePro);
	void DrawPolygon(vector<CoPnt>& Poly,CoPolyPro PolyPro);
    void XDrawPolygon(vector<CoPnt>& Poly,CoPolyPro PolyPro);
	void DrawRect(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro);
    void DrawEillpse(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro);

	void DrawLine(vector<CoPnt>& Line,CoLinePro LinePro);
	void XDrawLine(vector<CoPnt>&Line,CoLinePro LinePro);
	
	void XDrawLine(CoPnt PointStart,CoPnt PointEnd,CoLinePro LinePro);
	void XDrawRect(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro);
    void XDrawEillpse(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro);
	void XDrawRectNULLFill(CoPnt Point1,CoPnt point2);
	void XDrawEillpseNullFill(CoPnt Point1,CoPnt point2,CoLinePro LinePro);

	void DrawAllPoly(vector<CoPnt>& Poly,CoPolyPro PolyPro);
	void XDrawAllPoly(vector<CoPnt>& Poly,CoPolyPro PolyPro);
	//====================================================================
	//画点

	void DrawPoint(vector<CoPnt>& Point);
	void DrawPoint(CoPnt Point);
	void DrawAllPnt(CoPnt& point,CoPntPro& pntpro);
	void XDrawAllPnt(CoPnt& point,CoPntPro& pntpro);

	void CoInvalidateRect(bool Tug,vector<CoPnt>&Point);
	void CoInvalidateRect(bool Tug,CoRect& rc);

public:
	void DrawCirclePnt(CoPnt Point,CoPntPro PntPro);
	void XDrawCirclePnt(CoPnt Point,CoPntPro PntPro);
	
	void DrawSquarePnt(CoPnt Point,CoPntPro PntPro);
	void XDrawSquarePnt(CoPnt Point,CoPntPro PntPro);

	void DrawTrianglePnt(CoPnt Point,CoPntPro PntPro);
    void XDrawTrianglePnt(CoPnt Point,CoPntPro PntPro);

	//绘制字体
	void XDrawText(CoPnt Point,CoTagPro &TagPro,int Tug);
	void DrawText(CoPnt Point,CoTagPro &TagPro);
private:
	CView* m_ptView;
	CoScreen m_Screen;

private:
	void DPtoVP(double x,double y,long *X,long *Y);
	void VPtoDP(long x,long y,double *X,double *Y);
	long DLtoVL(double l);
	double VLtoDL(long l);
};

//========================================================
//字符串操作
//========================================================

class Logic CoString
{
public:
	CoString();
	~CoString();
	CString dtostr(double a);//把double类型数据转换为string类型
	CString itostr(int b);//把int类型数据转换为string类型
	void DepTwoPart(CString &str,CString &str1,const CString tug);//把一个字符串按某一个标志分为两半
	CString GetString(CoPnt Point);
	CoPnt GetCoPnt(CString str);
};
//=========================================================
//读写文件逻辑
//=========================================================
class Logic CoRWFile
{
public:
	CoRWFile();
	~CoRWFile();
	void WriteToFile(vector<CoPnt>& Point);
	void ReadFromFile(vector<CoPnt>& Point);
};
#ifndef _CoLogic_EXPORT_
#ifdef _DEBUG
#pragma comment(lib,"CoLogic.lib")
#else
#pragma comment(lib,"CoLogic.lib")
#endif
#endif
#endif