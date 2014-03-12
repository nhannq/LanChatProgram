// PrivateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "PrivateDlg.h"
#include "ChatClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrivateDlg dialog


CPrivateDlg::CPrivateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrivateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrivateDlg)
	m_edtMessageCSt = _T("");
	//}}AFX_DATA_INIT
}


void CPrivateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrivateDlg)
	DDX_Control(pDX, IDC_EDIT_MESSAGE_PRIVATE, m_edtMessageCtr);
	DDX_Control(pDX, IDC_LIST_MESSAGE_PRIVATE, m_lstMessagPrv);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_PRIVATE, m_edtMessageCSt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrivateDlg, CDialog)
	//{{AFX_MSG_MAP(CPrivateDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SEND_PRIVATE, OnButtonSendPrivate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrivateDlg message handlers

BOOL CPrivateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//CComQIPtr<ISkin> pSkin = GetDlgItem(IDC_SKIN1)->GetControlUnknown();
	//pSkin->ApplySkin((long)m_hWnd);
	
	// TODO: Add extra initialization here
	SetWindowText(m_strRecipient);
	SetControlFont("Arial",18);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrivateDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CChatClientDlg*		MainDlg= (CChatClientDlg*) AfxGetApp()->GetMainWnd();
	for (int i=0; i<=MainDlg->nFriend;i++)
		if (MainDlg->Friendlist[i]==m_strRecipient)
		{
			MainDlg->bChat[i]=FALSE;
			break;
		}
	CDialog::OnClose();
}

void CPrivateDlg::OnButtonSendPrivate() 
{
	UpdateData(TRUE);
	CChatClientDlg*		MainDlg= (CChatClientDlg*) AfxGetApp()->GetMainWnd();
	MainDlg->SendPrivate(m_strRecipient,m_edtMessageCSt);
	CString szTemp;
	szTemp="["+MainDlg->m_strName+"] :"+m_edtMessageCSt;
	m_lstMessagPrv.AddString(szTemp);
	m_edtMessageCSt="";
	UpdateData(FALSE);
}

void CPrivateDlg::SetControlFont(CString font, int fsize)
{
	LOGFONT	lf;
	memset(&lf, 0, sizeof(lf));			
	lf.lfWeight = FW_NORMAL;
	lf.lfHeight=fsize;
	lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	lf.lfCharSet= VIETNAMESE_CHARSET;
	wcscpy(lf.lfFaceName, font);	
	m_font.CreateFontIndirect(&lf);		
	m_lstMessagPrv.SetFont(&m_font);
	m_edtMessageCtr.SetFont(&m_font);
}

void CPrivateDlg::DisplayMessage(CString UserSend, CString Message)
{
	CString szTemp;
	szTemp="["+UserSend+"] :"+Message;
	m_lstMessagPrv.AddString(szTemp);
}

LRESULT CPrivateDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (message==WM_DROPFILES)
	{
		TCHAR	szTmp[MAX_PATH];
		HDROP hDropInfo=(HDROP)wParam;
		DragQueryFile(hDropInfo,0,szTmp,sizeof(szTmp));
		MessageBox(szTmp);
	}

	return CDialog::WindowProc(message, wParam, lParam);
}
