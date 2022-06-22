#pragma once

class Value {
    virtual Value& get() = 0;
    virtual void set() = 0;
};
