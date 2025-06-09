# CMakeLists.txt（MyGame プロジェクト用）
cmake_minimum_required(VERSION 3.10)
project(MyGame)
message("project name is automatically set as : ${PROJECT_NAME}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 外部ライブラリのパスを明示的に指定
set(EXTERNAL_LIBS_DIR "C:/dev/ExternalLibs")

# gladはソースファイルを直接追加してライブラリ化
include_directories(${EXTERNAL_LIBS_DIR}/glad/include) # glad.cをビルドするためのインクルード
add_library(glad STATIC ${EXTERNAL_LIBS_DIR}/glad/src/glad.c)

# 各外部ライブラリの探索
find_package(OpenGL REQUIRED)

find_library(GLFW_LIBRARY NAMES glfw3 PATHS ${EXTERNAL_LIBS_DIR}/glfw/lib NO_DEFAULT_PATH)
message(${GLFW_LIBRARY})

find_library(Z_LIBRARY NAMES zs PATHS ${EXTERNAL_LIBS_DIR}/zlib/lib NO_DEFAULT_PATH)
message(${Z_LIBRARY})

find_library(ASSIMP_LIBRARY NAMES assimp PATHS ${EXTERNAL_LIBS_DIR}/assimp/build/lib NO_DEFAULT_PATH)
message(${ASSIMP_LIBRARY})

find_library(FREETYPE_LIBRARY NAMES freetype PATHS ${EXTERNAL_LIBS_DIR}/freetype/install/lib NO_DEFAULT_PATH)
message(${FREETYPE_LIBRARY})

# 外部ライブラリのインクルードパスまとめ
set(EXTERNAL_INCLUDE
    ${EXTERNAL_LIBS_DIR}/glad/include
    ${EXTERNAL_LIBS_DIR}/glfw/include
    ${EXTERNAL_LIBS_DIR}/glm
    ${EXTERNAL_LIBS_DIR}/freetype/install/include/freetype2
    ${EXTERNAL_LIBS_DIR}/json/include
    ${EXTERNAL_LIBS_DIR}/stb/include
    ${EXTERNAL_LIBS_DIR}/assimp/include
    ${EXTERNAL_LIBS_DIR}/assimp/build/include
    ${EXTERNAL_LIBS_DIR}/zlib/include
)
message("EXTERNAL_INCLUDE: ${EXTERNAL_INCLUDE}")

message(${OPENGL_LIBRARIES})
message(${PROJECT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(main)