
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was Config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

####################################################################################

if(NOT CMakeFindDependencyMacro_FOUND)
    find_file(CMAKE_FIND_DEPENDENCY_MACRO_FILE CMakeFindDependencyMacro.cmake
        PATHS ${CMAKE_MODULE_PATH} ${CMAKE_ROOT}/Modules NO_DEFAULT_PATH)
    if(CMAKE_FIND_DEPENDENCY_MACRO_FILE)
        include(${CMAKE_FIND_DEPENDENCY_MACRO_FILE})
        set(CMakeFindDependencyMacro_FOUND TRUE)
    else()
        message(FATAL_ERROR "CMakeFindDependencyMacro.cmake not found. Please ensure CMake is installed correctly.")
    endif()
endif()

find_dependency(SDL2 REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/SDL_Graph.cmake")
check_required_components("YourLib")
