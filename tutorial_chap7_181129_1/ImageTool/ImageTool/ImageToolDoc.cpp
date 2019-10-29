
// ImageToolDoc.cpp : implementation of the CImageToolDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#include "ImageToolDoc.h"

#include <propkey.h>

#include "FileNewDialog.h"
#include "BrightContrastDialog.h"
#include "GammarCorrectionDialog.h"
#include "HistogramDialog.h"
#include "ArithmeticLogicalDialog.h"

#include "IppImage\IppImage.h"
#include "IppImage\IppConvert.h"
#include "IppImage\IppEnhance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageToolDoc

IMPLEMENT_DYNCREATE(CImageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolDoc, CDocument)
    ON_COMMAND(ID_WINDOW_DUPLICATE, &CImageToolDoc::OnWindowDuplicate)
    ON_COMMAND(ID_EDIT_COPY, &CImageToolDoc::OnEditCopy)
    ON_COMMAND(ID_IMAGE_INVERSE, &CImageToolDoc::OnImageInverse)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_INVERSE, &CImageToolDoc::OnUpdateImageInverse)
    ON_COMMAND(ID_IMAGE_BRIGHT_CONTRAST, &CImageToolDoc::OnImageBrightContrast)
    ON_COMMAND(ID_IMAGE_GAMMAR, &CImageToolDoc::OnImageGammarCorrection)
    ON_COMMAND(ID_VIEW_HISTOGRAM, &CImageToolDoc::OnViewHistogram)
    ON_COMMAND(ID_HISTOGRAM_STRETCH, &CImageToolDoc::OnHistogramStretch)
    ON_COMMAND(ID_HISTOGRAM_EQUALIZATION, &CImageToolDoc::OnHistogramEqualization)
    ON_UPDATE_COMMAND_UI(ID_VIEW_HISTOGRAM, &CImageToolDoc::OnUpdateViewHistogram)
    ON_UPDATE_COMMAND_UI(ID_HISTOGRAM_EQUALIZATION, &CImageToolDoc::OnUpdateHistogramEqualization)
    ON_UPDATE_COMMAND_UI(ID_HISTOGRAM_STRETCH, &CImageToolDoc::OnUpdateHistogramStretch)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_BRIGHT_CONTRAST, &CImageToolDoc::OnUpdateImageBrightContrast)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_GAMMAR, &CImageToolDoc::OnUpdateImageGammar)
    ON_COMMAND(ID_ARITHMETIC_LOGICAL, &CImageToolDoc::OnArithmeticLogical)
    ON_COMMAND(ID_BITPLANE_SLICING, &CImageToolDoc::OnBitplaneSlicing)
    ON_UPDATE_COMMAND_UI(ID_BITPLANE_SLICING, &CImageToolDoc::OnUpdateBitplaneSlicing)
END_MESSAGE_MAP()


// CImageToolDoc construction/destruction

CImageToolDoc::CImageToolDoc()
{
	// TODO: add one-time construction code here

}

CImageToolDoc::~CImageToolDoc()
{
}

BOOL CImageToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

    BOOL ret = TRUE;

    if (theApp.getNewDib() == nullptr) {
        CFileNewDialog dial;
        if (dial.DoModal() == IDOK) {
            if (dial.getType() == 0) {
                ret = m_dib.createGrayBitmap(dial.getWidth(), dial.getHeight());
            }
            else {
                ret = m_dib.createRgbBitmap(dial.getWidth(), dial.getHeight());
            }
        }
        else {
            ret = FALSE;
        }
    }
    else {
        m_dib = *(theApp.getNewDib());
        theApp.setNewDib(nullptr);
    }

	return ret;
}




// CImageToolDoc serialization

void CImageToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CImageToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CImageToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageToolDoc diagnostics

#ifdef _DEBUG
void CImageToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageToolDoc commands


BOOL CImageToolDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    if (!CDocument::OnOpenDocument(lpszPathName))
        return FALSE;

    // TODO:  Add your specialized creation code here
    BOOL res = m_dib.load(CT2A(lpszPathName));
    if (res) {
        AfxPrintInfo(_T("[File Open] File path: %s [File Info] Width: %d pix, Height: %d pix, #Colors: %d"), 
            lpszPathName, m_dib.getWidth(), m_dib.getHeight(), 0x01 << m_dib.getBitCount());
    }

    return res;
}


BOOL CImageToolDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
    // TODO: Add your specialized code here and/or call the base class

    return m_dib.save(CT2A(lpszPathName));
}


void CImageToolDoc::OnWindowDuplicate()
{
    // TODO: Add your command handler code here
    AfxNewBitmap(m_dib);
}


void CImageToolDoc::OnEditCopy()
{
    // TODO: Add your command handler code here
    if (m_dib.isValid()) {
        m_dib.copyToClipboard();
    }
}


void CImageToolDoc::OnImageInverse()
{
    // TODO: Add your command handler code here
    CONVERT_DIB_TO_IMAGE(m_dib, img);

    IppEnhance::imageInverse(img);

    CONVERT_IMAGE_TO_DIB(img, dib);

    AfxPrintInfo(_T("[Image Inverse] Input image: %s"), GetTitle());
    AfxNewBitmap(dib);
}


void CImageToolDoc::OnUpdateImageInverse(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(m_dib.getBitCount() == 8);
}


