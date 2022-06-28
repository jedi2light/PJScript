#pragma once

#include "primitive.hpp"

#include "../objects/object.hpp"

class UndefinedPrimitive : public Primitive {
public:
    Object* to_object();
    UndefinedPrimitive();
    // this can not be initialized from char*
};
