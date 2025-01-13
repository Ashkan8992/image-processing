# Ensure CMake version is compatible with required features
cmake_minimum_required(VERSION 3.18)

# Set the project name
project(ImageProcessingLib LANGUAGES CXX) # Add "CUDA" later

# Set the C++ standard to C++17 or to c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source files
set(SOURCES
		src/image.cpp
		src/image_processing.cpp
)

# Image Processing Library (C++)
add_library(ImageProcessingLib STATIC ${SOURCES})

# Include directories (headers) for the target Library
target_include_directories(ImageProcessingLib PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Enable Unit Testing for CTest
enable_testing()

# Add subdirectories for source code, tests, Python bindings, and CUDA
# add_subdirectory(src)      # Core Library
add_subdirectory(tests)    # Google tests
# add_subdirectory(python)   # Python bindings
# add_subdirectory(cuda)     # CUDA parallel computing

# ----------------------------

# Set CUDA (for GPU-accelerated operations)
# find_package(CUDA REQUIRED)
# set(CUDA_ARCH_BIN "75")
# cuda_add_library(cuda_processing STATIC src/cuda_processing.cu)
# target_link_libraries(ImageProcessingLib PRIVATE CUDA::cudart)
