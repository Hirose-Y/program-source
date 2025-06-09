add_library(game_camera)

target_sources(game_camera PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
)


target_link_libraries(game_camera
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(game_camera PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_camera PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_camera PRIVATE RELEASE_MODE)
endif()