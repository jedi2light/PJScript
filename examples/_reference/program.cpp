// each module has its own header: <name>-to.hpp.
#include "startup.tjs-to.hpp"

int main() {
    Environment* environment = new Environment();
    // GUIEnvironment gui = new GUIEnvironment();
    // environment->merge(gui);
    startup(environment);
    return 0;
}
