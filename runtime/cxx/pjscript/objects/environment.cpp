#include "environment.hpp"

#include "console.hpp"

#include "../primitives/string.hpp"

// todo: we should set 'version' variable to match our runtime' short ref

Environment::Environment() {
    this->m_type = ENVIRONMENT_OBJ;
    this->m_name = (char*)"Environment";

    this->m_primitive = nullptr;
    this->set(
        (char*)"typeof",
        [](ArgumentsType args) {
           Some* some =  args[0];
           switch(some->type()) {
           case OBJECT:
               return (new StringPrimitive((char*)"object"))->some();
               break;
           case FUNCTION:
               return (new StringPrimitive((char*)"function"))->some();
               break;
           case PRIMITIVE:
               switch (some->primitive()->type()) {
               case NIL:
                   // although 'null' is the one of the 'primitive types'
                   // we need to return 'object' string due to js legacy?
                   return (new StringPrimitive((char*)"object"))->some();
                   break;
               case STRING:
                   return (new StringPrimitive((char*)"string"))->some();
                   break;
               }
               break;
           case CONSTRUCTOR:
               return (new StringPrimitive((char*)"constructor"))->some();
               break;
           }
           return (new StringPrimitive((char*)"unreachable/bug"))->some();
        },
        true
    );
    this->set(
        (char*)"Object",
        [](ArgumentsType) {
            return (new Object())->some();
        },
        true
    );
    this->set(
        (char*)"Object#constructor",
        [](ArgumentsType) { return new Object(); },
        true
    );
    this->set(
        (char*)"String",
        [](ArgumentsType args) {
            if (args.empty())
                return (new StringPrimitive())->some();
            return args[0]->primitive()->some();
        },
        true
    );
    this->set(
        (char*)"String#constructor",
        [](ArgumentsType args) {
            if (args.empty())
                return new String();
            return new String(args[0]->primitive());
        },
        true
    );
    this->set((char*)"console", new Console(), true);
    this->set((char*)"version", new StringPrimitive((char*)"v0.1"), true);
}
