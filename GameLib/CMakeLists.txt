cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(GameLib)

set(SOURCE_FILES
        src/GameObject.cpp
        src/GameObject.h
        src/LightSrcObject.cpp
        src/LightSrcObject.h
        src/GameObjectVisitor.cpp
        src/GameObjectVisitor.h
        src/PlayerObject.cpp
        src/PlayerObject.h
        src/CameraManager.cpp
        src/CameraManager.h
        src/SceneBuilderVisitor.cpp
        src/SceneBuilderVisitor.h
        src/Game.cpp
        src/Game.h
)

set(HEADER_FILES
        include/GameLib/api.h
)

# Add library target
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Make the includes files public; add them to include path
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)