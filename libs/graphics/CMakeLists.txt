project(graphics_lib)

# Add include directories for the src code
include_directories(include)

set(SOURCE_FILES
        src/Shader.cpp
        src/Shader.h
        src/Camera.cpp
        src/Camera.cpp
        src/Camera.h
        src/Texture2D.cpp
        src/Texture2D.h
        src/LightSource.cpp
        src/LightSource.h
        src/PointLight.cpp
        src/PointLight.h
        src/DirectionalLight.cpp
        src/DirectionalLight.h
        src/SpotLight.cpp
        src/SpotLight.h
        src/Mesh.cpp
        src/Mesh.h
        src/Model.cpp
        src/Model.h
        src/WindowManager.cpp
        src/WindowManager.h
        src/RenderData.cpp
        src/RenderData.h
        src/Scene.cpp
        src/Scene.h
        include/graphics.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
# Export include files
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


#
# Link all the dependencies:
#

# Here is where all the libraries are
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)


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



