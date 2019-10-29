// GaussianDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageTool.h"
#include "GaussianDialog.h"
#include "afxdialogex.h"


// CGaussianDialog dialog

IMPLEMENT_DYNAMIC(CGaussianDialog, CDialogEx)

CGaussianDialog::CGaussianDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAUSSIAN, pParent)
    , m_fSigma(1.4f)
{

}

CGaussianDialog::~CGaussianDialog()
{
}

void CGaussianDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SIGMA_SLIDER, m_sliderSigma);
    DDX_Text(pDX, IDC_SIGMA_EDIT, m_fSigma);
	DDV_MinMaxFloat(pDX, m_fSigma, 0.2f, 5.0f);
}


BEGIN_MESSAGE_MAP(CGaussianDialog, CDialogEx)
    ON_WM_HSCROLL()
    ON_EN_CHANGE(IDC_SIGMA_EDIT, &CGaussianDialog::OnEnChangeSigmaEdit)
END_MESSAGE_MAP()


// CGaussianDialog message handlers


BOOL CGaussianDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  Add extra initialization here
    m_sliderSigma.SetRange(20, 500);
    m_sliderSigma.SetTicFreq(20);
    m_sliderSigma.SetPageSize(20);
    m_sliderSigma.SetPos((int)(m_fSigma * 100));

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CGaussianDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: Add your message handler code here and/or call default
    if (m_sliderSigma.GetSafeHwnd() == pScrollBar->GetSafeHwnd()) {
        int pos = m_sliderSigma.GetPos();
        m_fSigma = (float)pos / 100.0f;
        UpdateData(FALSE);
    }

    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CGaussianDialog::OnEnChangeSigmaEdit()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    UpdateData(TRUE);
    m_sliderSigma.SetPos((int)(m_fSigma * 100));
}
