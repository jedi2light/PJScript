#include <vector>

#include "boolean.hpp"

#include "../primitives/string.hpp"
#include "../primitives/boolean.hpp"

// todo:       implement something like StringPrototype class
//             , then move toString() method there, so we can
//             waste less memory and avoid 'code-duplication'

Boolean::Boolean() {
    this->m_type = BOOLEAN_OBJ;
    this->m_name = (char*)"Boolean";
    this->m_primitive = new BooleanPrimitive((char*)"false");

    this->set(
        (char*)"toString",
        [this](ArgumentsType args, bool) {
            return (new StringPrimitive(this->raw()))->some();
        },
        true
    );
}

Boolean::Boolean(Primitive* primitive) {
    this->m_type = BOOLEAN_OBJ;
    this->m_name = (char*)"Boolean";
    this->m_primitive = primitive;

    this->set(
        (char*)"toString",
        [this](ArgumentsType args, bool) {
           return (new StringPrimitive(this->raw()))->some();
        },
        true
    );
}

// todo: implement the rest of the JavaScript Boolean methods
