#ifndef DRAW_H_
#define DRAW_H_
#include "CoStructClass.h"
#include <vector>
using namespace std;

class CoPointTemp
{
public:
	CoPnt m_point;
	CoPntPro m_pointpro;
public:
	CoPointTemp(CoPnt point,CoPntPro pntpro);
	~CoPointTemp(){};
};

class CoLineTemp
{
public:
	CoLineTemp(vector<CoPnt>& Line,CoLinePro LinePro);
	~CoLineTemp();
public:
	vector<CoPnt> m_Line;
	CoLinePro m_LinePro;
	
};

class CoPolyTemp
{
public:
	CoPolyTemp(vector<CoPnt>&Poly,CoPolyPro PolyPro);
	~CoPolyTemp();
public:
	vector<CoPnt> m_Poly;
	CoPolyPro m_PolyPro;
};

class CoTagTemp
{
public:
	CoTagTemp(CoPnt Point,CoTagPro Tagpro);
	~CoTagTemp();
public:
	CoPnt m_Point;
	CoTagPro m_tagpro;
};
#endif





















