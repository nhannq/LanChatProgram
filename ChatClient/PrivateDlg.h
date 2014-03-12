#if !defined(AFX_PRIVATEDLG_H__99C67956_EEA5_4645_8518_AAE7238AAAD6__INCLUDED_)
#define AFX_PRIVATEDLG_H__99C67956_EEA5_4645_8518_AAE7238AAAD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrivateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrivateDlg dialog

class CPrivateDlg : public CDialog
{
// Construction
public:
	void DisplayMessage(CString UserSend, CString Message);
	CFont m_font;
	CString m_strRecipient;
	CPrivateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrivateDlg)
	enum { IDD = IDD_PRIVATE_DIALOG };
	CEdit	m_edtMessageCtr;
	CListBox	m_lstMessagPrv;
	CString	m_edtMessageCSt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrivateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetControlFont(CString font, int fsize);

	// Generated message map functions
	//{{AFX_MSG(CPrivateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnButtonSendPrivate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIVATEDLG_H__99C67956_EEA5_4645_8518_AAE7238AAAD6__INCLUDED_)
