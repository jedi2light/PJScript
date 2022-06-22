cmake_minimum_required(VERSION 3.20.0)

project(pjscript VERSION 1.0.0
                 DESCRIPTION "PJScript C++ Runtime")

add_library(pjscript SHARED pjscript/console.cpp
                            pjscript/console.hpp
                            pjscript/environment.cpp
                            pjscript/environment.hpp
                            pjscript/nullvalue.cpp
                            pjscript/nullvalue.hpp
                            pjscript/objectvalue.cpp
                            pjscript/objectvalue.hpp
                            pjscript/stringvalue.cpp
                            pjscript/stringvalue.hpp
                            pjscript/value.cpp
                            pjscript/value.hpp
                            pjscript.hpp)

set_property(TARGET pjscript PROPERTY CXX_STANDARD 20)

set_target_properties(pjscript PROPERTIES
                               PUBLIC_HEADER pjscript.hpp)

include(GNUInstallDirs)

install(TARGETS pjscript
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
