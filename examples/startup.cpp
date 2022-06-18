#include <pjs>

int main() {
    Value& foo = ObjectValue();
    foo.set('name', StringValue("User"));
    System.inform(StringValue("Hello, ", foo.get("name")));
    return 0;
}