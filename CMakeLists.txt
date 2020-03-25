cmake_minimum_required(VERSION 3.13)
project(net_Slim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/nodes.cpp
        src/helpers.cpp
        src/factory.cpp
        )


add_executable(main__debug ${SOURCE_FILES} main.cpp)

set(SOURCES_FILES_TESTS
        test/test_package.cpp
        test/test_storage_types.cpp
        test/test_nodes.cpp include/factory.hpp src/factory.cpp
        test_final/test_package.cpp
        test_final/test_storage_types.cpp
#        test_final/test_nodes.cpp
        test_final/test_Factory.cpp
#        test_final/test_factory_io.cpp
        )

add_executable(main__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

target_include_directories(main__test PUBLIC
        ../googletest-master/googlemock/include
        ../googletest-master/googletest/include
        )

add_subdirectory(../googletest-master googletest-master)


target_link_libraries(main__test gmock)