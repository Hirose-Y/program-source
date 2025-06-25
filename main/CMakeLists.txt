# 実行ファイルを作成
add_executable(MyGame main.cpp)

# リンクするライブラリを指定
target_link_libraries(MyGame PRIVATE 
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
    game_core
    game_scene
    game_stage
    game_world
    game_object
    game_camera
    game_collider
    InputSystem
    InputActions
    game_math
    game_behavior
    game_graphics
    game_util
)

# インクルードディレクトリ
target_include_directories(MyGame PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(MyGame PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(MyGame PRIVATE RELEASE_MODE)
endif()

# オプション：Windowsでのマクロ定義（GLAD使用時に推奨）
if (WIN32)
    target_compile_definitions(MyGame PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

set (RUN_TIME_LIBS
    ${EXTERNAL_LIBS_DIR}/openal-soft/buildlib/OpenAL32.dll
)
message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
file(COPY ${RUN_TIME_LIBS} DESTINATION ${CMAKE_BINARY_DIR}/main)