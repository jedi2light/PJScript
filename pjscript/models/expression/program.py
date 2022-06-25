"""PJScript ProgramExpression"""

from typing import List
from pjscript.models.expression.base \
    import BaseExpression
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

    def to_dict(self) -> dict:

        """Returns dict representation"""

        return {
            "class": 'ProgramExpression',
            "body": [expression.to_dict() for expression in self.body()]
        }

    def generate(self, top: bool = False, **opts) -> str:

        """Generate ProgramExpression"""

        name = opts['name']  # it should fail if we did not provide a name

        generated = '\n'.join(map(lambda e_child:  e_child.generate(True),
                                  self.body()))

        generated += '\nreturn new NullPrimitive();'  # returns null value

        return f'#include "runtime/cxx/pjscript.hpp"\n' \
               f'Primitive* {name}(Environment* _env) {{\n{generated}\n}}'

    def __repr__(self) -> str:

        """Debugging simplified"""

        return self.__str__()

    def __str__(self) -> str:

        """Custom ProgramExpression serializer was written with the aim to simplify debugging"""

        return f'ProgramExpression([{", ".join(map(str, self.body())) if self.body() else ""}])'
