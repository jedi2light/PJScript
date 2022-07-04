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

VarType Some::type() {
    return this->m_type;
}

Object* Some::object() {
    return this->m_object;
}

Primitive* Some::primitive() {
    return this->m_primitive;
}

bool Some::is_mutable() {
    return this->m_is_mutable;
}

Some* Some::operator() (ArgsType args, bool $is_instantiation) {
    if (this->m_object)
        return this->m_object->operator()(args, $is_instantiation);
    return nullptr;
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

Some* Some::get(char* name, bool check) {
    switch(this->m_type) {
    case OBJECT:
        return this->m_object->get(name); break;
    case PRIMITIVE:
        return this->m_primitive->to_object()->get(name); break;
    }
    return UNREACHABLE_NULLPTR;  // this is to suppress clang++ warning
}

void Some::del(char* name) {
    if (this->m_object)
        this->m_object->del(name); // delete an object propetry by name
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
            msg += object->raw();  // use raw() instead of view() there
            msg += "'";
        // in all other cases, just append underlying primitive 'raw()'
        } else {
            msg += object->raw();  // use raw() instead of view() there
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
    std::string str;
    if (object->alias()) {
        str += object->alias(); // prepend object alias (if it has one)
        str += " "; // separate starting curly-brace with a white-space
    }
    str += "{ ";
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
            str += std::move(it->second->view());  // view() the object
            str += std::move("'");
        } else {
            str += std::move(it->second->view());  // view() the object
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
        return this->m_object->raw(); break;
    case PRIMITIVE:
        return this->m_primitive->raw(); break;
    }
    return UNREACHABLE;  // that is, we remove clang++ compiler warning
}

char* Some::view() {
    switch(this->m_type) {
    case OBJECT:
        return this->m_object->view(); break;
    case PRIMITIVE:
        return this->m_primitive->raw(); break;  // use primitive raw()
    }
    return UNREACHABLE;  // that is, we remove clang++ compiler warning
}

Some* Some::some() {
    return this; // jsut a tiny, small proxy function, but it is useful
}

Object::Object() {}

Object::Object(NFunction function) : m_function(function) {}

Object::Object(Primitive* primitive) : m_primitive(primitive) {}

char* Object::name() {
    return this->m_name;
}

char* Object::alias() {
    return this->m_alias;
}

ObjType Object::type() {
    return this->m_type;
}

Object* Object::called() {
    return this->m_called;
}

void Object::flushCalled() {
    this->m_called = nullptr;
}

void Object::setCalled(Object* called) {
    this->m_called = called;
}

void Object::setParent(Object* parent) {
    this->m_parent = parent;
}

void Object::setType(ObjType type) {
    this->m_type = type;
}

void Object::setAlias(char* alias) {
    this->m_alias = alias;
}

Primitive* Object::primitive() {
    return this->m_primitive;
}

std::unordered_map<char*, Some*> Object::props() {
    return this->m_props;
}

Some* Object::operator() (ArgsType args, bool $is_instantiation) {
    this->m_parent->setCalled(this); // set a function just called
    Some* retval = this->m_function(args, $is_instantiation);
    this->m_parent->flushCalled(); // flush called() function slot
    return retval; // return a called function retruned value back
}

void groom_object(Object* object, ObjType type, char* name) {
    object->setType(type);
    object->setAlias(name);
}

void Object::set(char* name, Object* object, bool is_mutable) {
    if (object) {
        groom_object(object, CASUAL_OBJ, name);
        this->m_props.insert({name, new Some(object, is_mutable)});
    }
}

void Object::set(char* name, NFunction function, bool is_mutable) {
    if (function) {
        Object* object = new Object(function);
        object->setParent(this); // set parent (only for functions)
        groom_object(object, CALLABLE_OBJ, name);
        this->m_props.insert({name, new Some(object, is_mutable)});
    }
}

void Object::set(char* name, Primitive* primitive, bool is_mutable) {
    if (primitive) {
        this->m_props.insert({name, new Some(primitive, is_mutable)});
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

void Object::del(char* name) {
    this->m_props.erase(name); // delete an arbitary object property by its name
}

char* Object::raw() {
    if (this->m_primitive)
        return this->m_primitive->raw();
    return nullptr;  // if object wasn't based on a primitive type, return NULL;
}

char* Object::view() {
    return strdup(object_to_string(this).c_str()); // view an object as a string
}

Some* Object::some() {
    return new Some(this, true); // this is a small proxy method, but its useful
}
