cmake_minimum_required(VERSION 3.18.0)
project(experimental_c_api)


add_library(public_api INTERFACE)
target_include_directories(public_api INTERFACE include)

add_library(internal_lib src/internal.hpp src/public_api_impl.cpp)
target_compile_features(internal_lib PUBLIC cxx_std_20)
target_link_libraries(internal_lib PUBLIC public_api)

add_library(user_lib SHARED tests/user_lib.c tests/user_lib.h)
target_link_libraries(user_lib internal_lib)

add_executable(user_app tests/user_app.c)
target_link_libraries(user_app user_lib)