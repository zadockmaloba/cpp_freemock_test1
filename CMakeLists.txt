cmake_minimum_required(VERSION 3.5)

project(cpp_freemock_test1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp_freemock_test1
    main.cpp
    googletest/googletest/src/gtest-all.cc
    googletest/googlemock/src/gmock-all.cc
)

target_include_directories(cpp_freemock_test1
    PRIVATE
    ${CMAKE_SOURCE_DIR}/googletest/googletest
    ${CMAKE_SOURCE_DIR}/googletest/googletest/include
    ${CMAKE_SOURCE_DIR}/googletest/googlemock
    ${CMAKE_SOURCE_DIR}/googletest/googlemock/include
    ${CMAKE_SOURCE_DIR}/CppFreeMock
)

include(GNUInstallDirs)
install(TARGETS cpp_freemock_test1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
