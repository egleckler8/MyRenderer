cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(JsonLib)

set(SOURCE_FILES
        src/json_utils.cpp
        src/json_utils.h
)

set(HEADER_FILES
        include/JsonLib/api.h
)

# Add library target
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Make the includes files public; add them to include path
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)