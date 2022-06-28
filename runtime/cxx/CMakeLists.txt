cmake_minimum_required(VERSION 3.20.0)

project(PJScript VERSION 1.0.0
                 DESCRIPTION "PJScript C++ Runtime")

add_library(PJScriptShared SHARED pjscript/objects/object.hpp
                                  pjscript/objects/object.cpp
                                  pjscript/objects/console.hpp
                                  pjscript/objects/console.cpp
                                  pjscript/objects/environment.hpp
                                  pjscript/objects/environment.cpp
                                  pjscript/objects/string.hpp
                                  pjscript/objects/string.cpp
                                  pjscript/objects/boolean.hpp
                                  pjscript/objects/boolean.cpp
                                  pjscript/primitives/primitive.hpp
                                  pjscript/primitives/primitive.cpp
                                  pjscript/primitives/undefined.hpp
                                  pjscript/primitives/undefined.cpp
                                  pjscript/primitives/null.hpp
                                  pjscript/primitives/null.cpp
                                  pjscript/primitives/string.hpp
                                  pjscript/primitives/string.cpp
                                  pjscript/primitives/boolean.cpp
                                  pjscript/primitives/boolean.hpp
                                  pjscript.hpp
                                  pjscript.cpp)

add_library(PJScriptStatic STATIC pjscript/objects/object.hpp
                                  pjscript/objects/object.cpp
                                  pjscript/objects/console.hpp
                                  pjscript/objects/console.cpp
                                  pjscript/objects/environment.hpp
                                  pjscript/objects/environment.cpp
                                  pjscript/objects/string.hpp
                                  pjscript/objects/string.cpp
                                  pjscript/primitives/primitive.hpp
                                  pjscript/primitives/primitive.cpp
                                  pjscript/primitives/undefined.hpp
                                  pjscript/primitives/undefined.cpp
                                  pjscript/primitives/null.hpp
                                  pjscript/primitives/null.cpp
                                  pjscript/primitives/string.hpp
                                  pjscript/primitives/string.cpp
                                  pjscript/primitives/boolean.cpp
                                  pjscript/primitives/boolean.hpp
                                  pjscript.hpp
                                  pjscript.cpp)

set_property(TARGET PJScriptShared PROPERTY CXX_STANDARD 20)
set_property(TARGET PJScriptStatic PROPERTY CXX_STANDARD 20)

set_target_properties(PJScriptShared PROPERTIES OUTPUT_NAME pjscript)
set_target_properties(PJScriptStatic PROPERTIES OUTPUT_NAME pjscript)

set_target_properties(PJScriptShared PROPERTIES PUBLIC_HEADER pjscript.hpp)
set_target_properties(PJScriptStatic PROPERTIES PUBLIC_HEADER pjscript.hpp)

include(GNUInstallDirs)

install(TARGETS PJScriptShared LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                               PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS PJScriptStatic LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                               PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
