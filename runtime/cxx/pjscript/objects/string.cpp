#include <vector>

#include "string.hpp"

#include "../primitives/string.hpp"

// todo: implement something like StringPrototype class
//       , then move toString() method there, so we can
//       waste less memory and avoid 'code-duplication'

String::String() {
    this->m_type = STRING_OBJ;
    this->m_name = (char*)"String";
    this->m_primitive = new StringPrimitive((char*)"");

    this->set(
     (char*)"toString",
     [this](ArgumentsType args, bool) {
     return (new StringPrimitive(this->raw()))->some();
     },
     true
    );
}

String::String(Primitive* primitive) {
    this->m_type = STRING_OBJ;
    this->m_name = (char*)"String";
    this->m_primitive = primitive;

    this->set(
     (char*)"toString",
     [this](ArgumentsType args, bool) {
     return (new StringPrimitive(this->raw()))->some();
     },
     true
    );
}

// todo: implement the rest of JavaScriptString methods
