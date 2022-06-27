#include "environment.hpp"

#include "console.hpp"

#include "../primitives/string.hpp"
#include "../primitives/boolean.hpp"

// todo: we should set 'version' variable to match our runtime' short ref

Environment::Environment() {
    this->m_name = (char*)"Environment";

    this->m_primitive = nullptr;
    this->set(
        (char*)"typeof",
        [](ArgumentsType args, bool) {
           Some* some =  args[0];
           switch(some->type()) {
           case OBJECT:
               switch(some->object()->type()) {
               case CASUAL_OBJ:
                   return (new StringPrimitive((char*)"object"))->some();
                   break;
               case STRING_OBJ:
                   return (new StringPrimitive((char*)"object"))->some();
                   break;
               case CALLABLE_OBJ:
                 return (new StringPrimitive((char*)"function"))->some();
                 break;
               case BOOLEAN_OBJ:
                   return (new StringPrimitive((char*)"object"))->some();
                   break;
               }
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
               case BOOLEAN:
                   return (new StringPrimitive((char*)"boolean"))->some();
                   break;
               }
           }
           return (new StringPrimitive((char*)"unreachable/bug"))->some();
        },
        true
    );
    this->set(
        (char*)"Object",
        [](ArgumentsType, bool $instantiation) {
            return (new Object())->some();
        },
        true
    );
    this->set(
        (char*)"String",
        [](ArgumentsType args, bool $instantiation) {
            if ($instantiation) {
                if (args.empty())
                    return (new String())->some();
                return (new String(args[0]->primitive()))->some();
            } else {
                if (args.empty())
                    return (new StringPrimitive())->some();
                return args[0]->primitive()->some();
            }
        },
        true
    );
    this->set(
        (char*)"Boolean",
        [](ArgumentsType args, bool $instantiation) {
            if ($instantiation) {
                if (args.empty())
                    return (new Boolean())->some();
                return (new Boolean(args[0]->primitive()))->some();
            } else {
                if (args.empty())
                    return (new BooleanPrimitive())->some();
                return args[0]->primitive()->some();
            }
        },
        true
    );

    this->set((char*)"console", new Console(), true);
    this->set((char*)"version", new StringPrimitive((char*)"v0.1"), true);
}
