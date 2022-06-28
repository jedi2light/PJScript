"""PJScript MemberAccessExpression"""

from pjscript.models.expression.access \
    import AccessExpression


class MemberAccessExpression(AccessExpression):

    """MemberAccessExpression class"""

    def generate(self, top: bool = False, **opts) -> str:

        """Generate MemberAccessExpression"""

        return f'{self._get_member_gen(self.name())}' + self._semicolon(top)
