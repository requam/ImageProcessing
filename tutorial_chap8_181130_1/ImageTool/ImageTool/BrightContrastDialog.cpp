// BrightContrastDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageTool.h"
#include "BrightContrastDialog.h"
#include "afxdialogex.h"


// CBrightContrastDialog dialog

IMPLEMENT_DYNAMIC(CBrightContrastDialog, CDialogEx)

CBrightContrastDialog::CBrightContrastDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BRIGHT_CONTRAST, pParent)
    , m_nBright(0)
    , m_fContrast(0.0f)
{

}

CBrightContrastDialog::~CBrightContrastDialog()
{
}

void CBrightContrastDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_BRIGHT_EDIT, m_nBright);
    DDV_MinMaxInt(pDX, m_nBright, -255, 255);
    DDX_Text(pDX, IDC_CONTRAST_EDIT, m_fContrast);
    DDV_MinMaxFloat(pDX, m_fContrast, -1.0f, 1.0f);
    DDX_Control(pDX, IDC_BRIGHT_SLIDER, m_sliderBright);
    DDX_Control(pDX, IDC_CONTRAST_SLIDER, m_sliderContrast);
}


BEGIN_MESSAGE_MAP(CBrightContrastDialog, CDialogEx)
    ON_WM_HSCROLL()
    ON_EN_CHANGE(IDC_BRIGHT_EDIT, &CBrightContrastDialog::OnEnChangeBrightEdit)
    ON_EN_CHANGE(IDC_CONTRAST_EDIT, &CBrightContrastDialog::OnEnChangeContrastEdit)
END_MESSAGE_MAP()


// CBrightContrastDialog message handlers


BOOL CBrightContrastDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  Add extra initialization here
    m_sliderBright.SetRange(-255, 255);
    m_sliderBright.SetTicFreq(32);
    m_sliderBright.SetPageSize(32);

    m_sliderContrast.SetRange(-100, 100);
    m_sliderContrast.SetTicFreq(20);
    m_sliderContrast.SetPageSize(20);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CBrightContrastDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: Add your message handler code here and/or call default
    if (m_sliderBright.GetSafeHwnd() == pScrollBar->GetSafeHwnd()) {
        m_nBright = m_sliderBright.GetPos();
        UpdateData(FALSE);
    }
    else if (m_sliderContrast.GetSafeHwnd() == pScrollBar->GetSafeHwnd()) {
        m_fContrast = (float)m_sliderContrast.GetPos() / 100;
        UpdateData(FALSE);
    }

    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBrightContrastDialog::OnEnChangeBrightEdit()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    UpdateData(TRUE);
    m_sliderBright.SetPos(m_nBright);
}


void CBrightContrastDialog::OnEnChangeContrastEdit()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    UpdateData(TRUE);
    m_sliderContrast.SetPos((int)(m_fContrast * 100));
}
