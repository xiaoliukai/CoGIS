#include "stdafx.h"
#include "_CoDB.h"
#include "Draw.h"


CoPointTemp::CoPointTemp(CoPnt point,CoPntPro pntpro)
{
	m_point=point;
	m_pointpro=pntpro;
}

//////////////////////////////////////////////////////////////////////////

CoLineTemp::CoLineTemp(vector<CoPnt>& Line,CoLinePro LinePro)
{
	int Length = Line.size();
	for (int i=0;i<Length;i++)
	{
		m_Line.push_back(Line[i]);
	}
	m_LinePro.LineID = LinePro.LineID;
	m_LinePro.LineColor=LinePro.LineColor;
	m_LinePro.LineLayer=LinePro.LineLayer;
	m_LinePro.LineStyle=LinePro.LineStyle;
	m_LinePro.LineWidth=LinePro.LineWidth;
}

CoLineTemp::~CoLineTemp()
{
	if(m_Line.size())
		m_Line.clear();
}

//////////////////////////////////////////////////////////////////////////

CoPolyTemp::CoPolyTemp(vector<CoPnt>&Poly,CoPolyPro PolyPro)
{
	int Length=Poly.size();
	for(int i=0;i<Length;i++)
		m_Poly.push_back(Poly[i]);
	m_PolyPro.PolyArea = PolyPro.PolyArea;
	m_PolyPro.PolyColor=PolyPro.PolyColor;
	m_PolyPro.PolyFillStyle=PolyPro.PolyFillStyle;
	m_PolyPro.PolyID=PolyPro.PolyID;
	m_PolyPro.PolyLayer=PolyPro.PolyLayer;
	m_PolyPro.PolyStyle=PolyPro.PolyStyle;
}

CoPolyTemp::~CoPolyTemp()
{
	if(m_Poly.size())
		m_Poly.clear();
}

//////////////////////////////////////////////////////////////////////////

CoTagTemp::CoTagTemp(CoPnt Point,CoTagPro Tagpro)
{
	m_Point = Point;
	m_tagpro.ID = Tagpro.ID;
	m_tagpro.TagAngle = Tagpro.TagAngle;
	m_tagpro.TagColor = Tagpro.TagColor;
	m_tagpro.TagFont = Tagpro.TagFont;
	m_tagpro.TagHeight = Tagpro.TagHeight;
	m_tagpro.TagLayer = Tagpro.TagLayer;
	m_tagpro.TagOffsite = Tagpro.TagOffsite;
	m_tagpro.TagStr = Tagpro.TagStr;
	m_tagpro.TagWidth = Tagpro.TagWidth;
	m_tagpro.TextAngle = Tagpro.TextAngle;
}

CoTagTemp::~CoTagTemp()
{
	
}
