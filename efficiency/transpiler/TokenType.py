from typing import Literal
from enum import Enum


class TokenType(Enum):
    # Boolean Tokens
    TRUE = 1
    FALSE = 2
    STRING = 3

    # 単項演算子
    UNARY_MINUS = 4
    UNARY_NOT = 5
    UNARY_TO_INT = 6
    UNARY_TO_STRING = 7

    # 二項演算子
    BINARY_PLUS = 8
    BINARY_MINUS = 9
    BINARY_MULTIPLY = 10
    BINARY_DIVIDE = 11
    BINARY_MODULO = 12
    BINARY_ELSS_THAN = 13
    BINARY_GREATER_THAN = 14
    BINARY_EQUAL = 15
    BINARY_OR = 16
    BINARY_AND = 17
    BINARY_STRING_CONCAT = 18
    BINARY_STRING_TOP = 19
    BINARY_STRING_DROP = 20
    BINARY_APPLY = 21

    # if文
    IF = 22

    # Lambda関係
    LAMBDA = 23
    LAMBDA_VAR = 24

    # intなど
    INTEGER = 25

    # EOF
    EOF = 26

    # # Single-character tokens.
    # LEFT_PAREN = 1
    # RIGHT_PAREN = 2
    # LEFT_BRACE = 3
    # RIGHT_BRACE = 4
    # COMMA = 5
    # DOT = 6
    # MINUS = 7
    # PLUS = 8
    # SEMICOLON = 9
    # SLASH = 10
    # STAR = 11

    # # One or two character tokens.
    # BANG = 12
    # BANG_EQUAL = 13
    # EQUAL = 14
    # EQUAL_EQUAL = 15
    # GREATER = 16
    # GREATER_EQUAL = 17
    # LESS = 18
    # LESS_EQUAL = 19

    # # Literals.
    # IDENTIFIER = 20
    # STRING = 21
    # NUMBER = 22

    # # Keywords.
    # AND = 23
    # CLASS = 24
    # ELSE = 25
    # FALSE = 26
    # FUN = 27
    # FOR = 28
    # IF = 29
    # NIL = 30
    # OR = 31
    # PRINT = 32
    # RETURN = 33
    # SUPER = 34
    # THIS = 35
    # TRUE = 36
    # VAR = 37
    # WHILE = 38

    # EOF = 39

    def __str__(self):
        return self.name

    def __repr__(self):
        return self.name

    def __eq__(self, other):
        if isinstance(other, TokenType):
            return self.value == other.value
        elif isinstance(other, Literal):
            return self.name == other
        else:
            return False

    def __ne__(self, other):
        return not self.__eq__(other)
