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
