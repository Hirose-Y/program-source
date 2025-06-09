add_library(InputSystem)

target_sources(InputSystem PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/InputSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Keyboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GamePad.cpp
)

target_link_libraries(InputSystem
    glad 
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(InputSystem PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(InputSystem PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(InputSystem PRIVATE RELEASE_MODE)
endif()