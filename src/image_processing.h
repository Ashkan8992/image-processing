#ifndef image_processing_h
#define image_processing_h

#include "image.h"

// All methods: Round to the nearest integer for Image Processing
    
// Grayscale Conversion: Convert RGB image to grayscale
// by averaging or using a weighted sum of the RGB channels.
Image<Gray> grayscaleConversion(const Image<RGB>& img);

// Blur: Apply a simple "box" blur
template <typename PixelType>
Image<PixelType> applyBlur(const Image<PixelType>& img, int kernelSize);

// Edge Detection: Implement edge detection using a Sobel operator.
Image<Gray> applyEdgeDetection(const Image<Gray>& img);

// Histogram Equalization: Enhance image contrast by adjusting the image histogram
Image<Gray> applyHistogramEqualization(const Image<Gray>& img);

#endif /* image_processing_h */
