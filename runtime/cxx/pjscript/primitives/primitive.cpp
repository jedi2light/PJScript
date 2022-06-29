#include "primitive.hpp"

#include "../objects/object.hpp"

#include <iostream>

Primitive::Primitive(char* raw) {
    this->m_raw = raw;
}

char* Primitive::raw() {
    return this->m_raw;
}

Some* Primitive::some() {
    return new Some(this, true);
}

PrimitiveType Primitive::type() {
    return this->m_type;
}
