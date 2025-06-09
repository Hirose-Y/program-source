add_library(game_graphics)

target_sources(game_graphics PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextRenderer.cpp
)

target_link_libraries(game_graphics
    glad 
    ${GLFW_LIBRARY}
    ${FREETYPE_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${Z_LIBRARY}
)

target_include_directories(game_graphics PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_graphics PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_graphics PRIVATE RELEASE_MODE)
endif()