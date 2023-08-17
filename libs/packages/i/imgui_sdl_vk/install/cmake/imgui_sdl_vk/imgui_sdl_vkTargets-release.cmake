#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "imgui_sdl_vk::imgui_sdl_vk" for configuration "Release"
set_property(TARGET imgui_sdl_vk::imgui_sdl_vk APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(imgui_sdl_vk::imgui_sdl_vk PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "ASM_NASM;C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libimgui_sdl_vk.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS imgui_sdl_vk::imgui_sdl_vk )
list(APPEND _IMPORT_CHECK_FILES_FOR_imgui_sdl_vk::imgui_sdl_vk "${_IMPORT_PREFIX}/lib/libimgui_sdl_vk.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
