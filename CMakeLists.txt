cmake_minimum_required(VERSION 3.14)
project(coro_demo)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${PROJECT_SOURCE_DIR}/thirdparty/libgo
        ${PROJECT_SOURCE_DIR}
)
link_directories(
        ${PROJECT_SOURCE_DIR}/thirdparty/libgo/build
)

add_executable(coro_demo main.cpp)
target_link_libraries(coro_demo libgo pthread)
