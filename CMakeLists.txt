cmake_minimum_required(VERSION 3.0)
project(Engine)


#===================Global vars========================
SET_PROPERTY(GLOBAL PROPERTY ENGINE_LIBS "")
SET_PROPERTY(GLOBAL PROPERTY ENGINE_INCLUDES "")
#======================================================


#===================Build options======================
option(BUILD_STATIC_LIB OFF)
option(BUILD_DYNAMIC_LIB OFF)

#Third-party libraries
option(USE_LUA ON)
option(USE_PHYSFS ON)
option(USE_SIMPLE_JSON ON)
#======================================================


#=====================Includes=========================
#Get Engine's sources
aux_source_directory(src SRC)
aux_source_directory(src/Core SRC_CORE)
aux_source_directory(src/GUI SRC_GUI)
aux_source_directory(src/GUI/Widgets SRC_WIDGETS)
aux_source_directory(src/Render SRC_RENDER)
aux_source_directory(src/IO SRC_IO)
aux_source_directory(src/LuaBindings SRC_LUA_BINDINGS)
aux_source_directory(src/Common SRC_COMMON)

set(SOURCES
    ${SRC}
    ${SRC_CORE}
    ${SRC_GUI}
    ${SRC_WIDGETS}
    ${SRC_RENDER}
    ${SRC_IO}
    ${SRC_COMMON}

    src/Common/sys.h
    src/Common/constants.h
    )

#Append Lua includes
if(USE_LUA)
    set(SOURCES ${SOURCES} ${SRC_LUA_BINDINGS})
    add_definitions("-DUSE_LUA")
endif()

if(USE_PHYSFS)
    add_definitions("-DUSE_PHYSFS")
endif()

if(USE_SIMPLE_JSON)
    add_definitions("-DUSE_SIMPLE_JSON")
endif()

#include sources root
include_directories(src)
#======================================================


#================Compiler determining==================
set(GNU_CLANG ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

if(UNIX AND NOT APPLE)
    set(LINUX ON)
endif()

if(APPLE)
    message(SEND_ERROR "MacOSX is not configured yet.\n[WARNING] Trying to use Linux build configuration.")
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message(SEND_ERROR "MSVC isn't configured yet, but it's able to compile with it ;)")
endif()

if(WIN32)
    #Fix for sol2 building under MinGW
    add_definitions("-D_GLIBCXX_USE_C99_CTYPE_TR1")
endif()
#======================================================


#================Compiler configuring==================
if(COVERAGE_ENABLED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif(COVERAGE_ENABLED)

if(BUILD_STATIC_LIB)
    add_definitions("-DBUILD_STATIC_LIB")
    add_library(${PROJECT_NAME} STATIC ${SOURCES})

elseif(BUILD_DYNAMIC_LIB)
    add_library(${PROJECT_NAME} SHARED ${SOURCES})

elseif(NOT(BUILD_STATIC_LIB AND BUILD_DYNAMIC_LIB))
    #Set binary folder
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    #add_executable(${PROJECT_NAME} ${SOURCES})
endif()
#======================================================


#==================Libraries linking===================
#Add third-party libs
add_subdirectory(Third-party)

#extract globals
GET_PROPERTY(LOCAL_INCLUDES GLOBAL PROPERTY ENGINE_INCLUDES)
GET_PROPERTY(LOCAL_LIBS GLOBAL PROPERTY ENGINE_LIBS)

include_directories(${LOCAL_INCLUDES})
target_link_libraries(${PROJECT_NAME} ${LOCAL_LIBS})
#======================================================


#=================C++ standard setup===================
set(CXX_STANDARD_REQUIRED ON)

if(USE_LUA)
    #Require c++14 standard
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
else()
    #Require c++11 standard
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
endif()
#======================================================
