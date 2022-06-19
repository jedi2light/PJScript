"""PJScript Span and Token"""


class Span:

    """Span represents a Token position in a source code"""

    _line_no: int
    _char_no: int

    def __init__(self, line_no: int, char_no: int) -> None:

        """Instantiate Span"""

        self._line_no = line_no
        self._char_no = char_no

    def line(self) -> int:

        """Returns line number"""

        return self._line_no

    def char(self) -> int:

        """Returns character number"""

        return self._char_no

    def tuple(self) -> tuple:

        """Returns span as a tuple"""

        return self._line_no, self._char_no

    def formatted(self) -> str:

        """Returns span as a string"""

        return ':'.join(map(str, self.tuple()))

    def __sub__(self, char_no: int) -> "Span":

        """Returns new Span with a char_no decremented"""

        return Span(self.line(), self._char_no - char_no)


class Token:

    """Token represents some part of the language syntax"""

    Coma = 'Coma'
    Operator = 'Operator'
    Semicolon = 'Semicolon'
    OpeningBracket = 'OpeningBracket'
    ClosingBracket = 'ClosingBracket'
    String = 'String'
    Identifier = 'Identifier'

    _kind: str
    _value: str
    _span: Span

    def __init__(self, kind: str, value: str, span: Span) -> None:

        """Instantiate Token"""

        self._kind = kind
        self._value = value
        self._span = span

    def kind(self) -> str:

        """Returns token kind"""

        return self._kind

    def value(self) -> str:

        """Returns token value"""

        return self._value

    def span(self) -> Span:

        """Returns token span"""

        return self._span

    def is_coma(self) -> bool:

        """Returns whether token is coma"""

        return self._kind == self.Coma

    def is_operator(self) -> bool:

        """Returns whether token is operator"""

        return self._kind == self.Operator

    def is_semicolon(self) -> bool:

        """Returns whether token is semicolon"""

        return self._kind == self.Semicolon

    def is_opening_bracket(self) -> bool:

        """Returns whether token is opening bracket"""

        return self._kind == self.OpeningBracket

    def is_closing_bracket(self) -> bool:

        """Returns whether token is closing bracket"""

        return self._kind == self.ClosingBracket

    def is_string(self) -> bool:

        """Returns whether token is string"""

        return self._kind == self.String

    def is_identifier(self) -> bool:

        """Returns whether token is identifier"""

        return self._kind == self.Identifier

    def __repr__(self) -> str:

        """Debugging simplified"""

        return self.__str__()

    def __str__(self) -> str:

        """Custom serializer helps to simplify debugging process"""

        value = self.value() \
            if not self.is_string() else f'"{self.value()}"'

        return f'[{self.span().formatted()} {self.kind()}] {value}'
