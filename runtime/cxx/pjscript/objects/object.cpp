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
  m_object(new Object(function)), m_is_mutable(is_mutable), m_type(OBJECT) {}

Some::Some(Primitive* primitive, bool is_mutable) :
  m_primitive(primitive), m_is_mutable(is_mutable), m_type(PRIMITIVE) {}

Some::Some(NConstructor constructor, bool is_mutable) :
  m_object(new Object(constructor)), m_is_mutable(is_mutable), m_type(OBJECT) {}

VarType Some::type() {
    return this->m_type;
}

Object* Some::object() {
    return this->m_object;
}

NFunction Some::function() {
    if (this->m_object)
        return this->m_object->function();
    return nullptr;
}

Primitive* Some::primitive() {
    return this->m_primitive;
}

NConstructor Some::constructor() {
    if (this->m_object)
        return this->m_object->constructor();
    return nullptr;
}

bool Some::is_mutable() {
    return this->m_is_mutable;
}

bool exists_and_mutable(Some* some) {
    return some && some->is_mutable();
}

Some* check(Object* object, char* name) {
    return object->get(name, true);
}

bool available(char* name, Object* object) {
    Some* existing = check(object, name);
    return exists_and_mutable(existing) || !existing;
}

void Some::set(char* name, Some* some, bool is_mutable) {
    if (this->m_type == OBJECT
            && available(name, this->m_object))
        this->m_object->set(name, some, is_mutable);
}

void Some::set(char* name, Object* object, bool is_mutable) {
    if (this->m_type == OBJECT
            && available(name, this->m_object))
        this->m_object->set(name, object, is_mutable);
}

void Some::set(char* name, NFunction function, bool is_mutable) {
    if (this->m_type == OBJECT
            && available(name, this->m_object))
        this->m_object->set(name, function, is_mutable);
}

void Some::set(char* name, Primitive* primitive, bool is_mutable) {
    if (this->m_type == OBJECT
            && available(name, this->m_object))
        this->m_object->set(name, primitive, is_mutable);
}

void Some::set(char* name, NConstructor constructor, bool is_mutable) {
    if (this->m_type == OBJECT
            && available(name, this->m_object))
        this->m_object->set(name, constructor, is_mutable);
}

Some* Some::get(char* name, bool check) {
    switch(this->m_type) {
    case OBJECT:
        return this->m_object->get(name); break;
    case PRIMITIVE:
        return this->m_primitive->to_object()->get(name); break;
    }
    return UNREACHABLE_NULLPTR;  // this is to suppress clang++ warning
}

std::string object_to_string(Object* object) {
    // if an 'object' is callable, return: "[Function: <object alias>]"
    if (object->type() == CALLABLE_OBJ) {
        std::string msg = "[Function: ";
        msg += object->alias();
        msg += "]";
        return msg;
    }
    // if an 'object' has been initialized from one of 'primitive' type
    if (object->primitive()) {
        std::string msg = "[";
        msg += object->name();
        msg += ": ";
        // if 'object' is a type of 'String' wrap its value in 'quotes'
        if (object->type() == STRING_OBJ) {
            msg += "'";
            msg += object->primitive()->raw();
            msg += "'";
        // in all other cases, just append underlying primitive 'raw()'
        } else {
            msg += object->primitive()->raw();
        }
        msg += "]";
        return msg; // return this message; do not iterate over props()
    }
    const auto& props = object->props();
    // if object has no any single property there's no sense to iterate
    if (props.empty())
        return "{}";
    // first, start with the 'curly-brace' following by a 'white-space'
    std::string msg;
    std::string str = "{ ";
    int circularefcount = 0; // count 'circular referencing' properties
    for (auto it = props.begin(); it != props.end(); ++it) {
        str += std::move(it->first);
        str += std::move(": ");
        // detect when 'object' property's referencing its own 'object'
        if (it->second->type() == OBJECT
                && it->second->object() == object) {
            str += std::move("[Circular *");
            str += std::move(std::to_string(++circularefcount));
            str += std::move("]");
        }
        // wrap string primitives in the single-quotes, that is fancier
        else if (it->second->type() == PRIMITIVE &&
                it->second->primitive()->type() == STRING) {
            str += std::move("'");
            str += std::move(it->second->raw());
            str += std::move("'");
        } else {
            str += std::move(it->second->raw());
        }
        // separate key-values by a coma character, 'cause it's fancier
        if (std::distance(it, props.end()) != 1) {
            str += std::move(", ");
        }
    }
    // and we end with a white-space following by a closing curly-brace
    str += std::move(" }");
    // prepend this, if we've encountered at least 1 circular reference
    for (int i = 0; i < circularefcount; ++i)
        msg += "<ref *" + std::to_string(++i) + "> "; // todo: improve?
    msg += std::move(str);
    return msg;  // 'msg' needs to be further converted to char* (btw).
}

