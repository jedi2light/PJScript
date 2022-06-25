#include <iostream>

#include <string.h>
#include <assert.h>

#include "object.hpp"

Some::Some(Object* object, bool is_mutable) :
    m_object(object), m_is_mutable(is_mutable), m_type(OBJECT) {}

Some::Some(Function function, bool is_mutable) :
    m_function(function), m_is_mutable(is_mutable), m_type(FUNCTION) {}

Some::Some(Primitive* primitive, bool is_mutable) :
    m_primitive(primitive), m_is_mutable(is_mutable), m_type(PRIMITIVE) {}

Some::Some(Constructor constructor, bool is_mutable) :
    m_constructor(constructor), m_is_mutable(is_mutable), m_type(CONSTRUCTOR) {}

Type Some::type() {
    return this->m_type;
}

Object* Some::object() {
    return this->m_object;
}

Function Some::function() {
    return this->m_function;
}

Primitive* Some::primitive() {
    return this->m_primitive;
}

Constructor Some::constructor() {
    return this->m_constructor;
}

bool Some::is_mutable() {
    return this->m_is_mutable;
}

bool exists_and_mutable(Some* some) {
    return some && some->is_mutable();
}

void Some::set(char* name, Object* object, bool is_mutable) {
    if (this->m_type == OBJECT) {
        Some* existing = this->m_object->get(name, false);
        if (exists_and_mutable(existing) || !existing) {
            this->m_object->set(name, object, is_mutable);
        }
    }
}

void Some::set(char* name, Function function, bool is_mutable) {
    if (this->m_type == OBJECT) {
        Some* existing = this->m_object->get(name, false);
        if (exists_and_mutable(existing) || !existing) {
            this->m_object->set(name, function, is_mutable);
        }
    }
}

void Some::set(char* name, Primitive* primitive, bool is_mutable) {
    if (this->m_type == OBJECT) {
        Some* existing = this->m_object->get(name, false);
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
}

char* Some::raw() {
    switch (this->m_type) {
    case OBJECT:
        // todo: need to figure out how to display 'object' name
        return (char*)"[Object]"; break;
    case FUNCTION:
        // todo: need to implement somehting like FunctionObject
        return (char*)"[Function]"; break;
    case PRIMITIVE:
        return this->m_primitive->raw(); break;
    case CONSTRUCTOR:
        // todo: need to implement something like FunctionObject
        return (char*)"[Constructor]"; break;
    }
}

Some* Some::some() {
    return this; // jsut a small proxy function, but it's useful
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

void Object::set(char* name, Function function, bool is_mutable) {
    if (function)
        this->m_storage.insert({name, new Some(function, is_mutable)});
}

void Object::set(char* name, Primitive* primitive, bool is_mutable) {
    if (primitive)
        this->m_storage.insert({name, new Some(primitive, is_mutable)});
}

void Object::set(char* name, Constructor constructor, bool is_mutable) {
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
    if (check) {
        std::cout << "ReferenceError: "
                  << name << " is not defined" << std::endl; // print and exit()
        exit(1);
    }
    return nullptr;  // if we didn't find anything matching 'name', return NULL;
}

Some* Object::some() {
    return new Some(this, true); // this is a small proxy method, but its useful
}
