#pragma once
#include "afxcmn.h"


// CBrightContrastDialog dialog

class CBrightContrastDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CBrightContrastDialog)

public:
	CBrightContrastDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBrightContrastDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BRIGHT_CONTRAST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
    // image brightness offset
    int m_nBright;
    // image contrast offset
    float m_fContrast;
    // image brightness control slider
    CSliderCtrl m_sliderBright;
    // image contrast control slider
    CSliderCtrl m_sliderContrast;
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnEnChangeBrightEdit();
    afx_msg void OnEnChangeContrastEdit();

public:
    int getBright() const { return m_nBright; }
    float getContrast() const { return m_fContrast; }
};
