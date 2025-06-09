add_library(game_stage)

target_sources(game_stage PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Stage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StageBuilder.cpp
)

target_link_libraries(game_stage
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(game_stage PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_stage PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_stage PRIVATE RELEASE_MODE)
endif()