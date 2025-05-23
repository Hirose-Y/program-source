# Install script for directory: C:/programing/C++/openglGame/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/openGL_training")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/programing/C++/openglGame/build/Release/src/Input/cmake_install.cmake")
  include("C:/programing/C++/openglGame/build/Release/src/InputActions/cmake_install.cmake")
  include("C:/programing/C++/openglGame/build/Release/src/Object/cmake_install.cmake")
  include("C:/programing/C++/openglGame/build/Release/src/Scene/cmake_install.cmake")
  include("C:/programing/C++/openglGame/build/Release/src/Camera/cmake_install.cmake")
  include("C:/programing/C++/openglGame/build/Release/src/Collider/cmake_install.cmake")
  include("C:/programing/C++/openglGame/build/Release/src/Stage/cmake_install.cmake")
  include("C:/programing/C++/openglGame/build/Release/src/Behavior/cmake_install.cmake")
  include("C:/programing/C++/openglGame/build/Release/src/World/cmake_install.cmake")

endif()

