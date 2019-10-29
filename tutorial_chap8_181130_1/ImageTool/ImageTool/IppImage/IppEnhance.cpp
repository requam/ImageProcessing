#include "stdafx.h"
#include "IppEnhance.h"

#include <math.h>
#include <algorithm>

void IppEnhance::imageInverse(IppByteImage& img) {
    int size = img.getSize();
    BYTE* p = img.getPixels();

    for (int i = 0; i < size; i++) {
        p[i] = 255 - p[i];
    }
}

void IppEnhance::imageBrightness(IppByteImage& img, int offset) {
    int size = img.getSize();
    BYTE* p = img.getPixels();

    for (int i = 0; i < size; i++) {
        p[i] = static_cast<BYTE>(limit(p[i] + offset));
    }
}

void IppEnhance::imageContrast(IppByteImage& img, float offset) {
    int size = img.getSize();
    BYTE* p = img.getPixels();

    unsigned long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += p[i];
    }

    BYTE avg = (BYTE)(sum / size);
    for (int i = 0; i < size; i++) {
        p[i] = static_cast<BYTE>(limit(p[i] + (p[i] - 128) * offset + 0.5f));
    }
}

void IppEnhance::imageGammarCorrection(IppByteImage& img, float gammar) {
    float inv_gammar = 1.0f / gammar;

    BYTE gammar_lut[256] = { 0 };
    for (int i = 0; i < 256; i++) {
        gammar_lut[i] = static_cast<BYTE>(limit(pow((i / 255.0f), inv_gammar) * 255.0f + 0.5f));
    }

    int size = img.getSize();
    BYTE* p = img.getPixels();

    for (int i = 0; i < size; i++) {
        p[i] = gammar_lut[p[i]];
    }
}

void IppEnhance::imageHistogram(IppByteImage& img, float hist[256]) {
    int size = img.getSize();
    BYTE* p = img.getPixels();

    int cnt[256];
    memset(cnt, 0, sizeof(int) * 256);
    for (int i = 0; i < size; i++) {
        cnt[p[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        hist[i] = (float)cnt[i] / size;
    }
}

void IppEnhance::imageHistogramStretch(IppByteImage& img) {
    int size = img.getSize();
    BYTE* p = img.getPixels();

    BYTE gray_max, gray_min;
    gray_max = gray_min = p[0];
    for (int i = 1; i < size; i++) {
        if (p[i] > gray_max) {
            gray_max = p[i];
        }
        else if (p[i] < gray_min) {
            gray_min = p[i];
        }
    }

    if (gray_max == gray_min) {
        return;
    }

    BYTE minmax5 = (BYTE)((gray_max - gray_min) * 5.0f / 100.0f + 0.5f);
    gray_min += minmax5;
    gray_max -= minmax5;

    for (int i = 0; i < size; i++) {
        p[i] = static_cast<BYTE>(limit((p[i] - gray_min) * 255 / (gray_max - gray_min)));
    }
}

void IppEnhance::imageHistogramEqualizatioon(IppByteImage& img) {
    int size = img.getSize();
    BYTE* p = img.getPixels();

    float hist[256];
    imageHistogram(img, hist);

    float cdf[256] = { 0 };
    cdf[0] = hist[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + hist[i];
    }

    for (int i = 0; i < size; i++) {
        p[i] = static_cast<BYTE>(limit(cdf[p[i]] * 255));
    }
}

bool IppEnhance::imageAddition(IppByteImage& img1, IppByteImage& img2, IppByteImage& res) {
    int w = img1.getWidth();
    int h = img1.getHeight();

    if (w != img2.getWidth() || h != img2.getHeight()) {
        return false;
    }

    res.createImage(w, h);

    int size = res.getSize();
    BYTE* p1 = img1.getPixels();
    BYTE* p2 = img2.getPixels();
    BYTE* p3 = res.getPixels();

    for (int i = 0; i < size; i++) {
        p3[i] = limit(p1[i] + p2[i]);
    }

    return true;
}

bool IppEnhance::imageSubtraction(IppByteImage& img1, IppByteImage& img2, IppByteImage& res) {
    int w = img1.getWidth();
    int h = img1.getHeight();

    if (w != img2.getWidth() || h != img2.getHeight()) {
        return false;
    }

    res.createImage(w, h);

    int size = res.getSize();
    BYTE* p1 = img1.getPixels();
    BYTE* p2 = img2.getPixels();
    BYTE* p3 = res.getPixels();

    for (int i = 0; i < size; i++) {
        p3[i] = limit(p1[i] - p2[i]);
    }

    return true;
}

bool IppEnhance::imageAverage(IppByteImage& img1, IppByteImage& img2, IppByteImage& res) {
    int w = img1.getWidth();
    int h = img1.getHeight();

    if (w != img2.getWidth() || h != img2.getHeight()) {
        return false;
    }

    res.createImage(w, h);

    int size = res.getSize();
    BYTE* p1 = img1.getPixels();
    BYTE* p2 = img2.getPixels();
    BYTE* p3 = res.getPixels();

    for (int i = 0; i < size; i++) {
        p3[i] = (p1[i] + p2[i]) / 2;
    }

    return true;
}

bool IppEnhance::imageDifference(IppByteImage& img1, IppByteImage& img2, IppByteImage& res) {
    int w = img1.getWidth();
    int h = img1.getHeight();

    if (w != img2.getWidth() || h != img2.getHeight()) {
        return false;
    }

    res.createImage(w, h);

    int size = res.getSize();
    BYTE* p1 = img1.getPixels();
    BYTE* p2 = img2.getPixels();
    BYTE* p3 = res.getPixels();

    int diff;
    for (int i = 0; i < size; i++) {
        diff = p1[i] - p2[i];
        p3[i] = (BYTE)((diff >= 0) ? diff : -diff);
    }

    return true;
}

bool IppEnhance::imageAND(IppByteImage& img1, IppByteImage& img2, IppByteImage& res) {
    int w = img1.getWidth();
    int h = img1.getHeight();

    if (w != img2.getWidth() || h != img2.getHeight()) {
        return false;
    }

    res.createImage(w, h);

    int size = res.getSize();
    BYTE* p1 = img1.getPixels();
    BYTE* p2 = img2.getPixels();
    BYTE* p3 = res.getPixels();

    for (int i = 0; i < size; i++) {
        p3[i] = (BYTE)(p1[i] & p2[i]);
    }

    return true;
}

bool IppEnhance::imageOR(IppByteImage& img1, IppByteImage& img2, IppByteImage& res) {
    int w = img1.getWidth();
    int h = img1.getHeight();

    if (w != img2.getWidth() || h != img2.getHeight()) {
        return false;
    }

    res.createImage(w, h);

    int size = res.getSize();
    BYTE* p1 = img1.getPixels();
    BYTE* p2 = img2.getPixels();
    BYTE* p3 = res.getPixels();

    for (int i = 0; i < size; i++) {
        p3[i] = (BYTE)(p1[i] | p2[i]);
    }

    return true;
}

void IppEnhance::imageBitPlane(IppByteImage& img1, IppByteImage& res, int bit) {
    res.createImage(img1.getWidth(), img1.getHeight());

    int size = img1.getSize();
    BYTE* p1 = img1.getPixels();
    BYTE* p2 = res.getPixels();

    for (int i = 0; i < size; i++) {
        p2[i] = (p1[i] & (1 << bit)) ? 255 : 0;
    }
}
