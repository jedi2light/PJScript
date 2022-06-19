"""PJScript MemberAccessExpression"""

from pjscript.models.expression.base import BaseExpression
from pjscript.models.literal.identifier import IdentifierLiteral


class MemberAccessExpression(BaseExpression):

    """MemberAccessExpression class"""

    _name: IdentifierLiteral

    def __init__(self, name: IdentifierLiteral) -> None:

        """Instantiate MemberAccessExpression"""

        self._name = name

    def name(self) -> IdentifierLiteral:

        """Returns MemberAccessExpression name"""

        return self._name

    def __repr__(self) -> str:

        """Debugging simplified"""

        return self.__str__()

    def __str__(self) -> str:

        """Custom serializer made to simplify debugging"""

        return f'{self.__class__.__name__}({self.name()})'
