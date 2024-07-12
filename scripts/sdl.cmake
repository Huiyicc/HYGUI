include(ExternalProject)

set(EP_SDL_DIR modules/projects/SDL)
set(SDL_INSTALL_PATH ${PROJECT_SOURCE_DIR}/modules)
set(SDL_BINARY_PATH ${CMAKE_BINARY_DIR}/submodules/SDL)

#ExternalProject_Add(SDL_SUBMODEL
#    SOURCE_DIR "${EP_SDL_DIR}"
#    INSTALL_DIR "${SDL_INSTALL_PATH}"
#    TMP_DIR "${SDL_BINARY_PATH}/tmp"
#    BINARY_DIR "${SDL_BINARY_PATH}/bin"
#)
#
#add_custom_target(SDL_SUBMODEL_BUILD ALL
#    COMMAND ${CMAKE_COMMAND} --build ${SDL_BINARY_PATH}
#    WORKING_DIRECTORY ${SDL_INSTALL_PATH}
#)
if (WIN32)
  add_definitions(-DWIN32)
  add_definitions(-D_WINDOWS)
  add_definitions(-DUSING_GENERATED_CONFIG_H)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DSDL_BUILD_MAJOR_VERSION=3)
  add_definitions(-DSDL_BUILD_MINOR_VERSION=1)
  add_definitions(-DSDL_BUILD_MICRO_VERSION=2)
  add_definitions(-DCMAKE_INTDIR="${CMAKE_BUILD_TYPE}")
  add_definitions(-DDLL_EXPORT)

endif ()
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
add_subdirectory(${MODULES_DIR}/projects/SDL)