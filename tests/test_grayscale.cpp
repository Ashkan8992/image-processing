#include "gtest/gtest.h"
#include "image_processing.h"
#include <vector>

// Test Grayscale Conversion
TEST(ImageProcessingTest, GrayscaleConversion) {
    Image<RGB> img(3, 1, true, nullptr);  // Create a 3x1 RGB image
    RGB red(255, 0, 0);       img.setPixel(0, 0, red);
    RGB green(0, 255, 0);     img.setPixel(1, 0, green);
    RGB blue(0, 0, 255);      img.setPixel(2, 0, blue);

    Image<Gray> res_img = grayscaleConversion(img);  // Convert to grayscale

    // Check if the pixels are converted to grayscale correctly
    EXPECT_EQ(res_img.getPixel(0, 0).val, 76);  // Red -> Gray value
    EXPECT_EQ(res_img.getPixel(1, 0).val, 150); // Green -> Gray value
    EXPECT_EQ(res_img.getPixel(2, 0).val, 29);  // Blue -> Gray value
    
    RGB datax[4][2] = {
        {RGB(255, 0,   0), RGB(0,   255, 0)},     // Red, Green
        {RGB(0,   0,   255), RGB(255, 255, 255)}, // Blue, White
        {RGB(255, 255, 0), RGB(0,   255, 255)},   // Yellow, Cyan
        {RGB(255, 0,   255), RGB(0,   0,   0)}    // Magenta, Black
    };
    
    RGB data[4 * 2]; // Flatten the 4x2 RGB image
    std::copy(&datax[0][0], &datax[0][0] + 4 * 2, data);
    
    std::unique_ptr<RGB[]> pixelData = std::make_unique<RGB[]>(4 * 2);
    std::memcpy(pixelData.get(), data, sizeof(data)); // Create smart pointer array

    
    Image<RGB> pic(4, 2, true, std::move(pixelData));  // Create a 4x2 RGB image

    Image<Gray> res_pic = grayscaleConversion(pic);  // Convert to grayscale
    
    // Check if the pixels are converted to grayscale correctly
    EXPECT_EQ(res_pic.getPixel(1, 1).val, 255);
    EXPECT_EQ(res_pic.getPixel(2, 0).val, 226);
    EXPECT_EQ(res_pic.getPixel(2, 1).val, 179);
    EXPECT_EQ(res_pic.getPixel(3, 0).val, 105);
    EXPECT_EQ(res_pic.getPixel(3, 1).val, 0);
}
