#pragma once

#include "primitive.hpp"

#include "../objects/string.hpp"

class StringPrimitive : public Primitive {
public:
    String* to_object();
    StringPrimitive();
    StringPrimitive(char* raw); // has one
};
