cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)

# Project setup
project(learning_opengl)


# Add the graphics library we've written :)
set(GRAPHICS_LIBRARY GraphicsLib) # set the target name
add_subdirectory(${GRAPHICS_LIBRARY})

# And the "Game" library
set(GAME_LIBRARY GameLib)
add_subdirectory(${GAME_LIBRARY})

# The Json config utils library
set(JSON_LIBRARY JsonLib)
add_subdirectory(${JSON_LIBRARY})



# Define a variable for the source files
set(SOURCE_FILES
        main.cpp
)

set(HEADER_FILES

)

# Add source files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})




# ****************************************************************
#                       Dependencies
# ****************************************************************

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
# to graphics lib
target_link_libraries(${GRAPHICS_LIBRARY} PRIVATE glfw ${GLFW_LIBRARIES})
target_include_directories(${GRAPHICS_LIBRARY} PRIVATE ${GLFW_DIR}/include)
# to root
target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${GLFW_LIBRARIES}) # lib to graphics lib
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include) # includes to graphics lib


# GLM (header-only)
set(GLM_DIR ${LIB_DIR}/glm)
# Publish include directories:
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_DIR}) # to root project
target_include_directories(${GRAPHICS_LIBRARY} PUBLIC ${GLM_DIR}) # to graphics lib
target_include_directories(${GAME_LIBRARY} PUBLIC ${GLM_DIR}) # to game lib
target_include_directories(${JSON_LIBRARY} PUBLIC ${GLM_DIR}) # to json lib



# nlohmann json
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json) # to root
target_link_libraries(${GRAPHICS_LIBRARY} PRIVATE nlohmann_json::nlohmann_json) # to graphics lib
target_link_libraries(${GAME_LIBRARY} PRIVATE nlohmann_json::nlohmann_json) # to game lib
target_link_libraries(${JSON_LIBRARY} PRIVATE nlohmann_json::nlohmann_json) # to config lib, obviously

# wow... that is scary easy... WHY!??! (existential pain)

# ****************************************************************



# Make sure to link against our own libraries...

# GraphicsLib:
# link to root
target_include_directories(${PROJECT_NAME} PRIVATE ${GRAPHICS_LIBRARY}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GRAPHICS_LIBRARY})
# link to game
target_include_directories(${GAME_LIBRARY} PRIVATE ${GRAPHICS_LIBRARY}/include)
target_link_libraries(${GAME_LIBRARY} PRIVATE ${GRAPHICS_LIBRARY})


# GameLib:
# link to root
target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_LIBRARY}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GAME_LIBRARY})


# JsonLib:
# link to game
target_include_directories(${GAME_LIBRARY} PRIVATE ${JSON_LIBRARY}/include)
target_link_libraries(${GAME_LIBRARY} PRIVATE ${JSON_LIBRARY})
# link to graphics
target_include_directories(${GRAPHICS_LIBRARY} PRIVATE ${JSON_LIBRARY}/include)
target_link_libraries(${GAME_LIBRARY} PRIVATE ${JSON_LIBRARY})







# Copy the resources directories to the build directory
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
