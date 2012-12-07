#include "StdAfx.h"
#include "_MouseOper.h"

CoBaseTool::CoBaseTool()
{
	m_ptView = NULL;
}

CoBaseTool::~CoBaseTool(){}

void CoBaseTool::LButtonDown(UINT nFlags, CoPnt point){}

void CoBaseTool::LButtonUp(UINT nFlags, CoPnt point){}

void CoBaseTool::RButtonDown(UINT nFlags, CoPnt point){}

void CoBaseTool::RButtonUp(UINT nFlags, CoPnt point){}

void CoBaseTool::MouseMove(UINT nFlags, CoPnt point){}

void CoBaseTool::MouseWheel(UINT nFlags, short zDelta, CoPnt pt){}
