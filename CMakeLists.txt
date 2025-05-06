cmake_minimum_required(VERSION 3.1)
project(openGL_training CXX)
message("project name is automatically set as : ${PROJECT_NAME}")

set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENTIONS OFF)

# 外部ライブラリの探索
find_package(OpenGL REQUIRED)

find_library(glfw_LIBRARY NAMES libglfw3 PATHS ${PROJECT_SOURCE_DIR}/extern/GLFW/lib)
message(${glfw_LIBRARY})

find_library(glew_LIBRARY NAMES libglew PATHS ${PROJECT_SOURCE_DIR}/extern/GLEW/lib)
message(${glew_LIBRARY})

find_library(zlib_LIBRARY NAMES libzs PATHS ${PROJECT_SOURCE_DIR}/extern/zlib/lib)
message(${zlib_LIBRARY})

find_library(assimp_LIBRARY NAMES libassimp PATHS ${PROJECT_SOURCE_DIR}/extern/Assimp/lib)
message(${assimp_LIBRARY})

find_library(freetype_LIBRARY NAMES libfreetype PATHS ${PROJECT_SOURCE_DIR}/extern/freetype/lib)
message(${freetype_LIBRARY})

find_library(zlibstatic_LIBRARY NAMES libzlibstatic PATHS ${PROJECT_SOURCE_DIR}/extern/Assimp/lib)
message(${zlibstatic_LIBRARY})

set(cmake_extern_INCLUDE
    ${PROJECT_SOURCE_DIR}/extern/GLFW/include
    ${PROJECT_SOURCE_DIR}/extern/GLEW/include
    ${PROJECT_SOURCE_DIR}/extern/glad/include
    ${PROJECT_SOURCE_DIR}/extern/glm
    ${PROJECT_SOURCE_DIR}/extern/freetype/include
    ${PROJECT_SOURCE_DIR}/extern/Assimp/include
    ${PROJECT_SOURCE_DIR}/extern/stb/include
    ${PROJECT_SOURCE_DIR}/extern/nlohmann/include
)
message("cmake_extern_INCLUDE: ${cmake_extern_INCLUDE}")

message(${OPENGL_LIBRARIES})
message(${PROJECT_SOURCE_DIR})

add_definitions(-DGLEW_STATIC)

add_subdirectory(src)
add_subdirectory(test)