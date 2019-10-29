// HistogramDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageTool.h"
#include "HistogramDialog.h"
#include "afxdialogex.h"

#include "IppImage\IppDib.h"
#include "IppImage\IppImage.h"
#include "IppImage\IppConvert.h"
#include "IppImage\IppEnhance.h"

// CHistogramDialog dialog

IMPLEMENT_DYNAMIC(CHistogramDialog, CDialogEx)

CHistogramDialog::CHistogramDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTOGRAM, pParent)
{
    memset(m_histogram, 0, sizeof(int) * 256);
    memset(m_histCdf, 0, sizeof(float) * 256);
}

CHistogramDialog::~CHistogramDialog()
{
}

void CHistogramDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDialog, CDialogEx)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void CHistogramDialog::setImageToHistogram(IppDib* pDib) {
    if (pDib != nullptr && pDib->getBitCount() == 8) {
        CONVERT_DIB_TO_IMAGE(*pDib, img);

        float hist[256] = { 0 };
        IppEnhance::imageHistogram(img, hist);

        float max_hist = hist[0];
        for (int i = 1; i < 256; i++) {
            if (hist[i] > max_hist) {
                max_hist = hist[i];
            }
        }

        m_histCdf[0] = hist[0];
        for (int i = 0; i < 256; i++) {
            m_histogram[i] = (int)(hist[i] * 100 / max_hist);
            m_histCdf[i] = m_histCdf[i - 1] + hist[i];
        }
    }
    else {
        memset(m_histogram, 0, sizeof(int) * 256);
        memset(m_histCdf, 0, sizeof(float) * 256);
    }
}

// CHistogramDialog message handlers


void CHistogramDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: Add your message handler code here
                       // Do not call CDialogEx::OnPaint() for painting messages
    CGdiObject* pOldPen = dc.SelectStockObject(DC_PEN);

    dc.SetDCPenColor(RGB(128, 128, 128));
    dc.MoveTo(20, 120);
    dc.LineTo(275, 120);

    dc.SetDCPenColor(RGB(0, 0, 0));
    for (int i = 0; i < 256; i++) {
        dc.MoveTo(20 + i, 120);
        dc.LineTo(20 + i, 120 - m_histogram[i]);
    }

    dc.SetDCPenColor(RGB(128, 128, 128));
    for (int i = 0; i < 256; i++) {
        dc.MoveTo(20 + i, 120 - (int)(m_histCdf[i] * 100));
        dc.LineTo(20 + i, 120 - (int)(m_histCdf[i] * 100) + 1);
    }

    for (int i = 0; i < 256; i++) {
        dc.SetDCPenColor(RGB(i, i, i));
        dc.MoveTo(20 + i, 130);
        dc.LineTo(20 + i, 145);
    }

    dc.SelectObject(pOldPen);
}
