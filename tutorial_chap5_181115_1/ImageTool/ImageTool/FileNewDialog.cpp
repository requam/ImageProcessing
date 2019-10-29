// FileNewDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageTool.h"
#include "FileNewDialog.h"
#include "afxdialogex.h"


// CFileNewDialog dialog

IMPLEMENT_DYNAMIC(CFileNewDialog, CDialogEx)

CFileNewDialog::CFileNewDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILE_NEW, pParent)
    , m_nWidth(256)
    , m_nHeight(256)
    , m_nType(0)
{

}

CFileNewDialog::~CFileNewDialog()
{
}

void CFileNewDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_NEW_WIDTH, m_nWidth);
    DDV_MinMaxInt(pDX, m_nWidth, 1, 4096);
    DDX_Text(pDX, IDC_NEW_HEIGHT, m_nHeight);
    DDV_MinMaxInt(pDX, m_nHeight, 1, 4096);
    DDX_CBIndex(pDX, IDC_NEW_IMAGE_TYPE, m_nType);
}


BEGIN_MESSAGE_MAP(CFileNewDialog, CDialogEx)
END_MESSAGE_MAP()


// CFileNewDialog message handlers
