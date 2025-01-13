# Find GoogleTest package (if not installed globally)
find_package(GTest REQUIRED)

# Add the test source files
set(TEST_SOURCES
		test_grayscale.cpp
		test_blur.cpp
		test_edge_detection.cpp
		test_histogram.cpp
)

# Create the test executables
add_executable(ImageProcessingTests ${TEST_SOURCES})

# Link ImageProcessingLib (library) and GoogleTest to ImageProcessingTests (test executable)
target_link_libraries(ImageProcessingTests
		ImageProcessingLib
		GTest::GTest
		GTest::Main
)

# Enable testing with CTest (CMake's testing framework)
enable_testing()

# Add the tests using CTest
add_test(NAME ImageProcessingLibTests COMMAND ImageProcessingTests --gtest_output=console)