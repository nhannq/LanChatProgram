#if !defined(AFX_RECVDIALOG_H__50EB9F41_071A_41B6_AA76_EBE25FB93945__INCLUDED_)
#define AFX_RECVDIALOG_H__50EB9F41_071A_41B6_AA76_EBE25FB93945__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecvDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecvDialog dialog
class CFileDialogX;
class CRecvDialog : public CDialog
{
// Construction
public:
	CString m_strFileName;
	CRecvDialog(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CRecvDialog)
	enum { IDD = IDD_RECVFILE };
	CString	m_strSaveTo;
	CString	m_strInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecvDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CRecvDialog)
	afx_msg void OnBrowser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECVDIALOG_H__50EB9F41_071A_41B6_AA76_EBE25FB93945__INCLUDED_)
