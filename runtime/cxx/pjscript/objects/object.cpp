#include <utility>
#include <iostream>

#include <string.h>
#include <assert.h>

#include "object.hpp"

#define UNREACHABLE_NULLPTR nullptr;
#define UNREACHABLE (char*)"(uncreachable)"

Some::Some(Object* object, bool is_mutable) :
    m_object(object), m_is_mutable(is_mutable), m_type(OBJECT) {}

Some::Some(NFunction function, bool is_mutable) :
    m_nfunction(function), m_is_mutable(is_mutable), m_type(FUNCTION) {}

Some::Some(Primitive* primitive, bool is_mutable) :
    m_primitive(primitive), m_is_mutable(is_mutable), m_type(PRIMITIVE) {}

Some::Some(NConstructor constructor, bool is_mutable) :
    m_nconstructor(constructor), m_is_mutable(is_mutable), m_type(CONSTRUCTOR) {}

Type Some::type() {
    return this->m_type;
}

Object* Some::object() {
    return this->m_object;
}

NFunction Some::function() {
    return this->m_nfunction;
}

Primitive* Some::primitive() {
    return this->m_primitive;
}

NConstructor Some::constructor() {
    return this->m_nconstructor;
}

bool Some::is_mutable() {
    return this->m_is_mutable;
}

bool exists_and_mutable(Some* some) {
    return some && some->is_mutable();
}

void Some::set(char* name, Some* some, bool is_mutable) {
    if (this->m_type == OBJECT) {
        Some* existing = this->m_object->get(name, true);
        if (exists_and_mutable(existing) || !existing) {
            this->m_object->set(name, some, is_mutable);
        }
    }
}

void Some::set(char* name, Object* object, bool is_mutable) {
    if (this->m_type == OBJECT) {
        Some* existing = this->m_object->get(name, true);
        if (exists_and_mutable(existing) || !existing) {
            this->m_object->set(name, object, is_mutable);
        }
    }
}

void Some::set(char* name, NFunction function, bool is_mutable) {
    if (this->m_type == OBJECT) {
        Some* existing = this->m_object->get(name, true);
        if (exists_and_mutable(existing) || !existing) {
            this->m_object->set(name, function, is_mutable);
        }
    }
}

void Some::set(char* name, Primitive* primitive, bool is_mutable) {
    if (this->m_type == OBJECT) {
        Some* existing = this->m_object->get(name, true);
        if (exists_and_mutable(existing) || !existing) {
            this->m_object->set(name, primitive, is_mutable);
        }
    }
}

Some* Some::get(char* name, bool check) {
    switch(this->m_type) {
    case OBJECT:
        return this->m_object->get(name); break;
    case FUNCTION:
        // todo: need to implement something like FunctionObject
        return nullptr; break;
    case PRIMITIVE:
        return this->m_primitive->to_object()->get(name); break;
    case CONSTRUCTOR:
        // todo: need to implement something like FunctionObject
        return nullptr; break;
    }
    return UNREACHABLE_NULLPTR;  // it removes 'clang++' warning
}

