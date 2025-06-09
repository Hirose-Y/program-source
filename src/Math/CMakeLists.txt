add_library(game_math)

target_sources(game_math PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Ray.cpp
)
target_link_libraries(game_math
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(game_math PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game_math PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game_math PRIVATE RELEASE_MODE)
endif()