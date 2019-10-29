#pragma once


// CHistogramDialog dialog

class CHistogramDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDialog)

public:
	CHistogramDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHistogramDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
    int m_histogram[256];
    float m_histCdf[256];

public:
    void setImageToHistogram(IppDib* pDib);
    afx_msg void OnPaint();
};