void CImageToolDoc::OnImageBrightContrast()
{
    // TODO: Add your command handler code here
    CBrightContrastDialog dial;
    if (dial.DoModal() == IDOK) {
        CONVERT_DIB_TO_IMAGE(m_dib, img);

        IppEnhance::imageBrightness(img, dial.getBright());
        IppEnhance::imageContrast(img, dial.getContrast());

        CONVERT_IMAGE_TO_DIB(img, dib);

        AfxPrintInfo(_T("[Image Brightness & Contrast] Input image: %s, Brightness: %d, Contrast: %d%%"), 
            GetTitle(), dial.getBright(), dial.getContrast());
        AfxNewBitmap(dib);
    }
}


void CImageToolDoc::OnImageGammarCorrection()
{
    // TODO: Add your command handler code here
    CGammarCorrectionDialog dial;
    if (dial.DoModal() == IDOK) {
        CONVERT_DIB_TO_IMAGE(m_dib, img);

        IppEnhance::imageGammarCorrection(img, dial.getGammar());

        CONVERT_IMAGE_TO_DIB(img, dib);

        AfxPrintInfo(_T("[Image Gammar Correction] Input image: %s, Gammar: %1.2f"),
            GetTitle(), dial.getGammar());
        AfxNewBitmap(dib);
    }
}


void CImageToolDoc::OnViewHistogram()
{
    // TODO: Add your command handler code here
    CHistogramDialog dial;
    dial.setImageToHistogram(&m_dib);
    dial.DoModal();
}


void CImageToolDoc::OnHistogramStretch()
{
    // TODO: Add your command handler code here
    CONVERT_DIB_TO_IMAGE(m_dib, img);
    IppEnhance::imageHistogramStretch(img);
    CONVERT_IMAGE_TO_DIB(img, dib);

    AfxPrintInfo(_T("[Image Histogram Stretch] Input image: %s"), GetTitle());
    AfxNewBitmap(dib);
}


void CImageToolDoc::OnHistogramEqualization()
{
    // TODO: Add your command handler code here
    CONVERT_DIB_TO_IMAGE(m_dib, img);
    IppEnhance::imageHistogramEqualizatioon(img);
    CONVERT_IMAGE_TO_DIB(img, dib);

    AfxPrintInfo(_T("[Image Histogram Equalization] Input image: %s"), GetTitle());
    AfxNewBitmap(dib);
}


void CImageToolDoc::OnUpdateViewHistogram(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(m_dib.getBitCount() == 8);
}


void CImageToolDoc::OnUpdateHistogramEqualization(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(m_dib.getBitCount() == 8);
}


void CImageToolDoc::OnUpdateHistogramStretch(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(m_dib.getBitCount() == 8);
}


void CImageToolDoc::OnUpdateImageBrightContrast(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(m_dib.getBitCount() == 8);
}


void CImageToolDoc::OnUpdateImageGammar(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(m_dib.getBitCount() == 8);
}


void CImageToolDoc::OnArithmeticLogical()
{
    // TODO: Add your command handler code here
    CArithmeticLogicalDialog dial;
    if (dial.DoModal() == IDOK) {
        CImageToolDoc* pDoc1 = (CImageToolDoc*)dial.getDoc1();
        CImageToolDoc* pDoc2 = (CImageToolDoc*)dial.getDoc2();

        CONVERT_DIB_TO_IMAGE(pDoc1->getDib(), img1);
        CONVERT_DIB_TO_IMAGE(pDoc2->getDib(), img2);
        IppByteImage res;

        bool ret = false;

        switch (dial.getALFunc()) {
        case 0: ret = IppEnhance::imageAddition(img1, img2, res);
            break;
        case 1: ret = IppEnhance::imageSubtraction(img1, img2, res);
            break;
        case 2: ret = IppEnhance::imageAverage(img1, img2, res);
            break;
        case 3: ret = IppEnhance::imageDifference(img1, img2, res);
            break;
        case 4: ret = IppEnhance::imageAND(img1, img2, res);
            break;
        case 5: ret = IppEnhance::imageOR(img1, img2, res);
            break;
        }

        if (ret) {
            CONVERT_IMAGE_TO_DIB(res, dib);

            TCHAR* op[] = { _T("Add"), _T("Sub"), _T("Ave"), _T("Diff"), _T("AND"), _T("OR") };

            AfxPrintInfo(_T("[Image Arithmetic & Logical operation] [%s] Input image #1: %s, Input image #2: %s"), 
                op[dial.getALFunc()], pDoc1->GetTitle(), pDoc2->GetTitle());
            AfxNewBitmap(dib);
        }
        else {
            AfxMessageBox(_T("Two input images should be the same size!"));
        }
    }
}


void CImageToolDoc::OnBitplaneSlicing()
{
    // TODO: Add your command handler code here
    CONVERT_DIB_TO_IMAGE(m_dib, img);
    IppByteImage imgPlane;

    for (int i = 0; i < 8; i++) {
        IppEnhance::imageBitPlane(img, imgPlane, i);

        CONVERT_IMAGE_TO_DIB(imgPlane, dib);
        AfxNewBitmap(dib);
    }

    AfxPrintInfo(_T("[Image Bit Plane] Input image: %s"), GetTitle());
}


void CImageToolDoc::OnUpdateBitplaneSlicing(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(m_dib.getBitCount() == 8);
}
