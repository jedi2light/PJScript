#include "string.hpp"

String* StringPrimitive::to_object() {
    return new String(this);
}

StringPrimitive::StringPrimitive() : Primitive((char*)"") {
    this->m_raw = (char*)"";
    this->m_type = STRING;
}

StringPrimitive::StringPrimitive(char* raw) : Primitive((char*) raw) {
    this->m_raw = raw;
    this->m_type = STRING;
}
