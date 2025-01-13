#include "image_processing.h"
#include <algorithm> // for std::min and std::max
#include <cmath>     // for std::sqrt
#include <vector>

// Grayscale Conversion: Convert RGB to grayscale
Image<Gray> grayscaleConversion(const Image<RGB>& img) {
    /* if (!img.isRgbImage()) {
        throw std::logic_error("Image is already in grayscale format.");
    } */
    
    // Create a result image with the same dimensions and type as input image
    Image<Gray> gray_img(img.getWidth(), img.getHeight(), false);
    
    // Iterate through the pixels and convert RGB to grayscale
    // #pragma omp parallel for collapse(2) // For parallel computing
    for (unsigned int y = 0; y < img.getHeight(); ++y) {
        for (unsigned int x = 0; x < img.getWidth(); ++x) {
            Gray gray(img.getPixel(x, y).grayscaleConvert());
            gray_img.setPixel(x, y, gray);
        }
    }
    
    return gray_img;
}

// Blur: Apply a simple box blur (average of surrounding pixels)
// TODO: Kernel size cannot be very large: int overflow
template <> // rgb
Image<RGB> applyBlur(const Image<RGB>& img, int kernelSize) {
    // Round up even kernelSize to the next odd integer -- radius won't change
    int kernelRadius = kernelSize / 2;
    
    // Create a result image with the same dimensions and type as input image
    Image<RGB> blur_img(img.getWidth(), img.getHeight(), img.isRgbImage());
    
    // Iterate through each pixel
    for (unsigned int y = 0; y < img.getHeight(); ++y) {
        for (unsigned int x = 0; x < img.getWidth(); ++x) {
            // blur_img.setPixel(x, y, img.getPixel(x, y).blur());
            int count = 0;
            int sumR = 0, sumG = 0, sumB = 0;
            
            // Apply kernel within the bounds of the image
            for (int ky = -kernelRadius; ky <= kernelRadius; ++ky) {
                int ky_pos = y + ky;
                if (ky_pos < 0 || ky_pos >= img.getHeight()) { continue; }
                
                for (int kx = -kernelRadius; kx <= kernelRadius; ++kx) {
                    int kx_pos = x + kx;
                    if (kx_pos < 0 || kx_pos >= img.getWidth()) { continue; }
                    
                    // For RGB image: sum the RGB components
                    RGB pixel = img.getPixel(kx_pos, ky_pos);
                    sumR += pixel.r;
                    sumG += pixel.g;
                    sumB += pixel.b;
                    
                    count++; // Increment the count of pixels in bound
                }
            }
            
            // Set blurred pixel value
            // Calculate average for RGB components and convert the result to uint8_t
            uint8_t avgR = static_cast<uint8_t>(std::round(sumR / count));
            uint8_t avgG = static_cast<uint8_t>(std::round(sumG / count));
            uint8_t avgB = static_cast<uint8_t>(std::round(sumB / count));
            RGB avgPixel(avgR, avgG, avgB);
            blur_img.setPixel(x, y, avgPixel);
        }
    }
    
    return blur_img;
}

// Blur: Apply a simple box blur (average of surrounding pixels)
template <> // grayscale
Image<Gray> applyBlur(const Image<Gray>& img, int kernelSize) {
    // Round up even kernelSize to the next odd integer -- radius won't change
    int kernelRadius = kernelSize / 2;
    
    // Create a result image with the same dimensions and type as input image
    Image<Gray> blur_img(img.getWidth(), img.getHeight(), img.isRgbImage());
    
    // Iterate through each pixel
    for (unsigned int y = 0; y < img.getHeight(); ++y) {
        for (unsigned int x = 0; x < img.getWidth(); ++x) {
            int sum = 0, count = 0;
            
            // Apply kernel within the bounds of the image
            for (int ky = -kernelRadius; ky <= kernelRadius; ++ky) {
                int ky_pos = y + ky;
                if (ky_pos < 0 || ky_pos >= img.getHeight()) { continue; }
                
                for (int kx = -kernelRadius; kx <= kernelRadius; ++kx) {
                    int kx_pos = x + kx;
                    if (kx_pos < 0 || kx_pos >= img.getWidth()) { continue; }
                    
                    // For grayscale image: sum the grayscale value
                    sum += img.getPixel(kx_pos, ky_pos).val;
                    
                    count++; // Increment the count of pixels in bound
                }
            }
            
            // Set blurred pixel value
            // For grayscale, average the sum and convert it to uint8_t
            Gray avgGray(static_cast<uint8_t>(std::round(sum / count)));
            blur_img.setPixel(x, y, avgGray);
        }
    }
    
    return blur_img;
}

