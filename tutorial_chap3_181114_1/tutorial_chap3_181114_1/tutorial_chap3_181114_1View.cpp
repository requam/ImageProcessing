
// tutorial_chap3_181114_1View.cpp : implementation of the Ctutorial_chap3_181114_1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "tutorial_chap3_181114_1.h"
#endif

#include "tutorial_chap3_181114_1Doc.h"
#include "tutorial_chap3_181114_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctutorial_chap3_181114_1View

IMPLEMENT_DYNCREATE(Ctutorial_chap3_181114_1View, CView)

BEGIN_MESSAGE_MAP(Ctutorial_chap3_181114_1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Ctutorial_chap3_181114_1View construction/destruction

Ctutorial_chap3_181114_1View::Ctutorial_chap3_181114_1View()
{
	// TODO: add construction code here

}

Ctutorial_chap3_181114_1View::~Ctutorial_chap3_181114_1View()
{
}

BOOL Ctutorial_chap3_181114_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ctutorial_chap3_181114_1View drawing

void Ctutorial_chap3_181114_1View::OnDraw(CDC* /*pDC*/)
{
	Ctutorial_chap3_181114_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Ctutorial_chap3_181114_1View printing

BOOL Ctutorial_chap3_181114_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ctutorial_chap3_181114_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ctutorial_chap3_181114_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Ctutorial_chap3_181114_1View diagnostics

#ifdef _DEBUG
void Ctutorial_chap3_181114_1View::AssertValid() const
{
	CView::AssertValid();
}

void Ctutorial_chap3_181114_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctutorial_chap3_181114_1Doc* Ctutorial_chap3_181114_1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctutorial_chap3_181114_1Doc)));
	return (Ctutorial_chap3_181114_1Doc*)m_pDocument;
}
#endif //_DEBUG


// Ctutorial_chap3_181114_1View message handlers

#define DIB_HEADER_MARKER ((WORD) ('M'<<8) | 'B')

void Ctutorial_chap3_181114_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    FILE* fp = nullptr;
    fopen_s(&fp, "lenna.bmp", "rb");
    if (!fp) {
        return;
    }

    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;

    if (fread(&bmfh, sizeof(BITMAPFILEHEADER), 1, fp) != 1) {
        fclose(fp);
        return;
    }

    if (bmfh.bfType != DIB_HEADER_MARKER) {
        fclose(fp);
        return;
    }

    if (fread(&bmih, sizeof(BITMAPINFOHEADER), 1, fp) != 1) {
        fclose(fp);
        return;
    }

    LONG nWidth = bmih.biWidth;
    LONG nHeight = bmih.biHeight;
    WORD nBitCount = bmih.biBitCount;

    DWORD dwWidthStep = (DWORD)((nWidth * nBitCount / 8 + 3) & ~3);
    DWORD dwSizeImage = nHeight * dwWidthStep;

    DWORD dwDibSize;
    if (nBitCount == 24) {
        dwDibSize = sizeof(BITMAPINFOHEADER) + dwSizeImage;
    }
    else {
        dwDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<<nBitCount) + dwSizeImage;
    }

    BYTE* pDib = new BYTE[dwDibSize];
    if (pDib == NULL) {
        fclose(fp);
        return;
    }

    fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);
    if (fread(pDib, sizeof(BYTE), dwDibSize, fp) != dwDibSize) {
        delete[] pDib;
        pDib = nullptr;
        fclose(fp);
        return;
    }

    LPVOID lpvBits;
    if (nBitCount == 24) {
        lpvBits = pDib + sizeof(BITMAPINFOHEADER);
    }
    else {
        lpvBits = pDib + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<<nBitCount);
    }

    CClientDC dc(this);
    ::SetDIBitsToDevice(dc.m_hDC, point.x, point.y, nWidth, nHeight, 0, 0, 0, nHeight, lpvBits, (BITMAPINFO*)pDib, DIB_RGB_COLORS);

    delete[] pDib;
    fclose(fp);

    CView::OnLButtonDown(nFlags, point);
}
