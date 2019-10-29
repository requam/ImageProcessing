#include "stdafx.h"
#include "IppDib.h"


IppDib::IppDib()
    : m_nWidth(0), m_nHeight(0), m_nBitCount(0), m_nDibSize(0), m_pDib(nullptr)
{
}

IppDib::IppDib(const IppDib& dib) 
    : m_nWidth(dib.m_nWidth), m_nHeight(dib.m_nHeight), m_nBitCount(dib.m_nBitCount), m_nDibSize(dib.m_nDibSize), m_pDib(nullptr)
{
    if (dib.m_pDib != nullptr) {
        m_pDib = new BYTE[m_nDibSize];
        memcpy(m_pDib, dib.m_pDib, m_nDibSize);
    }
}

IppDib::~IppDib()
{
    if (m_pDib) {
        delete[] m_pDib;
        m_pDib = nullptr;
    }
}

////
BYTE* IppDib::getDIBitsAddr() const {
    if (m_pDib == nullptr) {
        return nullptr;
    }

    LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;
    return ((BYTE*)m_pDib + lpbmi->biSize + (sizeof(RGBQUAD) * getPaletteNums()));
}

int IppDib::getPaletteNums() const {
    switch (m_nBitCount) {
    case 1:
        return 2;
    case 4:
        return 16;
    case 8:
        return 256;
    default:
        return 0;
    }
}

IppDib& IppDib::operator=(const IppDib& dib) {
    if (this == &dib) {
        return *this;
    }

    if (m_pDib) {
        delete[] m_pDib;
    }

    m_nWidth = dib.m_nWidth;
    m_nHeight = dib.m_nHeight;
    m_nBitCount = dib.m_nBitCount;
    m_nDibSize = dib.m_nDibSize;
    m_pDib = nullptr;

    if (dib.m_pDib != nullptr) {
        m_pDib = new BYTE[m_nDibSize];
        memcpy(m_pDib, dib.m_pDib, m_nDibSize);
    }

    return *this;
}

void IppDib::copy(IppDib* pImage) {
    if (this == pImage) {
        return;
    }

    if (m_pDib) {
        delete[] m_pDib;
    }

    m_nWidth = pImage->m_nWidth;
    m_nHeight = pImage->m_nHeight;
    m_nBitCount = pImage->m_nBitCount;
    m_nDibSize = pImage->m_nDibSize;
    m_pDib = nullptr;

    if (pImage->m_pDib != nullptr) {
        m_pDib = new BYTE[m_nDibSize];
        memcpy(m_pDib, pImage->m_pDib, m_nDibSize);
    }
}

////
bool IppDib::createGrayBitmap(LONG nWidth, LONG nHeight) {
    if (m_pDib) {
        destroyBitmap();
    }

    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_nBitCount = 8;

    DWORD dwWidthStep = (m_nWidth * m_nBitCount / 8 + 3) & ~3;
    DWORD dwSizeImage = (m_nHeight * dwWidthStep);
    m_nDibSize = sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * getPaletteNums()) + dwSizeImage;

    m_pDib = new BYTE[m_nDibSize];
    if (m_pDib == nullptr) {
        return false;
    }

    LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;
    lpbmi->biSize = sizeof(BITMAPINFOHEADER);
    lpbmi->biWidth = m_nWidth;
    lpbmi->biHeight = m_nHeight;
    lpbmi->biPlanes = 1;
    lpbmi->biBitCount = m_nBitCount;
    lpbmi->biCompression = BI_RGB;
    lpbmi->biSizeImage = dwSizeImage;
    lpbmi->biXPelsPerMeter = 0;
    lpbmi->biYPelsPerMeter = 0;
    lpbmi->biClrUsed = 0;
    lpbmi->biClrImportant = 0;

    RGBQUAD* pPal = (RGBQUAD*)((BYTE*)m_pDib + sizeof(BITMAPINFOHEADER));
    for (int i = 0; i < 256; i++) {
        pPal->rgbBlue = (BYTE)i;
        pPal->rgbGreen = (BYTE)i;
        pPal->rgbRed = (BYTE)i;
        pPal->rgbReserved = 0;
        pPal++;
    }

    BYTE* pData = getDIBitsAddr();
    memset(pData, 0, dwSizeImage);

    return true;
}

