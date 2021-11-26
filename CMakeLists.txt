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
    "draw_2d.cpp"
    "draw_3d.cpp"
)

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
