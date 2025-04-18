cmake_minimum_required(VERSION 3.15)

# Project name
project(CalibrationDLL LANGUAGES CXX)

# Define the output as a shared library (DLL)
add_library(calibration SHARED
    dllmain.cpp
    calibration.cpp
    calibration.h
)

# Include directories (e.g., if you have EposCmd64.h or other headers)
target_include_directories(calibration PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Link libraries if needed (e.g., Maxon EPOS library)
target_link_libraries(calibration
    PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/EposCmd64.lib
)

# Define export macro
target_compile_definitions(calibration PRIVATE CALIBRATIONDLL_EXPORTS)

# Set C++ standard
set_target_properties(calibration PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

# Define output directories
set_target_properties(calibration PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
