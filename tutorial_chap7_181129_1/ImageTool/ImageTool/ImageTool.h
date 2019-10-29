
// ImageTool.h : main header file for the ImageTool application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CImageToolApp:
// See ImageTool.cpp for the implementation of this class
//
class IppDib;
class CImageToolApp : public CWinAppEx
{
public:
	CImageToolApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:

    IppDib* getNewDib() const { return m_pNewDib; }
    void setNewDib(IppDib* dib) { m_pNewDib = dib; }

    CMultiDocTemplate* getImgDocTemplate() const { return m_pImgDocTemplate; }
    void setImgDocTemplate(CMultiDocTemplate* doc) { m_pImgDocTemplate = doc; }

private:
    IppDib* m_pNewDib;
    CMultiDocTemplate* m_pImgDocTemplate;

public:
    afx_msg void OnEditPaste();
    afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
    afx_msg void OnWindowCloseall();
};

extern CImageToolApp theApp;

void AfxNewBitmap(IppDib& dib);
void AfxPrintInfo(CString message);
void AfxPrintInfo(LPCTSTR lpszFormat, ...);