std::string strobject(Object* object) {
    // if an 'object' has been initialized from a primitive type
    if (object->primitive()) {
        std::string msg = "[";
        msg += object->name();
        msg += ": ";
        // if 'object' is a type of String, wrap value in quotes
        if (object->type() == STRING_OBJ) {
            msg += "'";
            msg += object->primitive()->raw();
            msg += "'";
        } else {
            msg += object->primitive()->raw();
        }
        msg += "]";
        return msg; // return this message; do not iterate props
    }
    const auto& storage = object->storage();
    // there's no sence to iterate over pairs, if object's empty
    if (storage.empty())
        return "{}";
    // start with the 'curly-brace' following by a 'white-space'
    std::string msg;
    std::string str = "{ ";
    int circularefcount = 0; // count circular referencing props
    for (auto it = storage.begin(); it != storage.end(); ++it) {
        str += std::move(it->first);
        str += std::move(": ");
        // detect when object property referencing to its object
        if (it->second->type() == OBJECT
                && it->second->object() == object) {
            str += std::move("[Circular *");
            str += std::move(std::to_string(++circularefcount));
            str += std::move("]");
        }
        // wrap string primitives in single-quotes, it's fancier
        else if (it->second->type() == PRIMITIVE &&
                it->second->primitive()->type() == STRING) {
            str += std::move("'");
            str += std::move(it->second->raw());
            str += std::move("'");
        } else {
            str += std::move(it->second->raw());
        }
        // separate key-values by a coma character, it's fancier
        if (std::distance(it, storage.end()) != 1) {
            str += std::move(", ");
        }
    }
    // end with a white-space following by a closing curly-brace
    str += std::move(" }");
    // prepend this if we have encountered at least one circular
    for (int i = 0; i < circularefcount; ++i)
        msg += "<ref *" + std::to_string(++i) + "> "; // improve
    msg += std::move(str);
    return msg;  // 'str' needs to be further converted to char*
}

char* Some::raw() {
    switch (this->m_type) {
    case OBJECT:
        return strdup(strobject(this->m_object).c_str()); break;
    case FUNCTION:
        // todo: need to implement somehting like FunctionObject
        return (char*)"[Function]"; break;
    case PRIMITIVE:
        return this->m_primitive->raw(); break;
    case CONSTRUCTOR:
        // todo: need to implement something like FunctionObject
        return (char*)"[Constructor]"; break;
    }
    return UNREACHABLE;  // this should remove 'clang++' warning
}

Some* Some::some() {
    return this; // jsut a small proxy function, but it's useful
}

char* Object::name() {
    return this->m_name;
}

ObjType Object::type() {
    return this->m_type;
}

Primitive* Object::primitive() {
    return this->m_primitive;
}

Object::Object() : m_primitive(nullptr) {}

Object::Object(Primitive* primitive) : m_primitive(primitive) {}

std::unordered_map<char*, Some*> Object::storage() {
    return this->m_storage;
}

void Object::set(char* name, Object* object, bool is_mutable) {
    if (object)
        this->m_storage.insert({name, new Some(object, is_mutable)});
}

void Object::set(char* name, NFunction function, bool is_mutable) {
    if (function)
        this->m_storage.insert({name, new Some(function, is_mutable)});
}

void Object::set(char* name, Primitive* primitive, bool is_mutable) {
    if (primitive)
        this->m_storage.insert({name, new Some(primitive, is_mutable)});
}

void Object::set(char* name, NConstructor constructor, bool is_mutable) {
    if (constructor)
        this->m_storage.insert({name, new Some(constructor, is_mutable)});
}

void Object::set(char* name, Some* some, bool is_mutable) {
    switch (some->type()) {
    case OBJECT:
        this->m_storage.insert({name,
                                new Some(some->object(), is_mutable)});
        break;
    case FUNCTION:
        this->m_storage.insert({name,
                                new Some(some->function(), is_mutable)});
        break;
    case PRIMITIVE:
        this->m_storage.insert({name,
                                new Some(some->primitive(), is_mutable)});
        break;
    case CONSTRUCTOR:
        this->m_storage.insert({name,
                                new Some(some->constructor(), is_mutable)});
        break;
    }
}

Some* Object::get(char* name, bool check) {
    // we use strcmp() and manually iterate, because find() method is unreliable
    for (auto it = this->m_storage.begin(); it != this->m_storage.end(); ++it) {
        if (!strcmp(it->first, name)) {
            return it->second;
        }
    }
    // todo: we need to implement something like 'source-map' to show exact span
    if (!check) {
        std::cout << "ReferenceError: "
                  << name << " is not defined" << std::endl; // print and exit()
        exit(1);
    }
    return nullptr;  // if we didn't find anything matching 'name', return NULL;
}

Some* Object::some() {
    return new Some(this, true); // this is a small proxy method, but its useful
}
