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



#
# Dependencies
#

# Here is where all the libraries are
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)


# GLFW (built as cmake lib)
set(GLFW_DIR ${LIB_DIR}/glfw-3.4)
# Some build flags...
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_DIR})
# Link to all the targets that need it:
target_link_libraries(${GRAPHICS_LIBRARY} glfw ${GLFW_LIBRARIES}) # lib to graphics lib
target_include_directories(${GRAPHICS_LIBRARY} PRIVATE ${GLFW_DIR}/include) # includes to graphics lib
# And the input lib


# GLM (header-only)
set(GLM_DIR ${LIB_DIR}/glm)
# Publish include directories:
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_DIR}) # includes to main project
target_include_directories(${GRAPHICS_LIBRARY} PUBLIC ${GLM_DIR}) # includes to graphics lib





# Make sure to link against our own libraries...
target_link_libraries(${PROJECT_NAME} PRIVATE ${GRAPHICS_LIBRARY})


# Copy the resources directories to the build directory
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
