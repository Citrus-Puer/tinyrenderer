cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(tinyrenderer VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)

# 查找 Eigen 库
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# 设置源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# 可执行文件
add_executable(main ${SOURCES} ${HEADERS})

# 链接 Eigen 库
target_link_libraries(main Eigen3::Eigen)

# 打印消息以确认 Eigen 库的路径
message(STATUS "Eigen3 include dir: ${EIGEN3_INCLUDE_DIR}")
