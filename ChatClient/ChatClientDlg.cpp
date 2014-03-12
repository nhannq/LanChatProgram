// ChatClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CChatClientDlg *g_pChatClientDlg;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CString Message,Sender;
/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg dialog
//CString MainDlg->Friendlist[100];

CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatClientDlg)
	m_sPort = 0;
	m_strName = _T("");
	m_strMessage = _T("");
	m_iOption = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatClientDlg)
	DDX_Control(pDX, IDC_LIST_FRIEND, m_lstFriend);
	DDX_Control(pDX, IDC_MESSAGE, m_ctrMessage);
	//DDX_Control(pDX, IDC_TREEUSER, m_tcTreeUser);
	DDX_Control(pDX, IDC_LIST, m_lMsgList);
	DDX_Control(pDX, IDC_IPADDRESS, m_cServerIP);
	DDX_Text(pDX, IDC_EDITPORT, m_sPort);
	DDX_Text(pDX, IDC_CLIENTNAME, m_strName);
	DDX_Text(pDX, IDC_MESSAGE, m_strMessage);
	//DDX_Radio(pDX, IDC_RADIOMSG, m_iOption);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	//{{AFX_MSG_MAP(CChatClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCONNECT, OnConnect)
	ON_BN_CLICKED(IDEXIT, OnExit)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_LBN_DBLCLK(IDC_LIST_FRIEND, OnDblclkListFriend)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg message handlers

BOOL CChatClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_pChatClientDlg = this;

	//CComQIPtr<ISkin> pSkin = GetDlgItem(IDC_SKIN)->GetControlUnknown();
	//pSkin->ApplySkin((long)m_hWnd);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_cServerIP.SetAddress(127, 0, 0, 1);
	m_sPort= 6868;
	m_lMsgList.InsertColumn(0,_T("Message"));
	m_lMsgList.SetColumnWidth(0, 390);
	m_iMsgIndex= 1;
	m_iOption= 0;
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
	SetControlFont();
	setParent(this);
	bSendPress=FALSE;
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


UINT RecvThread(LPVOID lpParam)
{
	SOCKET				sock= (SOCKET) lpParam;
    TCHAR				szMsgBuff[100], szName[20];
    int					ret;
	CChatClientDlg*		MainDlg= (CChatClientDlg*) AfxGetApp()->GetMainWnd();
	CString				strTemp, strName;

    while(1)
    {
        ret = MainDlg->Recv(sock, (char*)szMsgBuff, 1024, 0);
		if (ret == SOCKET_ERROR) break;
		szMsgBuff[ret]= '\0';
		if(_tcsncmp(_T("NAME"), szMsgBuff, 4)==0)//co 1 nguoi vua dang nhap
		{
			_tcscpy(szName, &szMsgBuff[4]);
			strName= szName;
			MainDlg->nFriend++;
			MainDlg->Friendlist[MainDlg->nFriend]=szName;
			MainDlg->m_lstFriend.AddString(szName);
			strTemp="SEND"+strName;//gui toi nguoi day
			MainDlg->Send(sock, (char*)strTemp.GetBuffer(1), strTemp.GetLength()*2, 0);
			int a=strTemp.GetLength();
			strTemp="UPME"+MainDlg->m_strName;//ten cua minh
			a=strTemp.GetLength();
			MainDlg->Send(sock, (char*)strTemp.GetBuffer(1), strTemp.GetLength()*2, 0);
		}

		if(_tcsncmp(_T("SERVERTOCLIENT"), szMsgBuff, 14)==0)
		{
			ret = MainDlg->Recv(sock, (char*)szMsgBuff, 1024, 0);
			szMsgBuff[ret]= '\0';
			strName="[FROM SERVER] : ";
			strName=strName+szMsgBuff;
			MainDlg->m_lMsgList.InsertItem(MainDlg->m_iMsgIndex, (LPCTSTR) strName);
			MainDlg->m_iMsgIndex ++;			
		}			


		if(_tcsncmp(_T("SENDALL"), szMsgBuff, 7)==0)
		{
			_tcscpy(szName, &szMsgBuff[7]);
			ret = MainDlg->Recv(sock, (char*)szMsgBuff, 1024, 0);
			szMsgBuff[ret]= '\0';
			for (int i=0; i<=MainDlg->nFriend;i++)
				if (MainDlg->Friendlist[i]==szName)
				{
					if (MainDlg->bChat[i]==TRUE)
					{
						MainDlg->CMemDlg[i]->DisplayMessage(szName,szMsgBuff);	
						break;
					}
					else		
					{
						MainDlg->bChat[i]=TRUE;
						Sender=szName;
						Message=szMsgBuff;
						SendMessage(g_pChatClientDlg->m_hWnd,WM_OPENPRVDLG,i,NULL);				
					}
				}

			
			//MainDlg->m_tcTreeUser.InsertItem(szName, TVI_ROOT, TVI_LAST);
		}//co nguoi bao minh them ten ho vao danh sach

		if(_tcsncmp(_T("UPME"), szMsgBuff, 4)==0)
		{
			_tcscpy(szName, &szMsgBuff[4]);
			MainDlg->nFriend++;
			MainDlg->Friendlist[MainDlg->nFriend]=szName;
			MainDlg->m_lstFriend.AddString(szName);
			//MainDlg->m_tcTreeUser.InsertItem(szName, TVI_ROOT, TVI_LAST);
		}//co nguoi bao minh them ten ho vao danh sach
		
		if(_tcsncmp(_T("FROM"), szMsgBuff, 4)==0)//co message do nguoi khac gui den
		{
			_tcscpy(szName, &szMsgBuff[4]);
			strName= szName;
			strName="["+strName+"] : ";
			ret = MainDlg->Recv(sock, (char*)szMsgBuff, 1024, 0);
			szMsgBuff[ret]= '\0';
			strName+= szMsgBuff;
			
			for (int i=0; i<=MainDlg->nFriend;i++)
				if (MainDlg->Friendlist[i]==szName)
				{
					if (MainDlg->bChat[i]==TRUE)
					{
						MainDlg->CMemDlg[i]->DisplayMessage(szName,szMsgBuff);	
						break;
					}
					else		
					{
						MainDlg->bChat[i]=TRUE;
						Sender=szName;
						Message=szMsgBuff;
						SendMessage(g_pChatClientDlg->m_hWnd,WM_OPENPRVDLG,i,NULL);						
					}

				}
		}

		if(_tcsncmp(_T("DISC"), szMsgBuff, 4)==0)//co nguoi out nick
		{
			_tcscpy(szName, &szMsgBuff[4]);
			strName= szName; 
			for (int i=0; i<=MainDlg->nFriend;i++)
				if (MainDlg->Friendlist[i]==strName)
					{
						MainDlg->bQuit[i]=TRUE;
						break;
					}
			CString MsgQuit;
			MsgQuit=strName;
			MsgQuit=MsgQuit+" has been sign out";
			if (MainDlg->bChat[i]==TRUE)
			{
				MainDlg->CMemDlg[i]->m_lstMessagPrv.AddString(MsgQuit);	
			}
			else
				{
					MainDlg->m_lMsgList.InsertItem(MainDlg->m_iMsgIndex, (LPCTSTR) MsgQuit);
					MainDlg->m_iMsgIndex ++;		
				}
			MainDlg->m_lstFriend.ResetContent();
			for (i=0;i<=MainDlg->nFriend;i++)
				if (MainDlg->bQuit[i]==FALSE)
					MainDlg->m_lstFriend.AddString(MainDlg->Friendlist[i]);

		}
    }
	AfxEndThread(0);
    return 0;
}

