#pragma once

#include <Windows.h>

#include "RGBByte.h"

template<typename T>
class IppImage {
public:
    IppImage();
    IppImage(int w, int h);
    IppImage(const IppImage<T>& img);
    virtual ~IppImage();

    void createImage(int w, int h);
    void destroyImage();
    
    T* getPixels() const {
        if (pixels) {
            return pixels[0];
        }
        else {
            return nullptr;
        }
    }
    T** getPixels2D() const { return pixels; }

    IppImage<T>& operator=(const IppImage<T>& img);
    template<typename U>
    void convert(const IppImage<U>& img, bool use_limit);

    int getWidth() const { return nWidth; }
    int getHeight() const { return nHeight; }
    int getSize() const { return nWidth * nHeight; }
    bool isValid() const { return (pixels != nullptr); }

protected:
    int nWidth;
    int nHeight;
    T** pixels;
};

typedef IppImage<BYTE> IppByteImage;
typedef IppImage<int> IppIntImage;
typedef IppImage<float> IppFloatImage;
typedef IppImage<double> IppDoubleImage;
typedef IppImage<RGBBYTE> IppRgbImage;

template<typename T>
inline T limit(const T& value) {
    return ((value > 255) ? 255 : ((value < 0) ? 0 : value));
}

////
template<typename T>
IppImage<T>::IppImage() 
    :nWidth(0), nHeight(0), pixels(nullptr)
{
}

template<typename T>
IppImage<T>::IppImage(int w, int h) 
    : nWidth(w), nHeight(h), pixels(nullptr)
{
    pixels = new T*[sizeof(T*) * nHeight];
    pixels[0] = new T[sizeof(T) * nWidth * nHeight];

    for (int i = 1; i < nHeight; i++) {
        pixels[i] = pixels[i - 1] + nWidth;
    }

    memset(pixels[0], 0, sizeof(T) * nWidth * nHeight);
}

template<typename T>
IppImage<T>::IppImage(const IppImage<T>& img)
    :nWidth(img.nWidth), nHeight(img.nHeight), pixels(nullptr)
{
    if (img.isValid()) {
        pixels = new T*[sizeof(T*) * nHeight];
        pixels[0] = new T[sizeof(T) * nWidth * nHeight];

        for (int i = 1; i < nHeight; i++) {
            pixels[i] = pixels[i - 1] + nWidth;
        }

        memset(pixels[0], img.pixels[0], sizeof(T) * nWidth * nHeight);
    }
}

template<typename T>
IppImage<T>::~IppImage() {
    if (pixels != nullptr) {
        delete[] pixels[0];
        delete[] pixels;
        pixels = nullptr;
    }
}

////
template<typename T>
void IppImage<T>::createImage(int w, int h) {
    destroyImage();

    nWidth = w;
    nHeight = h;

    pixels = new T*[sizeof(T*) * nHeight];
    pixels[0] = new T[sizeof(T) * nWidth * nHeight];

    for (int i = 1; i < nHeight; i++) {
        pixels[i] = pixels[i - 1] + nWidth;
    }

    memset(pixels[0], 0, sizeof(T) * nWidth * nHeight);
}

template<typename T>
void IppImage<T>::destroyImage() {
    if (pixels != nullptr) {
        delete[] pixels[0];
        delete[] pixels;
        pixels = nullptr;
    }

    nWidth = nHeight = 0;
}

////
template<typename T>
IppImage<T>& IppImage<T>::operator=(const IppImage<T>& img) {
    if (this == &img) {
        return *this;
    }

    createImage(img.nWidth, img.nHeight);
    memcpy(pixels[0], img.pixels[0], sizeof(T) * nWidth * nHeight);

    return *this;
}

template<typename T> template<typename U> 
void IppImage<T>::convert(const IppImage<U>& img, bool use_limit) {
    createImage(img.getWidth(), img.getHeight());

    int size = getSize();
    T* p1 = getPixels();
    U* p2 = img.getPixels();

    if (use_limit) {
        if (int i = 0; i < size; i++) {
            p1[i] = static_cast<T>(limit(p2[i]));
        }
    }
    else {
        if (int i = 0; i < size; i++) {
            p1[i] = static_cast<T>(p2[i]);
        }
    }
}
