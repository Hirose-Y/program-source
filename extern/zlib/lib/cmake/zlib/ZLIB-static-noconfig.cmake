#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ZLIB::ZLIBSTATIC" for configuration ""
set_property(TARGET ZLIB::ZLIBSTATIC APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ZLIB::ZLIBSTATIC PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libzs.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS ZLIB::ZLIBSTATIC )
list(APPEND _IMPORT_CHECK_FILES_FOR_ZLIB::ZLIBSTATIC "${_IMPORT_PREFIX}/lib/libzs.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
