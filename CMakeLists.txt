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

add_executable(crow_test main.cpp)

target_include_directories(crow_test PRIVATE
  ${asio_SOURCE_DIR}/asio/include
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party  
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)
target_link_libraries(crow_test PRIVATE Threads::Threads)

file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

target_sources(crow_test PRIVATE
  src/telemetry/TelemetryStorage.cpp
  src/telemetry/TelemetryService.cpp
  src/telemetry/APIController.cpp  
  ${PROJECT_HEADERS}
)
