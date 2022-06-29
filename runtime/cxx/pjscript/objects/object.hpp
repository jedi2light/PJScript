#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "../primitives/primitive.hpp"

class Some;
class Object;

enum VarType { OBJECT,       PRIMITIVE };
enum ObjType { CASUAL_OBJ,   STRING_OBJ,
               BOOLEAN_OBJ,  CALLABLE_OBJ };

typedef std::vector<Some*> ArgsType;
typedef std::function<Some*(ArgsType, bool)> NFunction;

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
    Primitive* primitive();
    bool is_mutable();
    Some* operator () (ArgsType args, bool $is_instantiation);
    void set(char* name, Some* some, bool is_mutable);
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, NFunction function, bool is_mutable);
    void set(char* name, Primitive* primitive, bool is_mutable);
    Some* get(char* name, bool check = false);
    void del(char* name);
    char* raw();
    char* view();
    Some* some();
};

class Object {
protected:
    char* m_name;
    char* m_alias;
    ObjType m_type;
    Object* m_called;
    Object* m_parent;
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
    Object* called();
    Object* parent();
    void flushCalled();
    void setCalled(Object* called); // be able to set a called
    void setParent(Object* parent); // be able to set a parent
    void setType(ObjType type); // be able to set object' type
    void setAlias(char* alias); // be able to set object alias
    Primitive* primitive(); // be able to get a tied primitive
    std::unordered_map<char*, Some*> props(); // get obj props
    Some* operator () (ArgsType args, bool $is_instantiation);
    void set(char* name, Some* some, bool is_mutable);
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, NFunction function, bool is_mutable);
    void set(char* nane, Primitive* primitive, bool is_mutable);
    Some* get(char* name, bool check = false);
    void del(char* name);
    char* raw();
    char* view();
    Some* some();
};
