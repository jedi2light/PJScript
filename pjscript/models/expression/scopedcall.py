"""PJScript ScopedCallExpression"""

# pylint: disable=line-too-long  # :)

from pjscript.models.expression.call \
    import CallExpression


class ScopedCallExpression(CallExpression):

    """ScopedCallExpression class"""

    def generate(self, top: bool = False, **opts) -> str:

        """Generate ScopedCallExpression"""

        args = '{' + ', '.join(map(lambda argument:  argument.generate() + '->some()', self.args())) + '}'

        inst_bf = 'true' if self.instantiation() else 'false'  # <---- '$instantiation' flag boolean value

        return f'_env->get({self.name().generate()})->operator()({args}, {inst_bf})' + (';'if top else '')
