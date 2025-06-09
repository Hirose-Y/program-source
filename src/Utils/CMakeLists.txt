add_library(game_util)

target_sources(game_util PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/CallbackRegistry.cpp
)

target_link_libraries(game_util
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(game_util PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_util PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_util PRIVATE RELEASE_MODE)
endif()