cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)


project(learning_opengl)

# ????
# WTF....
# got it from:
# https://stackoverflow.com/questions/63628159/how-to-correctly-setup-cmake-for-glfw-on-clion-on-macos
# some guy... jesus christ... what does this mean?? I only picked
# to try this response because I was seeing "Cocoa" in my errors
# and ChatGPT was suggesting things to do with macOS and stuff...
# crazy...
if (APPLE)
    set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit")
    # -framework OpenGL -framework CoreVideo
    add_compile_definitions(GL_SILENCE_DEPRECATION)
endif ()


# Define a variable for the source files
set(SOURCE_FILES main.cpp
        glad.c
        MyFunctions.h
        MyFunctions.cpp
        Shader.cpp
        Shader.h
        Camera.cpp
        Camera.h
        Texture2D.cpp
        Texture2D.h
        LightSource.cpp
        LightSource.h
        lighting_structs.h
        PointLight.cpp
        PointLight.h
)

# Add source files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Set up paths
set(INCLUDE_DIR /Users/eli/ThirdParty/Include/) # all headers
set(GLFW_LIB /Users/eli/ThirdParty/Libs/libglfw3.a) # glfw lib

# Include GLFW headers
include_directories(${INCLUDE_DIR})

# Find OpenGL
find_package(OpenGL REQUIRED) # populates CMake with the data on OpenGL!
include_directories(${OPENGL_INCLUDE_DIR})


# Copy the resources directories to the build directory
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)




# Link GLFW and OpenGL libraries
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLFW_LIB})
