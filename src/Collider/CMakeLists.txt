add_library(game_collider)

target_sources(game_collider PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Collider_AABB.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Collider_OBB.cpp
)

target_link_libraries(game_collider
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(game_collider PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_collider PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_collider PRIVATE RELEASE_MODE)
endif()