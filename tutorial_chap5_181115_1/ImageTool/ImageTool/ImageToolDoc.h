
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
};
