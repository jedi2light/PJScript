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
typedef std::function<Some*(ArgumentsType, bool)> NFunction;

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
    VarType type();
    Object* object();
    Some* operator () (ArgumentsType args, bool $instantiation);
    Primitive* primitive();
    bool is_mutable();
    void set(char* name, Some* some, bool is_mutable);
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, NFunction function, bool is_mutable);
    void set(char* name, Primitive* primitive, bool is_mutable);
    Some* get(char* name, bool check = false);
    char* raw();
    char* view();
    Some* some();
};

class Object {
protected:
    char* m_name;
    char* m_alias;
    ObjType m_type;
    NFunction m_function;
    Primitive* m_primitive;
    std::unordered_map<char*, Some*> m_props;
public:
    Object();
    Object(NFunction);
    Object(Primitive*);
    char* name();
    char* alias();
    ObjType type();
    Some* operator () (ArgumentsType args, bool $instantiation);
    Primitive* primitive();
    void setType(ObjType type);
    void setAlias(char* alias);
    std::unordered_map<char*, Some*> props();
    void set(char* name, Some* some, bool is_mutable);
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, NFunction function, bool is_mutable);
    void set(char* nane, Primitive* primitive, bool is_mutable);
    Some* get(char* name, bool check = false);
    char* raw();
    char* view();
    Some* some();
};
