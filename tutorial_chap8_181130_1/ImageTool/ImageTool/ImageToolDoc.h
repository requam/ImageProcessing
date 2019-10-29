
// ImageToolDoc.h : interface of the CImageToolDoc class
//


#pragma once
#include ".\IppImage\IppDib.h"


class CImageToolDoc : public CDocument
{
protected: // create from serialization only
	CImageToolDoc();
	DECLARE_DYNCREATE(CImageToolDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CImageToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

    IppDib getDib() const { return m_dib; }

private:
    // bitmap data object
    IppDib m_dib;
public:
    afx_msg void OnWindowDuplicate();
    afx_msg void OnEditCopy();
    afx_msg void OnImageInverse();
    afx_msg void OnUpdateImageInverse(CCmdUI *pCmdUI);
    afx_msg void OnImageBrightContrast();
    afx_msg void OnImageGammarCorrection();
    afx_msg void OnViewHistogram();
    afx_msg void OnHistogramStretch();
    afx_msg void OnHistogramEqualization();
    afx_msg void OnUpdateViewHistogram(CCmdUI *pCmdUI);
    afx_msg void OnUpdateHistogramEqualization(CCmdUI *pCmdUI);
    afx_msg void OnUpdateHistogramStretch(CCmdUI *pCmdUI);
    afx_msg void OnUpdateImageBrightContrast(CCmdUI *pCmdUI);
    afx_msg void OnUpdateImageGammar(CCmdUI *pCmdUI);
    afx_msg void OnArithmeticLogical();
    afx_msg void OnBitplaneSlicing();
    afx_msg void OnUpdateBitplaneSlicing(CCmdUI *pCmdUI);
    afx_msg void OnFilterMean();
    afx_msg void OnFilterWeightedmean();
    afx_msg void OnFilterGaussian();
    afx_msg void OnFilterLaplacian();
    afx_msg void OnFilterUnsharpmask();
    afx_msg void OnFilterHighboost();
};
