// ChatServerDlg.h : header file
//
#include <afxtempl.h>
#if !defined(AFX_CHATSERVERDLG_H__46A6B5D8_22D8_4B7E_9B9F_2104E12150CD__INCLUDED_)
#define AFX_CHATSERVERDLG_H__46A6B5D8_22D8_4B7E_9B9F_2104E12150CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatServerDlg dialog

class CNameList;
class CChatServerDlg : public CDialog
{
// Construction
public:
	void SetControlFont();
	CFont m_font;
	int Recv(SOCKET sock, char *buf, int len, int flags);
	bool Send(SOCKET sock, const char *buf, int len, int flags);
	int m_iClientCnt;
	CArray <CString, CString> m_arName;
	CArray <SOCKET, SOCKET> m_arSocket;
	SOCKET		m_sListen;
	CTreeCtrl	m_cClientTree;
	CChatServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatServerDlg)
	enum { IDD = IDD_CHATSERVER_DIALOG };
	CEdit	m_sentCtr;
	CString	m_sentMessage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBegin();
	afx_msg void OnExit();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSERVERDLG_H__46A6B5D8_22D8_4B7E_9B9F_2104E12150CD__INCLUDED_)
