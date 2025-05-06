add_library(InputActions)

add_subdirectory(Context)
add_subdirectory(Player)
add_subdirectory(Transition)
add_subdirectory(World)
add_subdirectory(Camera)

target_link_libraries(InputActions
    ${glew_LIBRARY}
    ${glfw_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${freetype_LIBRARY}
    ${assimp_LIBRARY}
    ${zlibstatic_LIBRARY}   
    ${zlib_LIBRARY}
)

target_include_directories(InputActions PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${cmake_extern_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(InputActions PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(InputActions PRIVATE RELEASE_MODE)
endif()