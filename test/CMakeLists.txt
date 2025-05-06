add_executable(main main.cpp)

# ライブラリのリンク
target_link_libraries(main
    ${glew_LIBRARY}
    ${glfw_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${freetype_LIBRARY}
    ${assimp_LIBRARY}
    ${zlibstatic_LIBRARY}   
    ${zlib_LIBRARY}
    game_core
)

# インクルードディレクトリ
target_include_directories(main PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${cmake_extern_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(main PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(main PRIVATE RELEASE_MODE)
endif()