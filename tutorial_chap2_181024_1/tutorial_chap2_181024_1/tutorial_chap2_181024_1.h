
// tutorial_chap2_181024_1.h : main header file for the tutorial_chap2_181024_1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ctutorial_chap2_181024_1App:
// See tutorial_chap2_181024_1.cpp for the implementation of this class
//

class Ctutorial_chap2_181024_1App : public CWinApp
{
public:
	Ctutorial_chap2_181024_1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ctutorial_chap2_181024_1App theApp;
