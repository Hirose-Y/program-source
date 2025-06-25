add_library(LIB_Sound)

target_sources(LIB_Sound PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/AudioEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SoundBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SoundSource.cpp
)

target_link_libraries(LIB_Sound
    ${OPENAL_LIBRARY}
)

target_include_directories(LIB_Sound PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${EXTERNAL_INCLUDE}
)

# ビルドタイプによる切り替え
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(LIB_Sound PRIVATE DEBUG_MODE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(LIB_Sound PRIVATE RELEASE_MODE)
endif()