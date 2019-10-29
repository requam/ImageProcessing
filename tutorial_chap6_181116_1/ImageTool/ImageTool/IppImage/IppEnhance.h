#pragma once

#include "IppImage.h"

class IppEnhance {
public:
    IppEnhance() {}
    virtual ~IppEnhance() {}

    static void imageInverse(IppByteImage& img);
    static void imageBrightness(IppByteImage& img, int offset);
    static void imageContrast(IppByteImage& img, float offset);
    static void imageGammarCorrection(IppByteImage& img, float gammar);
    static void imageHistogram(IppByteImage& img, float hist[256]);
    static void imageHistogramStretch(IppByteImage& img);
    static void imageHistogramEqualizatioon(IppByteImage& img);
};
