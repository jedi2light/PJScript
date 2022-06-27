#pragma once

#include "primitive.hpp"

#include "../objects/object.hpp"

class NullPrimitive : public Primitive {
public:
    Object* to_object();
    NullPrimitive();
    // can not be initialized from char*
};
