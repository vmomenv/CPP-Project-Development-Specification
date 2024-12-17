cmake_minimum_required(VERSION 2.8)

# 项目名称
project(1.2防止头文件重复包含)

# 包含当前目录的头文件
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 如果CMake版本低于3.16，添加调试信息
if(${CMAKE_MAJOR_VERSION} LESS 3 OR (${CMAKE_MAJOR_VERSION} EQUAL 3 AND ${CMAKE_MINOR_VERSION} LESS 16))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    message(STATUS "Adding -g to CXX_FLAGS because CMake is less than 3.16")
endif()

# 列出所有源文件
set(SOURCE_FILES
    main.cpp
    a.h
    a.cpp
    b.h
    b.cpp
    c.h
    c.cpp
    c.cpp
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 如果需要使用 C++11 或更高版本，启用 C++ 标准
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
)
