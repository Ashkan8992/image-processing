#include "gtest/gtest.h"
#include "image_processing.h"
#include <vector>

// Test Box Blur
TEST(ImageProcessingTest, ApplyBlur) {
    Image<Gray> img(3, 3, false, nullptr);  // Create a 3x3 grayscale image
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
