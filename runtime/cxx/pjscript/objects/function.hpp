#pragma once

#include "object.hpp"

class Function: public Object {
protected:
    char* m_alias;
    NFunction m_handler;
public:
    Function(char* alias, NFunction handler);
    char* alias();
    NFunction handler();
};
