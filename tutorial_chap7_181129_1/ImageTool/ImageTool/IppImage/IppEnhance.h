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

    static bool imageAddition(IppByteImage& img1, IppByteImage& img2, IppByteImage& res);
    static bool imageSubtraction(IppByteImage& img1, IppByteImage& img2, IppByteImage& res);
    static bool imageAverage(IppByteImage& img1, IppByteImage& img2, IppByteImage& res);
    static bool imageDifference(IppByteImage& img1, IppByteImage& img2, IppByteImage& res);

    static bool imageAND(IppByteImage& img1, IppByteImage& img2, IppByteImage& res);
    static bool imageOR(IppByteImage& img1, IppByteImage& img2, IppByteImage& res);
    static void imageBitPlane(IppByteImage& img1, IppByteImage& res, int bit);
};
