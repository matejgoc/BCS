##############################################
# CMake setup
cmake_minimum_required(VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR})


##############################################
# Create project
project(biochem_sim LANGUAGES CXX)

##############################################
# Declare dependencies

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)

##############################################
# Find source files
file(GLOB_RECURSE SOURCE_FILES src/*.[hc]pp)

##############################################
# Create target and set properties
add_executable( biochem_sim ${SOURCE_FILES})

# Set compilation features
target_compile_features(biochem_sim PRIVATE cxx_std_11) # Specify C++11 for any compiler (ex. g++ -std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -pthread")

# Set target properties
target_include_directories(biochem_sim
        PRIVATE
        ${SFML_INCLUDE_DIR}
        )

# Link libraries to target
target_link_libraries(biochem_sim
        PRIVATE
        ${SFML_LIBRARIES}
        ${SFML_DEPENDENCIES}
        )
