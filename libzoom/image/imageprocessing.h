/****
    libzoom - Library for processing images
    Copyright (C) 2015  Simon Everts

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include "image.h"

#include "lut.h"

typedef Lut Histogram;

class ImageProcessing
{
public:
    ImageProcessing();

    static void createHistogram (const Image& image, Histogram& histogram);    
    static void normalizeHistogram (Histogram& histogram, const int max_value);

    static void generateLut (float brightness, float contrast, float gamma, float wbRed, float wbGreen, float wbBlue, Lut& lut);
    static void applyLut (const Image* src, Image* dest, const Lut& lut);

    static Image fastScale (const Image& image, QSize minimumSize);
    static void scale (const Image* src, Image* dest, QSize size);

    static void applyGamma_16u (const Image* src, Image* dest);

    static void applyCameraMatrix_16u (const Image* src, Image* dest);

    static Image autoCrop_8u (const Image* src);
    static Image cropHeaderFooter_8u (const Image* src, int amount);
    static Image cropHeader_8u (const Image* src, int amount);
    static Image cropFooter_8u (const Image* src, int amount);

    static void fastDebayer_16u (const Image& src, Image& dest);

    static void NLdenoise_8u (const Image& src, Image& dest, int h, int hColor, int templateWindow, int searchWindow);

    static void medianFilter_8u (const Image& src, Image& dest, int kernelSize);
    static void medianFilter_16u (const Image& src, Image& dest, int kernelSize);

    static void applyProperties (const Image* src, Image* dest, float brightness, float contrast, float gamma, float wbRed, float wbGreen, float wbBlue);

private:
    static void createHistogram_8u (const Image& image, Histogram& histogram);
    static void createHistogram_16u (const Image& image, Histogram& histogram);

    static void applyLut_8u (const Image* src, Image* dest, const Lut& lut);
    static void applyLut_16u8u (const Image* src, Image* dest, const Lut& lut);

    static Image fastScale_8u (const Image& image, int scale);
    static Image fastScale_16u (const Image& image, int scale);

    static void scale_8u (const Image* src, Image* dest, QSize size);

    static void applyProperties_8u (const Image* src, Image* dest, float brightness, float contrast, float gamma, float wbRed, float wbGreen, float wbBlue);
    static void applyProperties_16u8u (const Image* src, Image* dest, float brightness, float contrast, float gamma, float wbRed, float wbGreen, float wbBlue);

    static void convertRGBtoXYZ (float r, float g, float b, float& x, float& y, float& z);
    static void convertXYZtoRGB (float x, float y, float z, float& r, float& g, float& b);

    static void convertLABtoXYZ (float l, float a, float b, float& x, float& y, float& z);
    static void convertXYZtoLAB (float x, float y, float z, float& l, float& a, float& b);
};

#endif // IMAGEPROCESSING_H
