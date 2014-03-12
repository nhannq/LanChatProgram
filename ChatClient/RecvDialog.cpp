// RecvDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "RecvDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecvDialog dialog


CRecvDialog::CRecvDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRecvDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecvDialog)
	m_strSaveTo = _T("");
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
}


void CRecvDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecvDialog)
	DDX_Text(pDX, IDC_SAVETO, m_strSaveTo);
	DDX_Text(pDX, IDC_INFOSTATIC, m_strInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecvDialog, CDialog)
	//{{AFX_MSG_MAP(CRecvDialog)
	ON_BN_CLICKED(IDC_BROWSER, OnBrowser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecvDialog message handlers



void CRecvDialog::OnBrowser() 
{
	CFileDialog m_cdSaveTo(FALSE, NULL, m_strFileName.GetBuffer(1));
	if(m_cdSaveTo.DoModal() == IDOK)
	{
		m_strSaveTo= m_cdSaveTo.GetPathName();
		UpdateData(FALSE);
		return;
	}
	else
	{
		return;
	}
}
