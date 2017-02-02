cmake_minimum_required(VERSION 3.0)
project(Engine)

#Build Engine as library if enabled, else as executable
OPTION(AS_LIBRARY ON)

#Get Engine's sources
AUX_SOURCE_DIRECTORY(src SRC)
AUX_SOURCE_DIRECTORY(src/Core SRC_CORE)  
AUX_SOURCE_DIRECTORY(src/GUI SRC_GUI)
AUX_SOURCE_DIRECTORY(src/GUI/Widgets SRC_WIDGETS)
AUX_SOURCE_DIRECTORY(src/Render SRC_RENDER)
AUX_SOURCE_DIRECTORY(src/IO SRC_IO)
AUX_SOURCE_DIRECTORY(src/LuaBindings SRC_LUA_BINDINGS)
AUX_SOURCE_DIRECTORY(src/Common SRC_COMMON)

set(SOURCES
    ${SRC}
    ${SRC_CORE}
    ${SRC_GUI}
    ${SRC_WIDGETS}
    ${SRC_RENDER}
    ${SRC_IO}
    ${SRC_DEMO}
    ${SRC_LUA_BINDINGS}
    ${SRC_COMMON}

    src/Common/sys.h
    src/Common/constants.h
    )


if(UNIX AND NOT APPLE)
    set(LINUX ON)
endif(UNIX AND NOT APPLE)


if(APPLE)
        message(SEND_ERROR "MacOSX is unsupported yet, try to build as for linux")
endif(APPLE)


if(LINUX)
        include(FindPkgConfig)
        PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2>=2.0.0)
	PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
	PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
	PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
	
	if(COVERAGE_ENABLED)
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
        endif(COVERAGE_ENABLED)
	
        include_directories(src ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
endif(LINUX)


if(WIN32)
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIB_FLAGS} -Wall")

        include(FindPkgConfig)
        PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2>=2.0.0)
        PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
        PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
        PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

        include_directories(src ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
            message(SEND_ERROR "MSVC isn't configured yet, but it's able to compile with it ;)")
            return()
    endif()
endif(WIN32)

if(AS_LIBRARY)    
    add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
    set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
    #Set binary folder
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    add_executable(${PROJECT_NAME} ${SOURCES})
endif(AS_LIBRARY)



#Add third-party libs
add_subdirectory(Third-party)
set(SDL2_DEPS ${SDL2_STATIC_LIBRARIES} ${SDL2IMAGE_STATIC_LIBRARIES} ${SDL2TTF_STATIC_LIBRARIES} ${SDL2MIXER_STATIC_LIBRARIES})

set(LIBS ${SDL2_DEPS} physfs++ sol2)

if(LINUX)
    target_link_libraries(${PROJECT_NAME} ${LIBS})
endif(LINUX)

if(WIN32)
    if(GNU_CLANG)
        target_link_libraries(${PROJECT_NAME} ${LIBS})
    endif(GNU_CLANG)
endif(WIN32)



#Require c++14 standard
set(CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
