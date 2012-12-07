#include "StdAfx.h"
#include "_CoLogic.h"
#include <math.h>

const double pi = 3.14159;

template<class T>
void SWEAP(T &a,T &b)
{
	T t;
	t = a;
	a = b;
	b = t;
}

double F(double a1,double a2,double b1,double b2)
{
	return (a1*b2-a2*b1);
}

CoLog::CoLog()
{


}

CoLog::CoLog(double operx,double opery)
{
	m_tranx = operx;
	m_trany = opery;

	m_scax = operx;
	m_scay = opery;
}

CoLog::CoLog(double rotejd)
{
	m_rotejd = rotejd;
}

CoLog::~CoLog()
{

}

double CoLog::GetMax_X(vector<CoPnt>& Point)
{
	int LineNum = Point.size();
	int pos=0; 
	for (int i=1; i<LineNum; i++)
	{
		if(Point[pos].x<Point[i].x)
			pos=i;
	}
 	return Point[pos].x;
}

double CoLog::GetMax_Y(vector<CoPnt>& Point)
{
	int LineNum = Point.size();
	int pos=0; 
	for (int i=1; i<LineNum; i++)
	{
		if(Point[pos].y<Point[i].y)
			pos=i;
	}
 	return Point[pos].y;
}

double CoLog::GetMin_X(vector<CoPnt>& Point)
{

	int LineNum = Point.size();
	int pos=0; 
	for (int i=1; i<LineNum; i++)
	{
		if(Point[pos].x>=Point[i].x)
			pos=i;
	}
 	return Point[pos].x;
}

double CoLog::GetMin_Y(vector<CoPnt>& Point)
{
	int LineNum = Point.size();
	int pos=0; 
	for (int i=1; i<LineNum; i++)
	{
		if(Point[pos].y>=Point[i].y)
			pos=i;
	}
 	return Point[pos].y;
}

CoRect CoLog::GetMaxRect(CoRect rc1,CoRect rc2)
{
	CoRect rc;
	rc.xmax = rc1.xmax>=rc2.xmax?rc1.xmax:rc2.xmax;
	rc.xmin = rc1.xmin<=rc2.xmin?rc1.xmin:rc2.xmin;
	rc.ymax = rc1.ymax>=rc2.ymax?rc1.ymax:rc2.ymax;
	rc.ymin = rc1.ymin<=rc2.ymin?rc1.ymin:rc2.ymin;
	return rc;
}

CoRect CoLog::GetPntRect(CoPnt point,CoPntPro pointpro)
{
	CoRect rc;
	rc.xmin=point.x-pointpro.PntRadio;
	rc.ymin=point.y-pointpro.PntRadio;
	rc.ymax=point.y+pointpro.PntRadio;
	rc.xmax=point.x+pointpro.PntRadio;
	return rc;
}

CoRect CoLog::GetFontRect(CoPnt point,CoTagPro tagpro)
{
	CoRect rc;
	rc.xmax=point.x+tagpro.TagStr.GetLength();
	rc.ymax=point.y+tagpro.TagStr.GetLength();
	rc.xmin=point.x-tagpro.TagStr.GetLength();
	rc.ymin=point.y-tagpro.TagStr.GetLength();
	return rc;
}

//相离返回1，相交返回2，在区内返回3
int CoLog::LineAndPolygon(vector<CoPnt>&Line,vector<CoPnt>&Polygon)
{
	int length = Line.size();
	int index = 0;
	int m=0;
	for(int i=1;i<length;i++)
	{
		m = LineAndPolygon(Line[i-1],Line[i],Polygon);
		if(m==1)
			index++;
		if(m==2)
			return 2;
	}
	if(index==length-1)
		return 1;
	return 3;
}

//相离返回1，相交返回2，在区内返回3
int CoLog::LineAndPolygon(CoPnt pntStart,CoPnt pntEnd,vector<CoPnt>&Polygon)
{
	if (IsPointInPolygon(pntStart,Polygon)&&(IsPointInPolygon(pntEnd,Polygon)))
		return 3;
	int length = Polygon.size();
	for(int i=1;i<length;i++)
	{
		if(IsTwoLineIntersect(pntStart,pntEnd,Polygon[i-1],Polygon[i]))
			return 2;
	}
	return 1;
}

//相等返回1，相交返回2，内含返回3,相离返回4,覆盖返回5
int CoLog::PolygonAndPolygon(vector<CoPnt>&Polygon1,vector<CoPnt>&Polygon2)
{
// 	if(Polygon1==Polygon2)
// 		return 1;
	if(LineAndPolygon(Polygon1,Polygon2)==2)
		return 2;
	int length= Polygon1.size();
	
	int index = 0;
	int i;
	for( i=0;i<length;i++)
	{
		if(IsPointInPolygon(Polygon1[i],Polygon2))
			index++;
	}
	if(index==length)
		return 3;
	int length2 = Polygon2.size();
	index = 0;
	
	for(i=0;i<length2;i++)
	{
		if(IsPointInPolygon(Polygon2[i],Polygon1))
			index++;
	}
	if(index==length2)
		return 5;
	return 4;
}

bool CoLog::RectAndPoly(CoRect& rc,vector<CoPnt>&Poly)
{
	vector<CoPnt>Poly1;
	CoPnt A,B,C,D;
	A.x = rc.xmin;
	A.y = rc.ymin;
	B.x = rc.xmax;
	B.y = rc.ymin;
	C.x = rc.xmax;
	C.y = rc.ymax;
	D.x = rc.xmin;
	D.y = rc.ymax;
	Poly1.push_back(A);
	Poly1.push_back(B);
	Poly1.push_back(C);
	Poly1.push_back(D);
	if(Poly.size()==2)
	{
		CoRect rc1;
		if(Poly[0].x>Poly[1].x)
		{
			rc.xmax=Poly[0].x;
			rc.xmin=Poly[1].x;
		}
		else
		{
			rc.xmax=Poly[1].x;
			rc.xmin=Poly[0].x;
		}

		if(Poly[0].y>Poly[1].y)
		{
			rc.ymax=Poly[0].y;
			rc.ymin=Poly[1].y;
		}
		else
		{
			rc.ymax=Poly[1].y;
			rc.ymin=Poly[0].y;
		}
		if(TwoRectDeviat(rc,rc1))
			return TRUE;
		return FALSE;

	}
	if(PolygonAndPolygon(Poly1,Poly)==4)
		return FALSE;
	return TRUE;
}

