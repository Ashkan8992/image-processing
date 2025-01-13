import image_processing_python as ipp
import numpy as np
#import sys
#sys.path.append('path_to_your_build_directory')  # Add the build directory to the Python path

# Create a dummy RGB image (e.g., 2x2 image)
image_data = np.array([[[255, 0, 0], [0, 255, 0]],
                       [[0, 0, 255], [255, 255, 0]]], dtype=np.uint8)

# Call the grayscale conversion function
grayscale_image = image_processing_python.grayscaleConversion(image_data)

print(grayscale_image)

# ----------------------------------

# Generate random pixel data (256x256 image, RGB format)
# Random RGB values in range [0, 255] -- Ensure values are uint8 -- Ensure its 1-dim
pixels_data = np.random.randint(0, 256, size=(256, 256, 3), dtype=np.uint8).flatten()

# Create an image object (10x10, RGB)
img = ipp.Image(10, 10, True, pixels_data)

# Call the methods
res_img = ipp.grayscaleConversion(img)
# Get the raw pixel data after conversion
result_data = res_img.getData()
# Print the results
print(result_data)

ipp.applyBlur(img, 3)
ipp.applyEdgeDetection(img)
ipp.applyHistogramEqualization(img)

# ----------------------------------

# Create a grayscale image
image = ipp.ImageGray(10, 10, False, None)

# Set and get pixel values
image.setPixel(0, 0, 100)
pixel = image.getPixel(0, 0)
print(pixel)
