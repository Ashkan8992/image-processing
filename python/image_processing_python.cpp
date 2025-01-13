#include "image_processing.h"
#include <memory>  // for std::unique_ptr
#include <nanobind/nanobind.h>
#include <vector>

namespace nb = nanobind;

// Helper Function to Convert List to std::unique_ptr<RGB[]>
/* std::unique_ptr<RGB[]> convert_to_unique_ptr_rgb(const std::vector<RGB>& pixels) {
    auto ptr = std::make_unique<std::vector<RGB>>(pixels.size());
    std::copy(pixels.begin(), pixels.end(), ptr.get());
    return ptr;
}

// Helper Function to Convert List to std::unique_ptr<Gray[]>
std::unique_ptr<Gray[]> convert_to_unique_ptr_gray(const std::vector<Gray>& pixels) {
    auto ptr = std::make_unique<Gray[]>(pixels.size());
    std::copy(pixels.begin(), pixels.end(), ptr.get());
    return ptr;
} */


// Define the main function for bindings
NB_MODULE(image_processing_python, m) {
    // Binding for RGB class
    nb::class_<RGB>(m, "RGB")
        .def(nb::init<uint8_t, uint8_t, uint8_t>());

    // Binding for Gray class
    nb::class_<Gray>(m, "Gray")
        .def(nb::init<uint8_t>());

    // Binding for Image<RGB> class
    /* nb::class_<Image<RGB>>(m, "ImageRGB")
        .def(nb::init<unsigned int, unsigned int, bool, std::unique_ptr<RGB[]>>())
        .def(nb::init<unsigned int, unsigned int, bool, const std::vector<RGB>&>())
        .def("print", &Image<RGB>::print);

    // Binding for Image<Gray> class
    nb::class_<Image<Gray>>(m, "ImageGray")
        .def(nb::init<unsigned int, unsigned int, bool, std::unique_ptr<Gray[]>>())
        .def(nb::init<unsigned int, unsigned int, bool, const std::vector<Gray>&>())
        .def("print", &Image<Gray>::print); */

    // Grayscale conversion function
    m.def("grayscaleConversion", &grayscaleConversion, "Convert an RGB image to grayscale");
    m.def("applyBlur", &applyBlur<RGB>, "Apply blur on RGB image");
    m.def("applyBlur", &applyBlur<Gray>, "Apply a box blur filter to grayscale image");
    m.def("applyEdgeDetection", &applyEdgeDetection, "Apply edge detection (Sobel) on grayscale image");
    m.def("applyHistogramEqualization", &applyHistogramEqualization, "Apply histogram equalization on grayscale image");
}

