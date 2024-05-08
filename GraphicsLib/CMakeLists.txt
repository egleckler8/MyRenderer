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
        src/RenderObject.cpp
        src/RenderObject.h
        src/Scene.cpp
        src/Scene.h
        src/RenderObjectFactory.cpp
        src/RenderObjectFactory.h
        src/LightSourceFactory.cpp
        src/LightSourceFactory.h
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
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)


# Assimp (built as cmake lib)
set(ASSIMP_DIR ${LIB_DIR}/assimp)
add_subdirectory(${ASSIMP_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC assimp) # idk how to not make public
# does the thing where the includes are not found in the header file "Model.h"
# but they are found in the cpp, and theres an enum in one of the function
# declarations, so I can't exactly forward declare everything...
target_include_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_DIR}/include)


# GLAD (built as cmake lib)
set(GLAD_DIR ${LIB_DIR}/glad)
add_subdirectory(${GLAD_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)


# stb_image (header-only)
set(STB_DIR ${LIB_DIR}/stb_image)
target_include_directories(${PROJECT_NAME} PUBLIC ${STB_DIR})


# OpenGL (package on machine)
find_package(OpenGL REQUIRED) # populates CMake with the data on OpenGL!
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})




