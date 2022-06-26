#include "constructor.hpp"

Constructor::Constructor(char* alias, NConstructor handler) {
    this->m_type = FUNCTIONABLE_OBJ;
    this->m_name = (char*)"Function";
    this->m_alias = alias;
    this->m_handler = handler;
}

char* Constructor::alias() {
    return this->m_alias;
}

NConstructor Constructor::handler() {
    return this->m_handler;
}
