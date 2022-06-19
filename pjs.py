#!/usr/bin/env python3

"""PJScript core script"""

import json
import argparse
from pjscript.syntax.lexer import Lexer
from pjscript.syntax.parser import Parser

parser = argparse.ArgumentParser('PJScript')
parser.add_argument('source', nargs='?', default='')
parser.add_argument('--dump-mode', '-d',
                    help='Prints an AST pseudo code', action='store_true')
parser.add_argument('--json-mode', '-j',
                    help='Serializes an AST to JSON', action='store_true')

if __name__ == '__main__':

    args = parser.parse_args()
    if not args.source:
        print('REPL is not implemented yet')
    with open(args.source, 'r', encoding='utf-8') as source_code_reader:
        parsed = Parser(Lexer(source_code_reader.read()).lexed()).parsed()
        if args.dump_mode:
            print(parsed)  # <-- use built-in string Program serialization
        if args.json_mode:
            print(json.dumps(parsed.to_dict()))  # dumps out a JSON string
