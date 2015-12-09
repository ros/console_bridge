cmake_minimum_required(VERSION 2.8)
project(console_bridge)

set (CONSOLE_BRIDGE_MAJOR_VERSION 0)
set (CONSOLE_BRIDGE_MINOR_VERSION 3)
set (CONSOLE_BRIDGE_PATCH_VERSION 0)

set (CONSOLE_BRIDGE_VERSION ${CONSOLE_BRIDGE_MAJOR_VERSION}.${CONSOLE_BRIDGE_MINOR_VERSION}.${CONSOLE_BRIDGE_PATCH_VERSION})
message (STATUS "${PROJECT_NAME} version ${CONSOLE_BRIDGE_VERSION}")

include(GNUInstallDirs)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# If compiler support symbol visibility, enable it.
include(CheckCCompilerFlag)
check_c_compiler_flag(-fvisibility=hidden HAS_VISIBILITY)
if (HAS_VISIBILITY)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
endif()

find_package(Boost COMPONENTS system thread REQUIRED)

if(MSVC OR MSVC90 OR MSVC10)
  set(MSVC ON)
endif (MSVC OR MSVC90 OR MSVC10)

if(MSVC)
  add_definitions(-DBOOST_ALL_NO_LIB)
endif(MSVC)

include_directories(include)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

if(NOT DEFINED BUILD_SHARED_LIBS)
  option(BUILD_SHARED_LIBS "Build dynamically-linked binaries" ON)
endif()

add_library(${PROJECT_NAME} src/console.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/)

install(DIRECTORY include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.h")

set(PKG_NAME ${PROJECT_NAME})
set(PKG_LIBRARIES ${PROJECT_NAME})
set(cmake_conf_file "${PROJECT_NAME}-config.cmake")
configure_file("${cmake_conf_file}.in" "${CMAKE_BINARY_DIR}/${cmake_conf_file}" @ONLY)
set(cmake_conf_version_file "${PROJECT_NAME}-config-version.cmake")
# Use write_basic_package_version_file to generate a ConfigVersion file that
# allow users of gazebo to specify the API or version to depend on
# TODO: keep this instruction until deprecate Ubuntu/Precise and update with
# https://github.com/Kitware/CMake/blob/v2.8.8/Modules/CMakePackageConfigHelpers.cmake
include(WriteBasicConfigVersionFile)
write_basic_config_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${cmake_conf_version_file}
  VERSION "${CONSOLE_BRIDGE_VERSION}"
  COMPATIBILITY SameMajorVersion)

if(WIN32 AND NOT CYGWIN)
  set(CMAKE_CONFIG_INSTALL_DIR CMake)
else()
  set(CMAKE_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake/)
endif()
install(FILES
        "${CMAKE_BINARY_DIR}/${cmake_conf_file}"
        "${CMAKE_BINARY_DIR}/${cmake_conf_version_file}"
  DESTINATION ${CMAKE_CONFIG_INSTALL_DIR} COMPONENT cmake)

if (NOT MSVC)
  set(PKG_DESC "Console Bridge")
  set(PKG_CB_LIBS "-l${PROJECT_NAME}")
  set(pkg_conf_file "console_bridge.pc")
  configure_file("${pkg_conf_file}.in" "${CMAKE_BINARY_DIR}/${pkg_conf_file}" @ONLY)
  install(FILES "${CMAKE_BINARY_DIR}/${pkg_conf_file}"
    DESTINATION lib/pkgconfig/ COMPONENT pkgconfig)
endif()

SET_DIRECTORY_PROPERTIES(PROPERTIES
  ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_BINARY_DIR}/console_bridge-config.cmake
  ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_BINARY_DIR}/console_bridge.pc)
