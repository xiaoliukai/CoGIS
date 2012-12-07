#ifndef __MouseOper_H
#define __MouseOper_H

#ifndef _MouseOper_EXPORT_
#define BaseOper  __declspec(dllimport)
#else
#define BaseOper  __declspec(dllexport)
#endif

#include "CoStructClass.h"

class BaseOper CoBaseTool
{
public:
	CoBaseTool();
	virtual ~CoBaseTool();
	virtual void LButtonDown (UINT nFlags, CoPnt point);
	virtual void LButtonUp (UINT nFlags, CoPnt point);
	virtual void RButtonDown(UINT nFlags, CoPnt point);
	virtual void RButtonUp(UINT nFlags, CoPnt point);
	virtual void MouseMove(UINT nFlags, CoPnt point);
	virtual void MouseWheel(UINT nFlags, short zDelta, CoPnt pt);

	CView* m_ptView;
};

  #ifndef _MouseOper_EXPORT_
    #ifdef _DEBUG
      #pragma comment(lib,"CoMouse.lib")
    #else
      #pragma comment(lib,"CoMouse.lib")
    #endif
 #endif
#endif

