#pragma once

#include "object.hpp"

class Constructor: public Object {
protected:
    char* m_alias;
    NConstructor m_handler;
public:
    Constructor(char* alias, NConstructor handler);
    char* alias();
    NConstructor handler();
};