void CChatClientDlg::OnConnect() 
{
	WSADATA       wsd;
	DWORD		  dwAddress;
    struct sockaddr_in server;
    struct hostent    *host = NULL;

	UpdateData(TRUE);
	nFriend=-1;
	for (int i=0; i<100; i++)
	{
		bChat[i]=FALSE;
		bQuit[i]=FALSE;
	}

 	if(m_strName.GetLength() == 0)
	{
		MessageBox(TEXT("Please enter an user name."), 
					TEXT("Error"), MB_OK | MB_ICONERROR);
		return;
	}

	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
    {
        MessageBox(_T("Failed to load Winsock library."));
        return;
    }

	m_sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sClient == INVALID_SOCKET)
    {
        MessageBox(_T("socket() failed."));
        return;
    }
	server.sin_family = AF_INET;
    server.sin_port = htons(m_sPort);
	
	m_cServerIP.GetAddress(dwAddress);
    server.sin_addr.s_addr = htonl(dwAddress);
	
	if (connect(m_sClient, (struct sockaddr *)&server, 
        sizeof(server)) == SOCKET_ERROR)
    {
        MessageBox(_T("connect() failed."));
        return;
	}
	Send (m_sClient, (char*)m_strName.GetBuffer(1), m_strName.GetLength()*2, 0);
	AfxBeginThread(RecvThread, (LPVOID) m_sClient);
	GetDlgItem(IDCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDITPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_CLIENTNAME)->EnableWindow(FALSE);
	GetDlgItem(IDEXIT)->EnableWindow(FALSE);
}

void CChatClientDlg::OnExit() 
{
		
	OnOK();
}

void CChatClientDlg::OnSend() 
{	
	UpdateData(TRUE);
	CString strTemp;
	if (bSendPress==FALSE)
	{
		MessageBox(_T("You can private chat by click on him/her name"));
		bSendPress=TRUE;
	}
	strTemp="SENDALL"+m_strName;
	Send (m_sClient, (char*)strTemp.GetBuffer(1), strTemp.GetLength()*2, 0);
	Send (m_sClient, (char*)m_strMessage.GetBuffer(1), m_strMessage.GetLength()*2, 0);
	strTemp="PUBLIC :";
	strTemp=strTemp+m_strMessage;
	m_lMsgList.InsertItem(m_iMsgIndex, (LPCTSTR) strTemp);
	m_iMsgIndex ++;
	m_strMessage="";
	UpdateData(FALSE);	
}

