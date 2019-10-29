#include "stdafx.h"
#include "IppFilter.h"

#include <math.h>

IppFilter::IppFilter()
{
}


IppFilter::~IppFilter()
{
}

void IppFilter::filterMean(IppByteImage& img, IppByteImage& res) {
    int w = img.getWidth();
    int h = img.getHeight();

    res = img;

    BYTE** pp1 = img.getPixels2D();
    BYTE** pp2 = res.getPixels2D();

    int mask[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    int sum;
    for (int j = 1; j < h - 1; j++) {
        for (int i = 1; i < w - 1; i++) {
            sum = 0;
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    sum += (pp1[j - 1 + m][i - 1 + n] * mask[m][n]);
                }
            }

            pp2[j][i] = (BYTE)limit((float)sum / 9 + 0.5f);
        }
    }
}

void IppFilter::filterWeightedMean(IppByteImage& img, IppByteImage& res) {
    int w = img.getWidth();
    int h = img.getHeight();

    res = img;

    BYTE** pp1 = img.getPixels2D();
    BYTE** pp2 = res.getPixels2D();

    int mask[3][3] = {
        { 1, 2, 1 },
        { 2, 4, 2 },
        { 1, 2, 1 }
    };

    int sum;
    for (int j = 1; j < h - 1; j++) {
        for (int i = 1; i < w - 1; i++) {
            sum = 0;
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    sum += (pp1[j - 1 + m][i - 1 + n] * mask[m][n]);
                }
            }

            pp2[j][i] = (BYTE)limit((float)sum / 16 + 0.5f);
        }
    }
}

void IppFilter::filterGaussian(IppByteImage& img, IppFloatImage& res, float sigma) {
    int w = img.getWidth();
    int h = img.getHeight();

    res.createImage(w, h);

    BYTE** pp1 = img.getPixels2D();
    float** pp2 = res.getPixels2D();

    int dim = (int)(2 * 4 * sigma + 1);
    if (dim < 3) {
        dim = 3;
    }

    if (dim % 2 == 0) {
        dim++;
    }

    int dim2 = dim / 2;

    IppFloatImage mask(dim, 1);
    float* p1 = mask.getPixels();

    int x;
    for (int i = 0; i < dim; i++) {
        x = i - dim2;
        p1[i] = (float)exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * 3.14159265358979323846f) * sigma);
    }

    IppFloatImage buff(w, h);
    float** pp3 = buff.getPixels2D();

    float sum1, sum2;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            sum1 = sum2 = 0.0f;
            for (int k = 0; k < dim; k++) {
                x = k - dim2 + j;

                if (x >= 0 && x < h) {
                    sum1 += p1[k];
                    sum2 += (p1[k] * pp1[x][i]);
                }
            }

            pp3[j][i] = sum2 / sum1;
        }
    }

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            sum1 = sum2 = 0.0f;
            for (int k = 0; k < dim; k++) {
                x = k - dim2 + i;

                if (x >= 0 && x < w) {
                    sum1 += p1[k];
                    sum2 += (p1[k] * pp3[j][x]);
                }
            }

            pp2[j][i] = sum2 / sum1;
        }
    }
}

void IppFilter::filterLaplacian(IppByteImage& img, IppByteImage& res) {
    int w = img.getWidth();
    int h = img.getHeight();

    res.createImage(w, h);

    BYTE** pp1 = img.getPixels2D();
    BYTE** pp2 = res.getPixels2D();

    int sum;
    for (int j = 1; j < h - 1; j++) {
        for (int i = 1; i < w - 1; i++) {
            sum = pp1[j - 1][i] + pp1[j][i - 1] + pp1[j + 1][i] + pp1[j][i + 1] - 4 * pp1[j][i];
            pp2[j][i] = (BYTE)limit(sum + 128);
        }
    }
}

void IppFilter::filterUnsharpMask(IppByteImage& img, IppByteImage& res) {
    int w = img.getWidth();
    int h = img.getHeight();

    res = img;

    BYTE** pp1 = img.getPixels2D();
    BYTE** pp2 = res.getPixels2D();

    int sum;
    for (int j = 1; j < h - 1; j++) {
        for (int i = 1; i < w - 1; i++) {
            sum = 5 * pp1[j][i] - pp1[j - 1][i] - pp1[j][i - 1] - pp1[j + 1][i] - pp1[j][i + 1];
            pp2[j][i] = (BYTE)limit(sum);
        }
    }
}

void IppFilter::filterHighBoost(IppByteImage& img, IppByteImage& res, float alpha) {
    int w = img.getWidth();
    int h = img.getHeight();

    res = img;

    BYTE** pp1 = img.getPixels2D();
    BYTE** pp2 = res.getPixels2D();

    int sum;
    for (int j = 1; j < h - 1; j++) {
        for (int i = 1; i < w - 1; i++) {
            sum = (4 + alpha) * pp1[j][i] - pp1[j - 1][i] - pp1[j][i - 1] - pp1[j + 1][i] - pp1[j][i + 1];
            pp2[j][i] = (BYTE)limit(sum + 0.5f);
        }
    }
}
