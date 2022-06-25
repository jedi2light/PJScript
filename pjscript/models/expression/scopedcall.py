"""PJScript ScopedCallExpression"""

from pjscript.models.expression.call \
    import CallExpression


class ScopedCallExpression(CallExpression):

    """ScopedCallExpression class"""

    def generate(self, top: bool = False) -> str:

        """Generate ScopedCallExpression"""

        return f''
