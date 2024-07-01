from typing import List, Any
import re
from generated.Expr import (
    ExprVisitor,
    Expr,
    Binary,
    Literal,
    Unary,
    If,
    Literal,
    Lambda,
    Lambda_Var
    # Variable,
    # Assign,
    # Logical,
    # Call,
)
# from generated.Stmt import (
#     StmtVisitor,
#     Print,
#     Expression,
#     Stmt,
#     Var,
#     Block,
#     If,
#     While,
#     Function,
#     Return,
# )
from TokenType import TokenType
from Token import Token
from Environment import Environment
from RunTimeError import RunTimeError
from Return import ReturnException
from Callable import Callable
from utils.converter import int_to_string, string_to_int

global_environment = Environment()



# global_environment.define("clock", Clock())


# # 関数
# class LoxFunction(LoxCallable):
#     def __init__(self, declaration: Function):
#         self.declaration = declaration
# 
#     def call(self, interpreter: "Interpreter", arguments: List[Any]):
#         environment = Environment(global_environment)
#         for i in range(len(self.declaration.params)):
#             environment.define(self.declaration.params[i].lexeme, arguments[i])
# 
#         try:
#             interpreter.execute_block(self.declaration.body, environment)
#         except ReturnException as return_value:
#             return return_value.value
# 
#         return None
# 
#     def arity(self):
#         return len(self.declaration.params)
# 
#     def to_string(self):
#         return f"<fn {self.declaration.name.lexeme}>"


