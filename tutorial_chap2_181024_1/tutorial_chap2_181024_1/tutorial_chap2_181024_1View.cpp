
// tutorial_chap2_181024_1View.cpp : implementation of the Ctutorial_chap2_181024_1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "tutorial_chap2_181024_1.h"
#endif

#include "tutorial_chap2_181024_1Doc.h"
#include "tutorial_chap2_181024_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctutorial_chap2_181024_1View

IMPLEMENT_DYNCREATE(Ctutorial_chap2_181024_1View, CView)

BEGIN_MESSAGE_MAP(Ctutorial_chap2_181024_1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Ctutorial_chap2_181024_1View construction/destruction

Ctutorial_chap2_181024_1View::Ctutorial_chap2_181024_1View()
{
	// TODO: add construction code here

}

Ctutorial_chap2_181024_1View::~Ctutorial_chap2_181024_1View()
{
}

BOOL Ctutorial_chap2_181024_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ctutorial_chap2_181024_1View drawing

void Ctutorial_chap2_181024_1View::OnDraw(CDC* pDC)
{
	Ctutorial_chap2_181024_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

    int i, dan;
    CString str;

    for (dan = 2; dan < 10; dan++) {
        for (i = 1; i < 10; i++) {
            str.Format(_T("%dx%d=%d"), dan, i, dan*i);
            pDC->TextOutW((dan - 2) * 70 + 20, 20 * i, str);
        }
    }
}


// Ctutorial_chap2_181024_1View printing

BOOL Ctutorial_chap2_181024_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ctutorial_chap2_181024_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ctutorial_chap2_181024_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Ctutorial_chap2_181024_1View diagnostics

#ifdef _DEBUG
void Ctutorial_chap2_181024_1View::AssertValid() const
{
	CView::AssertValid();
}

void Ctutorial_chap2_181024_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctutorial_chap2_181024_1Doc* Ctutorial_chap2_181024_1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctutorial_chap2_181024_1Doc)));
	return (Ctutorial_chap2_181024_1Doc*)m_pDocument;
}
#endif //_DEBUG


// Ctutorial_chap2_181024_1View message handlers
