// NameList.h: interface for the CNameList class.
//
//////////////////////////////////////////////////////////////////////
#include <afxtempl.h>
#if !defined(AFX_NAMELIST_H__A5FCEE22_1802_4312_A90D_A3A7AED3C36D__INCLUDED_)
#define AFX_NAMELIST_H__A5FCEE22_1802_4312_A90D_A3A7AED3C36D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
struct ITEMINFO;
class CList;
class CNameList  
{
public:
	CNameList();
	virtual ~CNameList();
	CList <CString, CString&> m_lNameList;
};

#endif // !defined(AFX_NAMELIST_H__A5FCEE22_1802_4312_A90D_A3A7AED3C36D__INCLUDED_)
