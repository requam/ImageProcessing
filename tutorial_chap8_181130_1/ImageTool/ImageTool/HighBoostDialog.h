#pragma once


// CHighBoostDialog dialog

class CHighBoostDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHighBoostDialog)

public:
	CHighBoostDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHighBoostDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIGHBOOST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
