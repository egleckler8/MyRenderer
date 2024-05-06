cmake_minimum_required(VERSION 3.27)
project(learning_opengl)

set(CMAKE_CXX_STANDARD 17)



# Define a variable for the source files
set(SOURCE_FILES main.cpp
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
        DirectionalLight.cpp
        DirectionalLight.h
        SpotLight.cpp
        SpotLight.h
        Mesh.cpp
        Mesh.h
        Model.cpp
        Model.h
)

# Add source files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})




# Here is where all the libraries are
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/thirdparty)


# GLFW
set(GLFW_DIR ${LIB_DIR}/glfw-3.4)

set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
include_directories(${GLFW_DIR}/include)


# Assimp
set(ASSIMP_DIR ${LIB_DIR}/assimp/)
add_subdirectory(${ASSIMP_DIR})
target_link_libraries(${PROJECT_NAME} assimp)
include_directories(${ASSIMP_DIR}/include)


# glad
set(GLAD_DIR ${LIB_DIR}/glad)
add_library("glad" ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PRIVATE ${GLAD_DIR}/include/)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")


# glm
set(GLM_DIR ${LIB_DIR}/glm)
include_directories(${GLM_DIR})


# stb_image
set(STB_DIR ${LIB_DIR}/stb_image)
include_directories(${STB_DIR}/)


# OpenGL
find_package(OpenGL REQUIRED) # populates CMake with the data on OpenGL!
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})





# Copy the resources directories to the build directory
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
