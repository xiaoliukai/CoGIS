#include "StdAfx.h"
#include "_CoDB.h"
#include <_CoLogic.h>
#include <Winsock2.h>
#pragma comment (lib,"Ws2_32.lib")

CString DBIP;
CString workpath;
CoConnect::CoConnect()
{
}

CoConnect::CoConnect(CString szDsn,CString szName,CString szPwd)
{
	m_szDsn=szDsn;
	m_szName=szName;
	m_szPwd=szPwd;
}

CoConnect::~CoConnect()
{

}

long CoConnect::Connect(CString szDsn,CString szName,CString szPwd)
{
	return 1; 
}

long CoConnect::Connect()
{
	return 1; 
}

long CoConnect::DisConncet()
{
	return 1;
}
//返回1表示连接，返回0表示断开
long CoConnect::IsConnceted()
{
	return 1;
}

void CoConnect::GetIP(CString& MyIP)
{
	CString temp=DBIP;
	MyIP=temp;
}



// 执行查询指令并返回记录集
_RecordsetPtr&  CoConnect::GetRecordSet(_bstr_t bstrSQL)
{
	return m_pRecordset;
}

// 执行SQL命令
BOOL CoConnect::ExecuteSQL(_bstr_t bstrSQL)
{
	return true;//自己加的
}

//=================================================================
//
//=================================================================

CoFeatureset::CoFeatureset()
{

}

CoFeatureset::~CoFeatureset()
{

}

//成功打开返回1，否则返回0
long CoFeatureset::Open(CoConnect* pt,CString& name)
{
	m_tablename=workpath+name;
	return 1;//自己加的  返回为真
}

long CoFeatureset::Close()
{
	//m_giscon.DisConncet();
	return 1;
}

//如果是打开的返回1，否则返回0
long CoFeatureset::IsOpen()
{
	if (m_giscon.IsConnceted()==1)
		return 1;
	return 0;	
}



void CoFeatureset::GetTime(CString& time)
{
	CTime CurrentTime = CTime::GetCurrentTime();
	int Year = CurrentTime.GetYear();
	int Mouth = CurrentTime.GetMonth();
	int Day = CurrentTime.GetDay();
	int Hour = CurrentTime.GetHour();
	int Minute = CurrentTime.GetMinute();
	int Second = CurrentTime.GetSecond();
	time.Format("%d-%d-%d %d:%d:%d",Year,Mouth,Day,Hour,Minute,Second);
}

long CoFeatureset::NewTable(int index)
{
	return 1;//自己添加  默认新建表是成功的
}




long CoFeatureset::GetID(CString Item)
{
	/*CString str;
	str.Format("SELECT ID FROM [%s] WHERE ItemName ='%s'",m_tablename,Item);
	m_recordset = m_giscon.GetRecordSet(_bstr_t(str));
	long ID = 0;
	_variant_t vID;

	vID = m_recordset->GetCollect(_variant_t((long)0));
	ID = long(vID.lVal);
	return ID;*/
	return 1;
}


long CoFeatureset::DelTable(CString TableName)
{
	//删除数据目录的一行数据
	return 1;
}

//空表返回0，否则返回ID号
long CoFeatureset::GetMaxID(CString& TableName)
{
	return 1;
}

long CoFeatureset::GetMaxID()
{
	int ID=0;
	ReadFileMy();
	CString str=m_tablename.Right(4);
	if(str==".COP")
	{
		int Size=m_Point.size();
		for(int i=0;i<Size;i++)
		{
			if(m_Point[i].m_pointpro.PntID>=ID)
				ID=m_Point[i].m_pointpro.PntID;
		}
	}
	if(str==".COL")
	{
		int Size=m_Line.size();
		for(int i=0;i<Size;i++)
		{
			if(m_Line[i].m_LinePro.LineID>=ID)
				ID=m_Line[i].m_LinePro.LineID;
		}
	}
	if (str==".COA")
	{
		int Size = m_Poly.size();
		for(int i=0;i<Size;i++)
		{
			if(m_Poly[i].m_PolyPro.PolyID>=ID)
				ID=m_Poly[i].m_PolyPro.PolyID;
		}
	}

	if(str==".CON")
	{
		int Size = m_Tag.size();
		for(int i=0;i<Size;i++)
		{
			if(m_Tag[i].m_tagpro.ID>=ID)
				ID=m_Tag[i].m_tagpro.ID;
		}
	}
	return ID;
}

