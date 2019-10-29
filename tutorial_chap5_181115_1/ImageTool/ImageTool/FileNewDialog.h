#pragma once


// CFileNewDialog dialog

class CFileNewDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFileNewDialog)

public:
	CFileNewDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileNewDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_NEW };
#endif

    int getWidth() const { return m_nWidth; }
    int getHeight() const { return m_nHeight; }
    int getType() const { return m_nType; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
    // image width
    int m_nWidth;
    // image height
    int m_nHeight;
    // image color type
    int m_nType;
};
