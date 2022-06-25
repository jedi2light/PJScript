#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "../primitives/primitive.hpp"

class Some;
class Object;

enum Type {  OBJECT, PRIMITIVE,
             FUNCTION, CONSTRUCTOR  };

typedef std::vector<Some*> ArgumentsType;
typedef std::function<Some*(ArgumentsType)> Function;
typedef std::function<Object*(ArgumentsType)> Constructor;

class Some {
protected:
    Type m_type;
    Object* m_object;
    Function m_function;
    Primitive* m_primitive;
    Constructor m_constructor;
    bool m_is_mutable { true };
public:
    Some(Object* object, bool is_mutable);
    Some(Function function, bool is_mutable);
    Some(Primitive* primitive, bool is_mutable);
    Some(Constructor constrtor, bool is_mutable);
    Type type();
    Object* object();
    Function function();
    Primitive* primitive();
    Constructor constructor();
    bool is_mutable();
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, Function function, bool is_mutable);
    void set(char* name, Primitive* primitive, bool is_mutable);
    void set(char* name, Constructor constructor, bool is_mutable);
    Some* get(char* name, bool check = true);
    char* raw();
    Some* some();
};

class Object {
protected:
    Primitive* m_primitive;
    std::unordered_map<char*, Some*> m_storage;
public:
    Object();
    Object(Primitive* object);
    std::unordered_map<char*, Some*> storage();
    void set(char* name, Some* some, bool is_mutable);
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, Function function, bool is_mutable);
    void set(char* nane, Primitive* primitive, bool is_mutable);
    void set(char* name, Constructor constructor, bool is_mutable);
    Some* get(char* name, bool check = true);
    Some* some();
};
