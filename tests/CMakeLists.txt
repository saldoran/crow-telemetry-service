cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
  test_storage.cpp
  test_service.cpp
  ../src/telemetry/TelemetryStorage.cpp
  ../src/telemetry/TelemetryService.cpp
)

target_include_directories(tests PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)
target_link_libraries(tests
  PRIVATE
    gtest_main
    Threads::Threads
)

add_test(NAME all_tests COMMAND tests)