long CoFeatureset::GteCount()
{
	return 1;
}

long CoFeatureset::GetRect(int ID,CoRect& rc)
{
	CString str = m_tablename.Right(4);
	CoLog math;
	ReadFileMy();
	if(str==".COP")
	{
		int Size = m_Point.size();
		for(int i=0;i<Size;i++)
		{
			if(m_Point[i].m_pointpro.PntID==ID)
			{
				rc=math.GetPntRect(m_Point[i].m_point,m_Point[i].m_pointpro);
				break;
			}
		}

	}
	if (str==".COL")
	{
		int Size = m_Line.size();
		for(int i=0;i<Size;i++)
		{
			if(m_Line[i].m_LinePro.LineID==ID)
			{
				rc = math.GetRect(m_Line[i].m_Line);
				break;
			}
		}
	}

	if (str==".COA")
	{
		int Size = m_Poly.size();
		for(int i=0;i<Size;i++)
		{
			if(m_Poly[i].m_PolyPro.PolyID==ID)
			{
				rc = math.GetRect(m_Poly[i].m_Poly);
				break;
			}
		}
	}
	if (str==".CON")
	{
		int Size = m_Tag.size();
		for (int i=0;i<Size;i++)
		{
			if (m_Tag[i].m_tagpro.ID==ID)
			{
				rc = math.GetFontRect(m_Tag[i].m_Point,m_Tag[i].m_tagpro);
				break;
			}
		}
	}
	return ID;
}

