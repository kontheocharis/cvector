cmake_minimum_required(VERSION 2.8)
project(cvector C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

include_directories(${PROJECT_SOURCE_DIR}/src)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
