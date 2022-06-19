"""PJScript DumpMode"""


from pjscript.models.expression.program import ProgramExpression


class DumpMode:

    """Dumps out built AST"""

    _program: ProgramExpression

    def __init__(self, program: ProgramExpression) -> None:

        """Instantiate DumpMode"""

        self._program = program

    def program(self) -> ProgramExpression:

        """Returns program expression"""

        return self._program

    def dump(self, indent: int = 0) -> None:

        """Actually dumps out built AST"""

        print(self._program)  # TODO: implement dump() function
