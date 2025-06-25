add_library(LIB_Managers)

target_sources(LIB_Managers PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SoundManager.cpp
)

target_link_libraries(LIB_Managers
    ${OPENAL_LIBRARY}
    LIB_Sound
)

target_include_directories(LIB_Managers PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(LIB_Managers PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(LIB_Managers PRIVATE RELEASE_MODE)
endif()