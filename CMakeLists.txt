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
elseif(CMAKE_HOST_WIN32)
    # Windows
    set(OS_IS_WINDOWS TRUE)
    add_definitions(-D_HOST_WINDOWS_)
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

file(GLOB_RECURSE LIB_SRC src/*.cpp)
include_directories(${SKIA_PATH}/include)
include_directories(include)
add_library(HYGUI STATIC ${LIB_SRC})


# =================


if (NOT DEFINED NO_EXAMPLES)
    add_executable(HelloWorld examples/helloworld/main.cpp)
    target_link_libraries(HelloWorld HYGUI)
endif ()
