// ArithmeticLogicalDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageTool.h"
#include "ArithmeticLogicalDialog.h"
#include "afxdialogex.h"
#include "ImageToolDoc.h"

// CArithmeticLogicalDialog dialog

IMPLEMENT_DYNAMIC(CArithmeticLogicalDialog, CDialogEx)

CArithmeticLogicalDialog::CArithmeticLogicalDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ARITHMETIC_LOGICAL, pParent)
    , m_nALFunc(0), m_pDoc1(nullptr), m_pDoc2(nullptr)
{

}

CArithmeticLogicalDialog::~CArithmeticLogicalDialog()
{
}

void CArithmeticLogicalDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_IMAGE1, m_comboImg1);
    DDX_Control(pDX, IDC_COMBO_IMAGE2, m_comboImg2);
    DDX_Radio(pDX, IDC_AL_FUNC1, m_nALFunc);
}


BEGIN_MESSAGE_MAP(CArithmeticLogicalDialog, CDialogEx)
    ON_BN_CLICKED(IDOK, &CArithmeticLogicalDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CArithmeticLogicalDialog message handlers


BOOL CArithmeticLogicalDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  Add extra initialization here
    int index = 0;
    CString title;

    CImageToolApp* pApp = (CImageToolApp*)AfxGetApp();
    POSITION pos = pApp->getImgDocTemplate()->GetFirstDocPosition();

    while (pos != NULL) {
        CImageToolDoc* pDoc = (CImageToolDoc*)pApp->getImgDocTemplate()->GetNextDoc(pos);
        if (pDoc->getDib().getBitCount() != 8) {
            continue;
        }

        title = pDoc->GetTitle();

        m_comboImg1.InsertString(index, title);
        m_comboImg2.InsertString(index, title);

        m_comboImg1.SetItemDataPtr(index, (void*)pDoc);
        m_comboImg2.SetItemDataPtr(index, (void*)pDoc);

        index++;
    }

    m_comboImg1.SetCurSel(0);
    m_comboImg2.SetCurSel(0);
    if (index > 1) {
        m_comboImg2.SetCurSel(1);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CArithmeticLogicalDialog::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    m_pDoc1 = (CImageToolDoc*)m_comboImg1.GetItemDataPtr(m_comboImg1.GetCurSel());
    m_pDoc2 = (CImageToolDoc*)m_comboImg2.GetItemDataPtr(m_comboImg2.GetCurSel());

    CDialogEx::OnOK();
}
