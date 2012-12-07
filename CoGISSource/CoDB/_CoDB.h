#ifndef _CoGisDB_H
#define _CoGisDB_H

#ifndef _CoDBOper_EXPORT_
#define CoDBOper  __declspec(dllimport)
#else
#define CoDBOper  __declspec(dllexport)
#endif

#import "C:\program files\common files\system\ado\msado15.dll" rename_namespace("ADOBS")rename("EOF","adoEOF")
using namespace ADOBS;

#include "CoStructClass.h"
#include "Draw.h"
CoDBOper extern CString DBIP;
CoDBOper extern CString workpath;
class  CoDBOper CoConnect 
{
public:
	CoConnect();
	CoConnect(CString szDsn,CString szName,CString szPwd);
	virtual ~CoConnect();
	//数据库的链接与断开
	long Connect(CString szDsn,CString szName,CString szPwd);
	long Connect();
	long DisConncet();
	long IsConnceted();

	// 执行查询指令并返回记录集
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);

	// 执行SQL命令
	BOOL ExecuteSQL(_bstr_t bstrSQL);
	long AddUser(CoUser);
private:
	void GetIP(CString& MyIP);

public:
	CString m_szDsn;
	CString m_szName;
	CString m_szPwd;
	CString m_ip;
	_ConnectionPtr m_connect;
	_RecordsetPtr m_pRecordset;
};

//==================================================
//
//==================================================

class CoDBOper CoFeatureset  
{
public:
	CoFeatureset();
	virtual ~CoFeatureset();
public:
	long Open(CoConnect* pt,CString& name);
	long Close();
	long IsOpen();

	void GetTime(CString& time);//获取当地时间
	long GetMaxID(CString& TableName);
	long GetMaxID();
	long GteCount();

	//按照空间坐标得到符合的ID系列
	int GetAllID(CoRect& rc,vector<long>&ID);
	//按照属性值得到符合的ID系列
	int GetAllID(CString& ptSQL,vector<long>&ID);

	long GetID(CString Item);

	long  NewTable(int index);
	long DelTable(CString TableName);

	void ReadFileMy();
	void SaveFileMy();

	//把文件存入数据库
	long SaveFileToDB(CString FilePathName,long ID);
	long CoSaveFileToDB(CString FilePathName,long ID);
	long ReadDBToFile(vector<CoPnt>& Point,long ID);
	void AddFileToTree(vector<CString>& Item);
	long PointAdd(CoPnt Point,CoPntPro PointPro);
	long PointDelete(long ID);
	long PointUpdate(CoPnt& Point,CoPntPro& PntPro);
	long PointGet(CoPnt& Point,CoPntPro& PntPro);
	long TagAdd(CoPnt Point,CoTagPro& TagPro);
	long TagDelete(long ID);
	long TagUpdate(CoPnt& point,CoTagPro& TagPro);
	long TagGet(CoPnt& Point,CoTagPro& TagPro);
	long LineAdd(vector<CoPnt>& LinePnts,CoLinePro& linepro);
	long LineDelete(long ID);
	long LineUpdate(vector<CoPnt>& Line,CoLinePro& LinePro);
	long LineGet(vector<CoPnt>& Line,CoLinePro& LinePro);	
	long PolygonAdd(vector<CoPnt>& PlyPnt,CoPolyPro& PlyPro);
	long PolygonDelete(long ID);
	long PolygonUpdate(vector<CoPnt>&Poly,CoPolyPro& PolyPro);
	long PolygonGet(vector<CoPnt>& Poly,CoPolyPro& Polypro);
	bool DeleteAll();
	long CloseItem(CString ItemName);
	long OpenItem(CString ItemName);
	long GetRect(int ID,CoRect& rc);
public:
	CoConnect	m_giscon;
	CString m_tablename;
	_RecordsetPtr m_recordset;
	//临时数据变量
	vector<CoPointTemp> m_Point;
	vector<CoLineTemp>m_Line;
	vector<CoPolyTemp>m_Poly;
	vector<CoTagTemp>m_Tag;
};

//=====================================================
//
//=====================================================

class CoDBOper CoRecorset  
{
public:
	CoRecorset();
	~CoRecorset();
public:	
	long Open(CoFeatureset *pt,CString& PtSQL);
	long Open(CoFeatureset *pt,CoRect& rc);
	long Close();
	
	void MoveNext();
	void MoveLast();
	void MoveFirst();
	bool CoEOF();

	long GetPoint(CoPnt& Point,CoPntPro& PntPro);
	//--------------------------------------------
	long GetTag(CoPnt& Point,CoTagPro& TagPro);
	//--------------------------------------------
	long GetLine(vector<CoPnt>& Line,CoLinePro& LinePro);
	long GetPolygon(vector<CoPnt>& Poly,CoPolyPro& PolyPro);

private:
	long CoOpen();

private:
	CoFeatureset *m_File;
	CoRect m_ptRect;
	CString m_ptSQL;
	int m_IDNum;
	vector<long>m_ID;
	int m_Location;
};


#ifndef _CoDBOper_EXPORT_
#ifdef _DEBUG
#pragma comment(lib, "CoDB.lib")
#else
#pragma comment(lib, "CoDB.lib")
#endif
#endif
#endif