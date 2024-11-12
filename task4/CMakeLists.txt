cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0074 NEW)
project(lab3_task4)

enable_testing()

find_package(verilator HINTS $ENV{VERILATOR_ROOT} ${VERILATOR_ROOT})

if (NOT verilator_FOUND)
    message(FATAL_ERROR "Verilator not found!")
endif ()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(f1 ./verify.cpp)
target_compile_features(f1 PRIVATE cxx_std_17)

include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(f1 PRIVATE GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(f1)

verilate(f1 #TRACE
        VERILATOR_ARGS -Wall
        --make cmake
#        -CFLAGS "-isystem /opt/homebrew/Cellar/googletest/1.15.2/include"
#        -LDFLAGS "-L/opt/homebrew/Cellar/googletest/1.15.2/lib -lgtest -lgtest_main -lpthread"
        SOURCES ./top.sv
        #        --prefix Vdut # we use Vtop in TB, so keep this in tests
)
