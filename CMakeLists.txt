cmake_minimum_required(VERSION 3.14)
project(crow_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch Asio
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-28-0
)
FetchContent_MakeAvailable(asio)

# Создаём исполняемый файл
add_executable(crow_test main.cpp)

# Указываем include'ы: сначала Asio, потом crow_all.h
target_include_directories(crow_test PRIVATE
  ${asio_SOURCE_DIR}/asio/include
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

# Потоки
find_package(Threads REQUIRED)
target_link_libraries(crow_test PRIVATE Threads::Threads)