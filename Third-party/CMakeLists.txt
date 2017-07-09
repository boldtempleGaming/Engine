cmake_minimum_required(VERSION 3.0)
project(Third-party)

set(EXPORT_INCLUDES "")
set(EXPORT_LIBS "")


#======================SDL2 libs=======================
if(LINUX OR (WIN32 AND GNU_CLANG))
    message("Checking SDL2...")

    include(FindPkgConfig)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2>=2.0.0)
    PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
    PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

    #export includes to Engine
    set(EXPORT_INCLUDES
        ${EXPORT_INCLUDES}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
        ${SDL2TTF_INCLUDE_DIRS}
        ${SDL2MIXER_INCLUDE_DIRS}
        )

    #append libs
    set(EXPORT_LIBS
        ${EXPORT_LIBS}
        ${SDL2_LIBRARIES}
        ${SDL2IMAGE_LIBRARIES}
        ${SDL2TTF_LIBRARIES}
        ${SDL2MIXER_LIBRARIES}
        )
else()
    message(SEND_ERROR "SDL2 dependencies is not configured for your compiler.")
endif()

#======================================================


#=======================physfs=========================
if(USE_PHYSFS)
    message("Checking physfs...")

    set(PHYSFS_BUILD_TEST OFF CACHE BOOL "disable tests" FORCE)
    set(PHYSFS_ARCHIVE_7Z OFF CACHE BOOL "7z" FORCE)
    set(PHYSFS_ARCHIVE_GRP OFF CACHE BOOL "GRP" FORCE)
    set(PHYSFS_ARCHIVE_WAD OFF CACHE BOOL "WAD" FORCE)
    set(PHYSFS_ARCHIVE_HOG OFF CACHE BOOL "HOG" FORCE)
    set(PHYSFS_ARCHIVE_MVL OFF CACHE BOOL "MVL" FORCE)
    set(PHYSFS_ARCHIVE_QPAK OFF CACHE BOOL "QPAK" FORCE)
    set(PHYSFS_HAVE_CDROM_SUPPORT OFF CACHE BOOL "CDROM" FORCE)

    add_subdirectory("physfs")

    include_directories("physfs-cpp/include")
    add_subdirectory("physfs-cpp/src")

    target_include_directories(physfs++ PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/physfs>
    )

    #populate includes list
    set(EXPORT_INCLUDES
        ${EXPORT_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}/physfs
        ${CMAKE_CURRENT_SOURCE_DIR}/physfs-cpp/include
        )

    set(EXPORT_LIBS
        ${EXPORT_LIBS}
        physfs
        physfs++
        )
endif()
#======================================================


#===================Lua and sol2=======================
if(USE_LUA)
    message("Checking Lua and sol2...")

    #exporting includes to Engine
    find_package(Lua REQUIRED)

    set(SOL_HEADERS
        sol2/sol/as_args.hpp
        sol2/sol/bind_traits.hpp
        sol2/sol/call.hpp
        sol2/sol/compatibility
        sol2/sol/compatibility.hpp
        sol2/sol/container_usertype_metatable.hpp
        sol2/sol/coroutine.hpp
        sol2/sol/debug.hpp
        sol2/sol/demangle.hpp
        sol2/sol/deprecate.hpp
        sol2/sol/error.hpp
        sol2/sol/function.hpp
        sol2/sol/function_result.hpp
        sol2/sol/function_types_core.hpp
        sol2/sol/function_types.hpp
        sol2/sol/function_types_overloaded.hpp
        sol2/sol/function_types_stateful.hpp
        sol2/sol/function_types_stateless.hpp
        sol2/sol/function_types_templated.hpp
        sol2/sol/inheritance.hpp
        sol2/sol/in_place.hpp
        sol2/sol/load_result.hpp
        sol2/sol/object.hpp
        sol2/sol/optional.hpp
        sol2/sol/optional_implementation.hpp
        sol2/sol/overload.hpp
        sol2/sol/property.hpp
        sol2/sol/protected_function.hpp
        sol2/sol/protected_function_result.hpp
        sol2/sol/protect.hpp
        sol2/sol/proxy_base.hpp
        sol2/sol/proxy.hpp
        sol2/sol/raii.hpp
        sol2/sol/reference.hpp
        sol2/sol/resolve.hpp
        sol2/sol/simple_usertype_metatable.hpp
        sol2/sol/stack_check_get.hpp
        sol2/sol/stack_check.hpp
        sol2/sol/stack_core.hpp
        sol2/sol/stack_field.hpp
        sol2/sol/stack_get.hpp
        sol2/sol/stack_guard.hpp
        sol2/sol/stack.hpp
        sol2/sol/stack_pop.hpp
        sol2/sol/stack_probe.hpp
        sol2/sol/stack_proxy.hpp
        sol2/sol/stack_push.hpp
        sol2/sol/stack_reference.hpp
        sol2/sol/state.hpp
        sol2/sol/state_view.hpp
        sol2/sol/string_shim.hpp
        sol2/sol/table_core.hpp
        sol2/sol/table.hpp
        sol2/sol/table_iterator.hpp
        sol2/sol/thread.hpp
        sol2/sol/tie.hpp
        sol2/sol/traits.hpp
        sol2/sol/tuple.hpp
        sol2/sol/types.hpp
        sol2/sol/userdata.hpp
        sol2/sol/usertype.hpp
        sol2/sol/usertype_metatable.hpp
        sol2/sol/usertype_traits.hpp
        sol2/sol/variadic_args.hpp
        sol2/sol/wrapper.hpp
    )

    set(SOL_COMP
        sol2/sol/compatibility/5.0.0.h
        sol2/sol/compatibility/5.1.0.h
        sol2/sol/compatibility/5.2.0.h
        sol2/sol/compatibility/5.x.x.h
        sol2/sol/compatibility/5.x.x.inl
        sol2/sol/compatibility/version.hpp
        )

    add_library(sol2 STATIC sol2/sol.hpp ${SOL_HEADERS} ${SOL_COMP})
    target_link_libraries(sol2 ${LUA_LIBRARIES})
    set_target_properties(sol2 PROPERTIES LINKER_LANGUAGE CXX)

    set(EXPORT_INCLUDES
        ${EXPORT_INCLUDES}
        ${LUA_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/sol2/
        )

    set(EXPORT_LIBS
        ${EXPORT_LIBS}
        sol2
        )

endif()
#======================================================


#====================SimpleJSON========================
if(USE_SIMPLE_JSON)
    message("Checking SimpleJSON...")

    add_library(SimpleJSON STATIC SimpleJSON/json.hpp)
    set_target_properties(SimpleJSON PROPERTIES LINKER_LANGUAGE CXX)

    set(EXPORT_INCLUDES
        ${EXPORT_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}/SimpleJSON/
        )

    set(EXPORT_LIBS
        ${EXPORT_LIBS}
        SimpleJSON
        )
endif()
#======================================================


#export includes and libs
SET_PROPERTY(GLOBAL PROPERTY ENGINE_INCLUDES ${EXPORT_INCLUDES})
SET_PROPERTY(GLOBAL PROPERTY ENGINE_LIBS ${EXPORT_LIBS})
