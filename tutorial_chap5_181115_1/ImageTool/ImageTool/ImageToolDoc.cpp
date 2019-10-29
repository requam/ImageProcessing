
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageToolDoc

IMPLEMENT_DYNCREATE(CImageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolDoc, CDocument)
    ON_COMMAND(ID_WINDOW_DUPLICATE, &CImageToolDoc::OnWindowDuplicate)
    ON_COMMAND(ID_EDIT_COPY, &CImageToolDoc::OnEditCopy)
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
