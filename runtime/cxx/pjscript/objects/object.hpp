#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "../primitives/primitive.hpp"

class Some;
class Object;

enum VarType { OBJECT,       PRIMITIVE };
enum ObjType { CASUAL_OBJ,   STRING_OBJ,
               CALLABLE_OBJ, BOOLEAN_OBJ };

typedef std::vector<Some*> ArgumentsType;
typedef std::function<Some*(ArgumentsType)> NFunction;
typedef std::function<Object*(ArgumentsType)> NConstructor;

class Some {
protected:
    VarType m_type;
    Object* m_object;
    Primitive* m_primitive;
    bool m_is_mutable { true };
public:
    Some(Object* object, bool is_mutable);
    Some(NFunction function, bool is_mutable);
    Some(Primitive* primitive, bool is_mutable);
    Some(NConstructor constructor, bool is_mutable);
    VarType type();
    Object* object();
    NFunction function();
    Primitive* primitive();
    NConstructor constructor();
    bool is_mutable();
    void set(char* name, Some* some, bool is_mutable);
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, NFunction function, bool is_mutable);
    void set(char* name, Primitive* primitive, bool is_mutable);
    void set(char* name, NConstructor constructor, bool is_mutable);
    Some* get(char* name, bool check = false);
    char* raw();
    Some* some();
};

class Object {
protected:
    char* m_name;
    char* m_alias;
    ObjType m_type;
    NFunction m_function;
    Primitive* m_primitive;
    NConstructor m_constructor;
    std::unordered_map<char*, Some*> m_props;
public:
    Object();
    Object(NFunction);
    Object(Primitive*);
    Object(NConstructor);
    char* name();
    char* alias();
    ObjType type();
    NFunction function();
    Primitive* primitive();
    NConstructor constructor();
    void setType(ObjType type);
    void setAlias(char* alias);
    std::unordered_map<char*, Some*> props();
    void set(char* name, Some* some, bool is_mutable);
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, NFunction function, bool is_mutable);
    void set(char* nane, Primitive* primitive, bool is_mutable);
    void set(char* name, NConstructor constructor, bool is_mutable);
    Some* get(char* name, bool check = false);
    char* raw();
    Some* some();
};
