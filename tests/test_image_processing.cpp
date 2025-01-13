#include "gtest/gtest.h"
#include "image_processing.h"
#include <vector>

// Test Grayscale Conversion
TEST(ImageProcessingTest, GrayscaleConversion) {
    Image<RGB> img(3, 1, true);  // Create a 3x1 RGB image
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

// Test Box Blur
TEST(ImageProcessingTest, ApplyBlur) {
    Image<Gray> img(3, 3, false);  // Create a 3x3 grayscale image
    img.setPixel(0, 0, Gray(50));  img.setPixel(0, 1, Gray(100)); img.setPixel(0, 2, Gray(150));
    img.setPixel(1, 0, Gray(200)); img.setPixel(1, 1, Gray(250)); img.setPixel(1, 2, Gray(255));
    img.setPixel(2, 0, Gray(255)); img.setPixel(2, 1, Gray(255)); img.setPixel(2, 2, Gray(255));

    Image<Gray> res_img = applyBlur(img, 3);  // Apply blur with a 3x3 kernel

    // Check the blurred pixels (values are approximations)
    EXPECT_EQ(res_img.getPixel(0, 0).val, 150); // Top-Left pixel after blur
    EXPECT_EQ(res_img.getPixel(1, 1).val, 196); // Central pixel after blur
    
    Gray datax[3][3] = {
        Gray(10), Gray(20), Gray(30),
        Gray(40), Gray(50), Gray(60),
        Gray(70), Gray(80), Gray(90)
    };
    Gray data[3 * 3]; // Flatten the 3x3 Gray image
    std::copy(&datax[0][0], &datax[0][0] + 3 * 3, data);
    
    std::unique_ptr<Gray[]> pixelData = std::make_unique<Gray[]>(3 * 3);
    std::memcpy(pixelData.get(), data, sizeof(data)); // Create smart pointer array
    
    Image<Gray> pic(3, 3, false, std::move(pixelData));  // Create a 3x3 grayscale image

    Image<Gray> res_pic = applyBlur(pic, 3);  // Apply blur with a 3x3 kernel

    // Check the blurred pixels (values are approximations)
    EXPECT_EQ(res_pic.getPixel(0, 0).val, 30);
    EXPECT_EQ(res_pic.getPixel(0, 1).val, 35);
    EXPECT_EQ(res_pic.getPixel(0, 2).val, 40);
    EXPECT_EQ(res_pic.getPixel(1, 0).val, 45);
    EXPECT_EQ(res_pic.getPixel(1, 1).val, 50);
    EXPECT_EQ(res_pic.getPixel(1, 2).val, 55);
    EXPECT_EQ(res_pic.getPixel(2, 0).val, 60);
    EXPECT_EQ(res_pic.getPixel(2, 1).val, 65);
    EXPECT_EQ(res_pic.getPixel(2, 2).val, 70);
}

// Test Edge Detection (Sobel Operator)
TEST(ImageProcessingTest, ApplyEdgeDetection) {
    Image<Gray> img(3, 3, false);  // Create a 3x3 grayscale image
    img.setPixel(0, 0, Gray(10));  img.setPixel(1, 0, Gray(0)); img.setPixel(2, 0, Gray(100));
    img.setPixel(0, 1, Gray(0));   img.setPixel(1, 1, Gray(40)); img.setPixel(2, 1, Gray(0));
    img.setPixel(0, 2, Gray(100)); img.setPixel(1, 2, Gray(0)); img.setPixel(2, 2, Gray(10));

    Image<Gray> res_img = applyEdgeDetection(img);  // Apply edge detection (Sobel)

    // Check edge detection (values are approximations)
    EXPECT_EQ(res_img.getPixel(0, 0).val, 57);   // Conrner pixel
    EXPECT_EQ(res_img.getPixel(0, 1).val, 197); // Edge Pixel
    EXPECT_EQ(res_img.getPixel(1, 1).val, 0);   // Center pixel
    
    Gray datax[3][3] = {
        Gray(0),  Gray(0),    Gray(0),
        Gray(0),  Gray(255),  Gray(0),
        Gray(0),  Gray(0),    Gray(0)
    };
    Gray data[3 * 3]; // Flatten the 3x3 Gray image
    std::copy(&datax[0][0], &datax[0][0] + 3 * 3, data);
    
    std::unique_ptr<Gray[]> pixelData = std::make_unique<Gray[]>(3 * 3);
    std::memcpy(pixelData.get(), data, sizeof(data));
        
    Image<Gray> pic(3, 3, false, std::move(pixelData));  // Create a 3x3 grayscale image

    Image<Gray> res_pic = applyEdgeDetection(pic);  // Apply edge detection (Sobel)

    // Check edge detection (values are approximations)
    EXPECT_EQ(res_pic.getPixel(0, 0).val, 255); // Corner pixel
    EXPECT_EQ(res_pic.getPixel(0, 1).val, 255); // Edge pixel
    EXPECT_EQ(res_pic.getPixel(1, 1).val, 0);   // Center pixel
}

// Test Histogram Equalization
TEST(ImageProcessingTest, ApplyHistogramEqualization) {
    Image<Gray> img(5, 3, false);  // Create a 5x5 grayscale image
    img.setPixel(0, 0, Gray(0));   img.setPixel(0, 1, Gray(50));  img.setPixel(0, 2, Gray(100));
    img.setPixel(1, 0, Gray(50));  img.setPixel(1, 1, Gray(100)); img.setPixel(1, 2, Gray(150));
    img.setPixel(2, 0, Gray(100)); img.setPixel(2, 1, Gray(150)); img.setPixel(2, 2, Gray(200));
    img.setPixel(3, 0, Gray(150)); img.setPixel(3, 1, Gray(200)); img.setPixel(3, 2, Gray(250));
    img.setPixel(4, 0, Gray(200)); img.setPixel(4, 1, Gray(250)); img.setPixel(4, 2, Gray(255));
    
    Image<Gray> res_img = applyHistogramEqualization(img);  // Apply histogram equalization

    // Check some of the pixels after equal
    EXPECT_EQ(res_img.getPixel(0, 0).val, 0);   // Low value should stay low
    EXPECT_EQ(res_img.getPixel(0, 1).val, 36);
    EXPECT_EQ(res_img.getPixel(0, 2).val, 91);
    EXPECT_EQ(res_img.getPixel(1, 2).val, 146);
    EXPECT_EQ(res_img.getPixel(2, 2).val, 200);
    EXPECT_EQ(res_img.getPixel(3, 2).val, 237);
    EXPECT_EQ(res_img.getPixel(4, 2).val, 255); // High value should stay high
    
    Gray datax[3][3] = {
        Gray(0),    Gray(64),    Gray(128),
        Gray(192),  Gray(255),   Gray(0),
        Gray(128),  Gray(64),    Gray(0)
    };
    Gray data[3 * 3]; // Flatten the 3x3 Gray image
    std::copy(&datax[0][0], &datax[0][0] + 3 * 3, data);
    
    std::unique_ptr<Gray[]> pixelData = std::make_unique<Gray[]>(3 * 3);
    std::memcpy(pixelData.get(), data, sizeof(data));
    
    Image<Gray> pic(3, 3, false, std::move(pixelData));  // Create a 3x3 grayscale image
    
    Image<Gray> res_pic = applyHistogramEqualization(pic);  // Apply histogram equalization

    // Check some of the pixels after equal
    EXPECT_EQ(res_pic.getPixel(0, 0).val, 0);
    EXPECT_EQ(res_pic.getPixel(0, 1).val, 85);
    EXPECT_EQ(res_pic.getPixel(0, 2).val, 170);
    EXPECT_EQ(res_pic.getPixel(1, 0).val, 213);
    EXPECT_EQ(res_pic.getPixel(1, 1).val, 255);
}