class Transpiler(ExprVisitor):
    def __init__(self, runtime_error_method):
        self.runtime_error_method = runtime_error_method
        self.environment = global_environment
    
    def visit_binary_expr(self, expr: Binary):
        # BINARY_PLUS = 8
        # BINARY_MINUS = 9
        # BINARY_MULTIPLY = 10
        # BINARY_DIVIDE = 11
        # BINARY_MODULO = 12
        # BINARY_ELSS_THAN = 13
        # BINARY_GREATER_THAN = 14
        # BINARY_EQUAL = 15
        # BINARY_OR = 16
        # BINARY_AND = 17
        # BINARY_STRING_CONCAT = 18
        # BINARY_STRING_TOP = 19
        # BINARY_STRING_DROP = 20
        # BINARY_APPLY = 21
        if expr.operator.type == TokenType.BINARY_MINUS:
            return f"sub({self.evaluate(expr.left)},{self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_PLUS:
            return f"add({self.evaluate(expr.left)}, {self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_MULTIPLY:
            return f"mul({self.evaluate(expr.left)}, {self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_DIVIDE:
            return f"div({self.evaluate(expr.left)},{self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_MODULO:
            return f"mod({self.evaluate(expr.left)},{self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_ELSS_THAN:
            return f"lt({self.evaluate(expr.left)}, {self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_GREATER_THAN:
            return f"gt({self.evaluate(expr.left)}, {self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_EQUAL:
            return f"eq({self.evaluate(expr.left)},{self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_OR:
            return f"or({self.evaluate(expr.left)}, {self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_AND:
            return f"and({self.evaluate(expr.left)}, {self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_STRING_CONCAT:
            return f"concat({self.evaluate(expr.left)}, {self.evaluate(expr.right)})"
        elif expr.operator.type == TokenType.BINARY_STRING_TOP:
            return f"top({self.evaluate(expr.right)}, {self.evaluate(expr.left)})"
        elif expr.operator.type == TokenType.BINARY_STRING_DROP:
            # return self.evaluate(expr.right)[self.evaluate(expr.left):]
            return f"drop({self.evaluate(expr.right)},{self.evaluate(expr.left)})"
        elif expr.operator.type == TokenType.BINARY_APPLY:
            return f"app({self.evaluate(expr.left)},{self.evaluate(expr.right)})"
            # # leftは ((v[0..9]+) => (xxxx))
            # # という形式の文字列。。ここでv[0..9]を抽出する
            # left = self.evaluate(expr.left)
            # pattern = r"\(v(\d+)\) =>(.*)\)"

            # matched = re.search(pattern, left)
            # # print(matched.group(1))
            # # print(matched.group(2))
            # if matched:
            #     tmp_var_name = f"v{matched.group(1)}"
            #     expression = matched.group(2)
            #     return expression.replace(tmp_var_name, self.evaluate(expr.right))
            # else:
            #     # print(left)
            #     # raise Exception("Unreachable Binary")
            #     return f"{left}({self.evaluate(expr.right)})"

            




            #return f"{self.evaluate(expr.left)}({self.evaluate(expr.right)})"
            # tmp_var_name = f"v{expr.operator.value}"
            # print("temp var name:", tmp_var_name)
            # self.environment.define(tmp_var_name, self.evaluate(expr.right))
            # ret = self.evaluate(expr.left)
            # self.environment.erase(tmp_var_name)
            # return ret
        raise Exception("Unreachable Binary")


    def visit_unary_expr(self, expr: Unary):
        # UNARY_MINUS = 4
        # UNARY_NOT = 5
        # UNARY_TO_INT = 6
        # UNARY_TO_STRING = 7
        if expr.operator.type == TokenType.UNARY_MINUS:
            # return -self.evaluate(expr.right)
            return f"-{self.evaluate(expr.right)}"
        elif expr.operator.type == TokenType.UNARY_NOT:
            # return not self.evaluate(expr.right)
            return f"!{self.evaluate(expr.right)}"
        elif expr.operator.type == TokenType.UNARY_TO_INT:
            # return string_to_int(self.evaluate(expr.right))
            return f"{string_to_int(self.evaluate(expr.right))}"
        elif expr.operator.type == TokenType.UNARY_TO_STRING:
            # return int_to_string(self.evaluate(expr.right))
            return f"'{int_to_string(self.evaluate(expr.right))}'"
        raise Exception("Unreachable Unary")

    def visit_if_expr(self, expr: If):
        return f"if_({self.evaluate(expr.condition)}, {self.evaluate(expr.then_branch)},{self.evaluate(expr.else_branch)})"
        # if self.evaluate(expr.condition):
        #     return self.evaluate(expr.then_branch)
        # else:
        #     return self.evaluate(expr.else_branch)

    def visit_literal_expr(self, expr: Literal):
        # return expr.value
        if expr.operator.type == TokenType.STRING:
            return f'string("{expr.operator.value}")'
        elif expr.operator.type == TokenType.INTEGER:
            return f"integer({int(expr.operator.value)})"
        elif expr.operator.type == TokenType.TRUE:
            return "true_()"
        elif expr.operator.type == TokenType.FALSE:
            return "false_()"


    def visit_lambda_expr(self, expr: Lambda):
        # return self.evaluate(expr.function)
        return f"lambda(v{expr.operator.value} =>" +f"{self.evaluate(expr.function)})" 

    def visit_lambda_var_expr(self, expr: Lambda_Var):
        # return self.environment.get(f"v{expr.operator.value}")
        return f"v{expr.operator.value}"

    def evaluate(self, expr: Expr)->str:
        return expr.accept(self)




    # def interpret(self, statements: List[Stmt]):
    #     try:
    #         for stmt in statements:
    #             self.evaluate(stmt)
    #     except RunTimeError as error:
    #         print(error)
    #         self.runtime_error_method(error)

    # def evaluate(self, expr: Expr):
    #     return expr.accept(self)

    # def execute(self, stmt: Stmt):
    #     stmt.accept(self)

    # def execute_block(self, statements: List[Stmt], environment: Environment):
    #     previous = self.environment
    #     try:
    #         self.environment = environment
    #         for stmt in statements:
    #             self.execute(stmt)
    #     finally:
    #         self.environment = previous

    # # 文の評価
    # def visit_expression_stmt(self, stmt: Expression) -> None:
    #     self.evaluate(stmt.expression)
    #     return None

    # def visit_function_stmt(self, stmt: Function) -> None:
    #     function = LoxFunction(stmt)
    #     self.environment.define(stmt.name.lexeme, function)
    #     return None

    # def visit_print_stmt(self, stmt: Print) -> None:
    #     value = self.evaluate(stmt.expression)
    #     print(self.stringify(value))
    #     return None

    # def visit_var_stmt(self, stmt: Var) -> None:
    #     value = None
    #     if stmt.initializer is not None:
    #         value = self.evaluate(stmt.initializer)
    #     self.environment.define(stmt.name.lexeme, value)
    #     return None

    # def visit_block_stmt(self, stmt: Block) -> None:
    #     self.execute_block(stmt.statements, Environment(self.environment))
    #     return None

    # def visit_if_stmt(self, stmt: If) -> None:
    #     if self.is_truthy(self.evaluate(stmt.condition)):
    #         self.execute(stmt.then_branch)
    #     elif stmt.else_branch is not None:
    #         self.execute(stmt.else_branch)
    #     return None

    # def visit_while_stmt(self, stmt: While) -> None:
    #     while self.is_truthy(self.evaluate(stmt.condition)):
    #         self.execute(stmt.body)
    #     return None

    # def visit_return_stmt(self, stmt: Return) -> None:
    #     value = None
    #     if stmt.value is not None:
    #         value = self.evaluate(stmt.value)
    #     raise ReturnException(value)

    # # 式の評価
    # def visit_assign_expr(self, expr: Assign):
    #     value = self.evaluate(expr.value)
    #     self.environment.assign(expr.name, value)
    #     return value

    # def visit_binary_expr(self, expr: Binary):
    #     left = self.evaluate(expr.left)
    #     right = self.evaluate(expr.right)

    #     if expr.operator.type == TokenType.MINUS:
    #         self.check_number_operands(expr.operator, left, right)
    #         return left - right
    #     elif expr.operator.type == TokenType.SLASH:
    #         self.check_number_operands(expr.operator, left, right)
    #         return left / right
    #     elif expr.operator.type == TokenType.STAR:
    #         self.check_number_operands(expr.operator, left, right)
    #         return left * right
    #     elif expr.operator.type == TokenType.PLUS:
    #         if isinstance(left, float) and isinstance(right, float):
    #             return left + right
    #         elif isinstance(left, str) and isinstance(right, str):
    #             return left + right
    #         else:
    #             raise RuntimeError(
    #                 expr.operator, "Operands must be two numbers or two strings."
    #             )
    #     elif expr.operator.type == TokenType.GREATER:
    #         self.check_number_operands(expr.operator, left, right)
    #         return left > right
    #     elif expr.operator.type == TokenType.GREATER_EQUAL:
    #         self.check_number_operands(expr.operator, left, right)
    #         return left >= right
    #     elif expr.operator.type == TokenType.LESS:
    #         self.check_number_operands(expr.operator, left, right)
    #         return left < right
    #     elif expr.operator.type == TokenType.LESS_EQUAL:
    #         self.check_number_operands(expr.operator, left, right)
    #         return left <= right
    #     elif expr.operator.type == TokenType.BANG_EQUAL:
    #         return not self.is_equal(left, right)
    #     elif expr.operator.type == TokenType.EQUAL_EQUAL:
    #         return self.is_equal(left, right)

    #     # Unreachable.
    #     return None

    # def visit_logical_expr(self, expr: Logical):
    #     left = self.evaluate(expr.left)

    #     if expr.operator.type == TokenType.OR:
    #         if self.is_truthy(left):
    #             return left
    #     else:
    #         if not self.is_truthy(left):
    #             return left

    #     return self.evaluate(expr.right)

    # def visit_grouping_expr(self, expr: Grouping):
    #     return self.evaluate(expr.expression)

    # def visit_literal_expr(self, expr: Literal):
    #     return expr.value

    # def visit_unary_expr(self, expr: Unary):
    #     right = self.evaluate(expr.right)

    #     if expr.operator.type == TokenType.MINUS:
    #         self.check_number_operand(expr.operator, right)
    #         return -right
    #     elif expr.operator.type == TokenType.BANG:
    #         return not self.is_truthy(right)

    #     # Unreachable.
    #     return None

    # def visit_variable_expr(self, expr: Variable):
    #     return self.environment.get(expr.name)

    # def visit_call_expr(self, expr: Call):
    #     callee = self.evaluate(expr.callee)  # evaluateした結果どうしてCllableになるのか?
    #     arguments = [self.evaluate(argument) for argument in expr.arguments]

    #     if not isinstance(callee, LoxCallable):
    #         raise RunTimeError(expr.paren, "Can only call functions and classes.")

    #     function: LoxCallable = callee
    #     if len(arguments) != function.arity():
    #         raise RunTimeError(
    #             expr.paren,
    #             f"Expected {function.arity()} arguments but got {len(arguments)}.",
    #         )
    #     return function.call(self, arguments)

    # # インフラなど
    # def check_number_operand(self, operator: Token, operand):
    #     if isinstance(operand, float):
    #         return
    #     raise RunTimeError(operator, "Operand must be a number.")

    # def check_number_operands(self, operator: Token, left, right):
    #     if isinstance(left, float) and isinstance(right, float):
    #         return
    #     raise RunTimeError(operator, "Operands must be numbers.")

    # def is_truthy(self, obj):
    #     if obj is None:
    #         return False
    #     if isinstance(obj, bool):
    #         return obj
    #     return True

    # def stringify(self, obj):
    #     if obj is None:
    #         return "nil"
    #     if isinstance(obj, float):
    #         text = str(obj)
    #         if text.endswith(".0"):
    #             text = text[:-2]
    #         return text
    #     return str(obj)