CoRect CoLog::GetRect(vector<CoPnt>& Point)
{
	int LineNum = Point.size();
	CoRect rect;
	rect.xmax = GetMax_X(Point);
	rect.ymax = GetMax_Y(Point);
	rect.xmin = GetMin_X(Point);
	rect.ymin = GetMin_Y(Point);
	return rect;
}

bool CoLog::InnerCircle_Radius(CoPnt A,CoPnt B,CoPnt C,int& radius,CoPnt&Center)
{

	double x1=A.x;
	double y1=A.y;
	double x2=B.x;
	double y2=B.y;
	double x3=C.x;
    double y3=C.y;

	double a1=y1-y2;
	double b1=x2-x1;
	double c1=x1*y2-x2*y1;
	
	double a2=y1-y3;
	double b2=x3-x1;
	double c2=x1*y3-x3*y1;

	double a3=y2-y3;
	double b3=x3-x2;
	double c3=x2*y3-x3*y2;
	
	double sqrt1=sqrt(a1*a1+b1*b1);
	double sqrt2=sqrt(a2*a2+b2*b2);
	double sqrt3=sqrt(a3*a3+b3*b3);

	double A1=a1*sqrt2+a2*sqrt1;
	double B1=b1*sqrt2+b2*sqrt1;
	double C1=c1*sqrt2+c2*sqrt1;
   
	double A2=a1*sqrt3-a3*sqrt1;
	double B2=b1*sqrt3-b3*sqrt1;
	double C2=c1*sqrt3-c3*sqrt1;

	double fx=F(-C1,-C2,B1,B2);
	double fy=F(A1,A2,-C1,-C2);
	double f=F(A1,A2,B1,B2);

    if(f==0)
		return false;
    Center.x=fx/f;
    Center.y=fy/f;
	
	double a=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	double b=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
	double c=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
	double l=(a+b+c)/2;
	double s=sqrt( l*(l-a)*(l-b)*(l-c) ) ;
	radius=s/l;
	return true;
}