// Edge Detection: Implement edge detection using a Sobel operator.
// Image<Gray>: Only process grayscale images
Image<Gray> applyEdgeDetection(const Image<Gray>& img) {
    /* if (img.isRgbImage()) {
        throw std::logic_error("Edge detection is only supported for grayscale images.");
    } */
    
    int width_ = img.getWidth(); int height_ = img.getHeight();
    
    // Create a result image with the same dimensions and type as input image
    Image<Gray> res_img(img.getWidth(), img.getHeight(), false);
    
    // Sobel kernels for detecting edges in x and y directions
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    
    // Iterate over all pixels (except for the borders)
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {

            // Apply Sobel kernels
            int sumX = 0, sumY = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    // Zero-Padding
                    if (x + kx < 0 || x + kx >= width_ || y + ky < 0 || y + ky >= height_) { continue; }
                    uint8_t pixel_val = img.getPixel(x + kx, y + ky).val;
                    sumX += pixel_val * Gx[kx + 1][ky + 1];
                    sumY += pixel_val * Gy[kx + 1][ky + 1];
                }
            }

            // Calculate magnitude of gradient and assign to pixel
            int edge = static_cast<int>(std::round(std::sqrt(sumX * sumX + sumY * sumY)));
            
            // Clamp the result between 0 and 255
            Gray val(static_cast<uint8_t>(std::min(edge, 255)));
            
            // Set the resulting pixel value
            res_img.setPixel(x, y, val);
        }
    }
    
    return res_img;
}

// Histogram Equalization: Equalize the histogram to improve image contrast.
// Image<Gray>: Only process grayscale images
Image<Gray> applyHistogramEqualization(const Image<Gray>& img) {
    /* if (img.isRgbImage()) {
        throw std::logic_error("Histogram equalization is only supported for grayscale images.");
    } */
    
    // Create a result image with the same dimensions and type as input image
    Image<Gray> res_img(img.getWidth(), img.getHeight(), false);
    
    // Compute histogram (frequency of pixel intensities)
    std::vector<int> hist(256, 0); // 256 bins for pixel values (0-255)
    for (int y = 0; y < img.getHeight(); ++y) {
        for (int x = 0; x < img.getWidth(); ++x) {
            ++hist[img.getPixel(x, y).val];
        }
    }
    
    // Compute the cumulative distribution function (CDF)
    std::vector<int> cdf(256, 0);
    cdf[0] = hist[0];
    for (int i = 1; i < 256; ++i) {
        cdf[i] = cdf[i-1] + hist[i];
    }
    
    // Normalize the CDF to map pixel values to full range [0-255]
    int totalPixels = img.getWidth() * img.getHeight();
    std::vector<int> cdf_normalized(256, 0);
    for (int i = 0; i < 256; ++i) {
        cdf_normalized[i] = std::round((cdf[i] - cdf[0]) / float(totalPixels - cdf[0]) * 255);
    }
    
    // Set updated pixel value
    for (int y = 0; y < img.getHeight(); ++y) {
        for (int x = 0; x < img.getWidth(); ++x) {
            Gray pixel(static_cast<uint8_t>(cdf_normalized[img.getPixel(x, y).val]));
            res_img.setPixel(x, y, pixel);
        }
    }
    
    return res_img;
}