void CChatClientDlg::OnDisconnect() 
{
	CString strTemp;
	strTemp= "DISC"+m_strName;
	if (Send (m_sClient, (char*)strTemp.GetBuffer(1), strTemp.GetLength()*2, 0) == TRUE)
	{
		Sleep(1000);
		closesocket(m_sClient);
		WSACleanup();
		//m_tcTreeUser.DeleteAllItems();
		m_lstFriend.ResetContent();
	}
	m_lstFriend.ResetContent();
	m_lMsgList.DeleteAllItems();
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDCONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDITPORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLIENTNAME)->EnableWindow(TRUE);
	GetDlgItem(IDEXIT)->EnableWindow(TRUE);
}

bool CChatClientDlg::Send(SOCKET sock, const char *buf, int len, int flags)
{
	int iLeft;
	int index= 0, ret;
	iLeft= sizeof(len);
	int iLen= htonl(len);
	char *LenBuf= (char *)&iLen;
	while (iLeft > 0)
	{
		ret= send(sock, &LenBuf[index], iLeft, flags);
		if (ret == SOCKET_ERROR)
		{
			return FALSE;
		}
		iLeft-= ret;
		index+= ret;
	}
	iLeft= len;
	index= 0;
	while (iLeft > 0)
	{
		ret= send(sock, &buf[index], iLeft, flags);
		if (ret == SOCKET_ERROR)
		{
			return FALSE;
		}
		iLeft-= ret;
		index+= ret;
	}
	return TRUE;
}

int CChatClientDlg::Recv(SOCKET sock, char *buf, int len, int flags)
{
	int ret, iLeft, index, iLen;
	index = 0;
	iLeft= sizeof(len);
	char *LenBuf= (char *)&iLen;
	while (iLeft > 0)
	{
		ret = recv(sock, &LenBuf[index], iLeft, flags);
		if (ret == SOCKET_ERROR)
		{
			return -1;
		}
		index += ret;
	    iLeft -= ret;
	}
	iLeft= ntohl(iLen);//chuyen so bytes network ve so byte cua host
	index= 0;
	while (iLeft > 0)
	{
		ret = recv(sock, &buf[index], iLeft, flags);
		if (ret == SOCKET_ERROR)
		{
			return -1;
		}
		index += ret;
	    iLeft -= ret;
	}
	return ntohl(iLen)/2;
}

void CChatClientDlg::SetControlFont()
{
	LOGFONT	lf;
	memset(&lf, 0, sizeof(lf));			
	lf.lfWeight = FW_NORMAL;
	lf.lfHeight=15;
	lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	lf.lfCharSet= VIETNAMESE_CHARSET;
	wcscpy(lf.lfFaceName, _T("Arial"));	
	m_font.CreateFontIndirect(&lf);		
	m_ctrMessage.SetFont(&m_font);
	m_lMsgList.SetFont(&m_font);
}

void CChatClientDlg::OnDblclkListFriend() 
{
	CListBox*pMem = (CListBox*)GetDlgItem(IDC_LIST_FRIEND);
	UINT nIndex = pMem->GetCurSel(); 
	CString rString;
	pMem->GetText(nIndex,rString);
	for (int i=0; i<=nFriend;i++)
		if (Friendlist[i]==rString)
		{
			if (bChat[i]==TRUE)
				return;
			else		
				bChat[i]=TRUE;
			break;
		}
	ShowWindowsPrv(i,rString,"",0);
}

void CChatClientDlg::SendPrivate(CString username, CString Message)
{
	CString strTemp;
	strTemp="SEND"+username;
	Send (m_sClient, (char*)strTemp.GetBuffer(1), strTemp.GetLength()*2, 0);
	Send (m_sClient, (char*)Message.GetBuffer(1), Message.GetLength()*2, 0);
	m_strMessage="to "+username+": "+m_strMessage;
}

void CChatClientDlg::ShowWindowsPrv(int i, CString sender, CString Mesage, int nCheck)
{
	CMemDlg[i] = new CPrivateDlg;
	CMemDlg[i]->m_strRecipient = sender;
	CMemDlg[i]->Create(IDD_PRIVATE_DIALOG,this);
	CMemDlg[i]->ShowWindow(SW_SHOW);
	if (nCheck==1)
		CMemDlg[i]->DisplayMessage(sender,Message);
	CMemDlg[i]->SetForegroundWindow();
}

void CChatClientDlg::setParent(CWnd *pParent)
{
	m_pParent = pParent;
}


LRESULT CChatClientDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message==WM_OPENPRVDLG)
	{
		ShowWindowsPrv(int(wParam),Sender,Message,1);
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CChatClientDlg::OnClose() 
{
	OnDisconnect();
	
	CDialog::OnClose();
}
