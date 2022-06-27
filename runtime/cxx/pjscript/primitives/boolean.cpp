#include "boolean.hpp"

Boolean* BooleanPrimitive::to_object() {
    return new Boolean(this);
}

BooleanPrimitive::BooleanPrimitive() : Primitive((char*)"false") {
    this->m_raw = (char*)"false";
    this->m_type = BOOLEAN;
}

BooleanPrimitive::BooleanPrimitive(char* raw) : Primitive((char*) raw) {
    this->m_raw = raw;
    this->m_type = BOOLEAN;
}

