add_library(game_scene)

target_sources(game_scene PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/GameScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameSceneController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameScene_Clear.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameScene_Over.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameScene_Play.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameScene_Title.cpp
)

target_link_libraries(game_scene
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(game_scene PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_scene PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_scene PRIVATE RELEASE_MODE)
endif()