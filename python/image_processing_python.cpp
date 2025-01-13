#include "image_processing.h"
#include <memory>  // for std::unique_ptr
#include <nanobind/nanobind.h>

namespace nb = nanobind;

// Define the main function for bindings
NB_MODULE(image_processing_python, m) {
    // Binding for RGB class
    nb::class_<RGB>(m, "RGB")
        .def(nb::init<uint8_t, uint8_t, uint8_t>());

    // Binding for Gray class
    nb::class_<Gray>(m, "Gray")
        .def(nb::init<uint8_t>());

    // Binding for Image<RGB> class
    nb::class_<Image<RGB>>(m, "ImageRGB")
        .def(nb::init<unsigned int, unsigned int, bool, std::unique_ptr<RGB[]>>())
        .def("print", &Image<RGB>::print);

    // Binding for Image<Gray> class
    nb::class_<Image<Gray>>(m, "ImageGray")
        .def(nb::init<unsigned int, unsigned int, bool, std::unique_ptr<Gray[]>>())
        .def("print", &Image<Gray>::print);

    // Grayscale conversion function
    m.def("grayscaleConversion", &grayscaleConversion, "Convert an RGB image to grayscale");
    m.def("applyBlur", &applyBlur<RGB>, "Apply blur on RGB image");
    m.def("applyBlur", &applyBlur<Gray>, "Apply a box blur filter to grayscale image");
    m.def("applyEdgeDetection", &applyEdgeDetection, "Apply edge detection (Sobel) on grayscale image");
    m.def("applyHistogramEqualization", &applyHistogramEqualization, "Apply histogram equalization on grayscale image");
}

