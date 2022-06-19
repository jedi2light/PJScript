#include <pjs>

int main() {
    Value& foo = ObjectValue();
    Value& bar = foo;
    foo.set('name', StringValue("User"));
    console.log(StringValue("Hello, "), foo.get("name"));
    return 0;
}