#pragma once
#include "afxcmn.h"


// CGammarCorrectionDialog dialog

class CGammarCorrectionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CGammarCorrectionDialog)

public:
	CGammarCorrectionDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGammarCorrectionDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMMAR_CORRECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
    // image gammar
    float m_fGammar;
    // image gammar control slider
    CSliderCtrl m_sliderGammar;

public:
    float getGammar() const { return m_fGammar; }
    virtual BOOL OnInitDialog();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnChangeGammarEdit();
};
