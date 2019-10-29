#pragma once

#include "IppDib.h"
#include "IppImage.h"

class IppConvert {
public:
    IppConvert() {}
    virtual ~IppConvert() {}

    static void convertDibToImage(IppDib& dib, IppByteImage& img);
    static void convertDibToImage(IppDib& dib, IppRgbImage& img);

    static void convertImageToDib(IppByteImage& img, IppDib& dib);
    static void convertImageToDib(IppFloatImage& img, IppDib& dib);
    static void convertImageToDib(IppRgbImage& img, IppDib& dib);
};

#define CONVERT_DIB_TO_IMAGE(dib, img) IppByteImage img;IppConvert::convertDibToImage(dib, img);
#define CONVERT_IMAGE_TO_DIB(img, dib) IppDib dib;IppConvert::convertImageToDib(img, dib);
