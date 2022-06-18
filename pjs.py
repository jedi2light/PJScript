#!/usr/bin/env python3

"""PJScript core script"""

import argparse
from pjscript.mode.dump import DumpMode
from pjscript.syntax.lexer import Lexer
from pjscript.syntax.parser import Parser

parser = argparse.ArgumentParser('PJScript')
parser.add_argument('source', nargs='?', default='')

if __name__ == '__main__':

    args = parser.parse_args()
    if not args.source:
        print('REPL mode is not implemented yet')
    with open(args.source, 'r', encoding='utf-8') as source_code_reader:
        DumpMode(Parser(Lexer(source_code_reader.read()).lexed()).parsed()).dump()
