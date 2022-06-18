"""PJScript Parser"""


from typing import List
from pjscript.syntax.token import Token
from pjscript.models.literal import *
from pjscript.models.expression import *


class Parser:

    """Parser makes AST based on passed tokens"""

    _tokens: List[Token]
    _program: ProgramExpression

    def __init__(self, tokens: List[Token]) -> None:

        """Instantiate Parser"""

        self._tokens = tokens
        self._parse()

    def parsed(self) -> ProgramExpression:

        """Returns program expression instance"""

        return self._program

    def _parse(self) -> None:

        """Take list of tokens and produces ProgramExpression with its body"""

        self._program = ProgramExpression(body=[])