//添加点:返回点ID号
long CoFeatureset::PointAdd(CoPnt Point,CoPntPro PointPro)
{
	int ID=GetMaxID()+1;
	CFile file;
	file.Open(LPCTSTR(m_tablename),CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	CArchive ar(&file,CArchive::store);
	file.SeekToEnd();
	ar<<ID<<PointPro.PntRadio<<PointPro.PntStyle<<PointPro.PntColor<<PointPro.PntLayer;
	ar<<Point.x<<Point.y;
	ar.Close();
	file.Close();

	return ID;
}

//成功删除返回点ID，否则返回0
long CoFeatureset::PointDelete(long ID)
{
	vector<CoPointTemp>PntArray;
	ReadFileMy();
	int Size = m_Point.size();
	for(int i=0;i<Size;i++)
	{
		if(m_Point[i].m_pointpro.PntID!=ID)
			PntArray.push_back(m_Point[i]);
	}
	m_Point = PntArray;
	PntArray.clear();
	SaveFileMy();
	return ID;
}

long CoFeatureset::PointUpdate(CoPnt& Point,CoPntPro& PntPro)
{
	ReadFileMy();
	long ID=PntPro.PntID;
	int Size = m_Point.size();
	for(int i=0;i<Size;i++)
	{
		if (m_Point[i].m_pointpro.PntID==ID)
		{
			m_Point[i].m_point=Point;
			m_Point[i].m_pointpro=PntPro;
			break;
		}
	}
	SaveFileMy();
	return ID;
}

bool CoFeatureset::DeleteAll()
{
	CFile file;
	file.Open((LPCTSTR)m_tablename,CFile::modeCreate);
	return true;
}


long CoFeatureset::PointGet(CoPnt& Point,CoPntPro& PntPro)
{
	ReadFileMy();
	long ID=PntPro.PntID;
	int Size = m_Point.size();
	for(int i=0;i<Size;i++)
	{
		if (m_Point[i].m_pointpro.PntID==ID)
		{
			Point=m_Point[i].m_point;
			PntPro = m_Point[i].m_pointpro;
			break;
		}
	}
	return ID;
}
long CoFeatureset::TagAdd(CoPnt Point,CoTagPro& TagPro)
{
	int ID=GetMaxID()+1;
	CFile file;
	file.Open(LPCTSTR(m_tablename),CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	CArchive ar(&file,CArchive::store);
	file.SeekToEnd();
	ar<<ID<<TagPro.TagAngle<<TagPro.TagColor<<TagPro.TagFont
		<<TagPro.TagHeight<<TagPro.TagLayer<<TagPro.TagOffsite
		<<TagPro.TagStr<<TagPro.TagWidth<<TagPro.TextAngle;
	ar<<Point.x<<Point.y;
	ar.Close();
	file.Close();
	return ID;
}
long CoFeatureset::TagDelete(long ID)
{
	vector<CoTagTemp>TagArray;
	ReadFileMy();
	int Size = m_Tag.size();
	for(int i=0;i<Size;i++)
	{
		if(m_Tag[i].m_tagpro.ID!=ID)
			TagArray.push_back(m_Tag[i]);
	}
	m_Tag = TagArray;
	TagArray.clear();
	SaveFileMy();
	return ID;
}
long CoFeatureset::TagUpdate(CoPnt& Point,CoTagPro& TagPro)
{
	ReadFileMy();
	long ID=TagPro.ID;
	int Size = m_Tag.size();
	for(int i=0;i<Size;i++)
	{
		if (m_Tag[i].m_tagpro.ID==ID)
		{
			m_Tag[i].m_Point=Point;
			m_Tag[i].m_tagpro=TagPro;
			CString str=m_Tag[i].m_tagpro.TagStr;
			break;
		}
	}
	SaveFileMy();
	return ID;
}

long CoFeatureset::CloseItem(CString ItemName)
{
	return 0;
}

long CoFeatureset::OpenItem(CString ItemName)
{
	return 0;
}

long CoFeatureset::TagGet(CoPnt& Point,CoTagPro& TagPro)
{
	ReadFileMy();
	long ID = TagPro.ID;
	int Size = m_Tag.size();
	for(int i=0;i<Size;i++)
	{
		if(m_Tag[i].m_tagpro.ID==ID)
		{
			TagPro = m_Tag[i].m_tagpro;
			Point.x = m_Tag[i].m_Point.x;
			Point.y = m_Tag[i].m_Point.y;
			break;
		}
	}
	return ID;

}
void CoFeatureset::AddFileToTree(vector<CString>& Item)
{
	
}

//如果增加成功返回线ID,否则返回0
long CoFeatureset::LineAdd(vector<CoPnt>& LinePnts,CoLinePro& linepro)
{
	int ID=GetMaxID()+1;
	int linenum=LinePnts.size();
	CFile file;
	file.Open(LPCTSTR(m_tablename),CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	CArchive ar(&file,CArchive::store);
	file.SeekToEnd();
	ar<<ID<<linepro.LineStyle<<linepro.LineWidth<<linepro.LineColor<<linepro.LineLayer;
	ar<<linenum;
	for(int i=0;i<linenum;i++)
		ar<<LinePnts[i].x<<LinePnts[i].y;
	ar.Close();
	file.Close();

	return ID;
}

long CoFeatureset::SaveFileToDB(CString FilePathName,long ID)
{
	return ID;
}

long CoFeatureset::CoSaveFileToDB(CString FilePathName,long ID)
{
	return ID;
}

long CoFeatureset::ReadDBToFile(vector<CoPnt>& Point,long ID)
{
	return ID;
}

int CoFeatureset::GetAllID(CoRect& rc,vector<long>&ID)
{
	CoPnt point1,point2;
	point1.x = rc.xmin;
	point1.y = rc.ymin;
	point2.x = rc.xmax;
	point2.y = rc.ymax;
	CoLog math;
	CoRect rc1;
	CString str=m_tablename.Right(4);
	int Size=0;
	if (str==".COP")
	{

		ReadFileMy();
		Size=m_Point.size();
		for(int i=0;i<Size;i++)
		{
			int n=m_Point[i].m_pointpro.PntRadio;
			rc1=math.GetPntRect(m_Point[i].m_point,m_Point[i].m_pointpro);
			if (point1.x==point2.x&&point1.y==point2.y)
			{
				if(math.IsPntInRect(point1,rc1))
				{
					ID.push_back(m_Point[i].m_pointpro.PntID);
				}
			}
			else
			{
				if(!math.TwoRectDeviat(rc,rc1))
				{
					ID.push_back(m_Point[i].m_pointpro.PntID);
				}
			}

		}
	}
	if (str==".COL")
	{

		ReadFileMy();
		Size = m_Line.size();
		for(int i=0;i<Size;i++)
		{
			rc1 = math.GetRect(m_Line[i].m_Line);
			if (point1.x==point2.x&&point1.y==point2.y)
			{
				if(math.IsPntInRect(point1,rc1))
				{
					ID.push_back(m_Line[i].m_LinePro.LineID);

				}
			}
			else
			{
				if(!math.TwoRectDeviat(rc,rc1))
				{
					ID.push_back(m_Line[i].m_LinePro.LineID);
				}
			}
		}
	}

	if (str==".COA")
	{

		ReadFileMy();
		Size = m_Poly.size();
		for(int i=0;i<Size;i++)
		{
			rc1 = math.GetRect(m_Poly[i].m_Poly);
			if (point1.x==point2.x&&point1.y==point2.y)
			{
				if(math.IsPntInRect(point1,rc1))
				{
					ID.push_back(m_Poly[i].m_PolyPro.PolyID);

				}
			}
			else
			{
				if(!math.TwoRectDeviat(rc,rc1))
				{
					ID.push_back(m_Poly[i].m_PolyPro.PolyID);
				}
			}
		}
	}

	if (str==".CON")
	{

		ReadFileMy();
		Size = m_Tag.size();
		for(int i=0;i<Size;i++)
		{
			rc1 = math.GetFontRect(m_Tag[i].m_Point,m_Tag[i].m_tagpro);
			if (point1.x==point2.x&&point1.y==point2.y)
			{
				if(math.IsPntInRect(point1,rc1))
				{
					ID.push_back(m_Tag[i].m_tagpro.ID);

				}
			}
			else
			{
				if(!math.TwoRectDeviat(rc,rc1))
				{
					ID.push_back(m_Tag[i].m_tagpro.ID);
				}
			}
		}
	}
	return ID.size();
}

int CoFeatureset::GetAllID(CString& ptSQL,vector<long>&ID)
{
	ReadFileMy();
	CString str = m_tablename.Right(4);
	if(str==".COP")
	{
		int Size = m_Point.size();
		for(int i=0;i<Size;i++)
			ID.push_back(m_Point[i].m_pointpro.PntID);
	}

	if (str==".COL")
	{
		int Size = m_Line.size();
		for(int i=0;i<Size;i++)
			ID.push_back(m_Line[i].m_LinePro.LineID);
	}
	if (str==".COA")
	{
		int Size = m_Poly.size();
		for(int i=0;i<Size;i++)
			ID.push_back(m_Poly[i].m_PolyPro.PolyID);
	}
	if (str==".CON")
	{
		int Size = m_Tag.size();
		for(int i=0;i<Size;i++)
			ID.push_back(m_Tag[i].m_tagpro.ID);
	}
	return ID.size();
}


long CoFeatureset::LineDelete(long ID)
{	
	vector<CoLineTemp>LineArray;
	ReadFileMy();
	int Size = m_Line.size();
	for(int i=0;i<Size;i++)
	{
		if(m_Line[i].m_LinePro.LineID!=ID)
			LineArray.push_back(m_Line[i]);
	}
	m_Line = LineArray;
	LineArray.clear();
	SaveFileMy();
	return ID;
}

long CoFeatureset::LineUpdate(vector<CoPnt>& Line,CoLinePro& LinePro)
{
	ReadFileMy();
	long ID=LinePro.LineID;
	int Size=m_Line.size();
	for(int i=0;i<Size;i++)
	{
		if(m_Line[i].m_LinePro.LineID==ID)
		{
			m_Line[i].m_Line=Line;
			m_Line[i].m_LinePro=LinePro;
			break;
		}
	}
	SaveFileMy();
	return ID;
}
long CoFeatureset::LineGet(vector<CoPnt>& Line,CoLinePro& LinePro)
{
	ReadFileMy();
	long ID=LinePro.LineID;
	int Size = m_Line.size();
	for(int i=0;i<Size;i++)
	{
		if(m_Line[i].m_LinePro.LineID==ID)
		{
			LinePro=m_Line[i].m_LinePro;
			int Length=m_Line[i].m_Line.size();
			for(int j=0;j<Length;j++)
				Line.push_back(m_Line[i].m_Line[j]);
			break;
		}
	}
	return ID;
}

long CoFeatureset::PolygonAdd(vector<CoPnt>& PlyPnt,CoPolyPro& PlyPro)
{
	CoLog math;
	int ID=GetMaxID()+1;
	int polynum=PlyPnt.size();
	CFile file;

	if(PlyPro.PolyStyle==1)
		PlyPro.PolyArea=math.GetArea(PlyPnt);
	else
		PlyPro.PolyArea=0;

	file.Open(LPCTSTR(m_tablename),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	CArchive ar(&file,CArchive::store);
	file.SeekToEnd();
	ar<<ID<<PlyPro.PolyArea<<PlyPro.PolyColor<<PlyPro.PolyFillStyle<<PlyPro.PolyStyle<<PlyPro.PolyLayer;
	ar<<polynum;
	for(int i=0;i<polynum;i++)
		ar<<PlyPnt[i].x<<PlyPnt[i].y;
	ar.Close();
	file.Close();

	return ID;
}

long CoFeatureset::PolygonUpdate(vector<CoPnt>&Poly,CoPolyPro& PolyPro)
{
	ReadFileMy();
	long ID=PolyPro.PolyID;
	int Size = m_Poly.size();
	for(int i=0;i<Size;i++)
	{
		if (m_Poly[i].m_PolyPro.PolyID==ID)
		{
			m_Poly[i].m_Poly=Poly;
			m_Poly[i].m_PolyPro=PolyPro;
			break;
		}
	}
	SaveFileMy();
	return ID;
}

long CoFeatureset::PolygonDelete(long ID)
{
	vector<CoPolyTemp>PolyArray;
	ReadFileMy();
	int Size = m_Poly.size();
	for(int i=0;i<Size;i++)
	{
		if(m_Poly[i].m_PolyPro.PolyID!=ID)
			PolyArray.push_back(m_Poly[i]);
	}
	m_Poly = PolyArray;
	PolyArray.clear();
	SaveFileMy();
	return ID;
}

long CoFeatureset::PolygonGet(vector<CoPnt>& Poly,CoPolyPro& Polypro)
{
	ReadFileMy();
	long ID=Polypro.PolyID;
	int Size = m_Poly.size();
	for(int i=0;i<Size;i++)
	{
		if (m_Poly[i].m_PolyPro.PolyID==ID)
		{
			Polypro = m_Poly[i].m_PolyPro;
			int	Length = m_Poly[i].m_Poly.size();
			for(int j=0;j<Length;j++)
				Poly.push_back(m_Poly[i].m_Poly[j]);
			break;
		}
	}	
	return ID;
}
void CoFeatureset::SaveFileMy()
{
	CFile file;
	file.Open(LPCTSTR(m_tablename),CFile::modeCreate|CFile::modeWrite);
	CArchive ar(&file,CArchive::store);
	int Size=0;
	CString tag = m_tablename.Right(4);
	if(tag==".COP")
	{
		Size = m_Point.size();
		for(int i=0;i<Size;i++)
		{
			ar<<m_Point[i].m_pointpro.PntID<<m_Point[i].m_pointpro.PntRadio<<m_Point[i].m_pointpro.PntStyle
				<<m_Point[i].m_pointpro.PntColor<<m_Point[i].m_pointpro.PntLayer;
			ar<<m_Point[i].m_point.x<<m_Point[i].m_point.y;
		}
	}

	if(tag==".COL")
	{
		Size = m_Line.size();
		for(int i=0;i<Size;i++)
		{
			ar<<m_Line[i].m_LinePro.LineID<<m_Line[i].m_LinePro.LineStyle<<m_Line[i].m_LinePro.LineWidth
				<<m_Line[i].m_LinePro.LineColor<<m_Line[i].m_LinePro.LineLayer;
			ar<<m_Line[i].m_Line.size();
			for(int j=0;j<m_Line[i].m_Line.size();j++)
				ar<<m_Line[i].m_Line[j].x<<m_Line[i].m_Line[j].y;
		}
	}

	if (tag==".COA")
	{
		Size = m_Poly.size();
		for(int i=0;i<Size;i++)
		{
			ar<<m_Poly[i].m_PolyPro.PolyID<<m_Poly[i].m_PolyPro.PolyArea<<m_Poly[i].m_PolyPro.PolyColor
				<<m_Poly[i].m_PolyPro.PolyFillStyle<<m_Poly[i].m_PolyPro.PolyStyle<<m_Poly[i].m_PolyPro.PolyLayer;
			ar<<m_Poly[i].m_Poly.size();
			for(int j=0;j<m_Poly[i].m_Poly.size();j++)
				ar<<m_Poly[i].m_Poly[j].x<<m_Poly[i].m_Poly[j].y;
		}
	}

	if (tag==".CON")
	{
		Size = m_Tag.size();
		for(int i=0;i<Size;i++)
		{
			ar<<m_Tag[i].m_tagpro.ID<<m_Tag[i].m_tagpro.TagAngle<<m_Tag[i].m_tagpro.TagColor
				<<m_Tag[i].m_tagpro.TagFont<<m_Tag[i].m_tagpro.TagHeight<<m_Tag[i].m_tagpro.TagLayer
				<<m_Tag[i].m_tagpro.TagOffsite<<m_Tag[i].m_tagpro.TagStr<<m_Tag[i].m_tagpro.TagWidth
				<<m_Tag[i].m_tagpro.TextAngle;
			ar<<m_Tag[i].m_Point.x<<m_Tag[i].m_Point.y;
		}
	}
	ar.Close();
	file.Close();
}
void CoFeatureset::ReadFileMy()
{
	int length;
	CString str=m_tablename.Right(4);
	CFile file;
	file.Open(LPCTSTR(m_tablename),CFile::modeRead|CFile::modeCreate|CFile::modeNoTruncate);
	CArchive ar(&file,CArchive::load);
	if(str==".COP")
	{
		if (m_Line.size())
			m_Point.clear();
		CoPnt pnt;
		CoPntPro pntpro;
		while (1)
		{
			try
			{
				ar>>pntpro.PntID>>pntpro.PntRadio>>pntpro.PntStyle>>pntpro.PntColor>>pntpro.PntLayer;
				ar>>pnt.x>>pnt.y;
			}
			catch (CMemoryException* e)
			{
				break;
			}
			catch (CFileException* e)
			{
				break;
			}
			catch (CException* e)
			{
				break;
			}
			CoPointTemp MyPoint(pnt,pntpro);
			m_Point.push_back(MyPoint);
		}
	}
	if(str==".COL")
	{
		if (m_Line.size())
			m_Line.clear();
		CoLinePro linepro;	
		while (1)
		{
			try
			{

				ar>>linepro.LineID>>linepro.LineStyle>>linepro.LineWidth>>linepro.LineColor>>linepro.LineLayer;
				ar>>length;
			}
			catch (CMemoryException* e)
			{
				break;
			}
			catch (CFileException* e)
			{
				break;
			}
			catch (CException* e)
			{
				break;
			}
			vector<CoPnt>line;
			CoPnt point;
			for(int i=0;i<length;i++)
			{
				ar>>point.x>>point.y;
				line.push_back(point);
			}
			CoLineTemp MyLine(line,linepro);
			m_Line.push_back(MyLine);
			line.clear();
		}

	}
	if(str==".COA")
	{
		if (m_Poly.size())
			m_Poly.clear();
		CoPolyPro polypro;	
		while (1)
		{
			try
			{
				ar>>polypro.PolyID>>polypro.PolyArea>>polypro.PolyColor
					>>polypro.PolyFillStyle>>polypro.PolyStyle>>polypro.PolyLayer;
				ar>>length;
			}
			catch (CMemoryException* e)
			{
				break;
			}
			catch (CFileException* e)
			{
				break;
			}
			catch (CException* e)
			{
				break;
			}
			vector<CoPnt>poly;
			CoPnt point;
			for(int i=0;i<length;i++)
			{
				ar>>point.x>>point.y;
				poly.push_back(point);
			}

			CoPolyTemp MyPoly(poly,polypro);
			m_Poly.push_back(MyPoly);
			poly.clear();
		}
	}
	if (str==".CON")
	{
		if(m_Tag.size())
			m_Tag.clear();
		CoPnt tag;
		CoTagPro tagpro;
		while (1)
		{
			try
			{
				ar>>tagpro.ID>>tagpro.TagAngle>>tagpro.TagColor
					>>tagpro.TagFont>>tagpro.TagHeight>>tagpro.TagLayer
					>>tagpro.TagOffsite>>tagpro.TagStr>>tagpro.TagWidth>>tagpro.TextAngle;
				ar>>tag.x>>tag.y;
			}
			catch (CMemoryException* e)
			{
				break;
			}
			catch (CFileException* e)
			{
				break;
			}
			catch (CException* e)
			{
				break;
			}
			CoTagTemp MyTag(tag,tagpro);
			m_Tag.push_back(MyTag);
		}
	}
	ar.Close();
	file.Close();
}
//================================================================
//
//================================================================

CoRecorset::CoRecorset()
{
	m_Location = 0;
}

CoRecorset::~CoRecorset()
{
	if(m_ID.size())
		m_ID.clear();
}

long CoRecorset::Open(CoFeatureset *pt,CoRect& rc)
{
	m_Location = 0;
	m_IDNum=0;
	m_File = pt;
	m_File->GetAllID(rc,m_ID);
	return 1;
}

long CoRecorset::Open(CoFeatureset *pt,CString& PtSQL)
{
	m_Location = 0;
	m_IDNum=0;
	m_File = pt;
	m_File->GetAllID(PtSQL,m_ID);
	return 1;
}

long CoRecorset::Close()
{
	if(m_ID.size())
		m_ID.clear();
	m_Location = 0;
	return 1;
}

void CoRecorset::MoveNext()
{
	m_Location++;
}

void CoRecorset::MoveLast()
{
	m_Location=m_ID.size()-1;
}

void CoRecorset::MoveFirst()
{
	m_Location = 0;
}

long CoRecorset::GetPoint(CoPnt& Point,CoPntPro& PntPro)
{
	PntPro.PntID = m_ID[m_Location];
	m_File->PointGet(Point,PntPro);
	return PntPro.PntID;
}
long CoRecorset::GetTag(CoPnt& Point,CoTagPro& TagPro)
{
	TagPro.ID = m_ID[m_Location];
	m_File->TagGet(Point,TagPro);
	return TagPro.ID;
}
long CoRecorset::GetLine(vector<CoPnt>& Line,CoLinePro& LinePro)
{
	LinePro.LineID = m_ID[m_Location];
	m_File->LineGet(Line,LinePro);
	return LinePro.LineID;
}

long CoRecorset::GetPolygon(vector<CoPnt>& Poly,CoPolyPro& PolyPro)
{
	PolyPro.PolyID = m_ID[m_Location];
	m_File->PolygonGet(Poly,PolyPro);
	return PolyPro.PolyID;
}

bool CoRecorset::CoEOF()
{
	if (m_Location==m_ID.size())
		return TRUE;
	return FALSE;
}
