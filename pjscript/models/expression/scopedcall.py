"""PJScript ScopedCallExpression"""

# pylint: disable=line-too-long  # :)

from pjscript.models.expression.call \
    import CallExpression


class ScopedCallExpression(CallExpression):

    """ScopedCallExpression class"""

    def generate(self, top: bool = False, **opts) -> str:

        """Generate ScopedCallExpression"""

        args = '{' + ', '.join(map(lambda argument: argument.generate() + '->some()',  self.args())) + '}'

        instantiation = 'true' if self.instantiation() else 'false'  # <-- '$instantiation' argument value

        return f'{self._get_gen(self.name())}->operator()({args}, {instantiation})' + self._semicolon(top)
