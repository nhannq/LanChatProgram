; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatServerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChatServer.h"

ClassCount=3
Class1=CChatServerApp
Class2=CChatServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CHATSERVER_DIALOG

[CLS:CChatServerApp]
Type=0
HeaderFile=ChatServer.h
ImplementationFile=ChatServer.cpp
Filter=N

[CLS:CChatServerDlg]
Type=0
HeaderFile=ChatServerDlg.h
ImplementationFile=ChatServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_SEND

[CLS:CAboutDlg]
Type=0
HeaderFile=ChatServerDlg.h
ImplementationFile=ChatServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_SKIN1,{0944D16C-D0F4-4389-982A-A085595A9EB3},1342242816

[DLG:IDD_CHATSERVER_DIALOG]
Type=1
Class=CChatServerDlg
ControlCount=6
Control1=IDBEGIN,button,1342242817
Control2=IDEXIT,button,1342242816
Control3=IDC_TREE,SysTreeView32,1350631424
Control4=IDC_STATIC,button,1342177287
Control5=IDC_EDIT_SEND,edit,1350631552
Control6=IDC_BUTTON_SEND,button,1342242816

