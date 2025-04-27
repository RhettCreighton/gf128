cmake_minimum_required(VERSION 3.5)
project(gf128_tests C)

add_executable(test_gf128 test_gf128.c)
target_link_libraries(test_gf128 PRIVATE gf128)
add_test(NAME test_gf128 COMMAND test_gf128)