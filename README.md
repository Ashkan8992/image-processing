# Image Processing Library

Project description: This project provides a collection of image processing algorithms, including basic functions such as **grayscale conversion**, **blurring (using box blur)**, **edge detection (using Sobel operator)**, and **histogram equalization**. The core library is written in C++ and offers Python bindings via **Nanobind** for easy integration into Python applications.

## Features

- **Custom Pixel Class**: base Pixel class and derived Gray and RGB classes.
- **Custom Image Class**: manages pixel data, and handling both grayscale and RGB images efficiently with smart pointers.
- **Grayscale Conversion**: Convert RGB images to grayscale.
- **Blurring**: Apply a simple box blur using a configurable kernel size.
- **Edge Detection**: Implement edge detection using the Sobel operator.
- **Histogram Equalization**: Enhance image contrast by equalizing the histogram.

## Requirements

### For MacOS (using Homebrew):
- **C++ Compiler** (e.g., GCC or Clang)
- **CMake** (for building the project)
    brew install cmake
- **Python 3.8+**
- **Nanobind** (for Python bindings)
    brew install nanobind
- **GoogleTest** (for unit testing)
    brew install googletest

## Building

Build instructions (how to set up the environment and compile the project).
Examples of how to use the library from both C++ and Python.

### Clone the repository

```bash
git clone https://github.com/ashkan8992/image-processing.git
cd image-processing-library
mkdir build
cd build
cmake ..
make
```

### Tunning Tests (Unit Tests)
This project uses GoogleTest to ensure the correctness of the image processing functions.

```bash
mkdir build
cd build
cmake ..
make ImageProcessingTests
ctest
```
