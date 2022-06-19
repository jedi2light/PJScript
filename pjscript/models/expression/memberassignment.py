"""PJScript MemberAssignmentExpression"""

from pjscript.models.expression.base import BaseExpression
from pjscript.models.literal.identifier import IdentifierLiteral
from pjscript.models.base import BaseModel


class MemberAssignmentExpression(BaseExpression):

    """MemberAssignmentExpression class"""

    _mutable: bool
    _lhs: IdentifierLiteral
    _rhs: BaseModel

    def __init__(self, mutable: bool, lhs: IdentifierLiteral, rhs: BaseModel) -> None:

        """Instantiate MemberAssignmentExpression"""

        self._mutable = mutable
        self._lhs = lhs
        self._rhs = rhs

    def mutable(self) -> bool:

        """Returns MemberAssignmentExpression mutability flag"""

        return self._mutable

    def lhs(self) -> IdentifierLiteral:

        """Returns MemberAssignmentExpression left-hand-side"""

        return self._lhs

    def rhs(self) -> BaseModel:

        """Returns MemberAssignmentExpression right-hand-side"""

        return self._rhs

    def __repr__(self) -> str:

        """Debugging simplified"""

        return self.__str__()

    def __str__(self) -> str:

        """Custom MemberAssignment serializer's written in order to simplify debugging"""

        return f'{self.__class__.__name__}({self.mutable()}, {self.lhs()}, {self.rhs()})'
