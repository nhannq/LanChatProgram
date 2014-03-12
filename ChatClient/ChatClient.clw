; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatClientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChatClient.h"

ClassCount=6
Class1=CChatClientApp
Class2=CChatClientDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_CHATCLIENT_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CRecvDialog
Class5=CPrivateDlg
Class6=CChatOKNO
Resource4=IDD_PRIVATE_DIALOG

[CLS:CChatClientApp]
Type=0
HeaderFile=ChatClient.h
ImplementationFile=ChatClient.cpp
Filter=N

[CLS:CChatClientDlg]
Type=0
HeaderFile=ChatClientDlg.h
ImplementationFile=ChatClientDlg.cpp
Filter=D
LastObject=CChatClientDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ChatClientDlg.h
ImplementationFile=ChatClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHATCLIENT_DIALOG]
Type=1
Class=CChatClientDlg
ControlCount=16
Control1=IDC_MESSAGE,edit,1350631552
Control2=IDC_SEND,button,1342242816
Control3=IDC_IPADDRESS,SysIPAddress32,1342242816
Control4=IDC_EDITPORT,edit,1350631552
Control5=IDC_CLIENTNAME,edit,1350631552
Control6=IDCONNECT,button,1342242817
Control7=IDC_DISCONNECT,button,1342242816
Control8=IDEXIT,button,1342242816
Control9=IDC_STATICSERVER,static,1342308352
Control10=IDC_STATICPORT,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_LIST,SysListView32,1350631425
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342177287
Control16=IDC_LIST_FRIEND,listbox,1352728835

[CLS:CRecvDialog]
Type=0
HeaderFile=RecvDialog.h
ImplementationFile=RecvDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRecvDialog

[CLS:CPrivateDlg]
Type=0
HeaderFile=PrivateDlg.h
ImplementationFile=PrivateDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPrivateDlg

[DLG:IDD_PRIVATE_DIALOG]
Type=1
Class=CPrivateDlg
ControlCount=3
Control1=IDC_BUTTON_SEND_PRIVATE,button,1342242817
Control2=IDC_EDIT_MESSAGE_PRIVATE,edit,1350635648
Control3=IDC_LIST_MESSAGE_PRIVATE,listbox,1352728833

[CLS:CChatOKNO]
Type=0
HeaderFile=ChatOKNO.h
ImplementationFile=ChatOKNO.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

