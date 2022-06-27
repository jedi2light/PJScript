#pragma once

#include "primitive.hpp"

#include "../objects/boolean.hpp"

class BooleanPrimitive : public Primitive {
public:
    Boolean* to_object();
    BooleanPrimitive();
    BooleanPrimitive(char* raw); // has one
};
