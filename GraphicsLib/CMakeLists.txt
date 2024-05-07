cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(GraphicsLib)

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
)

set(HEADER_FILES
        include/GraphicsLib/api.h
)

# Add library target
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Make the includes files public; add them to include path
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



#
# Link all the dependencies:
#

# Here is where all the libraries are
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)


# GLFW (built as cmake lib)
set(GLFW_DIR ${LIB_DIR}/glfw-3.4)

set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)


# Assimp (built as cmake lib)
set(ASSIMP_DIR ${LIB_DIR}/assimp)
add_subdirectory(${ASSIMP_DIR})
target_link_libraries(${PROJECT_NAME} assimp)
# include_directories(${ASSIMP_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_DIR}/include)


# GLAD (built as cmake lib)
set(GLAD_DIR ${LIB_DIR}/glad)
add_subdirectory(${GLAD_DIR})
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)



# GLM (header-only)
set(GLM_DIR ${LIB_DIR}/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_DIR})


# stb_image (header-only)
set(STB_DIR ${LIB_DIR}/stb_image)
target_include_directories(${PROJECT_NAME} PUBLIC ${STB_DIR})


# OpenGL (package on machine)
find_package(OpenGL REQUIRED) # populates CMake with the data on OpenGL!
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})




