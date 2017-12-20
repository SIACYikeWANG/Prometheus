#1.cmake verson，指定cmake版本 
cmake_minimum_required(VERSION 3.2)

#2.project name，指定项目的名称，一般和项目的文件夹名称对应
PROJECT(PROMETHEUS)

#3.Qt Configuration
set(CMAKE_PREFIX_PATH "/home/yike/Qt5.10.0/5.10.0/gcc_64/")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)

FILE(GLOB SRC_FILES "./*.cxx")
FILE(GLOB HEAD_FILES "./*.h")
FILE(GLOB UI_FILES "./*.ui")

qt5_wrap_ui(WRAP_FILES ${UI_FILES})
#set(RCC_FILES rcc.prc)
source_group("ui" FILES ${UI_FILES} ${WRAP_FILES})

#指定编译类型为debug或者release
SET(CMAKE_BUILD_TYPE DEBUG)

#制定编译器
#CMAKE_C_FLAGS_DEBUG是C
#CMAKE_CXX_FLAGS_DEBUG是C++
#
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

#3.head file path，头文件目录
INCLUDE_DIRECTORIES( include )

#4.source directory，源文件目录
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

#5.set environment variable，设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"
SET(PROMETHEUS ${DIR_SRCS} )

#6.add executable file，添加要编译的可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ${WRAP_FILES}
                               src/main.cpp
                               src/kvrChannel.cpp
                               src/dbcparser.cpp
                               src/dev_kvaser.cpp
                               src/body_dbc_conf.cpp
                               src/thread_in_rx.cpp
                               src/dbc_test.cpp
                               src/mainWindow.cpp)

#7.add link library，添加可执行文件所需要的库，比如我们用到了libm.so（命名规则：lib+name+.so），就添加该库的名称
TARGET_LINK_LIBRARIES(${PROJECT_NAME} canlib pthread Qt5::Widgets Qt5::Core Qt5::Gui)