bool  CoLog::IsPointInLine(CoPnt point,CoPnt startPoint,CoPnt endPoint)
{
	long AX=startPoint.x;
	long AY=startPoint.y;
	long BX=endPoint.x;
	long BY=endPoint.y;
	long PX=point.x;
	long PY=point.y;
	
	double dx_AB=AX-BX;
	double dy_AB=AY-BY;
	double dx_PA=PX-AX;
	double dy_PA=PY-AY;
	double dx_PB=PX-BX;
	double dy_PB=PY-BY;
	
	double AB=sqrt(dx_AB*dx_AB+dy_AB*dy_AB);
	double PA=sqrt(dx_PA*dx_PA+dy_PA*dy_PA);
	double PB=sqrt(dx_PB*dx_PB+dy_PB*dy_PB);
	double rate=abs(PA+PB-AB)/AB;
	if (rate<0.00001)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CoLog::CopyPnt(vector<CoPnt>&Point1,vector<CoPnt>&Point2)
{
	int length = Point1.size();
	for(int i=0;i<length;i++)
		Point2.push_back(Point1[i]);
}
//判断点到点的距离
double CoLog::DistancePonToPon(CoPnt point1,CoPnt point2)
{
	double x1,y1;
	double x2,y2;
	double dis(0.0);
	x1 = point1.x;y1 = point1.y;
	x2 = point2.x;y2 = point2.y;
	dis = sqrt(double((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
	return dis;
}
//判断一条线的长度
double CoLog::DistanceLine(vector<CoPnt>& pLilne)
{
	double dis(0.0);
	for (int i=0;i<pLilne.size()-1;i++)
	{
		dis+=DistancePonToPon(pLilne[i],pLilne[i+1]);
	}
	return dis;
}
bool CoLog::IsTwoPntEqule(CoPnt point1,CoPnt point2)
{
	double dis = DistancePonToPon(point1,point2);
	if(dis<3)
		return TRUE;
	return FALSE;
}

double CoLog::DistancePointToLine(CoPnt point,CoPnt startPoint,CoPnt endPoint)
{
	long x,y;
	long x1,y1;
	long x2,y2;
	x = point.x; y = point.y;
	x1 = startPoint.x; y1 = startPoint.y;
	x2 = endPoint.x; y2 = endPoint.y;
	double k = double(y1-y2)/double(x1-x2);
	double A = k;
	double B = -1;
	double C = y1 - k*x1;
	double d = (A*x + B*y + C)/sqrt(A*A+B*B);
	return fabs(d);
}

bool  CoLog::PointInLine(CoPnt point,CoPnt startPoint,CoPnt endPoint)
{
	int x1=startPoint.x;
	int y1=startPoint.y;
	int x2=endPoint.x;
	int y2=endPoint.y;
	int PX=point.x;
	int PY=point.y;
	
    int xMin=min(x1,x2);
	int xMax=max(x1,x2);
    int yMin=min(y1,y2);
	int yMax=max(y1,y2);
	if(PX<xMin||PX>xMax||PY<yMin||PY>yMax)
		return false;
	int result=(PX-x1)*(PY-y2)-(PY-y1)*(PX-x2);
    if (result!=0) return false;
    else return true;
}

bool CoLog::IsPointInPolygon(CoPnt point,vector<CoPnt>& Poly)
{
	int LineNum = Poly.size();
	CoPnt leftP=point;
    CoPnt rightP;
	rightP.x = GetMax_X(Poly)+1;
	rightP.y = point.y;
    int count=0,yPrev=Poly[LineNum-2].y;
	CoPnt v1, v2;
	v1=Poly[LineNum-1];
	for (int i=0; i<LineNum; i++) 
	{
		v2=Poly[i];
        
        if(PointInLine(leftP,v1,v2)) 
			return true;
		
		if(v1.y!=v2.y) 
		{
			if(IsTwoLineIntersect(v1,v2,leftP,rightP))
			{
				if(PointInLine(v1,leftP,rightP))
				{
					if(v1.y<v2.y) {if(v1.y>yPrev)count++;}
					else {if(v1.y<yPrev) count++; } 
				}
				else if(!PointInLine(v2,leftP,rightP))
				{
					count++;
				}
			}
		}
		yPrev=v1.y;
		
		v1=v2;
	}
	return   (count%2==1);   
}



bool CoLog::IsTwoLineIntersect(CoPnt startPointA,CoPnt endPointA,CoPnt startPointB,CoPnt endPointB)
{
    double x1=startPointA.x;
	double y1=startPointA.y;
	double x2=endPointA.x;
	double y2=endPointA.y;
	double x3=startPointB.x;
	double y3=startPointB.y;
	double x4=endPointB.x;
	double y4=endPointB.y;
	double result=(x2-x1)*(y4-y3)-(x4-x3)*(y2-y1);
	if(result)
	{
		double G_x1y1=(y1-y3)*(x4-x3)-(y4-y3)*(x1-x3);
		double G_x2y2=(y2-y3)*(x4-x3)-(y4-y3)*(x2-x3);
		double F_x3y3=(y3-y1)*(x2-x1)-(y2-y1)*(x3-x1);
		double F_x4y4=(y4-y1)*(x2-x1)-(y2-y1)*(x4-x1);
		if (F_x3y3*F_x4y4<=0&&G_x1y1*G_x2y2<=0)
		  return true;
		else
			return false;
	}
  else
  {
	  return false;
  }
}

bool CoLog::IsTwoLineIntersect(CoPnt startPointA,CoPnt endPointA,vector<CoPnt>& Line)
{
	int Size = Line.size();
	for(int i=1;i<Size;i++)
	{
		if(IsTwoLineIntersect(startPointA,endPointA,Line[i-1],Line[i]))
			return TRUE;

	}
	return FALSE;
}

bool CoLog::ISLineInRect(CoRect& rc,vector<CoPnt>& Line)
{
	CoPnt A,B,C,D;
	A.x = rc.xmin-2;
	A.y = rc.ymin-2;
	B.x = rc.xmax+2;
	B.y = rc.ymin+2;
	C.x = rc.xmax+2;
	C.y = rc.ymax+2;
	D.x = rc.xmin-2;
	D.y = rc.ymax+2;
	if (IsTwoLineIntersect(A,B,Line))
		return TRUE;
	if (IsTwoLineIntersect(B,C,Line))
		return TRUE;
	if (IsTwoLineIntersect(C,D,Line))
		return TRUE;
	if (IsTwoLineIntersect(A,D,Line))
		return TRUE;
	return FALSE;
}

bool CoLog::IsPntInRect(CoPnt& Point,CoRect& rc)
{
	if((Point.x>=(rc.xmin-4))&&(Point.x<=(rc.xmax+4))&&(Point.y>=(rc.ymin-4))&&(Point.y<=(rc.ymax+4)))
		return TRUE;
	return FALSE;
}

bool CoLog::TwoRectDeviat(CoRect& rc1,CoRect& rc2)
{
	if (rc1.xmax<=rc2.xmin)
		return TRUE;
	if (rc1.xmin>=rc2.xmax)
		return TRUE;
	if(rc1.ymin>=rc2.ymax)
		return TRUE;
	if (rc1.ymax<=rc2.ymin)
		return TRUE;
	return FALSE;

}

bool CoLog::CutLine(CoPnt point,vector<CoPnt>& Line1,vector<CoPnt>& Line2)
{
	vector<CoPnt>Line;
	Line = Line1;
	int length = Line1.size();
	int pos = 0;
	bool tug = FALSE;
	for (int i=1;i<length;i++)
	{
		if (IsPointInLine(point,Line[i-1],Line[i]))
		{
			pos = i;
			tug = TRUE;
			break;
		}
	}

	if (tug)
	{
		Line1.clear();
		int j;
		for( j=0;j<pos;j++)
			Line1.push_back(Line[j]);
		Line1.push_back(point);

		Line2.push_back(point);
		for(j=pos;j<length;j++)
			Line2.push_back(Line[j]);

		return TRUE;
	}

	return FALSE;

}

bool CoLog::AddPntInLine(CoPnt point,vector<CoPnt>& Line)
{
	bool Tug = FALSE;
	int length = Line.size();
	vector<CoPnt>MyLine;
	int pos = 0;
	for (int i=1;i<length;i++)
	{
		if (IsPointInLine(point,Line[i-1],Line[i]))
		{
			Tug = TRUE;
			pos = i;
		}
		MyLine.push_back(Line[i-1]);
		if(Tug)
			break;
	}
	
	if (Tug)
	{
		MyLine.push_back(point);
		for (int j=pos;j<length;j++)
		{
			MyLine.push_back(Line[j]);
		}
		Line=MyLine;
		MyLine.clear();
		return TRUE;
	}
	return FALSE;
	
}

int CoLog::GetPos(CoPnt point,vector<CoPnt>& Line)
{
	int length = Line.size();
	double dis=0.0;
	for (int i=0;i<length;i++)
	{
		dis=DistancePonToPon(point,Line[i]);
		if (dis<=3)
			return i;
	}
	return -1;
}

bool CoLog::DeletePntLine(CoPnt point,vector<CoPnt>& Line)
{
	bool tug=FALSE;
	int length = Line.size();
	double dis=0.0;
	vector<CoPnt>MyPoints;
	int pos=0;
	int i;
	for ( i=0;i<length;i++)
	{
		dis=DistancePonToPon(point,Line[i]);
		if (dis<=3)
		{
			tug=TRUE;
			pos=i;
			break;
		}
		MyPoints.push_back(Line[i]);
	}
	if(tug)
	{
		if(pos<length-1)
		{
			for(i=pos+1;i<length;i++)
				MyPoints.push_back(Line[i]);
		}
		Line = MyPoints;
		MyPoints.clear();
		return TRUE;
	}
	return FALSE;
}


bool CoLog::AddPntPoly(CoPnt point,vector<CoPnt>& Poly)
{
	bool Tug = FALSE;
	int length = Poly.size();
	if(IsPointInLine(point,Poly[0],Poly[length-1]))
	{
		Poly.push_back(point);
		return TRUE;
	}
	vector<CoPnt>MyPoly;
	int pos = 0;
	for (int i=1;i<length;i++)
	{
		if (IsPointInLine(point,Poly[i-1],Poly[i]))
		{
			Tug = TRUE;
			pos = i;
		}
		MyPoly.push_back(Poly[i-1]);
		if(Tug)
			break;
	}
	
	if (Tug)
	{
		MyPoly.push_back(point);
		for (int j=pos;j<length;j++)
		{
			MyPoly.push_back(Poly[j]);
		}
		Poly=MyPoly;
		MyPoly.clear();
		return TRUE;
	}
	return FALSE;
}

bool CoLog::DelPntPoly(CoPnt point,vector<CoPnt>& Poly)
{
	bool tug=FALSE;
	int length = Poly.size();
	if(length<=3)
		return FALSE;
	double dis=0.0;
	vector<CoPnt>MyPoints;
	int pos=0;
	int i;
	for ( i=0;i<length;i++)
	{
		dis=DistancePonToPon(point,Poly[i]);
		if (dis<=3)
		{
			tug=TRUE;
			pos=i;
			break;
		}
		MyPoints.push_back(Poly[i]);
	}
	if(tug)
	{
		if(pos<length-1)
		{
			for(i=pos+1;i<length;i++)
				MyPoints.push_back(Poly[i]);
		}
		Poly = MyPoints;
		MyPoints.clear();
		return TRUE;
	}
	return FALSE;
}

////////////////////////////
void CoLog::Matrix3x3SetIdentity(Matrix3x3 matIdentx3x3)
{
	int row,col;
	for (row = 0;row<3;row++)
		for(col=0;col<3;col++)
			matIdentx3x3[row][col]=(row == col);
}

void CoLog::matrix3x3PerMulitiplay(Matrix3x3 m1,Matrix3x3 m2)
{
	int row,col;
	Matrix3x3 matTemp;
	for (row=0;row<3;row++)
		for(col=0;col<3;col++)
			matTemp [row][col] = m1[row][0] * m2[0][col]+
			m1[row][1]*m2 [1][col]+m1[row][2]*m2[2][col];
		for (row=0;row<3;row++)
			for(col=0;col<3;col++)
				m2[row][col] = matTemp[row][col];
}

void CoLog::translate2D(double tx,double ty)
{
	Matrix3x3 matTransl;
	Matrix3x3SetIdentity(matTransl);//初始化
	matTransl[0][2] = tx;
	matTransl[1][2] = ty;
	matrix3x3PerMulitiplay(matTransl,matComposite);
}

void CoLog::rote2D(CoPnt pivotPt,double theta)
{
	Matrix3x3 matRot;
	Matrix3x3SetIdentity(matRot);
	matRot [0][0] = cos(theta);
	matRot [0][1] = -sin(theta);
	matRot [0][2] = pivotPt.x *(1-cos(theta))+pivotPt.y*sin(theta);
	matRot [1][0] = sin(theta);
	matRot [1][1] = cos(theta);
	matRot [1][2] = pivotPt.y * (1 - cos(theta)) - pivotPt.x*sin(theta);
	matrix3x3PerMulitiplay(matRot,matComposite);
}

void CoLog::scale2D(float sx,float sy,CoPnt fixedPt)
{
	Matrix3x3 matScale;
	Matrix3x3SetIdentity(matScale);
	
	matScale[0][0] = sx;
	matScale[0][2] = (1-sx)*fixedPt.x;
	matScale[1][1] = sy;
	matScale[1][2] = (1-sy) *fixedPt.y;
	matrix3x3PerMulitiplay(matScale,matComposite);
}

void CoLog::transformVerts2D(vector<CoPnt>& verts)
{
	int nVerts = verts.size();
	int k;
	double temp;
	for(k=0;k<nVerts;k++)
	{
		temp = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
		verts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y +matComposite[1][2];
		verts[k].x = temp;
	}
}

void CoLog::displayFcn(vector<CoPnt>&verts,int Oper)
{
	int k=0;
	double xsum(0.0),ysum(0.0);
	int length = verts.size();
	for(k=0;k<length;k++)
	{
		xsum += verts[k].x;
		ysum += verts[k].y;
	}

	CoPnt centroidPt;
	centroidPt.x = xsum/double(length);
	centroidPt.y = ysum/double(length);

	Matrix3x3SetIdentity(matComposite);
	switch(Oper)
	{
	case 1:
		translate2D(m_tranx,m_trany);
		transformVerts2D(verts);
		break;

	case 2:
		rote2D(centroidPt,m_rotejd);
		transformVerts2D(verts);
		break;
	case 3:
		scale2D(m_scax,m_scay,centroidPt);
		transformVerts2D(verts);
		break;

	default:
		break;
	}

	for(k=0;k<length;k++)
	{
		verts[k].x = verts[k].x;
		verts[k].y = verts[k].y;
	}
}

double CoLog::GetArea(vector<CoPnt>&Poly)
{
	int length = Poly.size();
	double Area = 0.0;
	for(int i=1;i<length;i++)
	{
		Area+=(1/2)*(Poly[i-1].y+Poly[i].y)*(Poly[i].x-Poly[i-1].x);
	}
	return fabs(Area);
}

int CoLog::LineAndLine(vector<CoPnt>& Line1,vector<CoPnt>& Line2)
{
	int legth1 = Line1.size();
	int length2 = Line2.size();

		for(int i=1;i<legth1;i++)
		{
			for(int j=1;j<length2;j++)
				if(IsTwoLineIntersect(Line1[i-1],Line1[i],Line2[j-1],Line2[j]))
				{
					return 2;
				}
		}
		return 3;
}

bool CoLog::IsPointInLine(CoPnt point,vector<CoPnt>& Line)
{
	int MySize = Line.size();
	for(int i=0;i<MySize-1;i++)
	{
		if(IsPointInLine(point,Line[i],Line[i+1]))
			return TRUE;
	}
	return FALSE;
}

bool CoLog::IsPonEqlPon(CoPnt point1,CoPnt point2)
{
	double dis = DistancePonToPon(point1,point2);
	if (dis<=4)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////


//==========================================================================

//==========================================================================

CoCDC::CoCDC(CView* ptView,CoScreen Screen)
{
	m_ptView = ptView;
	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoCDC::~CoCDC()
{
	
}

void CoCDC::DPtoVP(double x,double y,long *X,long *Y)
{
	*X=(int)((x-m_Screen.sx)/m_Screen.blc);
/*	if(m_MapMode==1)*/
		*Y=m_Screen.hScreen-(int)((y-m_Screen.sy)/m_Screen.blc);
// 	else
// 		*Y=(int)((y-m_yStart)/m_blc)-m_hScreen;
}

void CoCDC::VPtoDP(long x,long y,double *X,double *Y)
{
	*X=m_Screen.sx+x*(m_Screen.blc);
//	if(m_MapMode==1)
		*Y=m_Screen.sy+(m_Screen.blc)*(m_Screen.hScreen-y);
// 	else
// 		*Y=m_yStart+m_blc*(y+m_hScreen);
}

long CoCDC::DLtoVL(double l)
{
	return (long)l/(m_Screen.blc);
}

double CoCDC::VLtoDL(long l)
{
	return double(l)*m_Screen.blc;
}


void CoCDC::DrawLine(CoPnt PointStart,CoPnt PointEnd,CoLinePro LinePro)
{
	CClientDC dc(m_ptView);

	COLORREF cor = LinePro.LineColor;
	int LineWide = LinePro.LineWidth;
	int LineStyle = LinePro.LineStyle;
	CPen Pen(LineStyle,LineWide,cor);
	CPen* OldPen =dc.SelectObject(&Pen);
	CPoint Point1;
	CPoint Point2;
	DPtoVP(PointStart.x,PointStart.y,&Point1.x,&Point1.y);
	DPtoVP(PointEnd.x,PointEnd.y,&Point2.x,&Point2.y);
	dc.MoveTo(Point1);
	dc.LineTo(Point2);
	dc.SelectObject(OldPen);
}

void CoCDC::XDrawLine(CoPnt PointStart,CoPnt PointEnd,CoLinePro LinePro)
{
	CClientDC dc(m_ptView);
	dc.SetROP2(R2_NOTXORPEN);
	COLORREF cor = LinePro.LineColor;
	int LineWide = LinePro.LineWidth;
	int LineStyle = LinePro.LineStyle;
	CPen Pen(LineStyle,LineWide,cor);
	CPen* OldPen =dc.SelectObject(&Pen);
	CPoint Point1;
	CPoint Point2;
	DPtoVP(PointStart.x,PointStart.y,&Point1.x,&Point1.y);
	DPtoVP(PointEnd.x,PointEnd.y,&Point2.x,&Point2.y);
	dc.MoveTo(Point1);
	dc.LineTo(Point2);
	dc.SelectObject(OldPen);
}

void CoCDC::DrawPolygon(vector<CoPnt>& Poly,CoPolyPro PolyPro)
{
	int PolyNum = Poly.size();
	CClientDC dc(m_ptView);

	CBrush MyBrush(PolyPro.PolyFillStyle,PolyPro.PolyColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPen Pen(0,1,RGB(0,0,0));
	CPen* OldPen = dc.SelectObject(&Pen);
	CPoint* PointArray = new CPoint[PolyNum];
	for(int i=0;i<PolyNum;i++)
	{
		DPtoVP(Poly[i].x,Poly[i].y,&PointArray[i].x,&PointArray[i].y);
	}
	dc.Polygon(PointArray,PolyNum);
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
	delete []PointArray;
}

void CoCDC::XDrawPolygon(vector<CoPnt>& Poly,CoPolyPro PolyPro)
{
	int PolyNum = Poly.size();
	CClientDC dc(m_ptView);
	dc.SetROP2(R2_NOTXORPEN);
	CBrush MyBrush(PolyPro.PolyFillStyle,PolyPro.PolyColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPen Pen(0,1,RGB(0,0,0));
	CPen* OldPen = dc.SelectObject(&Pen);
	CPoint* PointArray = new CPoint[PolyNum];
	for(int i=0;i<PolyNum;i++)
	{
		DPtoVP(Poly[i].x,Poly[i].y,&PointArray[i].x,&PointArray[i].y);
	}
	dc.Polygon(PointArray,PolyNum);
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
	delete []PointArray;
}

void CoCDC::DrawRect(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro)
{
	CClientDC dc(m_ptView);	


	CPen pen(0,1,RGB(0,0,0));
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PolyPro.PolyFillStyle,PolyPro.PolyColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint MyPoint1;
	CPoint MyPoint2;
	DPtoVP(Point1.x,Point1.y,&MyPoint1.x,&MyPoint1.y);
	DPtoVP(point2.x,point2.y,&MyPoint2.x,&MyPoint2.y);
	CRect re(MyPoint1,MyPoint2);
	dc.Rectangle(re);
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}



void CoCDC::XDrawRect(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro)
{
	CClientDC dc(m_ptView);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(0,1,RGB(0,0,0));
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PolyPro.PolyFillStyle,PolyPro.PolyColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint MyPoint1;
	CPoint MyPoint2;
	DPtoVP(Point1.x,Point1.y,&MyPoint1.x,&MyPoint1.y);
	DPtoVP(point2.x,point2.y,&MyPoint2.x,&MyPoint2.y);
	CRect re(MyPoint1,MyPoint2);
	dc.Rectangle(re);
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}


void CoCDC::XDrawRectNULLFill(CoPnt Point1,CoPnt point2)
{
	CClientDC dc(m_ptView);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(0,1,RGB(255,0,0));
	CPen* OldPen = dc.SelectObject(&pen);
	
	CPoint MyPoint1;
	CPoint MyPoint2;
	DPtoVP(Point1.x,Point1.y,&MyPoint1.x,&MyPoint1.y);
	DPtoVP(point2.x,point2.y,&MyPoint2.x,&MyPoint2.y);
	CRect re(MyPoint1,MyPoint2);
	dc.Rectangle(re);
	dc.SelectObject(OldPen);
}

void CoCDC::DrawEillpse(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro)
{

	CClientDC dc(m_ptView);

	CPen pen(0,1,RGB(0,0,0));
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PolyPro.PolyFillStyle,PolyPro.PolyColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint MyPoint1;
	CPoint MyPoint2;
	DPtoVP(Point1.x,Point1.y,&MyPoint1.x,&MyPoint1.y);
	DPtoVP(point2.x,point2.y,&MyPoint2.x,&MyPoint2.y);
	CRect re(MyPoint1,MyPoint2);
	dc.Ellipse(re);
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}

void CoCDC::XDrawEillpse(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro)
{
	
	CClientDC dc(m_ptView);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(0,1,RGB(0,0,0));
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PolyPro.PolyFillStyle,PolyPro.PolyColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint MyPoint1;
	CPoint MyPoint2;
	DPtoVP(Point1.x,Point1.y,&MyPoint1.x,&MyPoint1.y);
	DPtoVP(point2.x,point2.y,&MyPoint2.x,&MyPoint2.y);
	CRect re(MyPoint1,MyPoint2);
	dc.Ellipse(re);
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}

void CoCDC::XDrawEillpseNullFill(CoPnt Point1,CoPnt point2,CoLinePro LinePro)
{
	CClientDC dc(m_ptView);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(0,1,RGB(0,0,0));
	CPen* OldPen = dc.SelectObject(&pen);
	CPoint MyPoint1;
	CPoint MyPoint2;
	DPtoVP(Point1.x,Point1.y,&MyPoint1.x,&MyPoint1.y);
	DPtoVP(point2.x,point2.y,&MyPoint2.x,&MyPoint2.y);
	CRect re(MyPoint1,MyPoint2);
	dc.Ellipse(re);
	dc.SelectObject(OldPen);
}

void CoCDC::DrawLine(vector<CoPnt>& Line,CoLinePro LinePro)
{
	int LineNum = Line.size();
	for(int i=1;i<LineNum;i++)
		DrawLine(Line[i-1],Line[i],LinePro);
}

void CoCDC::XDrawLine(vector<CoPnt>&Line,CoLinePro LinePro)
{
	int LineNum = Line.size();
	for(int i=1;i<LineNum;i++)
		XDrawLine(Line[i-1],Line[i],LinePro);
}
//=======================================================
void CoCDC::DrawCirclePnt(CoPnt Point,CoPntPro PntPro)
{
	CClientDC dc(m_ptView);

	CPen pen(0,1,PntPro.PntColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.PntColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint Point1,Point2;
	DPtoVP(Point.x-PntPro.PntRadio,Point.y+PntPro.PntRadio,&Point1.x,&Point1.y);
	DPtoVP(Point.x+PntPro.PntRadio,Point.y-PntPro.PntRadio,&Point2.x,&Point2.y);
	dc.Ellipse(CRect(Point1,Point2));
    dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}

void CoCDC::XDrawCirclePnt(CoPnt Point,CoPntPro PntPro)
{
	CClientDC dc(m_ptView);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(0,1,PntPro.PntColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.PntColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint Point1,Point2;
	DPtoVP(Point.x-PntPro.PntRadio,Point.y+PntPro.PntRadio,&Point1.x,&Point1.y);
	DPtoVP(Point.x+PntPro.PntRadio,Point.y-PntPro.PntRadio,&Point2.x,&Point2.y);
	dc.Ellipse(CRect(Point1,Point2));
    dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}

void CoCDC::DrawSquarePnt(CoPnt Point,CoPntPro PntPro)
{
	CClientDC dc(m_ptView);

	CPen pen(0,1,PntPro.PntColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.PntColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint Point1,Point2;
	DPtoVP(Point.x-PntPro.PntRadio,Point.y+PntPro.PntRadio,&Point1.x,&Point1.y);
	DPtoVP(Point.x+PntPro.PntRadio,Point.y-PntPro.PntRadio,&Point2.x,&Point2.y);
	dc.Rectangle(CRect(Point1,Point2));
    dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);

}
void CoCDC::XDrawSquarePnt(CoPnt Point,CoPntPro PntPro)
{
	CClientDC dc(m_ptView);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(0,1,PntPro.PntColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.PntColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint Point1,Point2;
	DPtoVP(Point.x-PntPro.PntRadio,Point.y+PntPro.PntRadio,&Point1.x,&Point1.y);
	DPtoVP(Point.x+PntPro.PntRadio,Point.y-PntPro.PntRadio,&Point2.x,&Point2.y);
	dc.Rectangle(CRect(Point1,Point2));
    dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}

void CoCDC::DrawTrianglePnt(CoPnt Point,CoPntPro PntPro)
{
	double radio = PntPro.PntRadio;
	if(!radio)
		return;
	else
		radio += 4; 
	CClientDC dc(m_ptView);
	CPen pen(0,1,PntPro.PntColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.PntColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	double r1 = sqrtf(3)/2*radio;
	CPoint* MyArray = new CPoint[3];
	DPtoVP(Point.x,Point.y+r1,&MyArray[0].x,&MyArray[0].y);
	DPtoVP(Point.x-radio/2,Point.y,&MyArray[1].x,&MyArray[1].y);
	DPtoVP(Point.x+radio/2,Point.y,&MyArray[2].x,&MyArray[2].y);
	dc.Polygon(MyArray,3);
    dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}

void CoCDC::XDrawTrianglePnt(CoPnt Point,CoPntPro PntPro)
{
	double radio = PntPro.PntRadio;
	if(!radio)
		return;
	else
		radio += 4; 
	CClientDC dc(m_ptView);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(0,1,PntPro.PntColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.PntColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	double r1 = sqrtf(3)/2*radio;
	CPoint* MyArray = new CPoint[3];
	DPtoVP(Point.x,Point.y+r1,&MyArray[0].x,&MyArray[0].y);
	DPtoVP(Point.x-radio/2,Point.y,&MyArray[1].x,&MyArray[1].y);
	DPtoVP(Point.x+radio/2,Point.y,&MyArray[2].x,&MyArray[2].y);
	dc.Polygon(MyArray,3);
    dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}

void CoCDC::DrawAllPnt(CoPnt& point,CoPntPro& pntpro)
{
	int Radio=0;
	int style = pntpro.PntStyle;
	switch(style)
	{
	case 0:
		DrawCirclePnt(point,pntpro);
		break;
	case 1:
		DrawTrianglePnt(point,pntpro);
		break;
	case 2:
		DrawSquarePnt(point,pntpro);
		break;
	default:
		break;
	}
}

void CoCDC::DrawPoint(vector<CoPnt>& Point)
{
	int Size = Point.size();
	CoPntPro pntpro;
	pntpro.PntColor=RGB(0,255,0);
	pntpro.PntRadio=3;
	pntpro.PntStyle=1;
	for(int i=0;i<Size;i++)
		DrawSquarePnt(Point[i],pntpro);
}

void CoCDC::DrawPoint(CoPnt Point)
{
	CoPntPro pntpro;
	pntpro.PntColor=RGB(0,255,0);
	pntpro.PntRadio=3;
	pntpro.PntStyle=1;
	DrawSquarePnt(Point,pntpro);
}

void CoCDC::XDrawAllPnt(CoPnt& point,CoPntPro& pntpro)
{
	int Radio=0;
	int style = pntpro.PntStyle;
	switch(style)
	{
	case 0:
		XDrawCirclePnt(point,pntpro);
		break;
	case 1:
		XDrawTrianglePnt(point,pntpro);
		break;
	case 2:
		XDrawSquarePnt(point,pntpro);
		break;
	default:
		break;
	}
}

void CoCDC::DrawAllPoly(vector<CoPnt>& Poly,CoPolyPro PolyPro)
{
	int Radio;
	CoPnt Center,Point1,Point2;

	CoLog math;
	int style = PolyPro.PolyStyle;
	switch(style)
	{
	case 0:
		DrawRect(Poly[0],Poly[1],PolyPro);
		break;
	case 1:
		DrawPolygon(Poly,PolyPro);
		break;
	case 2:
		DrawEillpse(Poly[0],Poly[1],PolyPro);
		break;
	case 3:
		math.InnerCircle_Radius(Poly[0],Poly[1],Poly[2],Radio,Center);
		Point1.x = Center.x-Radio;
		Point1.y = Center.y+Radio;
		Point2.x = Center.x+Radio;
		Point2.y = Center.y-Radio;
		DrawEillpse(Point1,Point2,PolyPro);
		break;
	case 4:
		DrawPolygon(Poly,PolyPro);
		break;
	default:
		break;
	}
}

void CoCDC::XDrawAllPoly(vector<CoPnt>& Poly,CoPolyPro PolyPro)
{
	int Radio;
	CoPnt Center,Point1,Point2;
	
	CoLog math;
	int style = PolyPro.PolyStyle;
	switch(style)
	{
	case 0:
		XDrawRect(Poly[0],Poly[1],PolyPro);
		break;
	case 1:
		XDrawPolygon(Poly,PolyPro);
		break;
	case 2:
		XDrawEillpse(Poly[0],Poly[1],PolyPro);
		break;
	case 3:
		math.InnerCircle_Radius(Poly[0],Poly[1],Poly[2],Radio,Center);
		Point1.x = Center.x-Radio;
		Point1.y = Center.y+Radio;
		Point2.x = Center.x+Radio;
		Point2.y = Center.y-Radio;
		XDrawEillpse(Point1,Point2,PolyPro);
		break;
	case 4:
		XDrawPolygon(Poly,PolyPro);
		break;
	default:
		break;
	}
}

void CoCDC::CoInvalidateRect(bool Tug,vector<CoPnt>&Point)
{
	CRect rc;
	CoLog math;
	CPoint A,B;
	A.x=long(math.GetMin_X(Point));
	A.y=long(math.GetMin_Y(Point));
	B.x=long(math.GetMax_X(Point));
	B.y=long(math.GetMax_Y(Point));
	m_ptView->InvalidateRect(CRect(A,B),Tug);

}

void CoCDC::CoInvalidateRect(bool Tug,CoRect& rc)
{
	CRect rc1;
	CoLog math;
	CPoint A,B;
	A.x=long(rc.xmin);
	A.y=long(rc.ymin);
	B.x=long(rc.xmax);
	B.y=long(rc.ymax);
	m_ptView->InvalidateRect(CRect(A,B),Tug);
}

void CoCDC::DrawText(CoPnt Point,CoTagPro &TagPro)
{
	CClientDC pDC(m_ptView);

	CFont cjcf;								//定义一个字模
	long high,wide,cc1,cc2,cd,angg;
	unsigned char c1,c2;
	float x1,y1,ang1;
	char bz[4];
	const char *ls1;

	high = DLtoVL(TagPro.TagHeight);            //得到字体的点阵高度
	//high=(int)TagPro.TagHeight;				//得到字体的点阵高度
	ang1=(float)(TagPro.TagAngle*pi/180);
	angg=(int)(TagPro.TextAngle*10);
	wide = DLtoVL(TagPro.TagWidth);
//	wide=(int)TagPro.TagWidth;

	//起始点的屏幕点阵坐标
	x1=Point.x;y1=Point.y;
	DPtoVP(x1,y1,&cc1,&cc2);
	//cc1=(int)x1;cc2=(int)y1;
	//创建字模
	cjcf.CreateFont(high,wide,angg,0,50,0,0,0,255,OUT_TT_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,TagPro.TagFont);
	//选中字模
	CFont* cjcbakf=pDC.SelectObject(&cjcf);
	pDC.SetBkMode(TRANSPARENT);				//设定显示方式
	pDC.SetTextColor(TagPro.TagColor);		//设定文本颜色
	ls1=(const char *)TagPro.TagStr;        //文本内容
	cd=strlen(ls1);							//文本字符长度
	while(cd>0)								//绘出所有的字符
	{
		c1=*ls1;
		c2=*(ls1+1);
		if(c1>127&&c2>127)					//如果是一个汉字
		{
			strncpy(bz,ls1,2);				//拷贝一个汉字到bz中
			bz[2]=0;
			ls1=ls1+2;						//跳过汉字指向下一个字符位置
			pDC.TextOut(cc1,cc2,bz);		//在屏幕上写这个汉字
			cd=cd-2;						//字符数减2
											//下一个字符的显示位置
			x1=x1+(TagPro.TagWidth*2+TagPro.TagOffsite)*(float)cos(ang1);
			y1=y1+(TagPro.TagWidth*2+TagPro.TagOffsite)*(float)sin(ang1);
											//下一个字符显示位置的屏幕坐标
		//	cc1=(int)x1;cc2=(int)y1;
			DPtoVP(x1,y1,&cc1,&cc2);
		}
		else								//如果是一个西文字符
		{
			strncpy(bz,ls1,1);				//拷贝一个字符到bz中
			bz[1]=0;
			ls1++;							//跳过这一个字符到下一个字符
			pDC.TextOut(cc1,cc2,bz);		//在屏幕上写字符
			cd=cd-1;						//字符数减1
			//下一个字符的显示位置的实际坐标
			x1=x1+(TagPro.TagWidth+TagPro.TagOffsite/2)*(float)cos(ang1);
			y1=y1+(TagPro.TagWidth+TagPro.TagOffsite/2)*(float)sin(ang1);
			//下一个字符显示位置的屏幕坐标
			//cc1=(int)x1;cc2=(int)y1;
			DPtoVP(x1,y1,&cc1,&cc2);
		}
	} 
	pDC.SelectObject(cjcbakf);				//恢复字模
}


void CoCDC::XDrawText(CoPnt Point,CoTagPro &TagPro,int Tug)
{

	COLORREF MyCor;
	if(Tug==1)
	{
		MyCor = RGB(255,0,0);
	}
	if(Tug==2)
	{
		MyCor = RGB(0,255,0);
	}
	if(Tug==3)
	{
		MyCor = RGB(0,0,255);
	}
	CClientDC pDC(m_ptView);
	
	CFont cjcf;								//定义一个字模
	long high,wide,cc1,cc2,cd,angg;
	unsigned char c1,c2;
	float x1,y1,ang1;
	char bz[4];
	const char *ls1;
	
	high = DLtoVL(TagPro.TagHeight);            //得到字体的点阵高度
	//high=(int)TagPro.TagHeight;				//得到字体的点阵高度
	ang1=(float)(TagPro.TagAngle*pi/180);
	angg=(int)(TagPro.TextAngle*10);
	wide = DLtoVL(TagPro.TagWidth);
	//	wide=(int)TagPro.TagWidth;
	
	//起始点的屏幕点阵坐标
	x1=Point.x;y1=Point.y;
	DPtoVP(x1,y1,&cc1,&cc2);
	//cc1=(int)x1;cc2=(int)y1;
	//创建字模
	cjcf.CreateFont(high,wide,angg,0,50,0,0,0,255,OUT_TT_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,TagPro.TagFont);
	//选中字模
	CFont* cjcbakf=pDC.SelectObject(&cjcf);
	pDC.SetBkMode(TRANSPARENT);				//设定显示方式
	//pDC.SetTextColor(MyCor);		               //设定文本颜色
	ls1=(const char *)TagPro.TagStr;        //文本内容
	cd=strlen(ls1);							//文本字符长度
	while(cd>0)								//绘出所有的字符
	{
		c1=*ls1;
		c2=*(ls1+1);
		if(c1>127&&c2>127)					//如果是一个汉字
		{
			strncpy(bz,ls1,2);				//拷贝一个汉字到bz中
			bz[2]=0;
			ls1=ls1+2;						//跳过汉字指向下一个字符位置
			pDC.TextOut(cc1,cc2,bz);		//在屏幕上写这个汉字
			cd=cd-2;						//字符数减2
			//下一个字符的显示位置
			x1=x1+(TagPro.TagWidth*2+TagPro.TagOffsite)*(float)cos(ang1);
			y1=y1+(TagPro.TagWidth*2+TagPro.TagOffsite)*(float)sin(ang1);
			//下一个字符显示位置的屏幕坐标
			//	cc1=(int)x1;cc2=(int)y1;
			DPtoVP(x1,y1,&cc1,&cc2);
		}
		else								//如果是一个西文字符
		{
			strncpy(bz,ls1,1);				//拷贝一个字符到bz中
			bz[1]=0;
			ls1++;							//跳过这一个字符到下一个字符
			pDC.TextOut(cc1,cc2,bz);		//在屏幕上写字符
			cd=cd-1;						//字符数减1
			//下一个字符的显示位置的实际坐标
			x1=x1+(TagPro.TagWidth+TagPro.TagOffsite/2)*(float)cos(ang1);
			y1=y1+(TagPro.TagWidth+TagPro.TagOffsite/2)*(float)sin(ang1);
			//下一个字符显示位置的屏幕坐标
			//cc1=(int)x1;cc2=(int)y1;
			DPtoVP(x1,y1,&cc1,&cc2);
		}
	} 
	pDC.SelectObject(cjcbakf);				//恢复字模
}
//========================================================

//==================================================================
//
//==================================================================
CoString::CoString()
{
	
}

CoString::~CoString()
{
	
}

CString CoString::dtostr(double a)
{
	CString str;
	str.Format("%f",a);
	return str;
}

CString CoString::itostr(int b)
{
	CString str;
	str.Format("%d",b);
	return str;
}

void CoString::DepTwoPart(CString &str,CString &str1,const CString tug)
{
	int i=0;
	i = str.Find(tug);
	str1 = str.Mid(i+1);
	str = str.Mid(0,i);
}

CString CoString::GetString(CoPnt Point)
{
	double x,y;
	x = Point.x;
	y = Point.y;
	CString str1,str2;
	str1 = dtostr(x);
	str2 = dtostr(y);
	str1 =str1+",";
	return (str1+str2);
}

CoPnt CoString::GetCoPnt(CString str)
{
	CString str1,str2;
	str2 = ",";
	DepTwoPart(str,str1,str2);
	CoPnt Point;
	Point.x = atof(str);
	Point.y = atof(str1);
	return Point;
}

//=======================================================================
//读写文件
//=======================================================================
//数组写入文件
CoRWFile::CoRWFile()
{

}

CoRWFile::~CoRWFile()
{

}

void CoRWFile::WriteToFile(vector<CoPnt>& Point)
{
	int PointNum = Point.size();
	CoString MyStr;
	CString str; 
	for(int i=0;i<PointNum;i++)
	{
		str+=MyStr.GetString(Point[i]);
		str = str +"\r\n";
	}
	LPCTSTR PassName = "D:\\CoGIS\\temp\\CoFile.txt";
	CFile pFile(PassName,CFile::modeCreate | CFile::modeWrite);
	pFile.Write(str,strlen(str));
}

//从文件写入数组
void CoRWFile::ReadFromFile(vector<CoPnt>& Point)
{
	CoString MyString;
	LPCTSTR PassName = "D:\\CoGIS\\temp\\CoFile.txt";
	CStdioFile   pFile(PassName,CFile::modeRead);
	CString str,str1;
	while(pFile.ReadString(str))
	{
		if(str.GetLength())
			Point.push_back(MyString.GetCoPnt(str));

	}
}