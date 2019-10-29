
// tutorial_chap2_181024_1View.h : interface of the Ctutorial_chap2_181024_1View class
//

#pragma once


class Ctutorial_chap2_181024_1View : public CView
{
protected: // create from serialization only
	Ctutorial_chap2_181024_1View();
	DECLARE_DYNCREATE(Ctutorial_chap2_181024_1View)

// Attributes
public:
	Ctutorial_chap2_181024_1Doc* GetDocument() const;

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
	virtual ~Ctutorial_chap2_181024_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in tutorial_chap2_181024_1View.cpp
inline Ctutorial_chap2_181024_1Doc* Ctutorial_chap2_181024_1View::GetDocument() const
   { return reinterpret_cast<Ctutorial_chap2_181024_1Doc*>(m_pDocument); }
#endif

