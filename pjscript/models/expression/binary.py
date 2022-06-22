"""PJScript BinaryExpression"""

# pylint: disable=duplicate-code  # for Assignment, Binary

from pjscript.models.expression.base import BaseExpression
from pjscript.models.base import BaseModel


class BinaryExpression(BaseExpression):

    """BinaryExpression class"""

    Add = 'Add'
    Sub = 'Sub'
    Mul = 'Mul'
    Div = 'Div'

    _operator: str
    _lhs: BaseModel
    _rhs: BaseModel

    def __init__(self,
                 operator: str,
                 lhs: BaseModel,
                 rhs: BaseModel) -> None:

        """Instantiate BinaryExpression"""

        self._operator = operator
        self._lhs = lhs
        self._rhs = rhs

    def operator(self) -> str:

        """Returns BinaryExpression operator"""

        return self._operator

    def lhs(self) -> BaseModel:

        """Returns BinaryExpression left-hand-side"""

        return self._lhs

    def rhs(self) -> BaseModel:

        """Returns BinaryExpression right-hand-side"""

        return self._rhs

    def to_dict(self) -> dict:

        """Returns dict representation"""

        return {
            "class": 'BinaryExpression',
            "operator": self.operator(),
            "lhs": self.lhs().to_dict(),
            "rhs": self.rhs().to_dict()
        }

    def __repr__(self) -> str:

        """Debugging simplified"""

        return self.__str__()

    def __str__(self) -> str:

        """This custom serializer was made to simplify debugging"""

        return f'BinaryExpression' \
               f'(<{self.operator()}>, {self.lhs()}, {self.rhs()})'