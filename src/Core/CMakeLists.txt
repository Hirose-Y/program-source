add_library(game_core)

target_sources(game_core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
)

target_link_libraries(game_core
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
    LIB_Managers
    LIB_Sound
)

target_include_directories(game_core PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_core PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_core PRIVATE RELEASE_MODE)
endif()