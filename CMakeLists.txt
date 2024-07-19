cmake_minimum_required(VERSION 3.28)
project(HYGUI)

set(CMAKE_CXX_STANDARD 20)

# =================

#if (NOT DEFINED SKIA_PATH)
#    message(FATAL_ERROR "SKIA_PATH is not defined")
#endif ()

set(MODULES_DIR ./modules)
set(GLOBAL_INCLUDE_DIR ./modules/include)
set(GLOBAL_LIB_DIR ./modules/lib)
set(SKIA_PATH ${MODULES_DIR}/projects/skia)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# =================

# 添加环境宏
add_definitions(-DPRIOJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

# boost
add_subdirectory(${MODULES_DIR}/projects/boost)
include_directories(${MODULES_DIR}/projects/boost)

include_directories(${GLOBAL_INCLUDE_DIR})
link_directories(${GLOBAL_LIB_DIR})

# sdl
include(scripts/sdl.cmake)


# 检查操作系统
if ((CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin"))
    # macOS
    set(OS_IS_APPLE TRUE)
    add_definitions(-D_HOST_APPLE_)

    enable_language(OBJCXX)

    # 寻找icu
    set (C_INCLUDE_PATH C_INCLUDE_PATH:${ICU_PATH}/include)
    set (CPLUS_INCLUDE_PATH CPLUS_INCLUDE_PATH:${ICU_PATH}/include)
    set (LD_LIBRARY_PATH LD_LIBRARY_PATH:${ICU_PATH}/lib)
    set (LIBRARY_PATH LIBRARY_PATH:${ICU_PATH}/lib)
    include_directories(${ICU_PATH}/include)
    link_directories(${ICU_PATH}/lib)

#    # SDL2
#    include_directories(${SDL_PATH}/include)
#    link_directories(${SDL_PATH}/lib)

    find_library(COCOA_LIBRARY Cocoa)
    find_library(APPKIT_LIBRARY AppKit)
    find_library(FOUNDATION_LIBRARY Foundation)
    find_package(OpenGL REQUIRED)

    #    find_package(icu4c REQUIRED)
#    include_directories(${icu4c_INCLUDE_DIRS})
#    link_directories(${icu4c_LIBRARY_DIRS})


elseif(CMAKE_HOST_WIN32)
    # Windows
    set(OS_IS_WINDOWS TRUE)
    add_definitions(-D_HOST_WINDOWS_)

    # windows该干的事

#    # SDL2
#    include_directories(${MODULES_DIR}/include)
#    link_directories(${MODULES_DIR}/lib)
#    add_subdirectory(${MODULES_DIR}/projects/SDL)
#    include_directories(${MODULES_DIR}/projects/SDL/include)

elseif(CMAKE_HOST_UNIX)
    # Linux
    set(OS_IS_LINUX TRUE)
    add_definitions(-D_HOST_LINUX_)

#    # SDL2
#    include_directories(${MODULES_DIR}/SDL/include)
#    link_directories(${MODULES_DIR}/SDL/lib)

    # icu
    include_directories(${MODULES_DIR}/icu/include)
    link_directories(${MODULES_DIR}/icu/lib)
endif()

# 检查指针大小, 32位还是64位
if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    add_definitions(-D_X64_)
elseif (${CMAKE_SIZEOF_VOID_P} EQUAL 4)
    add_definitions(-D_X86_)
else()
    message(FATAL_ERROR "Unknown pointer size: ${CMAKE_SIZEOF_VOID_P}")
endif()

# =================
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
file(GLOB_RECURSE LIB_SRC src/*.cpp src/*.cc)
if (OS_IS_APPLE)
    file(GLOB_RECURSE LIB_SRC ${LIB_SRC} src/*.mm)
endif ()
include_directories(${SKIA_PATH}/include)
include_directories(${SKIA_PATH})
include_directories(${SKIA_PATH}/third_party/externals/freetype/include)
include_directories(include)
add_library(HYGUI STATIC ${LIB_SRC})
#add_dependencies(HYGUI SDL_SUBMODEL_BUILD)
# set_property(TARGET HYGUI PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_compile_definitions(HYGUI PRIVATE _HYGUI_MODULE_)
target_compile_definitions(HYGUI PRIVATE NOMINMAX)
target_include_directories(HYGUI PRIVATE interior/include)
target_include_directories(HYGUI PRIVATE src/utils)

if(MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE "/NODEFAULTLIB:libcmt.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/NODEFAULTLIB:libucrtd.lib")
endif()

# 检查是否为debug
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    link_directories(${SKIA_PATH}/out/debug_x64_static)
    # target_link_libraries(HYGUI PRIVATE glfw3d)
else()
    link_directories(${SKIA_PATH}/out/release_x64_static)
    # target_link_libraries(HYGUI PRIVATE glfw3)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -flto")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -flto")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -flto")

endif ()
target_link_libraries(HYGUI PRIVATE skia skshaper skcms sksg skresources skshaper sksg ${BOOST_LIBRARIES})
if (OS_IS_WINDOWS)
    target_link_libraries(HYGUI PRIVATE SDL3::SDL3-static)

    target_link_libraries(HYGUI PRIVATE opengl32.lib legacy_stdio_definitions)
    target_link_libraries(HYGUI PRIVATE  Winmm Setupapi Imm32 Version dwmapi FontSub)

elseif (OS_IS_APPLE)
    target_link_libraries(HYGUI PRIVATE  icudata icutu icui18n icuuc SDL2 ${COCOA_LIBRARY} ${APPKIT_LIBRARY} ${FOUNDATION_LIBRARY} OpenGL::GL)

elseif (OS_IS_LINUX)
    target_link_libraries(HYGUI PRIVATE SDL3::SDL3-static X11
            GL GLU glut
            png jpeg freetype fontconfig
    )

endif ()

# =================


if (NOT DEFINED NO_EXAMPLES)
#    # data
#    add_executable(ExamplesHashTable examples/data/hashtable.cpp)
#    target_link_libraries(ExamplesHashTable HYGUI)
    # helloworld
    add_executable(HelloWorld examples/helloworld/helloworld.cpp)
    target_link_libraries(HelloWorld PRIVATE HYGUI)
    # event
    add_executable(EventTest examples/event/events.cpp)
    target_link_libraries(EventTest PRIVATE HYGUI)
    # cloud_music
    add_executable(CloudMusic examples/CloudMusic/main_window.cpp examples/CloudMusic/layout.cpp)
    target_link_libraries(CloudMusic PRIVATE HYGUI)
endif ()
