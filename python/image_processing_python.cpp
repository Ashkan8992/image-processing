#include "image_processing.h"
#include <memory>  // for std::unique_ptr
#include <nanobind/nanobind.h>

namespace nb = nanobind;

// Expose the RGB structure, Image class and Image Processing functions to Python using nanobind
/* template <typename PixelType>
void bind_image(nb::module_ &m, const std::string &type_name) {
    nb::class_<Image<PixelType>>(m, ("Image" + std::string(type_name)).c_str())
        .def(nb::init<unsigned int, unsigned int, bool, std::unique_ptr<PixelType[]>>())  // Constructor
        .def("getWidth", &Image<PixelType>::getWidth)  // Get image width
        .def("getHeight", &Image<PixelType>::getHeight)  // Get image height
        .def("isRgbImage", &Image<PixelType>::isRgbImage)  // Check if the image is RGB
        .def("getChannels", &Image<PixelType>::getChannels)  // Get number of channels (RGB or grayscale)
        .def("setPixel", &Image<PixelType>::setPixel)  // Set pixel value
        .def("getPixel", &Image<PixelType>::getPixel)  // Get pixel value
        .def("getData", &Image<PixelType>::getData)  // Get pixel data (as shared pointer)
        .def("print", &Image<PixelType>::print);  // Print image (for debugging purposes)
} */

Image<uint8_t> applyHistogramEqualization(const Image<uint8_t>& img);

// Define the main function to expose the bindings
NB_MODULE(image_processing_python, m) {
    // Bind the RGB struct
    nb::class_<RGB>(m, "RGB")
        .def(nb::init<uint8_t, uint8_t, uint8_t>(), nb::arg("r") = 0, nb::arg("g") = 0, nb::arg("b") = 0)
        .def("__eq__", &RGB::operator==)
        .def("grayscale_convert", &RGB::grayscaleConvert);

    // Bind the Image class for RGB and grayscale uint8_t types
    /* bind_image<RGB>(m, "RGB");
    bind_image<uint8_t>(m, "Gray"); */
    
    // Bind the Image<RGB> class
    nb::class_<Image<RGB>>(m, "ImageRGB")
        .def(nb::init<unsigned int, unsigned int, bool, std::unique_ptr<RGB[]>&&>(),
             nb::arg("width"), nb::arg("height"), nb::arg("is_rgb") = true, nb::arg("data") = nullptr)
        .def("get_width", &Image<RGB>::getWidth)
        .def("get_height", &Image<RGB>::getHeight)
        .def("is_rgb", &Image<RGB>::isRgbImage)
        .def("get_channels", &Image<RGB>::getChannels)
        .def("set_pixel", &Image<RGB>::setPixel)
        .def("get_pixel", &Image<RGB>::getPixel)
        .def("get_data", &Image<RGB>::getData)
        .def("print", &Image<RGB>::print);

    // Bind the Image<uint8_t> class for grayscale images
    nb::class_<Image<uint8_t>>(m, "ImageGray")
        .def(nb::init<unsigned int, unsigned int, bool, std::unique_ptr<uint8_t[]>&&>(),
             nb::arg("width"), nb::arg("height"), nb::arg("is_rgb") = false, nb::arg("data") = nullptr)
        .def("get_width", &Image<uint8_t>::getWidth)
        .def("get_height", &Image<uint8_t>::getHeight)
        .def("is_rgb", &Image<uint8_t>::isRgbImage)
        .def("get_channels", &Image<uint8_t>::getChannels)
        .def("set_pixel", &Image<uint8_t>::setPixel)
        .def("get_pixel", &Image<uint8_t>::getPixel)
        .def("get_data", &Image<uint8_t>::getData)
        .def("print", &Image<uint8_t>::print);
    
    // Expose image processing functions
    m.def("grayscaleConversion", &grayscaleConversion, "Convert RGB image to grayscale");
    m.def("applyBlur", &applyBlur<RGB>, "Apply blur on RGB image", nb::arg("img"), nb::arg("kernelSize"));
    m.def("applyBlur", &applyBlur<uint8_t>, "Apply a box blur filter to grayscale image", nb::arg("img"), nb::arg("kernelSize"));
    m.def("applyEdgeDetection", &applyEdgeDetection, "Apply edge detection (Sobel) on grayscale image");
    // m.def("applyHistogramEqualization", &applyHistogramEqualization, "Apply histogram equalization on grayscale image");
}
