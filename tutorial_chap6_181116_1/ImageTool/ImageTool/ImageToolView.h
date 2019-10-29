
// ImageToolView.h : interface of the CImageToolView class
//

#pragma once


class CImageToolView : public CScrollView
{
protected: // create from serialization only
	CImageToolView();
	DECLARE_DYNCREATE(CImageToolView)

// Attributes
public:
	CImageToolDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CImageToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
private:
    // iamge zoom in/out
    float m_fZoom;

public:
    void setScrollSizeToFit();
    void showImageInfo(CPoint point);

    afx_msg void OnViewZoom1();
    afx_msg void OnUpdateViewZoom1(CCmdUI *pCmdUI);
    afx_msg void OnViewZoom2();
    afx_msg void OnUpdateViewZoom2(CCmdUI *pCmdUI);
    afx_msg void OnViewZoom3();
    afx_msg void OnUpdateViewZoom3(CCmdUI *pCmdUI);
    afx_msg void OnViewZoom4();
    afx_msg void OnUpdateViewZoom4(CCmdUI *pCmdUI);
    afx_msg void OnViewZoom01();
    afx_msg void OnUpdateViewZoom01(CCmdUI *pCmdUI);
    afx_msg void OnViewZoom05();
    afx_msg void OnUpdateViewZoom05(CCmdUI *pCmdUI);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in ImageToolView.cpp
inline CImageToolDoc* CImageToolView::GetDocument() const
   { return reinterpret_cast<CImageToolDoc*>(m_pDocument); }
#endif

