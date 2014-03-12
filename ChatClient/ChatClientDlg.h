// ChatClientDlg.h : header file
//

#if !defined(AFX_CHATCLIENTDLG_H__7FCBF283_DB30_44CD_A3C9_EC0F5BAD1E69__INCLUDED_)
#define AFX_CHATCLIENTDLG_H__7FCBF283_DB30_44CD_A3C9_EC0F5BAD1E69__INCLUDED_

#include "PrivateDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////#i////////////
// CChatClientDlg dialog

class CChatClientDlg : public CDialog
{
// Construction
public:
	BOOL bSendPress;
	CWnd* m_pParent;
	void setParent(CWnd *pParent);
	void ShowWindowsPrv(int i, CString sender, CString Mesage, int nCheck);
	CPrivateDlg* CMemDlg[100];
	void SendPrivate(CString username, CString Message);
	int nFriend;
	BOOL bQuit[100];
	BOOL bChat[100];
	CString Friendlist[100];
	CPrivateDlg m_prvDlg;
	CFont m_font;
	void SetControlFont();
	CString m_strFile;
	CString m_strSaveTo;
	int Recv(SOCKET sock, char FAR *buf, int len, int flags);
	bool Send(SOCKET sock, const char FAR * buf, int len, int flags);
	int m_iMsgIndex;
	SOCKET m_sClient;
	CChatClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatClientDlg)
	enum { IDD = IDD_CHATCLIENT_DIALOG };
	CListBox	m_lstFriend;
	CEdit	m_ctrMessage;
	CTreeCtrl	m_tcTreeUser;
	CListCtrl	m_lMsgList;
	CIPAddressCtrl	m_cServerIP;
	short	m_sPort;
	CString	m_strName;
	CString	m_strMessage;
	int		m_iOption;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnExit();
	afx_msg void OnSend();
	afx_msg void OnDisconnect();
	afx_msg void OnDblclkListFriend();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTDLG_H__7FCBF283_DB30_44CD_A3C9_EC0F5BAD1E69__INCLUDED_)
