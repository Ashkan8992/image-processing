#include "image.h"
#include <iostream>  // for print method / debugging
#include <cstring>   // for std::memcpy
#include <stdexcept> // for std::out_of_range exception

// Explicit template instantiations
template class Image<RGB>;
template class Image<Gray>;

//------------------------------------
// Explicit instantiations for all the methods used in the code:

// Constructors
template Image<RGB>::Image(unsigned int, unsigned int, bool, std::unique_ptr<RGB[]>);
template Image<Gray>::Image(unsigned int, unsigned int, bool, std::unique_ptr<Gray[]>);

// Getter methods
template unsigned int Image<RGB>::getWidth() const;
template unsigned int Image<Gray>::getWidth() const;

template unsigned int Image<RGB>::getHeight() const;
template unsigned int Image<Gray>::getHeight() const;

template bool Image<RGB>::isRgbImage() const;
template bool Image<Gray>::isRgbImage() const;

template uint8_t Image<RGB>::getChannels() const;
template uint8_t Image<Gray>::getChannels() const;

// Set and Get Pixel methods
template void Image<RGB>::setPixel(unsigned int, unsigned int, const RGB&);
template void Image<Gray>::setPixel(unsigned int, unsigned int, const Gray&);

template const RGB& Image<RGB>::getPixel(unsigned int, unsigned int) const;
template const Gray& Image<Gray>::getPixel(unsigned int, unsigned int) const;

// Get pixel data
template std::shared_ptr<RGB[]> Image<RGB>::getData() const;
template std::shared_ptr<Gray[]> Image<Gray>::getData() const;

// Print
template void Image<RGB>::print();
template void Image<Gray>::print();

//------------------------------------

// Constructor
// For efficiency use RGB struct for RGB pixel, and uint8_t for grayscale
template <typename PixelType>
Image<PixelType>::Image(unsigned int width, unsigned int height, bool isRgb, std::unique_ptr<PixelType[]> data) : width_(width), height_(height), isRgb_(isRgb), channels_(isRgb ? 3 : 1) {
    // Allocate memory for pixel data (1D array)
    pixels_ = std::make_unique<PixelType[]>(width * height);
        
    if (data) {
        /* if (sizeof(PixelType) * width_ * height_ != sizeof(data)) { // Wrong: data is ptr and sizeof(data) is 8
            throw std::invalid_argument("Input data size does not match required image size.");
        } */
        std::memcpy(pixels_.get(), data.get(), width_ * height_ * sizeof(PixelType)); // Efficient, fast memory copy
    }
}

template <typename PixelType>
Image<PixelType>::Image(unsigned int width, unsigned int height, bool isRgb, const std::vector<PixelType>& data) : width_(width), height_(height), isRgb_(isRgb), channels_(isRgb ? 3 : 1) {
    // Allocate memory for pixel data (1D array)
    pixels_ = std::make_unique<PixelType[]>(width * height);
        
    if (data) {
        /* if (sizeof(PixelType) * width_ * height_ != sizeof(data)) { // Wrong: data is ptr and sizeof(data) is 8
            throw std::invalid_argument("Input data size does not match required image size.");
        } */
        // Allocate memory for pixel data (1D array)
        pixels_ = std::move(data);  // Move the data into pixels_ (no need for std::memcpy)
    }
}

// Get image width
template <typename PixelType>
unsigned int Image<PixelType>::getWidth() const {
    return width_;
}

// Get image height
template <typename PixelType>
unsigned int Image<PixelType>::getHeight() const {
    return height_;
}

// Get image rgb
template <typename PixelType>
bool Image<PixelType>::isRgbImage() const {
    return isRgb_;
}

// Get number of channels
template <typename PixelType>
uint8_t Image<PixelType>::getChannels() const {
    return channels_;
}

// Set pixel value by coordinates (x, y)
template <typename PixelType>
void Image<PixelType>::setPixel(unsigned int x, unsigned int y, const PixelType& pxl) {
    if (x >= width_ || y >= height_) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }
    pixels_[x * height_ + y] = pxl;
}

// Get pixel value by coordinates (x, y)
template <typename PixelType>
const PixelType& Image<PixelType>::getPixel(unsigned int x, unsigned int y) const {
    if (x >= width_ || y >= height_) {
        throw std::out_of_range("Pixel coordinates out of range");
    }
    
    return pixels_[x * height_ + y];
}

// Get pixel data (shared for CUDA or direct manipulation)
template <typename PixelType>
std::shared_ptr<PixelType[]> Image<PixelType>::getData() const {
    return std::shared_ptr<PixelType[]>(pixels_.get(), [](PixelType* ptr) {});
}

// Print the image
template <typename PixelType>
void Image<PixelType>::print() {
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            PixelType pixel = this->getPixel(x, y);
            pixel.print();
        }
        std::cout << "\n";
    }
}
