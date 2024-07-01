from typing import List
from Token import Token
from TokenType import TokenType
from typing import List, Any
from generated.Expr import (
    Expr,
    Binary,
    # Grouping,
    Literal,
    Unary,
    Lambda,
    Lambda_Var,
    If
    # Variable,
    # Assign,
    # Logical,
    # Call,
)



class ParseError(Exception):
    pass


class Parser:
    def __init__(self, tokens: List[Token], error_method: Any):
        self.tokens = tokens
        self.current = 0
        self.error_method = error_method

    # def parse(self) -> List[Stmt]:
    #     statements = []
    #     while not self.is_at_end():
    #         statements.append(self.declaration())

    #     return statements

    # # 再起効果構文解析による文の分析
    # def declaration(self) -> Stmt:
    #     try:
    #         if self.match(TokenType.VAR):
    #             return self.declaration()
    #         return self.statement()
    #     except ParseError:
    #         self.synchronize()
    #         return None

    # def statement(self) -> Stmt:
    #     if self.match(TokenType.IF):
    #         return self.if_statement()
    #     if self.match(TokenType.PRINT):
    #         return self.print_statement()
    #     if self.match(TokenType.LEFT_BRACE):
    #         return Block(self.block())
    #     if self.match(TokenType.RETURN):
    #         return self.return_statement()
    #     if self.match(TokenType.WHILE):
    #         return self.while_statement()
    #     if self.match(TokenType.FOR):
    #         return self.for_statement()
    #     if self.match(TokenType.FUN):
    #         return self.function("function")

    #     return self.expression_statement()

    # def if_statement(self) -> Stmt:
    #     self.consume(TokenType.LEFT_PAREN, "Expect '(' after 'if'.")
    #     condition = self.expression()
    #     self.consume(TokenType.RIGHT_PAREN, "Expect ')' after if condition.")
    #     then_branch = self.statement()
    #     else_branch = None
    #     if self.match(TokenType.ELSE):
    #         else_branch = self.statement()
    #     return If(condition, then_branch, else_branch)

    # def print_statement(self) -> Stmt:
    #     value = self.expression()
    #     self.consume(TokenType.SEMICOLON, "Expect ';' after value.")
    #     return Print(value)

    # def return_statement(self) -> Stmt:
    #     keyword = self.previous()
    #     value = None
    #     if not self.check(TokenType.SEMICOLON):
    #         value = self.expression()
    #     self.consume(TokenType.SEMICOLON, "Expect ';' after return value.")
    #     return Return(keyword, value)

    # def block(self) -> List[Stmt]:
    #     statements = []
    #     while not self.check(TokenType.RIGHT_BRACE) and not self.is_at_end():
    #         statements.append(self.declaration())

    #     self.consume(TokenType.RIGHT_BRACE, "Expect '}' after block.")
    #     return statements

    # def expression_statement(self) -> Stmt:
    #     expr = self.expression()
    #     self.consume(TokenType.SEMICOLON, "Expect ';' after expression.")
    #     return Expression(expr)

    # def declaration(self) -> Stmt:
    #     try:
    #         if self.match(TokenType.VAR):
    #             return self.var_declaration()
    #         return self.statement()
    #     except ParseError:
    #         self.synchronize()
    #         return None

    # def var_declaration(self) -> Stmt:
    #     name = self.consume(TokenType.IDENTIFIER, "Expect variable name.")
    #     initializer = None
    #     if self.match(TokenType.EQUAL):
    #         initializer = self.expression()
    #     self.consume(TokenType.SEMICOLON, "Expect ';' after variable declaration.")
    #     return Var(name, initializer)

    # def while_statement(self) -> Stmt:
    #     self.consume(TokenType.LEFT_PAREN, "Expect '(' after 'while'.")
    #     condition = self.expression()
    #     self.consume(TokenType.RIGHT_PAREN, "Expect ')' after condition.")
    #     body = self.statement()
    #     return While(condition, body)

    # def for_statement(self) -> Stmt:
    #     self.consume(TokenType.LEFT_PAREN, "Expect '(' after 'for'.")
    #     initializer = None
    #     if self.match(TokenType.SEMICOLON):
    #         initializer = None
    #     elif self.match(TokenType.VAR):
    #         initializer = self.var_declaration()
    #     else:
    #         initializer = self.expression_statement()

    #     condition = None
    #     if not self.check(TokenType.SEMICOLON):
    #         condition = self.expression()
    #     self.consume(TokenType.SEMICOLON, "Expect ';' after loop condition.")

    #     increment = None
    #     if not self.check(TokenType.RIGHT_PAREN):
    #         increment = self.expression()
    #     self.consume(TokenType.RIGHT_PAREN, "Expect ')' after for clauses.")

    #     body = self.statement()

    #     if increment is not None:
    #         body = Block([body, Expression(increment)])

    #     if condition is None:
    #         condition = Literal(True)
    #     body = While(condition, body)

    #     if initializer is not None:
    #         body = Block([initializer, body])

    #     return body

    # def function(self, kind: str) -> Stmt:
    #     name = self.consume(TokenType.IDENTIFIER, f"Expect {kind} name.")
    #     self.consume(TokenType.LEFT_PAREN, f"Expect '(' after {kind} name.")
    #     parameters = []
    #     if not self.check(TokenType.RIGHT_PAREN):
    #         parameters.append(
    #             self.consume(TokenType.IDENTIFIER, "Expect parameter name.")
    #         )
    #         while self.match(TokenType.COMMA):
    #             if len(parameters) >= 255:
    #                 self.error(self.peek(), "Can't have more than 255 parameters.")
    #             parameters.append(
    #                 self.consume(TokenType.IDENTIFIER, "Expect parameter name.")
    #             )
    #     self.consume(TokenType.RIGHT_PAREN, "Expect ')' after parameters.")
    #     self.consume(TokenType.LEFT_BRACE, f"Expect '{{' before {kind} body.")
    #     body = self.block()
    #     return Function(name, parameters, body)

    # 以下、再帰下降構文解析による式の分析


    def expression(self) -> Expr:
        # print(self.peek())
        return self.binary_operation()
    
    def binary_operation(self) -> Expr:
        if self.match(
            TokenType.BINARY_AND,
            TokenType.BINARY_OR,
            TokenType.BINARY_EQUAL,
            TokenType.BINARY_STRING_CONCAT,
            TokenType.BINARY_STRING_TOP,
            TokenType.BINARY_STRING_DROP,
            TokenType.BINARY_APPLY,
            TokenType.BINARY_DIVIDE,
            TokenType.BINARY_GREATER_THAN,
            TokenType.BINARY_MINUS,
            TokenType.BINARY_MODULO,
            TokenType.BINARY_MULTIPLY,
            TokenType.BINARY_PLUS,
            TokenType.BINARY_ELSS_THAN,
        ):
            operator = self.previous()
            left = self.expression()
            right = self.expression()
            return Binary(operator, left, right)
        
        return self.unary_operation()
    
    def unary_operation(self) -> Expr:
        if self.match(
            TokenType.UNARY_MINUS,
            TokenType.UNARY_NOT,
            TokenType.UNARY_TO_INT,
            TokenType.UNARY_TO_STRING,
        ):
            operator = self.previous()
            right = self.expression()
            return Unary(operator, right)
        
        return self.if_expression()
    
    def if_expression(self) -> Expr:
        if self.match(
            TokenType.IF,
        ):
            condition = self.expression()
            then_branch = self.expression()
            else_branch = self.expression()
            return If(condition, then_branch, else_branch)
        
        return self.lambda_expression()
    
    def lambda_expression(self) -> Expr:
        if self.match(
            TokenType.LAMBDA,
        ):
            operator = self.previous()
            function = self.expression()
            return Lambda(operator, function)
        
        return self.lambda_var_expression()
    
    def _find_lambda_var_name(self, depth: int) -> str:
        self.current += 1

        if self.tokens[self.current].type == TokenType.LAMBDA_VAR:
            depth -= 1
        elif self.tokens[self.current].type == TokenType.LAMBDA:
            depth += 1
        else: 
            raise Exception("parse lambda depth error")
        
        if depth == 0:
            result = f"v{self.tokens[self.current].value}"
        else:
            result = self._find_lambda_var_name(depth)
        
        self.current -= 1
        return result
        




    
    
    def lambda_var_expression(self) -> Expr:
        if self.match(
            TokenType.LAMBDA_VAR,
        ):
            operator = self.previous()
            return Lambda_Var(operator)
        
        return self.literal_expression()
    
    def literal_expression(self) -> Expr:
        if self.match(
            TokenType.TRUE,
            TokenType.FALSE,
            TokenType.STRING,
            TokenType.INTEGER,
        ):
            return Literal(self.previous(), self.previous().value)

        # print(self.peek())
        raise Exception("not reach here")

    
    # def assignment(self) -> Expr:
    #     expr = self._or()
    #     if self.match(TokenType.EQUAL):
    #         equals = self.previous()
    #         value = self.assignment()
    #         if isinstance(expr, Variable):
    #             name = expr.name
    #             return Assign(name, value)
    #         self.error(equals, "Invalid assignment target.")
    #     return expr

    # def _or(self) -> Expr:
    #     expr = self._and()
    #     while self.match(TokenType.OR):
    #         operator = self.previous()
    #         right = self._and()
    #         expr = Logical(expr, operator, right)
    #     return expr

    # def _and(self) -> Expr:
    #     expr = self.equality()

    #     while self.match(TokenType.AND):
    #         operator = self.previous()
    #         right = self.equality()
    #         expr = Logical(expr, operator, right)

    #     return expr

    # def equality(self) -> Expr:
    #     expr = self.comparison()
    #     while self.match(TokenType.BANG_EQUAL, TokenType.EQUAL_EQUAL):
    #         operator = self.previous()
    #         right = self.comparison()
    #         expr = Binary(expr, operator, right)
    #     return expr

    # def comparison(self) -> Expr:
    #     expr = self.term()
    #     while self.match(
    #         TokenType.GREATER,
    #         TokenType.GREATER_EQUAL,
    #         TokenType.LESS,
    #         TokenType.LESS_EQUAL,
    #     ):
    #         operator = self.previous()
    #         right = self.term()
    #         expr = Binary(expr, operator, right)

    #     return expr

    # def term(self) -> Expr:
    #     expr = self.factor()
    #     while self.match(TokenType.MINUS, TokenType.PLUS):
    #         operator = self.previous()
    #         right = self.factor()
    #         expr = Binary(expr, operator, right)
    #     return expr

    # def factor(self) -> Expr:
    #     expr = self.unary()
    #     while self.match(TokenType.SLASH, TokenType.STAR):
    #         operator = self.previous()
    #         right = self.unary()
    #         expr = Binary(expr, operator, right)
    #     return expr

    # def unary(self) -> Expr:
    #     if self.match(TokenType.BANG, TokenType.MINUS):
    #         operator = self.previous()
    #         right = self.unary()
    #         return Unary(operator, right)
    #     return self.call()

    # def finish_call(self, callee: Expr) -> Expr:
    #     arguments = []
    #     if not self.check(TokenType.RIGHT_PAREN):
    #         arguments.append(self.expression())
    #         while self.match(TokenType.COMMA):
    #             if len(arguments) >= 255:
    #                 self.error(self.peek(), "Can't have more than 255 arguments.")
    #             arguments.append(self.expression())
    #     paren = self.consume(TokenType.RIGHT_PAREN, "Expect ')' after arguments.")
    #     return Call(callee, paren, arguments)

    # def call(self) -> Expr:
    #     expr = self.primary()
    #     while True:
    #         if self.match(TokenType.LEFT_PAREN):
    #             expr = self.finish_call(expr)
    #         else:
    #             break

    #     return expr

    # def primary(self) -> Expr:
    #     if self.match(TokenType.FALSE):
    #         return Literal(False)
    #     if self.match(TokenType.TRUE):
    #         return Literal(True)
    #     if self.match(TokenType.NIL):
    #         return Literal(None)
    #     if self.match(TokenType.NUMBER, TokenType.STRING):
    #         return Literal(self.previous().literal)
    #     if self.match(TokenType.LEFT_PAREN):
    #         expr = self.expression()
    #         self.consume(TokenType.RIGHT_PAREN, "Expect ')' after expression.")
    #         return Grouping(expr)
    #     if self.match(TokenType.IDENTIFIER):
    #         return Variable(self.previous())

    #     raise self.error(self.peek(), "Expect expression.")

    # インフラの類
    def match(self, *types: TokenType) -> bool:
        for type in types:
            if self.check(type):
                self.advance()
                return True
        return False

    def check(self, type: TokenType) -> bool:
        if self.is_at_end():
            return False
        return self.peek().type == type

    def advance(self) -> Token:
        if not self.is_at_end():
            self.current += 1
        return self.previous()

    def previous(self) -> Token:
        return self.tokens[self.current - 1]

    def peek(self) -> Token:
        return self.tokens[self.current]

    def is_at_end(self) -> bool:
        return self.peek().type == TokenType.EOF

    def consume(self, type: TokenType, message: str) -> Token:
        if self.check(type):
            return self.advance()
        raise self.error(self.peek(), message)

    def error(self, token: Token, message: str) -> Exception:
        print(f"[line {token.line}] Error {message}")
        self.error_method(token, message)
        return ParseError(message)

    # def synchronize(self) -> None:
    #     self.advance()
    #     while not self.is_at_end():
    #         if self.previous().type == TokenType.SEMICOLON:
    #             return
    #         if self.peek().type in (
    #             TokenType.CLASS,
    #             TokenType.FUN,
    #             TokenType.VAR,
    #             TokenType.FOR,
    #             TokenType.IF,
    #             TokenType.WHILE,
    #             TokenType.PRINT,
    #             TokenType.RETURN,
    #         ):
    #             return
    #         self.advance()
