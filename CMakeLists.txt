cmake_minimum_required(VERSION 3.5)

project(biguint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(biguint main.cpp
    biguint.h biguint.cpp)

include(GNUInstallDirs)
install(TARGETS biguint
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
