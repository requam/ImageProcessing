
// tutorial_chap4_181114_1View.cpp : implementation of the Ctutorial_chap4_181114_1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "tutorial_chap4_181114_1.h"
#endif

#include "tutorial_chap4_181114_1Doc.h"
#include "tutorial_chap4_181114_1View.h"

#include "IppDib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctutorial_chap4_181114_1View

IMPLEMENT_DYNCREATE(Ctutorial_chap4_181114_1View, CView)

BEGIN_MESSAGE_MAP(Ctutorial_chap4_181114_1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Ctutorial_chap4_181114_1View construction/destruction

Ctutorial_chap4_181114_1View::Ctutorial_chap4_181114_1View()
{
	// TODO: add construction code here

}

Ctutorial_chap4_181114_1View::~Ctutorial_chap4_181114_1View()
{
}

BOOL Ctutorial_chap4_181114_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ctutorial_chap4_181114_1View drawing

void Ctutorial_chap4_181114_1View::OnDraw(CDC* /*pDC*/)
{
	Ctutorial_chap4_181114_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Ctutorial_chap4_181114_1View printing

BOOL Ctutorial_chap4_181114_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ctutorial_chap4_181114_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ctutorial_chap4_181114_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Ctutorial_chap4_181114_1View diagnostics

#ifdef _DEBUG
void Ctutorial_chap4_181114_1View::AssertValid() const
{
	CView::AssertValid();
}

void Ctutorial_chap4_181114_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctutorial_chap4_181114_1Doc* Ctutorial_chap4_181114_1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctutorial_chap4_181114_1Doc)));
	return (Ctutorial_chap4_181114_1Doc*)m_pDocument;
}
#endif //_DEBUG


// Ctutorial_chap4_181114_1View message handlers

void Ctutorial_chap4_181114_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    IppDib dib;
    dib.load("lenna.bmp");

    CClientDC dc(this);
    dib.draw(dc.m_hDC, point.x, point.y);

    CView::OnLButtonDown(nFlags, point);
}
