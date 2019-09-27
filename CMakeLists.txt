#使用cmake进行编译时，命令行所在文件目录为PROJECT_BINARY_DIR目标生成目录
#根CMakeList所在目录为PROJECT_SOURCE_DIR

# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.5)

# 项目信息，.sln的名称
project (SqliteClient)

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
add_definitions(-DWIN32)
ELSE()
add_definitions(-DLinux)
ENDIF()

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
set(CMAKE_CXX_FLAGS "-std=c++11 -g -m64 -fpermissive -w ${CMAKKE_CXX_FLAGS}")
ENDIF()

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
file(GLOB_RECURSE CURRENT_HEADERS ${PROJECT_SOURCE_DIR}/*.h)
source_group("Header Files" FILES ${CURRENT_HEADERS})

#include路径
include_directories(${PROJECT_SOURCE_DIR}/include)

#lib路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/bin)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
link_directories(/lib)
link_directories(/lib64)
link_directories(/usr/lib)
link_directories(/usr/lib64)
link_directories(/usr/local/lib)
link_directories(/usr/local/lib64)

#lib库
#link_libraries(pthread.so)
ELSE()
#link_libraries(odbc32.lib)
ENDIF()

#设置Debug|Release编译选项
set(CMAKE_BUILD_TYPE DEBUG)  
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)

# 指定生成目标，solutin下project名称，生成exe的名称
add_executable(SqliteClient ${DIR_SRCS} ${CURRENT_HEADERS})

