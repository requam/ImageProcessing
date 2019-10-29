#pragma once

#include "IppImage.h"

class IppFilter
{
public:
    IppFilter();
    virtual ~IppFilter();

    static void filterMean(IppByteImage& img, IppByteImage& res);
    static void filterWeightedMean(IppByteImage& img, IppByteImage& res);
    static void filterGaussian(IppByteImage& img, IppFloatImage& res, float sigma);

    static void filterLaplacian(IppByteImage& img, IppByteImage& res);
    static void filterUnsharpMask(IppByteImage& img, IppByteImage& res);
    static void filterHighBoost(IppByteImage& img, IppByteImage& res, float alpha);
};
