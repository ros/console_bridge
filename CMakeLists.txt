cmake_minimum_required(VERSION 2.8)
project(console_bridge)

include(GNUInstallDirs)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
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
  DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h")

set(PKG_NAME ${PROJECT_NAME})
set(PKG_LIBRARIES ${PROJECT_NAME})
set(cmake_conf_file "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}-config.cmake")
configure_file("${cmake_conf_file}.in" "${cmake_conf_file}" @ONLY)
install(FILES ${cmake_conf_file}
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake/ COMPONENT cmake)

if (NOT MSVC)
  set(PKG_DESC "Console Bridge")
  set(PKG_CB_LIBS "-l${PROJECT_NAME}")
  set(pkg_conf_file "${CMAKE_CURRENT_SOURCE_DIR}/console_bridge.pc")
  configure_file("${pkg_conf_file}.in" "${pkg_conf_file}" @ONLY)
  install(FILES ${pkg_conf_file}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/ COMPONENT pkgconfig)
endif()

SET_DIRECTORY_PROPERTIES(PROPERTIES
  ADDITIONAL_MAKE_CLEAN_FILES console_bridge-config.cmake
  ADDITIONAL_MAKE_CLEAN_FILES console_bridge.pc)
