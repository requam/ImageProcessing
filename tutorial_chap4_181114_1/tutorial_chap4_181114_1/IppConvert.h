#pragma once

#include "IppDib.h"
#include "IppImage.h"

class IppConvert {
public:
    IppConvert() {}
    virtual ~IppConvert() {}

    void convertDibToImage(IppDib& dib, IppByteImage& img);
    void convertDibToImage(IppDib& dib, IppRgbImage& img);

    void convertImageToDib(IppByteImage& img, IppDib& dib);
    void convertImageToDib(IppFloatImage& img, IppDib& dib);
    void convertImageToDib(IppRgbImage& img, IppDib& dib);
};
