cmake_minimum_required(VERSION 3.16)

project(Codigo-desafio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Codigo-desafio main.cpp
    datos.h datos.cpp)

include(GNUInstallDirs)
install(TARGETS Codigo-desafio
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
