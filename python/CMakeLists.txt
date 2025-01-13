# Ensure that CMake can find Python3
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
#message(STATUS "Python Include directory: ${Python_INCLUDE_DIRS}")

find_package(nanobind CONFIG REQUIRED)
message(STATUS "Nanobind directory: ${nanobind_DIR}")

# Define the source files for the Python bindings
set(PYTHON_SOURCES
        image_processing_python.cpp   # Includes Python bindings
)

# Create the Python extension module
add_library(ImageProcessingPython MODULE ${PYTHON_SOURCES})

# Link the Python extension with the core library and nanobind
target_link_libraries(ImageProcessingPython PRIVATE
        ImageProcessingLib  # Link to the core C++ library
        #nanobind-static     # Link to Nanobind
        nanobind::nanobind  # Link to Nanobind
)

# Include directories for Python bindings
set(nanobind_headers "/opt/homebrew/nanobind/include/")
target_include_directories(ImageProcessingPython PRIVATE
        ${CMAKE_SOURCE_DIR}/src         # Include core library headers
        ${Python_INCLUDE_DIRS}          # Include Python headers
        ${nanobind_headers}             # Include nanobind headers
)

# Set the output directory for the built Python extension
set_target_properties(ImageProcessingPython PROPERTIES
        PREFIX "" # Do not include 'lib' prefix (standard for Python modules)
        SUFFIX ".so" # For Linux/MacOS (use .pyd for Windows)
)