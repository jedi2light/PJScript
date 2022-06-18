"""PJScript MemberAccessExpression"""

from pjscript.models.expression.base import BaseExpression
from pjscript.models.literal.identifier import IdentifierLiteral


class MemberAccessExpression(BaseExpression):

    """MemberAccessExpression class"""

    _name: IdentifierLiteral

    def __int__(self, name: IdentifierLiteral) -> None:

        """Instantiate MemberAccessExpression"""

        self._name = name

    def name(self) -> IdentifierLiteral:

        """Returns MemberAccessExpression name"""

        return self._name
