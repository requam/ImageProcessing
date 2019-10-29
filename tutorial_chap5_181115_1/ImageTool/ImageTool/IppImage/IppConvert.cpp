#include "stdafx.h"
#include <assert.h>

#include "IppConvert.h"

void IppConvert::convertDibToImage(IppDib& dib, IppByteImage& img) {
    assert(dib.isValid());
    assert(dib.getBitCount() == 8);

    int w = dib.getWidth();
    int h = dib.getHeight();
    int ws = (w + 3) & ~3;
    BYTE* pDIBits = dib.getDIBitsAddr();

    img.createImage(w, h);
    BYTE** pixels = img.getPixels2D();

    for (int i = 0; i < h; i++) {
        memcpy(pixels[i], &pDIBits[(h - 1 - i) * ws], w);
    }
}

void IppConvert::convertDibToImage(IppDib& dib, IppRgbImage& img) {
    assert(dib.isValid());
    assert(dib.getBitCount() == 24);

    int w = dib.getWidth();
    int h = dib.getHeight();
    int ws = (w * 3 + 3) & ~3;
    BYTE* pDIBits = dib.getDIBitsAddr();

    img.createImage(w, h);
    RGBBYTE** pixels = img.getPixels2D();

    for (int i = 0; i < h; i++) {
        memcpy(pixels[i], &pDIBits[(h - 1 - i) * ws], w * 3);
    }
}

void IppConvert::convertImageToDib(IppByteImage& img, IppDib& dib) {
    assert(img.isValid());

    int w = img.getWidth();
    int h = img.getHeight();
    int ws = (w + 3) & ~3;
    BYTE** pixels = img.getPixels2D();

    dib.createGrayBitmap(w, h);
    BYTE* pDIBits = dib.getDIBitsAddr();

    for (int i = 0; i < h; i++) {
        memcpy(&pDIBits[(h - 1 - i) * ws], pixels[i], w);
    }
}

void IppConvert::convertImageToDib(IppFloatImage& img, IppDib& dib) {
    assert(img.isValid());

    int w = img.getWidth();
    int h = img.getHeight();
    int ws = (w + 3) & ~3;
    float** pixels = img.getPixels2D();

    dib.createGrayBitmap(w, h);
    BYTE* pDIBits = dib.getDIBitsAddr();

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pDIBits[(h - 1 - j) * ws + i] = static_cast<BYTE>(limit(pixels[j][i] + 0.5f));
        }
    }
}

void IppConvert::convertImageToDib(IppRgbImage& img, IppDib& dib) {
    assert(img.isValid());

    int w = img.getWidth();
    int h = img.getHeight();
    int ws = (w * 3 + 3) & ~3;
    RGBBYTE** pixels = img.getPixels2D();

    dib.createGrayBitmap(w, h);
    BYTE* pDIBits = dib.getDIBitsAddr();

    for (int i = 0; i < h; i++) {
        memcpy(&pDIBits[(h - 1 - i) * ws], pixels[i], w * 3);
    }
}
