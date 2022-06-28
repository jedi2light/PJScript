"""PJScript MemberCallExpression"""

# pylint: disable=line-too-long  # :)

from pjscript.models.expression.call \
    import CallExpression


class MemberCallExpression(CallExpression):

    """MemberCallExpression class"""

    def generate(self, top: bool = False, **opts) -> str:

        """Generate MemberCallExpression"""

        args = '{' + ','.join(map(lambda _argument: '(' + _argument.generate() + ')->some()', self.args())) + '}'

        instantiation = 'true' if self.instantiation() else 'false'  # <--------- '$instantiation' argument value

        return f'{self._get_member_gen(self.name())}->operator()({args}, {instantiation})' + self._semicolon(top)
