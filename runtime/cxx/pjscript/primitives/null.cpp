#include "null.hpp"

Object* NullPrimitive::to_object() {
    return nullptr;
}

NullPrimitive::NullPrimitive() : Primitive((char*)"null") {
    this->m_raw = (char*)"null";
    this->m_type = NIL;
}
