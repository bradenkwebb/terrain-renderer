cmake_minimum_required(VERSION 3.10)

# Set the project name
project(terrain-renderer)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
file(GLOB SOURCES "src/*.cpp" "src/*.c")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/lib/libglfw3dll.a
)

if(WIN32)
    # Copy DLL to output directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/extern/glfw3.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
