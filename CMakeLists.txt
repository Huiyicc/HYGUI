cmake_minimum_required(VERSION 3.28)
project(HYGUI)

set(CMAKE_CXX_STANDARD 17)

# =================

if (NOT DEFINED SKIA_PATH)
    message(FATAL_ERROR "SKIA_PATH is not defined")
endif ()

# =================

# 添加环境宏
add_definitions(-DPRIOJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")

# 检查操作系统
if ((CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin"))
    # macOS
    set(OS_IS_APPLE TRUE)
    add_definitions(-D_HOST_APPLE_)

    enable_language(OBJCXX)

    # 寻找boost
    find_package(Boost REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

    # 寻找icu
    set (C_INCLUDE_PATH C_INCLUDE_PATH:${ICU_PATH}/include)
    set (CPLUS_INCLUDE_PATH CPLUS_INCLUDE_PATH:${ICU_PATH}/include)
    set (LD_LIBRARY_PATH LD_LIBRARY_PATH:${ICU_PATH}/lib)
    set (LIBRARY_PATH LIBRARY_PATH:${ICU_PATH}/lib)
    include_directories(${ICU_PATH}/include)
#    find_package(icu4c REQUIRED)
#    include_directories(${icu4c_INCLUDE_DIRS})
#    link_directories(${icu4c_LIBRARY_DIRS})


elseif(CMAKE_HOST_WIN32)
    # Windows
    set(OS_IS_WINDOWS TRUE)
    add_definitions(-D_HOST_WINDOWS_)

    # windows该干的事
    if (NOT MODULES_DIR)
        # boost
        include_directories($ENV{MODULES_DIR}/boost/include)
        link_directories($ENV{MODULES_DIR}/boost/lib)

        # SDL2
        include_directories($ENV{MODULES_DIR}/SDL/include)
        link_directories($ENV{MODULES_DIR}/SDL/lib)

#        # glfw
#        include_directories($ENV{MODULES_DIR}/glfw/include)
#        link_directories($ENV{MODULES_DIR}/glfw/lib)

    else()
        # boost
        include_directories(${MODULES_DIR}/boost/include)
        link_directories(${MODULES_DIR}/boost/lib)

        # SDL2
        include_directories($ENV{MODULES_DIR}/SDL/include)
        link_directories($ENV{MODULES_DIR}/SDL/lib)

#        # glfw
#        include_directories(${MODULES_DIR}/glfw/include)
#        link_directories(${MODULES_DIR}/glfw/lib)

    endif()

elseif(CMAKE_HOST_UNIX)
    # Linux
    set(OS_IS_LINUX TRUE)
    add_definitions(-D_HOST_LINUX_)
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
# skia
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
file(GLOB_RECURSE LIB_SRC src/*.cpp src/*.cc)
if (OS_IS_APPLE)
    file(GLOB_RECURSE LIB_SRC ${LIB_SRC} src/*.mm)
endif ()
include_directories(${SKIA_PATH}/include)
include_directories(${SKIA_PATH})
include_directories(include)
add_library(HYGUI STATIC ${LIB_SRC})
target_compile_definitions(HYGUI PRIVATE _HYGUI_MODULE_)
target_compile_definitions(HYGUI PRIVATE NOMINMAX)
target_include_directories(HYGUI PRIVATE interior/include)
target_include_directories(HYGUI PRIVATE src/utils)

if(MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE "/NODEFAULTLIB:libcmt.lib")
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
target_link_libraries(HYGUI PRIVATE skia)
if (OS_IS_WINDOWS)
    target_link_libraries(HYGUI PRIVATE opengl32.lib)
    target_link_libraries(HYGUI PRIVATE SDL2-static Winmm Setupapi Imm32 Version)

elseif (OS_IS_APPLE)
    target_link_libraries(HYGUI PRIVATE iconv)
endif ()

# =================


if (NOT DEFINED NO_EXAMPLES)
#    # data
#    add_executable(ExamplesHashTable examples/data/hashtable.cpp)
#    target_link_libraries(ExamplesHashTable HYGUI)
    # helloworld
    add_executable(HelloWorld examples/helloworld/helloworld.cpp)
    target_link_libraries(HelloWorld PRIVATE HYGUI)
endif ()
