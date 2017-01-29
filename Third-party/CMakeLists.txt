cmake_minimum_required(VERSION 3.0)
project(External)


#physfs lib
set(PHYSFS_BUILD_TEST OFF CACHE BOOL "disable tests" FORCE)
set(PHYSFS_ARCHIVE_7Z OFF CACHE BOOL "7z" FORCE)
set(PHYSFS_ARCHIVE_GRP OFF CACHE BOOL "GRP" FORCE)
set(PHYSFS_ARCHIVE_WAD OFF CACHE BOOL "WAD" FORCE)
set(PHYSFS_ARCHIVE_HOG OFF CACHE BOOL "HOG" FORCE)
set(PHYSFS_ARCHIVE_MVL OFF CACHE BOOL "MVL" FORCE)
set(PHYSFS_ARCHIVE_QPAK OFF CACHE BOOL "QPAK" FORCE)
set(PHYSFS_HAVE_CDROM_SUPPORT OFF CACHE BOOL "CDROM" FORCE)

add_subdirectory("physfs-2.0.3")

include_directories("physfs-cpp/include")
add_subdirectory("physfs-cpp/src")

target_include_directories(physfs++ PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/physfs-2.0.3> # <prefix>/include/mylib
)

#exporting includes to Engine
target_include_directories(Engine PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/physfs-cpp/include>
)
########


