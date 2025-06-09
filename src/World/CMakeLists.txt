add_library(game_world)

target_sources(game_world PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/World.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldRotator.cpp
)

target_link_libraries(game_world
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(game_world PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_world PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_world PRIVATE RELEASE_MODE)
endif()