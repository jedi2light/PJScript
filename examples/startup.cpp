// examples/startup.tjs

Value& startup(Environment& _env) {
    _env.set("xyz", StringValue("This gonna be treated as 'var xyz = ...' form"), mutable=true);
    _env.get("xyz");
    _env.set("foo", ObjectValue(), mutable=true);
    _env.set("foo", ObjectValue(), mutable=true);
    _env.set("foo", ObjectValue::AsInstance(), mutable=true);
    _env.set("bar", _env.get("foo"), mutable=false);
    _env.get("bar").set("name", StringValue("User"), mutable=true);
    _env.get("bar").get("name");
    return Console::Log(StringValue("Hello, ", _env.get("bar").get("name"), _env.get("bar").get("name").toString()));
}