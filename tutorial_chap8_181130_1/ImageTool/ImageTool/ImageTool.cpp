
// ImageTool.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ImageTool.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "ImageToolDoc.h"
#include "ImageToolView.h"

#include ".\IppImage\IppDib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageToolApp

BEGIN_MESSAGE_MAP(CImageToolApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CImageToolApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
    ON_COMMAND(ID_EDIT_PASTE, &CImageToolApp::OnEditPaste)
    ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CImageToolApp::OnUpdateEditPaste)
    ON_COMMAND(ID_WINDOW_CLOSEALL, &CImageToolApp::OnWindowCloseall)
END_MESSAGE_MAP()


// CImageToolApp construction

CImageToolApp::CImageToolApp()
    : m_pNewDib(nullptr), m_pImgDocTemplate(nullptr)
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ImageTool.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CImageToolApp object

CImageToolApp theApp;


// CImageToolApp initialization

BOOL CImageToolApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	//CMultiDocTemplate* pDocTemplate;
	m_pImgDocTemplate = new CMultiDocTemplate(IDR_ImageToolTYPE,
		RUNTIME_CLASS(CImageToolDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CImageToolView));
	if (!m_pImgDocTemplate)
		return FALSE;
	AddDocTemplate(m_pImgDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

    if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) {
        cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
    }

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CImageToolApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CImageToolApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CImageToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CImageToolApp customization load/save methods

void CImageToolApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CImageToolApp::LoadCustomState()
{
}

void CImageToolApp::SaveCustomState()
{
}

// CImageToolApp message handlers


void AfxNewBitmap(IppDib& dib) {
    theApp.setNewDib(&dib);
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

void AfxPrintInfo(CString message) {
    CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    pFrame->getWndOutput().addString(message);
}

void AfxPrintInfo(LPCTSTR lpszFormat, ...) {
    CString message;

    va_list arg_list;
    va_start(arg_list, lpszFormat);
    message.FormatV(lpszFormat, arg_list);
    va_end(arg_list);

    AfxPrintInfo(message);
}

void CImageToolApp::OnEditPaste()
{
    // TODO: Add your command handler code here
    IppDib dib;
    if (dib.pasteFromClipboard()) {
        AfxNewBitmap(dib);
    }
}


void CImageToolApp::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(IsClipboardFormatAvailable(CF_DIB));
}


void CImageToolApp::OnWindowCloseall()
{
    // TODO: Add your command handler code here
    CloseAllDocuments(TRUE);
}
