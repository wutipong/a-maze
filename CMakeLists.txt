cmake_minimum_required(VERSION 3.10)

set(
    CMAKE_TOOLCHAIN_FILE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING 
    "Vcpkg toolchain file"
)

# set the project name
project(main)

# add the executable
add_executable(
    ${PROJECT_NAME} 
	"main.cpp" 
 "2d.hpp" "draw_2d.cpp")

add_subdirectory(maze-gen)

find_package(raylib CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_INCLUDE_DIRS} maze-gen)
target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARIES} maze-gen fmt::fmt)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()


# file(GLOB_RECURSE GLSL_SOURCE_FILES
#     "shaders/*.frag"
#     "shaders/*.vert"
# )

# add_custom_target(SHADER_COMPILE 
#     SOURCES ${GLSL_SOURCE_FILES} 
#     COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/shaders/"
#     COMMAND ${CMAKE_COMMAND} -E copy ${GLSL_SOURCE_FILES} "${CMAKE_CURRENT_BINARY_DIR}/shaders/"
# )
# 
# add_dependencies(main SHADER_COMPILE)

