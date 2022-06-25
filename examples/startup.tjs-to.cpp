#include "../runtime/cxx/pjscript.hpp"

// generated from examples/startup.tjs

Primitive* startup(Environment* _env) {
    // xyz = "This gonna be treated as 'var xyz = ...' form";
    _env->set(
        (char*)"xyz",
        new StringPrimitive(
            (char*)"This gonna be treated as 'var xyz = ...' form"),true);
    // xyz
    _env->get((char*)"xyz");
    // var foo = Object();
    _env->set(
        (char*)"foo",
        _env->get((char*)"Object")->function()({ }), true);
    // var foo = new Object();
    _env->set(
        (char*)"foo",
        _env->get((char*)"Object#constructor")->constructor()({ }), true);
    // todo: we should support 'user-defined functions' in runtime as well
    // const bar = foo;
    _env->set((char*)"bar", _env->get((char*)"foo"), false);
    // bar.name = "User";
    _env->get((char*)"bar")->set((char*)"name",
                                 new StringPrimitive((char*)"User"),true);
    // bar.name;
    _env->get((char*)"bar")->get((char*)"name");
    // todo: we should also be able to handle some arithmetical operations
    // todo: we also should implement some TJS builtins in runtime as well
    // console.log"Hello, ", bar.name, bar.name.toString());
    _env->get((char*)"console")->get((char*)"log")->function()({
        _env->get((char*)"my")->some(),
        _env->get((char*)"typeof")->function()(
                                            {_env->get((char*)"xyz")}),
        _env->get((char*)"typeof")->function()(
                                            {_env->get((char*)"Object")}),
        (new StringPrimitive((char*)"Hello, "))->some(),
        _env->get((char*)"bar")->get((char*)"name")->some(),
        _env->get((char*)"bar")->get((char*)"name")->get(
                                (char*)"toString")->function()({})->some()
    });
    return new NullPrimitive();  // todo: refactor to return module object
}
