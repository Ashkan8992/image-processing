#include "gtest/gtest.h"
#include "image_processing.h"
#include <vector>

// Test Edge Detection (Sobel Operator)
TEST(ImageProcessingTest, ApplyEdgeDetection) {
    Image<Gray> img(3, 3, false, nullptr);  // Create a 3x3 grayscale image
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
