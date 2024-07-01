from typing import List
from TokenType import TokenType
from Token import Token

from utils.converter import icfp_to_string, icfp_to_int




class Scanner:
    def __init__(self, source: str, error_method):
        self.source = source
        self.raw_tokens = source.split(" ")
        self.tokens = []
        self.current_token = 0
        self.line = 1
        self.error_method = error_method

    def scan_tokens(self) -> List[Token]:
        while not self._is_at_end():
            self._scan_token()
            self.current_token += 1
        
        self._add_token(TokenType.EOF, "")
        return self.tokens

    def _is_at_end(self):
        return self.current_token >= len(self.raw_tokens)

    def _add_token(self, token_type, text) -> None:
        self.tokens.append(Token(token_type, text))


    def _scan_token(self) -> str:
        raw_token = self.raw_tokens[self.current_token]
        first_char = raw_token[0]
        rest = raw_token[1:]

        if first_char == "T":
            self._add_token(TokenType.TRUE, True)
        elif first_char == "F":
            self._add_token(TokenType.FALSE, False)
        elif first_char == "I":
            self._add_token(TokenType.INTEGER, icfp_to_int(rest))
        elif first_char == "S":
            self._add_token(TokenType.STRING, icfp_to_string(rest))
        elif first_char == "U":
            second_char = rest[0]
            if second_char == "-":
                self._add_token(TokenType.UNARY_MINUS, "-")
            if second_char == "!":
                self._add_token(TokenType.UNARY_NOT, "!")
            if second_char == "#":
                self._add_token(TokenType.UNARY_TO_STRING, "#")
            if second_char == "$":
                self._add_token(TokenType.UNARY_TO_INT, "$")
        elif first_char == "B":
            second_char = rest[0]
            if second_char == "+":
                self._add_token(TokenType.BINARY_PLUS, "+")
            elif second_char == "-":
                self._add_token(TokenType.BINARY_MINUS, "-")
            elif second_char == "*":
                self._add_token(TokenType.BINARY_MULTIPLY, "*")
            elif second_char == "/":
                self._add_token(TokenType.BINARY_DIVIDE, "/")
            elif second_char == "%":
                self._add_token(TokenType.BINARY_MODULO, "%")
            elif second_char == "<":
                self._add_token(TokenType.BINARY_ELSS_THAN, "<")
            elif second_char == ">":
                self._add_token(TokenType.BINARY_GREATER_THAN, ">")
            elif second_char == "=":
                self._add_token(TokenType.BINARY_EQUAL, "=")
            elif second_char == "|":
                self._add_token(TokenType.BINARY_OR, "|")
            elif second_char == "&":
                self._add_token(TokenType.BINARY_AND, "&")
            elif second_char == ".":
                self._add_token(TokenType.BINARY_STRING_CONCAT, ".")
            elif second_char == "T":
                self._add_token(TokenType.BINARY_STRING_TOP, "T")
            elif second_char == "D":
                self._add_token(TokenType.BINARY_STRING_DROP, "D")
            elif second_char == "$":
                self._add_token(TokenType.BINARY_APPLY, "$")
        elif first_char == "?":
            self._add_token(TokenType.IF, "IF")
        elif first_char == "L":
            self._add_token(TokenType.LAMBDA, icfp_to_int(rest))
        elif first_char == "v":
            self._add_token(TokenType.LAMBDA_VAR, icfp_to_int(rest))
        
           
            

        # c = self._advance()
        # # 一文字の字句
        # if c == "(":
        #     self._add_token(TokenType.LEFT_PAREN)
        # elif c == ")":
        #     self._add_token(TokenType.RIGHT_PAREN)
        # elif c == "{":
        #     self._add_token(TokenType.LEFT_BRACE)
        # elif c == "}":
        #     self._add_token(TokenType.RIGHT_BRACE)
        # elif c == ",":
        #     self._add_token(TokenType.COMMA)
        # elif c == ".":
        #     self._add_token(TokenType.DOT)
        # elif c == "-":
        #     self._add_token(TokenType.MINUS)
        # elif c == "+":
        #     self._add_token(TokenType.PLUS)
        # elif c == ";":
        #     self._add_token(TokenType.SEMICOLON)
        # elif c == "*":
        #     self._add_token(TokenType.STAR)
        # # 二文字の字句
        # elif c == "!":
        #     self._add_token(
        #         TokenType.BANG_EQUAL if self._match("=") else TokenType.BANG
        #     )
        # elif c == "=":
        #     self._add_token(
        #         TokenType.EQUAL_EQUAL if self._match("=") else TokenType.EQUAL
        #     )
        # elif c == "<":
        #     self._add_token(
        #         TokenType.LESS_EQUAL if self._match("=") else TokenType.LESS
        #     )
        # elif c == ">":
        #     self._add_token(
        #         TokenType.GREATER_EQUAL if self._match("=") else TokenType.GREATER
        #     )
        # elif c == "/":
        #     # コメント
        #     if self._match("/"):
        #         while self._peek() != "\n" and not self._is_at_end():
        #             self._advance()
        #     else:
        #         self._add_token(TokenType.SLASH)
        # # 改行空白など
        # elif c in [" ", "\r", "\t"]:
        #     pass
        # elif c == "\n":
        #     self.line += 1
        # # 文字列リテラル
        # elif c == '"':
        #     self._string()
        # # 数値リテラル
        # else:
        #     if self._is_digit(c):
        #         self._number()
        #     elif self._is_alpha(c):
        #         self._identifier()
        #     else:
        #         self.error_method(self.line, "Unexpected character.")
