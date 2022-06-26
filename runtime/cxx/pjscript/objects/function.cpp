#include "function.hpp"

Function::Function(char* alias, NFunction handler) {
    this->m_type = FUNCTIONABLE_OBJ;
    this->m_name = (char*)"Function";
    this->m_alias = alias;
    this->m_handler = handler;
}

char* Function::alias() {
    return this->m_alias;
}

NFunction Function::handler() {
    return this->m_handler;
}
