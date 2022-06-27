#pragma once

class Some;
class Object;

enum PrimitiveType { NIL,
                     STRING,
                     BOOLEAN };

class Primitive {
protected:
    PrimitiveType m_type;
    char* m_raw;
public:
    Primitive(char* raw);
    char* raw();
    Some* some();
    PrimitiveType type();
    virtual Object* to_object() = 0;
};
