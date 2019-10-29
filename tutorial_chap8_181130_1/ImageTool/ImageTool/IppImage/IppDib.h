#pragma once

#include <Windows.h>

#define DIB_HEADER_MARKER ((WORD) ('M'<<8) | 'B')

class IppDib
{
public:
    IppDib();
    IppDib(const IppDib& dib);
    virtual ~IppDib();

    bool createGrayBitmap(LONG nWidth, LONG nHeight);
    bool createRgbBitmap(LONG nWidth, LONG nHeight);
    void destroyBitmap();

    bool load(const char* filename);
    bool save(const char* filename);

    void draw(HDC hdc, int dx = 0, int dy = 0);
    void draw(HDC hdc, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);
    void draw(HDC hdc, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD dwRop = SRCCOPY);

    bool copyToClipboard();
    bool pasteFromClipboard();

    IppDib& operator=(const IppDib& dib);
    void copy(IppDib* pImage);

    LONG getHeight() const { return m_nHeight; }
    LONG getWidth() const { return m_nWidth; }
    WORD getBitCount() const { return m_nBitCount; }
    DWORD getDibSize() const { return m_nDibSize; }
    LPBITMAPINFO getBitmapInfoAddr() const { return (LPBITMAPINFO)m_pDib; }
    BYTE* getDIBitsAddr() const;
    int getPaletteNums() const;
    bool isValid() const { return (m_pDib != nullptr); }

private:
    bool loadBMP(const char* filename);
    bool saveBMP(const char* filename);

    LONG m_nWidth;
    LONG m_nHeight;
    WORD m_nBitCount;
    DWORD m_nDibSize;
    BYTE* m_pDib;
};
