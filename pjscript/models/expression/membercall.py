"""PJScript MemberCallExpression"""

# pylint: disable=line-too-long  # :)

from pjscript.models.expression.call \
    import CallExpression


class MemberCallExpression(CallExpression):

    """MemberCallExpression class"""

    def generate(self, top: bool = False, **opts) -> str:

        """Generate MemberCallExpression"""

        # TODO: need to figure out how to offload certain amount of logic to the IdentifierLiteral class

        parts = self.name().token().value().split('.')  # <---- split a member name by the dot-character

        generated = f'_env->get((char*)"{parts[0]}")' \
                    + ''.join([f'->get((char*)"{p}")' for p in parts[1:]])  # <-- get the generated form

        args = '{' + ','.join(map(lambda _arg: '(' + _arg.generate() + ')->some()',  self.args())) + '}'

        inst_bf = 'true' if self.instantiation() else 'false'  # <-- '$instantiation' flag boolean value

        return f'{generated}->operator()({args}, {inst_bf})' + (';'if top else '')  # the C++ expression
