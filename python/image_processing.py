import image_processing_python as ipp
import numpy as np

# Generate random uint8 RGB values for a 1024x1024 image: 3 values per pixel (R, G, B)
pixels_data = np.random.randint(0, 256, size=(1024 * 1024 * 3), dtype=np.uint8)
# Create a list of RGB pixel objects from the numpy array
large_pixels_rgb = [
    ipp.RGB(pixels_data[i], pixels_data[i+1], pixels_data[i+2])
    for i in range(0, len(pixels_data), 3)
]

# Generate a 10x10 grid of RGB pixels with random uint8 values
rand_pixels_gray = [ipp.Gray(random.randint(0, 255)) for _ in range(10 * 10)]
# Generate a 10x10 grid of Gray pixels with random uint8 values
rand_pixels_rgb = [ipp.RGB(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)) for _ in range(10 * 10)]

pixels_gray = [
    ipp.Gray(10), ipp.Gray(20), ipp.Gray(30),
    ipp.Gray(40), ipp.Gray(50), ipp.Gray(60),
    ipp.Gray(70), ipp.Gray(80), ipp.Gray(90)
]

# Create an RGB image (3x3 for example) with some sample colors
pixels_rgb = [
    ipp.RGB(255, 0, 0), ipp.RGB(0, 255, 0), ipp.RGB(0, 0, 255),
    ipp.RGB(255, 255, 0), ipp.RGB(0, 255, 255), ipp.RGB(255, 0, 255),
    ipp.RGB(192, 192, 192), ipp.RGB(128, 128, 128), ipp.RGB(64, 64, 64)
]

# Create ImageRGB instance (3x3 image with RGB pixels)
image_rgb = ipp.ImageRGB(3, 3, True, pixels_rgb)
print("Original RGB Image:")
image_rgb.print()

# Convert the image to grayscale
image_gray = ipp.grayscaleConversion(image_rgb)
print("\nConverted Grayscale Image:")
image_gray.print()

# Apply Blur on the RGB image
image_blur_rgb = ipp.applyBlur(image_rgb)
print("\RGB Blurred Image:")
image_blur_rgb.print()

# Apply Blur on the grayscale image
image_blur_gray = ipp.applyBlur(image_gray)
print("\grayscale Blurred Image:")
image_blur_gray.print()

# Apply edge detection on grayscale image
image_edge_detect = ipp.applyEdgeDetection(image_gray)
print("\Edge Detected Image:")
image_edge_detect.print()

# Apply histogram equalization on grayscale image
image_hist = ipp.histogramEqualization(image_gray)
print("\Edge Equalized Image:")
image_hist.print()