bool IppDib::createRgbBitmap(LONG nWidth, LONG nHeight) {
    if (m_pDib) {
        destroyBitmap();
    }

    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_nBitCount = 24;

    DWORD dwWidthStep = (m_nWidth * m_nBitCount / 8 + 3) & ~3;
    DWORD dwSizeImage = (m_nHeight * dwWidthStep);
    m_nDibSize = sizeof(BITMAPINFOHEADER) + dwSizeImage;

    m_pDib = new BYTE[m_nDibSize];
    if (m_pDib == nullptr) {
        return false;
    }

    LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;
    lpbmi->biSize = sizeof(BITMAPINFOHEADER);
    lpbmi->biWidth = m_nWidth;
    lpbmi->biHeight = m_nHeight;
    lpbmi->biPlanes = 1;
    lpbmi->biBitCount = m_nBitCount;
    lpbmi->biCompression = BI_RGB;
    lpbmi->biSizeImage = dwSizeImage;
    lpbmi->biXPelsPerMeter = 0;
    lpbmi->biYPelsPerMeter = 0;
    lpbmi->biClrUsed = 0;
    lpbmi->biClrImportant = 0;

    BYTE* pData = getDIBitsAddr();
    memset(pData, 0, dwSizeImage);

    return true;
}

void IppDib::destroyBitmap() {
    if (m_pDib) {
        delete[] m_pDib;
        m_pDib = nullptr;
    }

    m_nWidth = 0;
    m_nHeight = 0;
    m_nBitCount = 0;
    m_nDibSize = 0;
}

////
bool IppDib::load(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if (!_strcmpi(ext, ".bmp")) {
        return loadBMP(filename);
    }
    else {
        return false;
    }
}

bool IppDib::save(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if (!_strcmpi(ext, ".bmp")) {
        return saveBMP(filename);
    }
    else {
        return false;
    }
}

bool IppDib::loadBMP(const char* filename) {
    FILE* fp = nullptr;
    fopen_s(&fp, filename, "rb");
    if (!fp) {
        return false;
    }

    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;

    if (fread(&bmfh, sizeof(BITMAPFILEHEADER), 1, fp) != 1) {
        fclose(fp);
        return false;
    }

    if (bmfh.bfType != DIB_HEADER_MARKER) {
        fclose(fp);
        return false;
    }

    if (fread(&bmih, sizeof(BITMAPINFOHEADER), 1, fp) != 1) {
        fclose(fp);
        return false;
    }

    m_nWidth = bmih.biWidth;
    m_nHeight = bmih.biHeight;
    m_nBitCount = bmih.biBitCount;

    DWORD dwWidthStep = (DWORD)((m_nWidth * m_nBitCount / 8 + 3) & ~3);
    DWORD dwSizeImage = m_nHeight * dwWidthStep;

    if (m_nBitCount == 24) {
        m_nDibSize = sizeof(BITMAPINFOHEADER) + dwSizeImage;
    }
    else {
        m_nDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << m_nBitCount) + dwSizeImage;
    }

    if (m_pDib) {
        destroyBitmap();
    }

    m_pDib = new BYTE[m_nDibSize];
    if (m_pDib == nullptr) {
        fclose(fp);
        return false;
    }

    fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);
    if (fread(m_pDib, sizeof(BYTE), m_nDibSize, fp) != m_nDibSize) {
        delete[] m_pDib;
        m_pDib = nullptr;
        fclose(fp);
        return false;
    }

    fclose(fp);

    return true;
}

