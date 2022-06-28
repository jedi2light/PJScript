#include "undefined.hpp"

Object* UndefinedPrimitive::to_object() {
    return nullptr;
}

UndefinedPrimitive::UndefinedPrimitive() : Primitive((char*)"undefined") {
    this->m_raw = (char*)"undefined";
    this->m_type = UNDEFINED;
}
