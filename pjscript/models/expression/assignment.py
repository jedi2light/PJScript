"""PJScript AssignmentExpression"""

from pjscript.models.expression.base import BaseExpression
from pjscript.models.literal.identifier import IdentifierLiteral
from pjscript.models.base import BaseModel


class AssignmentExpression(BaseExpression):

    """AssignmentExpression class"""

    _mutable: bool
    _lhs: IdentifierLiteral
    _rhs: BaseModel

    def __init__(self, mutable: bool, lhs: IdentifierLiteral, rhs: BaseModel) -> None:

        """Instantiate AssignmentExpression"""

        self._mutable = mutable
        self._lhs = lhs
        self._rhs = rhs

    def mutable(self) -> bool:

        """Returns AssignmentExpression mutability flag"""

        return self._mutable

    def lhs(self) -> IdentifierLiteral:

        """Returns AssignmentExpression left-hand-side"""

        return self._lhs

    def rhs(self) -> BaseModel:

        """Returns AssignmentExpression right-hand-side"""

        return self._rhs
