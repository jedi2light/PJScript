#!/usr/bin/env python3

"""PJScript core script"""

import os
import json
import argparse
from pjscript.syntax.lexer import Lexer
from pjscript.syntax.parser import Parser
from pjscript.compiler import CXXCompiler

parser = argparse.ArgumentParser('PJScript')
parser.add_argument('source', nargs='?', default='')
parser.add_argument('--mk-binary', '-b',
                    help='Generate executable file',  action='store_true')
parser.add_argument('--cgen-mode', '-c',
                    help='Generate .cpp, .hpp files', action='store_true')
parser.add_argument('--dump-mode', '-d',
                    help='Prints an AST pseudo code', action='store_true')
parser.add_argument('--json-mode', '-j',
                    help='Serializes an AST to JSON', action='store_true')

if __name__ == '__main__':

    args = parser.parse_args()
    if not args.source:
        print('REPL is not implemented yet')
    with open(args.source, 'r', encoding='utf-8') as source_code_reader:
        if args.mk_binary:
            # TODO: we should support more than one "modules", I would say
            CXXCompiler([args.source.split('/')[-1]]).compile(
                os.path.dirname(os.path.abspath(args.source)))  # <- build
        parsed = Parser(Lexer(source_code_reader.read()).lexed()).parsed()
        if args.cgen_mode:
            name = os.path.basename(args.source).split('.')[0]  # mod name
            with open(args.source+'-to.cpp', 'w', encoding='utf-8') as sw:
                sw.write(parsed.generate(name=name))  # <--- generate .cpp
            with open(args.source+'-to.hpp', 'w', encoding='utf-8') as sw:
                sw.write(f'#include "runtime/cxx/pjscript.hpp"\n' +
                         f'Primitive* {name}(Environment* _env);')  # .hpp
        if args.dump_mode:
            print(parsed)  # <-- use built-in string Program serialization
        if args.json_mode:
            print(json.dumps(parsed.to_dict()))  # dumps out a JSON string
