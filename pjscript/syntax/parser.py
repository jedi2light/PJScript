"""PJScript Parser"""

from typing import List
from pjscript.syntax.token import \
    Token, Span
from pjscript.models import \
    BaseModel, CallExpression
from pjscript.models.literal import *
from pjscript.models.expression import *


class Parser:

    """Parser makes AST based on passed tokens"""

    _errors: List[str]
    _warnings: List[str]
    _tokens: List[Token]
    _program_ast: ProgramExpression
    _last_semicolon_token_span: Span

    def __init__(self, tokens: List[Token]) -> None:

        """Instantiate Parser"""

        self._errors = []
        self._warnings = []
        self._tokens = tokens
        self._parse()

    def parsed(self) -> ProgramExpression:

        """Returns program expression instance"""

        return self._program_ast

    def _expressions(self) -> List[List[Token]]:

        """Returns tokens grouped by a semicolon token"""

        groups = []

        idx = 0
        while idx < len(self._tokens):
            if self._tokens[idx].is_semicolon():
                self._last_semicolon_token_span = self._tokens[idx].span()
                groups.append(self._tokens[:idx])
                self._tokens = self._tokens[idx + 1:]
                idx = 0
            else:
                idx += 1

        return groups

    @staticmethod
    def _arguments(tokens) -> List[List[Token]]:

        """Returns tokens grouped by a coma token"""

        arguments = []

        # TODO: this algorithm does not work properly yet, we definitely need to fix it up!

        idx = 0
        while idx < len(tokens):
            if tokens[idx].is_coma() or len(tokens) - idx == 1:
                arguments.append([tokens[idx]] if len(tokens) - idx == 1 else tokens[:idx])
                tokens = tokens[idx + 1:]
                idx = 0
            else:
                idx += 1

        return arguments

    def _parse_call_expression(self, tokens: List[Token]) -> CallExpression:

        """Returns parsed CallExpression (ObjectCallExpression, MemberCallExpression) instance"""

        name = IdentifierLiteral(tokens[0])
        args = [self._parse_expression(tokens) for tokens in self._arguments(tokens[2:len(tokens) - 1])]

        # TODO: in JS, we can also express Member*Expression by 'foo . bar', so we need to improve this logic

        return MemberCallExpression(name, args) if '.' in name.token().value() \
            else ObjectCallExpression(name, args)

    def _parse_member_assignment_expression(self, tokens: List[Token]) -> MemberAssignmentExpression:

        """Returns parsed MemberAssignmentExpression instance"""

        assert len(tokens) >= 3,   f'{tokens[0].span().formatted()}: error: incorrect MemberAssignment arity'

        mutable = True
        lhs = IdentifierLiteral(tokens[0])
        rhs = self._parse_expression(tokens[2:])

        return MemberAssignmentExpression(mutable, lhs, rhs)

    def _parse_assignment_expression(self, tokens: List[Token]) -> AssignmentExpression:

        """Returns parsed AssignmentExpression instance"""

        assert len(tokens) >= 4,         f'{tokens[0].span().formatted()}: error: incorrect Assignment arity'

        mutable = tokens[0].value() == 'var'
        lhs = IdentifierLiteral(tokens[1])
        rhs = self._parse_expression(tokens[3:])

        return AssignmentExpression(mutable, lhs, rhs)

    def _parse_expression(self, tokens: List[Token]) -> BaseModel:

        """Returns either a parsed expression or a parsed literal instance"""

        if not tokens:
            self._warnings.append(f'{self._last_semicolon_token_span.formatted()}: closing empty expression')
            return NullLiteral(Token(Token.Identifier, 'null', self._last_semicolon_token_span - 1))  # null;

        # TODO: implement matching instead of manual guessing what kind of expression we should parse/return!

        if tokens[0].is_null_keyword():
            return NullLiteral(tokens[0])

        if tokens[0].is_boolean_keyword():
            return BooleanLiteral(tokens[0])

        if tokens[0].is_mutable_keyword():
            return self._parse_assignment_expression(tokens)

        if tokens[0].is_string():
            return StringLiteral(tokens[0])

        if tokens[0].is_identifier():
            if len(tokens) == 1:
                return IdentifierLiteral(tokens[0])

            if tokens[1].is_opening_bracket():
                return self._parse_call_expression(tokens)

            if tokens[1].is_assignment_operator():
                return self._parse_member_assignment_expression(tokens)

    def _parse(self) -> None:

        """Takes list of tokens and produces ProgramExpression (AST) instance"""

        self._program_ast = ProgramExpression([self._parse_expression(expr) for expr in self._expressions()])