bool IppDib::saveBMP(const char* filename) {
    if (!isValid()) {
        return false;
    }

    FILE* fp = nullptr;
    fopen_s(&fp, filename, "wb");
    if (!fp) {
        return false;
    }

    BITMAPFILEHEADER bmfh;
    bmfh.bfType = DIB_HEADER_MARKER;
    bmfh.bfSize = (DWORD)sizeof(BITMAPFILEHEADER) + m_nDibSize;
    bmfh.bfReserved1 = 0;
    bmfh.bfReserved2 = 0;
    bmfh.bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * getPaletteNums()));

    fwrite(&bmfh, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(getBitmapInfoAddr(), m_nDibSize, 1, fp);

    fclose(fp);

    return true;
}

////
void IppDib::draw(HDC hdc, int dx, int dy) {
    if (m_pDib == nullptr) {
        return;
    }

    LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
    LPVOID lpBits = (LPVOID)getDIBitsAddr();

    ::SetDIBitsToDevice(hdc, dx, dy, m_nWidth, m_nHeight, 0, 0, 0, m_nHeight, lpBits, lpbi, DIB_RGB_COLORS);
}

void IppDib::draw(HDC hdc, int dx, int dy, int dw, int dh, DWORD dwRop) {
    draw(hdc, dx, dy, dw, dh, 0, 0, m_nWidth, m_nHeight, dwRop);
}

void IppDib::draw(HDC hdc, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD dwRop) {
    if (m_pDib == nullptr) {
        return;
    }

    LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
    LPVOID lpBits = (LPVOID)getDIBitsAddr();

    SetStretchBltMode(hdc, COLORONCOLOR);
    ::StretchDIBits(hdc, dx, dy, dw, dh, sx, sy, sw, sh, lpBits, lpbi, DIB_RGB_COLORS, dwRop);
}

////
bool IppDib::copyToClipboard() {
    if (!::OpenClipboard(nullptr)) {
        return false;
    }

    DWORD dwDibSize = getDibSize();
    HANDLE hDib = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, dwDibSize);
    if (hDib == nullptr) {
        ::CloseClipboard();
        return false;
    }

    LPVOID lpDib = ::GlobalLock((HGLOBAL)hDib);
    memcpy(lpDib, getBitmapInfoAddr(), dwDibSize);
    ::GlobalUnlock(hDib);

    ::EmptyClipboard();
    ::SetClipboardData(CF_DIB, hDib);
    ::CloseClipboard();

    return true;
}

bool IppDib::pasteFromClipboard() {
    if (!::IsClipboardFormatAvailable(CF_DIB)) {
        return false;
    }

    if (!::OpenClipboard(nullptr)) {
        return false;
    }

    HANDLE hDib = ::GetClipboardData(CF_DIB);
    if (hDib == nullptr) {
        ::CloseClipboard();
        return false;
    }

    DWORD dwSize = (DWORD)::GlobalSize((HGLOBAL)hDib);
    LPVOID lpDib = ::GlobalLock((HGLOBAL)hDib);

    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)lpDib;
    m_nWidth = lpbi->biWidth;
    m_nHeight = lpbi->biHeight;
    m_nBitCount = lpbi->biBitCount;

    DWORD dwWidthStep = (DWORD)((m_nWidth * m_nBitCount / 8 + 3) & ~3);
    DWORD dwSizeImage = m_nHeight * dwWidthStep;

    if (m_nBitCount == 24) {
        m_nDibSize = sizeof(BITMAPINFOHEADER) + dwSizeImage;
    }
    else {
        m_nDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<<m_nBitCount) + dwSizeImage;
    }

    if (m_pDib) {
        destroyBitmap();
    }

    m_pDib = new BYTE[m_nDibSize];
    if (m_pDib == nullptr) {
        ::GlobalUnlock(hDib);
        ::CloseClipboard();
        return false;
    }

    memcpy(m_pDib, lpDib, m_nDibSize);

    ::GlobalUnlock(hDib);
    ::CloseClipboard();
    
    return true;
}
