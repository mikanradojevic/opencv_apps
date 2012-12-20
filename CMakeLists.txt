PROJECT(opencv_tests)
cmake_minimum_required(VERSION 2.8)

SET(BOOST_ROOT_DIR "" CACHE PATH "")
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${BOOST_ROOT_DIR})
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${BOOST_ROOT_DIR}/lib)

find_package(BOOST)
if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIR})
	add_definitions("-DHAS_BOOST")
endif() 

FIND_PACKAGE(wxWidgets COMPONENTS core base)
if (wxWidgets_FOUND)
	include_directories(${wxWidgets_INCLUDE_DIRS})
	#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${wxWidgets_LIB_DIR})
endif()

# include path
include_directories(${PROJECT_SOURCE_DIR}/deps/include/) 
# library path
link_directories(${PROJECT_SOURCE_DIR}/deps/lib/)
link_directories(${PROJECT_SOURCE_DIR}/deps/lib/wxwidgets) 
link_directories(${PROJECT_SOURCE_DIR}/deps/lib/opencv)
# dll path
set(DEP_DLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/bin/)

# Adding src directory to the project
add_subdirectory(data)
add_subdirectory(src)