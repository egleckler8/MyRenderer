cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)

# Project setup
project(learning_opengl)
set(GRAPHICS_LIBRARY GraphicsLib) # set the target name


# Add the graphics library we've written :)
add_subdirectory(${GRAPHICS_LIBRARY})
include_directories(${GRAPHICS_LIBRARY}/include)


# Define a variable for the source files
set(SOURCE_FILES main.cpp)


# Add source files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Make sure to link against our libraries
target_link_libraries(${PROJECT_NAME} ${GRAPHICS_LIBRARY})


# Copy the resources directories to the build directory
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
