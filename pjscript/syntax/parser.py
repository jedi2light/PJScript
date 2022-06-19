"""PJScript Parser"""

# pylint: disable=line-too-long
# pylint: disable=wildcard-import

from typing import List
from pjscript.syntax.token import \
    Token, Span
from pjscript.models import \
    BaseModel, \
    CallExpression, AssignmentExpression
from pjscript.models.literal import *
from pjscript.models.expression import *


class Parser:  # pylint: disable=too-few-public-methods  # it's okay to have only one: `parsed()`

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
    def _args_by(tokens, cond) -> List[List[Token]]:

        """Returns tokens grouped by a some token"""

        groups = []
        group = []

        idx = 0
        while idx < len(tokens):
            if cond(tokens[idx]):
                groups.append(group)
                group = []
                tokens = tokens[idx + 1:]
                idx = 0
            else:
                group.append(tokens[idx])
                idx += 1

        # we do not want to lose last argument expression from the ExpressionCall' arguments list
        if group:
            groups.append(group)

        return groups

    def _parse_call_expression(self, tokens: List[Token], instantiation: bool) -> CallExpression:

        """Returns parsed CallExpression (ObjectCallExpression, MemberCallExpression) instance"""

        name, start = (IdentifierLiteral(tokens[1]), 2)if instantiation else(IdentifierLiteral(tokens[0]), 1)

        args = [self._parse_expression(tokens) for tokens in self._args_by(tokens[start + 1:len(tokens) - 1],
                                                                           # separate arguments by coma token
                                                                           lambda token:    token.is_coma())]

        # TODO: in JS, we can also express Member*Expression by 'foo . bar', so we need to improve this logic

        payload = instantiation, name, args

        return MemberCallExpression(*payload) if name.token().has_a_dot() else ObjectCallExpression(*payload)

    def _parse_assignment_expression(self, tokens: List[Token]) -> AssignmentExpression:

        """Returns parsed AssignmentExpression instance"""

        mutable, tokens = \
            (tokens[0].value() == 'var', tokens[1:]) if tokens[0].is_mutability_keyword() else (True, tokens)

        assert len(tokens) >= 3, f'{tokens[0].span().formatted()}: incorrect arity for assignment expression'

        lhs = IdentifierLiteral(tokens[0])
        rhs = self._parse_expression(tokens[2:])  # <-- skip over assignment operator, if empty -> raises err

        return MemberAssignmentExpression(mutable, lhs, rhs) \
            if tokens[0].has_a_dot() \
            else ScopedAssignmentExpression(mutable, lhs, rhs)   # <--- dispatch between two Assignment types

    def _parse_expression(self, tokens: List[Token]) -> BaseModel:  # pylint: disable=R0911  # it's okay, bro

        """Returns either a parsed expression or a parsed literal instance"""

        assert tokens, f'{(self._last_semicolon_token_span - 1).formatted()}: can not parse empty expression'

        # TODO: implement matching instead of manual guessing what kind of expression we should parse->return

        # null;
        # null keyword

        if tokens[0].is_null_keyword():
            return NullLiteral(tokens[0])  # <------------------------- parse 'null' keyword as a NullLiteral

        # "string";
        # string literal

        if tokens[0].is_string():
            return StringLiteral(tokens[0])  # <----------------------- parse string token as a StringLiteral

        # true;
        # false;
        # boolean keyword

        if tokens[0].is_boolean_keyword():
            return BooleanLiteral(tokens[0])  # <-------- parse ('true', 'false') keyword as a BooleanLiteral

        # Object;
        # foo.bar;
        # single identifier

        if len(tokens) == 1 and tokens[0].is_regular_identifier():  # it's needed for a secondary else branch

            if tokens[0].has_a_dot():  # <-- 'has_a_dot()' already checks that it's just a regular identifier
                return MemberAccessExpression(IdentifierLiteral(tokens[0]))  # <- parse as a MemberAccessExpr
            return ScopedAccessExpression(IdentifierLiteral(tokens[0]))  # <----- parse as a ScopedAccessExpr

        # new Object;
        #   ^      ^
        # new Object();
        #   ^      ^~~

        if tokens[0].is_new_keyword() and tokens[1].is_regular_identifier():
            return self._parse_call_expression(tokens,    instantiation=True)  # <-- parse instantiation call

        # Object();
        #      ^^^
        # console.log("Hello", "World", "!");
        #           ^^~~~~~~~~~~~~~~~~~~~~~^

        if tokens[0].is_regular_identifier() \
                and tokens[1].is_opening_bracket() and tokens[-1].is_closing_bracket():
            return self._parse_call_expression(tokens,    instantiation=False)  # <------- parse regular call

        # foo = "foo";
        #   ^ ^ ..... ...
        # var bar = "bar";
        #   ^   ^ ^ ..... ...
        # const xyz = bar;
        #     ^   ^ ^ ... ...

        if (len(tokens) >= 3  # pylint: disable=too-many-boolean-expressions  # might consider refactor this?
            and tokens[0].is_regular_identifier()
            and tokens[1].is_assignment_operator()) \
                or (len(tokens) >= 4
                    and tokens[0].is_mutability_keyword()
                    and tokens[1].is_regular_identifier()
                    and tokens[2].is_assignment_operator()):
            return self._parse_assignment_expression(tokens)  # <------------- parse an assignment expression

        raise SyntaxError(f'{tokens[0].span().formatted()}: it does not match any known expression pattern!')

    def _parse(self) -> None:

        """Takes list of tokens and produces ProgramExpression (AST) instance based on 'recursive parsing'"""

        self._program_ast = ProgramExpression([self._parse_expression(expr) for expr in self._expressions()])
