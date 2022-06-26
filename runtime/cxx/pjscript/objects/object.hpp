#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "../primitives/primitive.hpp"

class Some;
class Object;

enum Type {  OBJECT, PRIMITIVE,
             FUNCTION, CONSTRUCTOR  };

enum ObjType { ENVIRONMENT_OBJ, CONSOLE_OBJ,
               STRING_OBJ, FUNCTIONABLE_OBJ };

typedef std::vector<Some*> ArgumentsType;
typedef std::function<Some*(ArgumentsType)> NFunction;
typedef std::function<Object*(ArgumentsType)> NConstructor;

class Some {
protected:
    Type m_type;
    Object* m_object;
    NFunction m_nfunction;
    Primitive* m_primitive;
    NConstructor m_nconstructor;
    bool m_is_mutable { true };
public:
    Some(Object* object, bool is_mutable);
    Some(NFunction function, bool is_mutable);
    Some(Primitive* primitive, bool is_mutable);
    Some(NConstructor constrtor, bool is_mutable);
    Type type();
    Object* object();
    NFunction function();
    Primitive* primitive();
    NConstructor constructor();
    bool is_mutable();
    void set(char* name, Some* some, bool is_mutable);
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, Function function, bool is_mutable);
    void set(char* name, NFunction function, bool is_mutable);
    void set(char* name, Primitive* primitive, bool is_mutable);
    void set(char* name, Constructor constructor, bool is_mutable);
    void set(char* name, NConstructor constructor, bool is_mutable);
    Some* get(char* name, bool check = false);
    char* raw();
    Some* some();
};

class Object {
protected:
    char* m_name;
    ObjType m_type;
    Primitive* m_primitive;
    std::unordered_map<char*, Some*> m_storage;
public:
    char* name();
    ObjType type();
    Primitive* primitive();
    Object();
    Object(Primitive* object);
    std::unordered_map<char*, Some*> storage();
    void set(char* name, Some* some, bool is_mutable);
    void set(char* name, Object* object, bool is_mutable);
    void set(char* name, Function function, bool is_mutable);
    void set(char* name, NFunction function, bool is_mutable);
    void set(char* nane, Primitive* primitive, bool is_mutable);
    void set(char* name, Constructor constructor, bool is_mutable);
    void set(char* name, NConstructor constructor, bool is_mutable);
    Some* get(char* name, bool check = false);
    Some* some();
};
