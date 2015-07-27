cmake_minimum_required(VERSION 2.8)
project(Engine)

AUX_SOURCE_DIRECTORY(src SRC)
AUX_SOURCE_DIRECTORY(src/Core SRC_CORE)  
AUX_SOURCE_DIRECTORY(src/GUI SRC_GUI)
AUX_SOURCE_DIRECTORY(src/GUI/Widgets SRC_WIDGETS)
AUX_SOURCE_DIRECTORY(src/Render SRC_RENDER)
AUX_SOURCE_DIRECTORY(src/IO SRC_IO)
AUX_SOURCE_DIRECTORY(src/Demo SRC_DEMO)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

if(UNIX AND NOT APPLE)
    set(LINUX ON)
endif(UNIX AND NOT APPLE)

###################################################################################################
############################################--APPLE--##############################################
if(APPLE)
	message(SEND_ERROR "MacOSX is unsupported yet")
endif(APPLE)
###################################################################################################


###################################################################################################
############################################--LINUX--##############################################
if(LINUX)
	INCLUDE(FindPkgConfig)
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
	PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
	PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o0 -g3 -std=c++11 -Wall")
	INCLUDE_DIRECTORIES(src ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
endif(LINUX)
###################################################################################################


###################################################################################################
############################################--WIN32--##############################################
if(WIN32)
	if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -std=c++11 -Wall")
		#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
		#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
	elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
		message(SEND_ERROR "MSVC is unsupported")
		return()
	endif()

	set(LIB_SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2-2.0.3")
	set(LIB_SDL2_INCLUDE "${LIB_SDL2_PATH}/i686-w64-mingw32/include")
	set(LIB_SDL2_BIN "${LIB_SDL2_PATH}/i686-w64-mingw32/bin")
	find_library(
		SDL2_LIB
		NAMES SDL2
		PATHS ${LIB_SDL2_BIN}
		PATH_SUFFIXES dll
	)

	set(LIB_SDL2_IMAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2_image-2.0.0")
	set(LIB_SDL2_IMAGE_INCLUDE "${LIB_SDL2_IMAGE_PATH}/i686-w64-mingw32/include")
	set(LIB_SDL2_IMAGE_BIN "${LIB_SDL2_IMAGE_PATH}/i686-w64-mingw32/bin")
	find_library(
		SDL2_IMAGE_LIB
		NAMES SDL2_image
		PATHS ${LIB_SDL2_IMAGE_BIN}
		PATH_SUFFIXES dll
	)

	set(LIB_SDL2_TTF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2_ttf-2.0.12")
	set(LIB_SDL2_TTF_INCLUDE "${LIB_SDL2_TTF_PATH}/i686-w64-mingw32/include")
	set(LIB_SDL2_TTF_BIN "${LIB_SDL2_TTF_PATH}/i686-w64-mingw32/bin")
	find_library(
		SDL2_TTF_LIB
		NAMES SDL2_ttf
		PATHS ${LIB_SDL2_TTF_BIN}
		PATH_SUFFIXES dll
	)
	
	set(LIB_SDL2_MIXER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2_mixer-2.0.0")
	set(LIB_SDL2_MIXER_INCLUDE "${LIB_SDL2_MIXER_PATH}/i686-w64-mingw32/include")
	set(LIB_SDL2_MIXER_BIN "${LIB_SDL2_MIXER_PATH}/i686-w64-mingw32/bin")
	find_library(
		SDL2_MIXER_LIB
		NAMES SDL2_MIXER
		PATHS ${LIB_SDL2_MIXER_BIN}
		PATH_SUFFIXES dll
	)

	if (${SDL2_LIB} STREQUAL "SDL2_LIB-NOTFOUND")
		message(SEND_ERROR "SDL2.dll not found")
	endif()

	if (${SDL2_IMAGE_LIB} STREQUAL "SDL2_IMAGE_LIB-NOTFOUND")
		message(SEND_ERROR "SDL2_image.dll not found")
	endif()

	if (${SDL2_TTF_LIB} STREQUAL "SDL2_TTF_LIB-NOTFOUND")
		message(SEND_ERROR "SDL2_ttf.dll not found")
	endif()
	
	if (${SDL2_MIXER_LIB} STREQUAL "SDL2_MIXER_LIB-NOTFOUND")
		message(SEND_ERROR "SDL2_mixer.dll not found")
	endif()

	set(LIB_FLAGS "-L${LIB_SDL2_BIN} -L${LIB_SDL2_IMAGE_BIN} -L${LIB_SDL2_TTF_BIN} -L${LIB_SDL2_MIXER_BIN} -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer")
	set(LIB_INCLUDE " -I${CMAKE_CURRENT_SOURCE_DIR}/src -I${LIB_SDL2_INCLUDE} -I${LIB_SDL2_INCLUDE}/SDL2 -I${LIB_SDL2_IMAGE_INCLUDE} -I${LIB_SDL2_TTF_INCLUDE} -I${LIB_SDL2_MIXER_INCLUDE}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIB_INCLUDE} ${LIB_FLAGS} -o0 -g3 -static-libstdc++ -static-libgcc -std=c++11 -Wall")
	
	#INCLUDE_DIRECTORIES(src ${LIB_SDL2_INCLUDE} ${LIB_SDL2_IMAGE_INCLUDE} ${LIB_SDL2_TTF_INCLUDE})
endif(WIN32)
###################################################################################################

add_executable(Engine ${SRC} ${SRC_CORE} ${SRC_GUI} ${SRC_WIDGETS} ${SRC_RENDER} ${SRC_IO} ${SRC_DEMO})

if(LINUX)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
endif(LINUX)
