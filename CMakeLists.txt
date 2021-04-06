cmake_minimum_required(VERSION 3.0.0)

project(SoftwareArchitectureBestPractices VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

# set binaries output path 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Include source code and headers.
add_subdirectory(source)

# run and test on Win
# from build folder:
# cmake .. | cmake --build . --config 'Release'| ctest -C Release

