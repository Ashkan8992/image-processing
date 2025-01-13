#include "gtest/gtest.h"
#include "image_processing.h"
#include <vector>

// Test Histogram Equalization
TEST(ImageProcessingTest, ApplyHistogramEqualization) {
    Image<Gray> img(5, 3, false, nullptr);  // Create a 5x5 grayscale image
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
