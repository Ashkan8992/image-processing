#ifndef image_h
#define image_h

#include <cstdint>  // for uint8_t
#include <iostream> // for std::cout in print()
#include <memory>   // for unique_ptr

// Base class Pixel (non-abstract)
class Pixel {
public:
    // virtual ~Pixel() = default;  // Virtual destructor
};

// Derived class Gray from Pixel
class Gray : public Pixel {
public:
    uint8_t val; // brightness

    Gray(uint8_t val = 0) : val(val) {}
    
    // Equality comparison operator
    bool operator==(const Gray& other) const {
        return val == other.val;
    }
    
    // Addition operator for Apply blur -- Error: uint8_t overflow
    Gray operator+(const Gray& other) const {
        return Gray(val + other.val);
    }

    // Print method specific to Gray
    void print() const {
        std::cout << (int)val << " ";
    }
};

// Derived class RGB from Pixel
// Could use std::tuple instead -- may have grayscale
class RGB : public Pixel {
public:
    uint8_t r, g, b;

    RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b) {}

    // Equality comparison operator
    bool operator==(const RGB& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
    
    // Addition operator
    RGB operator+(const RGB& other) const {
        return RGB(r + other.r, g + other.g, b + other.b);
    }
    
    // Overload the stream insertion operator for RGB
    void print() const {
        std::cout << "(" << (int)r << ", " << (int)g << ", " << (int)b << ") ";
    }
    
    // Convert to grayscale using the weighted sum method
    Gray grayscaleConvert() const {
        return Gray(static_cast<uint8_t>(std::round(0.299 * r + 0.587 * g + 0.114 * b))); // NTSC formula
    }
};

// Image class
template<typename PixelType>
class Image {
public:
    // Constructor to create an image
    explicit Image(unsigned int width, unsigned int height, bool isRGB = true, std::unique_ptr<PixelType[]> data = nullptr); // implicit conversion
    explicit Image(unsigned int width, unsigned int height, bool isRGB = true, const std::vector<PixelType>& data = {});
    
    // Deconstructor (no need since using smart ptr)
    // ~Image() = default;
    
    // Getter methods
    // no Setters: ensures immutability
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    bool isRgbImage() const;
    uint8_t getChannels() const;
    
    // Get & Set Pixel methods (const: ensure data's not modified)
    void setPixel(unsigned int x, unsigned int y, const PixelType& pxl); // Set pixel by coordinates (x, y)
    const PixelType& getPixel(unsigned int x, unsigned int y) const;     // Get pixel by coordinates (x, y)
    
    // Get pixel data (shared for CUDA or direct manipulation)
    std::shared_ptr<PixelType[]> getData() const;
    
    // Print method
    void print();

private:
    // Maximum number of pixel dimensions ~10,000
    unsigned int width_;
    unsigned int height_;
    bool isRgb_;
    uint8_t channels_;  // GrayScale: 1, RGB: 3
    // Stores pixel data in a 1-dim vector: memory locality
    // GrayScale: uint8_t values, RGB: RGB structs with 3 uint8_t values
    std::unique_ptr<PixelType[]> pixels_; // Smart pointer for pixel data
};

#endif /* image_h */
