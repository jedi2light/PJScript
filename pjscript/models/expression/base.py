"""PJScript BaseExpression"""

# pylint: disable=R0903

from pjscript.models.base \
    import BaseModel
from pjscript.models.literal \
    import IdentifierLiteral


class BaseExpression(BaseModel):

    """Base expression class"""

    @staticmethod
    def _get_gen(identifier: IdentifierLiteral):

        """Generate _env->get(...)"""

        return f'_env->get({identifier.generate()})'

    @staticmethod
    def _get_member_gen(identifier: IdentifierLiteral):

        """Generate _env->get(...) (for obj. member)"""

        parts = identifier.token().value().split('.')
        resulting = f'_env->get((char*)"{parts[0]}")'

        for part in parts[1:]:
            resulting += f'->get((char*)"{part}")'

        return resulting

    @staticmethod
    def _set_gen(
            lhs: IdentifierLiteral,
            rhs: BaseModel, mutable: bool):

        """Generate _env->set(...)"""

        return f'_env->set({lhs.generate()}, ' \
               f'{rhs.generate()}, ' \
               f'{"true" if mutable else "false"})'

    @staticmethod
    def _set_member_gen(
            lhs: IdentifierLiteral,
            rhs: BaseModel, mutable: bool):

        """Generate _env->set(...) (for obj. member)"""

        parts = lhs.token().value().split('.')
        resulting = f'_env->get((char*)"{parts[0]}")'

        for part in parts[1:-1]:
            resulting += f'->get((char*)"{part}")'

        return resulting + f'->set((char*)"{parts[-1]}", ' \
                           f'{rhs.generate()}, ' \
                           f'{"true" if mutable else "false"})'
