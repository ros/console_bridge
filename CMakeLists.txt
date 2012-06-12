cmake_minimum_required(VERSION 2.8)
project(console_bridge)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Boost COMPONENTS thread REQUIRED)

if(MSVC OR MSVC90 OR MSVC10)
  set(MSVC ON)
endif (MSVC OR MSVC90 OR MSVC10)

if(MSVC)
  add_definitions(-DBOOST_ALL_NO_LIB)
endif(MSVC)

include_directories(include)

add_library(${PROJECT_NAME} SHARED src/console.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_THREAD_LIBRARY})

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/)

install(DIRECTORY include
  DESTINATION include
  FILES_MATCHING PATTERN "*.h")

if (NOT MSVC)
  set(PKG_NAME "console_bridge")
  set(PKG_DESC "Console Bridge")
  set(PKG_OMPL_LIBS "-l${PROJECT_NAME}")
  set(pkg_conf_file "${CMAKE_CURRENT_SOURCE_DIR}/console_bridge.pc")
  configure_file("${pkg_conf_file}.in" "${pkg_conf_file}" @ONLY)
  install(FILES ${pkg_conf_file} DESTINATION lib/pkgconfig/ COMPONENT pkgconfig)
endif()
