
// tutorial_chap3_181114_1View.h : interface of the Ctutorial_chap3_181114_1View class
//

#pragma once


class Ctutorial_chap3_181114_1View : public CView
{
protected: // create from serialization only
	Ctutorial_chap3_181114_1View();
	DECLARE_DYNCREATE(Ctutorial_chap3_181114_1View)

// Attributes
public:
	Ctutorial_chap3_181114_1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Ctutorial_chap3_181114_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in tutorial_chap3_181114_1View.cpp
inline Ctutorial_chap3_181114_1Doc* Ctutorial_chap3_181114_1View::GetDocument() const
   { return reinterpret_cast<Ctutorial_chap3_181114_1Doc*>(m_pDocument); }
#endif

