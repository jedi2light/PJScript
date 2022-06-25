#pragma once

#include "object.hpp"

class String : public Object {
public:
    String();
    String(Primitive*);
};
