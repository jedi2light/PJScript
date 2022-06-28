"""PJScript ScopedAssignmentExpression"""

from pjscript.models.expression.assignment \
    import AssignmentExpression


class ScopedAssignmentExpression(AssignmentExpression):

    """ScopedAssignmentExpression class"""

    def generate(self, top: bool = False, **opts) -> str:

        """Generate ScopedAssignmentExpression"""

        return f'{self._set_gen(self.lhs(), self.rhs(), self.mutable())}' + self._semicolon(top)
