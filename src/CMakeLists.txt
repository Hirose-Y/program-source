add_library(game_core)

add_subdirectory(Input)
add_subdirectory(InputActions)
add_subdirectory(Object)
add_subdirectory(Scene)
add_subdirectory(Camera)
add_subdirectory(Collider)
add_subdirectory(Stage)
add_subdirectory(Behavior)
add_subdirectory(World)

target_sources(game_core PRIVATE
    Game.cpp
    Window.cpp
    Shader.cpp
    Image.cpp
    TextRenderer.cpp
)

target_link_libraries(game_core
    ${glew_LIBRARY}
    ${glfw_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${freetype_LIBRARY}
    ${assimp_LIBRARY}
    ${zlibstatic_LIBRARY}   
    ${zlib_LIBRARY}
    InputActions
)

target_include_directories(game_core PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${cmake_extern_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_core PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_core PRIVATE RELEASE_MODE)
endif()