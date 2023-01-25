cmake_minimum_required(VERSION 3.14)

if(NOT DEFINED CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "clang")
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_COMPILER "clang++")
endif()

project(example1)

set(CMAKE_CXX_STANDARD 17)
# set(Boost_INCLUDE_DIR /usr/local/src/boost_1_46_1)
# set(Boost_LIBRARY_DIR /usr/local/src/boost_1_46_1/stage/lib)

# find_package(Boost)
# IF (Boost_FOUND)
# message("Boost!!!")
# ENDIF()
SET(myname 3)
set (myname 9)
message(${myname})
# include_directories(${Boost_INCLUDE_DIR})
  find_package(Qt5Widgets REQUIRED)
  include_directories(${Qt5Widgets_INCLUDES})
  # add_definitions(${Qt5Widgets_DEFINITIONS})
  # set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
  add_executable(myExe main.cpp)
  target_link_libraries(myExe ${Qt5Widgets_LIBRARIES})
# target_link_libraries(myExe ${Boost_LIBRARIES})
# set(CMAKE_CXX_STANDARD 11) set (var 5) option(USE_ANOTHER_LIBRARY "Do ydou
# want to use an another library?" off)

# add_library(libka1 STATIC Extrapolation.cpp) add_library(libka2 STATIC
# Splines.cpp) message ("variable is ${USE_ANOTHER_LIBRARY}") set
# (BUILD_SHARED_LIBS YES)
include_directories(include)
add_subdirectory(src)

message(${newnew})
set (var_a 3)
set(var_b 7)
set (var_c ${var_a} + ${var_b})
math(EXPR var_c "${var_a} + ${var_b}")
message("var_c = ${var_c}")
set(varvar a s f s g)
message("varvar = ${varvar}")
# ##############################################################################

target_link_libraries(myExe libka1)
