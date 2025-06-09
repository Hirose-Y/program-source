add_library(game_behavior)

target_sources(game_behavior PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Behavior.cpp
)


target_link_libraries(game_behavior
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(game_behavior PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_behavior PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_behavior PRIVATE RELEASE_MODE)
endif()