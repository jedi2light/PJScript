#include <iostream>

#include "console.hpp"

#include "../primitives/undefined.hpp"

Console::Console() {
    this->m_type = CASUAL_OBJ;
    this->m_name = (char*)"Console";
    this->m_primitive = nullptr;

    this->set(
        (char*)"log",
        [](ArgumentsType args, bool) {
            for (Some* arg : args)
                std::cout << arg->view() << " ";
            std::cout << std::endl;
            return (new UndefinedPrimitive())->some();
        },
        true
    );
    this->set(
        (char*)"error",
        [](ArgumentsType args, bool) {
            for (Some* arg : args) {
                std::cerr << arg->view() << " ";
            std::cerr << std::endl;
            }
            return (new UndefinedPrimitive())->some();
        },
        true
    );
}
