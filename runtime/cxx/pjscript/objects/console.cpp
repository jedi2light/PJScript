#include <iostream>

#include "console.hpp"

#include "../primitives/null.hpp"

Console::Console() {
    this->m_type = CONSOLE_OBJ;
    this->m_name = (char*)"Console";

    this->m_primitive = nullptr;
    this->set(
        (char*)"log",
        [](ArgumentsType args) {
            for (Some* arg : args)
                std::cout << arg->raw() << " ";
            std::cout << std::endl;
            return (new NullPrimitive())->some();
        },
        true
    );
    this->set(
        (char*)"error",
        [](ArgumentsType args) {
            for (Some* arg : args) {
                std::cerr << arg->raw() << " ";
            std::cerr << std::endl;
            }
            return (new NullPrimitive())->some();
        },
        true
    );
}
