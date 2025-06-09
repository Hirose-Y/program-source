add_library(game_object)

target_sources(game_object PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Object_Cube.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Object_Floor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Object_Pyramid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Object_Player.cpp
)

target_link_libraries(game_object
    glad 
    ${GLFW_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${Z_LIBRARY}
)

target_include_directories(game_object PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_object PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_object PRIVATE RELEASE_MODE)
endif()