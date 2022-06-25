"""PJScript C++ code compiler"""

import os
from typing import List


class CXXCompiler:

    """This class is responsible for C++ code compilation"""

    _sources: List[str]

    def __init__(self, sources: List[str]) -> None:

        """Instantiate CXXCompiler"""

        self._sources = sources

    def _generate_program_ctx(self) -> str:

        """This will generate program.cpp context"""

        includes = '\n'.join(map(lambda src: f'#include "{src}-to.hpp"', self._sources))

        main = 'int main(int argc, char* argv[])'\
               '{'\
               'Environment* environment = new Environment();'\
               + '\n'.join(map(lambda s: s.split('.')[0]+'(environment);', self._sources)) +\
               'return 0;'\
               '}'

        return f'{includes}\n{main}\n'  # <------------- return generated program.cpp context

    def compile(self, directory: str) -> None:

        """Compile to target (target should be a path)"""

        with open(os.path.join(directory, 'program.cpp'), 'w', encoding='utf-8') as p_writer:
            p_writer.write(self._generate_program_ctx())

        sources = ' '.join(map(lambda source: f'{directory}/{source}-to.cpp', self._sources))

        cmd = f'clang++ --std=c++20 ' \
              f'-I. -I{directory} ' \
              f'{sources} {directory}/program.cpp ' \
              f'-Lruntime/cxx/build -lpjscript -o {directory}/program'   # generate a command

        print(cmd)  # <-- print cmd so user can copy it and use separately (useful for debug)

        os.system(cmd)  # <------------------------------------- invoke cmd using os.system()
