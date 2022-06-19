"""PJScript CallExpression"""

from typing import List
from pjscript.models.expression.base import BaseExpression
from pjscript.models.literal.identifier import IdentifierLiteral
from pjscript.models.base import BaseModel


class CallExpression(BaseExpression):

    """CallExpression class"""

    _name: IdentifierLiteral
    _args: List[BaseModel]

    def __init__(self, name: IdentifierLiteral, args: List[BaseModel]) -> None:

        """Instantiate CallExpression"""

        self._name = name
        self._args = args

    def name(self) -> IdentifierLiteral:

        """Returns CallExpression name"""

        return self._name

    def args(self) -> list:

        """Returns CallExpression args"""

        return self._args

    def __repr__(self) -> str:

        """Debugging simplified"""

        return self.__str__()

    def __str__(self) -> str:

        """Custom '*CallExpression' serializer, was written in order to simplify debugging."""

        return f'{self.__class__.__name__}({self.name()}, {", ".join(map(str, self.args()))})'
