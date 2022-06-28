"""PJScript MemberAssignmentExpression"""

from pjscript.models.expression.assignment \
    import AssignmentExpression


class MemberAssignmentExpression(AssignmentExpression):

    """MemberAssignmentExpression class"""

    def generate(self, top: bool = False, **opts) -> str:

        """Generate MemberAssignmentExpression"""

        return f'{self._set_member_gen(self.lhs(), self.rhs(), self.mutable())}' + self._semicolon(top)
