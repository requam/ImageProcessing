#pragma once
#include "afxwin.h"


// CArithmeticLogicalDialog dialog

class CArithmeticLogicalDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CArithmeticLogicalDialog)

public:
	CArithmeticLogicalDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CArithmeticLogicalDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARITHMETIC_LOGICAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
    // Image1 combobox
    CComboBox m_comboImg1;
    // Image2 combobox
    CComboBox m_comboImg2;
    // Arithmetic & Logical Function radio button
    int m_nALFunc;

    void* m_pDoc1;
    void* m_pDoc2;

public:
    int getALFunc() const { return m_nALFunc; }

    void* getDoc1() const { return m_pDoc1; }
    void* getDoc2() const { return m_pDoc2; }

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
};
