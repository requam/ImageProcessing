#pragma once
#include "afxcmn.h"


// CGaussianDialog dialog

class CGaussianDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CGaussianDialog)

public:
	CGaussianDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGaussianDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAUSSIAN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
    // Gaussian sigma slider
    CSliderCtrl m_sliderSigma;
    // Gaussian sigma
    float m_fSigma;

public:
    float getSigma() const { return m_fSigma; }
    virtual BOOL OnInitDialog();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnEnChangeSigmaEdit();
};
