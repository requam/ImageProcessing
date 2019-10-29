
// ImageToolView.cpp : implementation of the CImageToolView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#include "MainFrm.h"

#include "ImageToolDoc.h"
#include "ImageToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageToolView

IMPLEMENT_DYNCREATE(CImageToolView, CScrollView)

BEGIN_MESSAGE_MAP(CImageToolView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_VIEW_ZOOM1, &CImageToolView::OnViewZoom1)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, &CImageToolView::OnUpdateViewZoom1)
    ON_COMMAND(ID_VIEW_ZOOM2, &CImageToolView::OnViewZoom2)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, &CImageToolView::OnUpdateViewZoom2)
    ON_COMMAND(ID_VIEW_ZOOM3, &CImageToolView::OnViewZoom3)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, &CImageToolView::OnUpdateViewZoom3)
    ON_COMMAND(ID_VIEW_ZOOM4, &CImageToolView::OnViewZoom4)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM4, &CImageToolView::OnUpdateViewZoom4)
    ON_COMMAND(ID_VIEW_ZOOM0_1, &CImageToolView::OnViewZoom01)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM0_1, &CImageToolView::OnUpdateViewZoom01)
    ON_COMMAND(ID_VIEW_ZOOM0_5, &CImageToolView::OnViewZoom05)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM0_5, &CImageToolView::OnUpdateViewZoom05)
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CImageToolView construction/destruction

CImageToolView::CImageToolView()
    : m_fZoom(1.0f)
{
	// TODO: add construction code here

}

CImageToolView::~CImageToolView()
{
}

BOOL CImageToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CImageToolView drawing

void CImageToolView::OnDraw(CDC* pDC)
{
	CImageToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
    if (pDoc->getDib().isValid()) {
        int w = pDoc->getDib().getWidth();
        int h = pDoc->getDib().getHeight();
        pDoc->getDib().draw(pDC->m_hDC, 0, 0, (int)(w * m_fZoom), (int)(h * m_fZoom));
    }
}

void CImageToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    setScrollSizeToFit();
}

void CImageToolView::setScrollSizeToFit() {
    CSize sizeTotal;
    // TODO: calculate the total size of this view
    CImageToolDoc* pDoc = GetDocument();

    if (pDoc->getDib().isValid()) {
        int w = pDoc->getDib().getWidth();
        int h = pDoc->getDib().getHeight();

        sizeTotal.cx = (int)(w * m_fZoom);
        sizeTotal.cy = (int)(h * m_fZoom);
    }
    else {
        sizeTotal.cx = sizeTotal.cy = 100;
    }

    SetScrollSizes(MM_TEXT, sizeTotal);

    ResizeParentToFit(true);
}

// CImageToolView printing


void CImageToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CImageToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageToolView diagnostics

#ifdef _DEBUG
void CImageToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageToolDoc* CImageToolView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageToolDoc)));
	return (CImageToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageToolView message handlers


BOOL CImageToolView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: Add your message handler code here and/or call default
    CBrush br;
    br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
    FillOutsideRect(pDC, &br);

    return TRUE;
}


void CImageToolView::OnViewZoom1()
{
    // TODO: Add your command handler code here
    m_fZoom = 1.0f;
    setScrollSizeToFit();
    Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_fZoom == 1.0f);
}


void CImageToolView::OnViewZoom2()
{
    // TODO: Add your command handler code here
    m_fZoom = 2.0f;
    setScrollSizeToFit();
    Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_fZoom == 2.0f);
}


void CImageToolView::OnViewZoom3()
{
    // TODO: Add your command handler code here
    m_fZoom = 3.0f;
    setScrollSizeToFit();
    Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_fZoom == 3.0f);
}


void CImageToolView::OnViewZoom4()
{
    // TODO: Add your command handler code here
    m_fZoom = 4.0f;
    setScrollSizeToFit();
    Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom4(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_fZoom == 4.0f);
}


void CImageToolView::OnViewZoom01()
{
    // TODO: Add your command handler code here
    m_fZoom = 0.1f;
    setScrollSizeToFit();
    Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom01(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_fZoom == 0.1f);
}


void CImageToolView::OnViewZoom05()
{
    // TODO: Add your command handler code here
    m_fZoom = 0.5f;
    setScrollSizeToFit();
    Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom05(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_fZoom == 0.5f);
}


void CImageToolView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CPoint pt = point + GetScrollPosition();
    pt.x /= m_fZoom;
    pt.y /= m_fZoom;

    showImageInfo(pt);

    CScrollView::OnMouseMove(nFlags, point);
}

void CImageToolView::showImageInfo(CPoint point) {
    CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    CImageToolDoc* pDoc = GetDocument();

    int w = pDoc->getDib().getWidth();
    int h = pDoc->getDib().getHeight();
    int c = pDoc->getDib().getPaletteNums();

    CString str;

    if (point.x >= 0 && point.y >= 0 && point.x < w && point.y < h) {
        str.Format(_T("(%d, %d)"), point.x, point.y);
        pFrame->getWndStatusBar().SetPaneText(0, str);
    }

    if (c == 0) {
        str.Format(_T("W: %d H: %d C: 16M"), w, h);
    }
    else {
        str.Format(_T("W: %d H: %d C: %d"), w, h, c);
    }
    pFrame->getWndStatusBar().SetPaneText(1, str);
}
