"""PJScript ProgramExpression"""

from typing import List
from pjscript.models.expression.base import BaseExpression
from pjscript.models.base import BaseModel


class ProgramExpression(BaseExpression):

    """ProgramExpression class"""

    _body: List[BaseModel]

    def __init__(self, body: List[BaseModel]) -> None:

        """Instantiate ProgramExpression"""

        self._body = body

    def body(self) -> List[BaseModel]:

        """Returns ProgramExpression body"""

        return self._body
