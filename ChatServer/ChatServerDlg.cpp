// ChatServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CChatServerDlg dialog

CChatServerDlg::CChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatServerDlg)
	m_sentMessage = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatServerDlg)
	DDX_Control(pDX, IDC_EDIT_SEND, m_sentCtr);
	DDX_Text(pDX, IDC_EDIT_SEND, m_sentMessage);
	DDX_Control(pDX, IDC_TREE, m_cClientTree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialog)
	//{{AFX_MSG_MAP(CChatServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDBEGIN, OnBegin)
	ON_BN_CLICKED(IDEXIT, OnExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatServerDlg message handlers

BOOL CChatServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
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
	SetControlFont();
	// TODO: Add extra initialization here
	m_iClientCnt=0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatServerDlg::OnPaint() 
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
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

UINT ClientThread(LPVOID lpParam)
{
    SOCKET				sock= (SOCKET) lpParam;
    TCHAR				szBuff[512], szName[512];
    int					ret, j, i;
	CChatServerDlg*		MainDlg= (CChatServerDlg*) AfxGetApp()->GetMainWnd();
	CString				strTemp,strTemp1;

    while(1)
    {
        ret = MainDlg->Recv(sock, (char*)szBuff, 1024, 0);
		if (ret == SOCKET_ERROR ) break;
		szBuff[ret]= '\0';
		if(_tcsncmp(_T("SENDALL"), szBuff, 7)==0)//client gui den
		{
			_tcscpy(szName, &szBuff[7]);
			strTemp= szName;
			ret = MainDlg->Recv(sock, (char*)szBuff, 1024, 0);
			szBuff[ret]= '\0';
			strTemp1="SENDALL"+strTemp;
			for(i=0; i<MainDlg->m_iClientCnt; i++) 
			{
				MainDlg->Send(MainDlg->m_arSocket[i], (char*)strTemp1.GetBuffer(1),strTemp1.GetLength()*2, 0);
				MainDlg->Send(MainDlg->m_arSocket[i], (char*)szBuff, ret*2, 0);
			}
		}

		if(_tcsncmp(_T("SEND"), szBuff, 4)==0)//client gui den
		{
			_tcscpy(szName, &szBuff[4]);
			strTemp= szName;
			ret = MainDlg->Recv(sock, (char*)szBuff, 1024, 0);
			szBuff[ret]= '\0';
			for(i=0; i<MainDlg->m_iClientCnt; i++) 
			{
				if(MainDlg->m_arName[i]== strTemp) break;
			}
			if(_tcsncmp(_T("UPME"), szBuff, 4)==0)//gui ten de nguoi dc yeu cau cap nhat vao danh sach
			{
				MainDlg->Send(MainDlg->m_arSocket[i], (char*)szBuff, ret*2, 0);
				continue;
			}
			if(_tcsncmp(_T("FILE"), szBuff, 4)==0)//gui den client yeu cau nhan file
			{
				for(j=0; j<MainDlg->m_iClientCnt; j++) 
				{
					if(MainDlg->m_arSocket[j]== sock) break;
				}
				MainDlg->Send(MainDlg->m_arSocket[i], (char*)szBuff, ret*2, 0);
				int a=MainDlg->m_arName[j].GetLength();
				MainDlg->Send(MainDlg->m_arSocket[i], (char*)MainDlg->m_arName[j].GetBuffer(1), MainDlg->m_arName[j].GetLength()*2, 0);
			}
			else
			{
				for(j=0; j<MainDlg->m_iClientCnt; j++) 
				{
					if(MainDlg->m_arSocket[j]== sock) break;
				}
				strTemp= "FROM"+MainDlg->m_arName.GetAt(j);
				int a=strTemp.GetLength();
				MainDlg->Send(MainDlg->m_arSocket[i], (char*)strTemp.GetBuffer(1), strTemp.GetLength()*2, 0);
				MainDlg->Send(MainDlg->m_arSocket[i], (char*)szBuff, ret*2, 0);
			}	
			continue;
		}
		if(_tcsncmp(_T("DISC"), szBuff, 4)==0)//client yeu cau thoat
		{
			for (i=0; i<MainDlg->m_iClientCnt; i++)
			{
				if(MainDlg->m_arSocket[i]==sock) break;
			}
			MainDlg->m_arName.RemoveAt(i, 1);
			MainDlg->m_arSocket.RemoveAt(i, 1);
			MainDlg->m_iClientCnt--;
			for (i=0; i<MainDlg->m_iClientCnt; i++)
			{
				MainDlg->Send(MainDlg->m_arSocket[i], (char*)szBuff, _tcslen(szBuff)*2, 0);
			}
			_tcscpy(szName, &szBuff[4]);
			strTemp= szName; 
			HTREEITEM hItem= MainDlg->m_cClientTree.GetFirstVisibleItem();
			HTREEITEM hNext;
			while (hItem != NULL)
			{
				if (MainDlg->m_cClientTree.GetItemText(hItem)==strTemp) break;
				hNext = MainDlg->m_cClientTree.GetNextItem(hItem, TVGN_NEXT);
				hItem = hNext;
			}
			MainDlg->m_cClientTree.DeleteItem(hItem);
			continue;
		}
    }
	AfxEndThread(0);
    return 0;
}

UINT ServerThread(LPVOID lpParam)
{
	struct sockaddr_in	client;
	int					iAddrSize, ret, i;
	TCHAR				szBuffer[512];
	SOCKET				sClient, sListen= (SOCKET) lpParam;
	CChatServerDlg*		MainDlg= (CChatServerDlg*) AfxGetApp()->GetMainWnd();
	CString				strName, strTemp;

	while (1)
    {
        iAddrSize = sizeof(client);
        sClient = accept(sListen, (struct sockaddr *)&client,
                        &iAddrSize);        
        if (sClient == INVALID_SOCKET)
        {   
            continue;
        }
		ret= MainDlg->Recv(sClient, (char*)szBuffer, 1024, 0);
		szBuffer[ret]= '\0';
		MainDlg->m_cClientTree.InsertItem(szBuffer, TVI_ROOT, TVI_LAST);
		for (i=0; i<MainDlg->m_iClientCnt; i++)
		{
			strTemp= szBuffer;	
			strName="NAME"+strTemp;
			int a=strName.GetLength();
			MainDlg->Send(MainDlg->m_arSocket[i], (char*)strName.GetBuffer(1), strName.GetLength()*2, 0);
		}
		MainDlg->m_arSocket.Add(sClient);
		MainDlg->m_arName.Add(CString(szBuffer));
		MainDlg->m_iClientCnt++;
		AfxBeginThread(ClientThread, (LPVOID)sClient);
    }
	return 0;
}

void CChatServerDlg::OnBegin() 
{
	WSADATA				wsd;
    struct sockaddr_in	local;
	


	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
    {
        MessageBox(_T("Failed to load Winsock!"));
        return;
    }
	
	m_sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (m_sListen == SOCKET_ERROR)
    {
        MessageBox(_T("socket failed."));
        return;
    }
	
	local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_family = AF_INET;
    local.sin_port = htons(6868);

    if (bind(m_sListen, (struct sockaddr *)&local, 
            sizeof(local)) == SOCKET_ERROR)
    {
        MessageBox(_T("binding failed."));
        return;
    }
	listen (m_sListen, 10);
	AfxBeginThread(ServerThread, (LPVOID) m_sListen);
	GetDlgItem(IDBEGIN)->EnableWindow(FALSE);
}


void CChatServerDlg::OnExit() 
{
	closesocket(m_sListen);  
	WSACleanup();
	OnOK();	
}

bool CChatServerDlg::Send(SOCKET sock, const char *buf, int len, int flags)
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

int CChatServerDlg::Recv(SOCKET sock, char *buf, int len, int flags)
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

void CChatServerDlg::OnButtonSend() 
{
	UpdateData(TRUE);
	CString strTemp1;
	strTemp1="SERVERTOCLIENT";
	for(int i=0; i<m_iClientCnt; i++) 
	{
		Send(m_arSocket[i], (char*)strTemp1.GetBuffer(1),strTemp1.GetLength()*2, 0);
		Send(m_arSocket[i], (char*)m_sentMessage.GetBuffer(1), m_sentMessage.GetLength()*2, 0);
	}
	m_sentMessage="";
	UpdateData(FALSE);
}

void CChatServerDlg::SetControlFont()
{
	LOGFONT	lf;
	memset(&lf, 0, sizeof(lf));			
	lf.lfWeight = FW_NORMAL;
	lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	lf.lfCharSet= VIETNAMESE_CHARSET;
	wcscpy(lf.lfFaceName, _T("Arial"));	
	m_font.CreateFontIndirect(&lf);		
	m_sentCtr.SetFont(&m_font);
	m_cClientTree.SetFont(&m_font);
}