char* Some::raw() {
    switch (this->m_type) {
    case OBJECT:
        return strdup(object_to_string(this->m_object).c_str()); break;
    case PRIMITIVE:
        return this->m_primitive->raw(); break;  // or just return raw;
    }
    return UNREACHABLE;  // that is, we remove clang++ compiler warning
}

Some* Some::some() {
    return this; // jsut a tiny, small proxy function, but it is useful
}

Object::Object() : m_primitive(nullptr){}

Object::Object(NFunction function) : m_function(function){}

Object::Object(Primitive* primitive) : m_primitive(primitive){}

Object::Object(NConstructor constructor) : m_constructor(constructor){}

char* Object::name() {
    return this->m_name;
}

char* Object::alias() {
    return this->m_alias;
}

ObjType Object::type() {
    return this->m_type;
}

NFunction Object::function() {
    return this->m_function;
}

Primitive* Object::primitive() {
    return this->m_primitive;
}

NConstructor Object::constructor() {
    return this->m_constructor;
}

void Object::setType(ObjType type) {
    this->m_type = type;
}

void Object::setAlias(char* alias) {
    this->m_alias = alias;
}

std::unordered_map<char*, Some*> Object::props() {
    return this->m_props;
}

void Object::set(char* name, Object* object, bool is_mutable) {
    if (object) {
        object->setAlias(name);
        this->m_props.insert({name, new Some(object, is_mutable)});
    }
}

void Object::set(char* name, NFunction function, bool is_mutable) {
    if (function) {
        Object* fn_object = new Object(function);
        fn_object->setType(CALLABLE_OBJ);
        fn_object->setAlias(name);
        this->m_props.insert({name, new Some(fn_object, is_mutable)});
    }
}

void Object::set(char* name, Primitive* primitive, bool is_mutable) {
    if (primitive) {
        this->m_props.insert({name, new Some(primitive, is_mutable)});
    }
}

void Object::set(char* name, NConstructor constructor, bool is_mutable) {
    if (constructor) {
        Object* cs_object = new Object(constructor);
        cs_object->setType(CALLABLE_OBJ);
        cs_object->setAlias(name);
        this->m_props.insert({name, new Some(cs_object, is_mutable)});
    }
}

void Object::set(char* name, Some* some, bool is_mutable) {
    switch (some->type()) {
    case OBJECT:
        this->m_props.insert({ name, new Some(some->object(), is_mutable) });
        break;
    case PRIMITIVE:
        this->m_props.insert({ name, new Some(some->primitive(), is_mutable) });
        break;
    }
}

Some* Object::get(char* name, bool check) {
    // we use strcmp() and manually iterate, because find() method is unreliable
    for (auto itr = this->m_props.begin(); itr != this->m_props.end(); ++itr) {
        if (!strcmp(itr->first, name)) {
            return itr->second;
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

char* Object::raw() {
    if (this->m_primitive)
        return this->m_primitive->raw();
    return nullptr;  // if object wasn't based on a primitive type, return NULL;
}

Some* Object::some() {
    return new Some(this, true); // this is a small proxy method, but its useful
}
