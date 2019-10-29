// GammarCorrectionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageTool.h"
#include "GammarCorrectionDialog.h"
#include "afxdialogex.h"


// CGammarCorrectionDialog dialog

IMPLEMENT_DYNAMIC(CGammarCorrectionDialog, CDialogEx)

CGammarCorrectionDialog::CGammarCorrectionDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAMMAR_CORRECTION, pParent)
    , m_fGammar(2.2f)
{

}

CGammarCorrectionDialog::~CGammarCorrectionDialog()
{
}

void CGammarCorrectionDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_GAMMAR_EDIT, m_fGammar);
    DDV_MinMaxFloat(pDX, m_fGammar, 0.2f, 5.0f);
    DDX_Control(pDX, IDC_GAMMAR_SLIDER, m_sliderGammar);
}


BEGIN_MESSAGE_MAP(CGammarCorrectionDialog, CDialogEx)
    ON_WM_HSCROLL()
    ON_EN_CHANGE(IDC_GAMMAR_EDIT, &CGammarCorrectionDialog::OnChangeGammarEdit)
END_MESSAGE_MAP()


// CGammarCorrectionDialog message handlers


BOOL CGammarCorrectionDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  Add extra initialization here
    m_sliderGammar.SetRange(20, 500);
    m_sliderGammar.SetTicFreq(20);
    m_sliderGammar.SetPageSize(20);
    m_sliderGammar.SetPos((int)(m_fGammar * 100));

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CGammarCorrectionDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: Add your message handler code here and/or call default
    if (m_sliderGammar.GetSafeHwnd() == pScrollBar->GetSafeHwnd()) {
        m_fGammar = m_sliderGammar.GetPos() / 100.0f;
        UpdateData(FALSE);
    }

    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CGammarCorrectionDialog::OnChangeGammarEdit()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    UpdateData(TRUE);
    m_sliderGammar.SetPos((int)(m_fGammar * 100));
}
