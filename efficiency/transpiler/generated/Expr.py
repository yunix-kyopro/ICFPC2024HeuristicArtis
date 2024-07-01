# Path: plox/Expr.py
# This file was automatically generated by plox/tools/generate_ast.py
from typing import Any, List
from Token import Token
from abc import ABC, ABCMeta, abstractmethod


class Expr(ABC):
    @abstractmethod
    def accept(visitor: "ExprVisitor")-> Any:
        pass



class ExprVisitor(ABC):
    pass

    @abstractmethod
    def visit_binary_expr(self, expr:"Binary"):
        pass

    @abstractmethod
    def visit_unary_expr(self, expr:"Unary"):
        pass

    @abstractmethod
    def visit_if_expr(self, expr:"If"):
        pass

    @abstractmethod
    def visit_literal_expr(self, expr:"Literal"):
        pass

    @abstractmethod
    def visit_lambda_expr(self, expr:"Lambda"):
        pass

    @abstractmethod
    def visit_lambda_var_expr(self, expr:"Lambda_Var"):
        pass

class Binary(Expr):
    def __init__(self, operator:Token,left:Expr,right:Expr):
        self.operator = operator
        self.left = left
        self.right = right

    def accept(self, visitor: 'ExprVisitor') -> Any:
        return visitor.visit_binary_expr(self)

class Unary(Expr):
    def __init__(self, operator:Token,right:Expr):
        self.operator = operator
        self.right = right

    def accept(self, visitor: 'ExprVisitor') -> Any:
        return visitor.visit_unary_expr(self)

class If(Expr):
    def __init__(self, condition:Expr,then_branch:Expr,else_branch:Expr):
        self.condition = condition
        self.then_branch = then_branch
        self.else_branch = else_branch

    def accept(self, visitor: 'ExprVisitor') -> Any:
        return visitor.visit_if_expr(self)

class Literal(Expr):
    def __init__(self, operator:Token,value:object):
        self.operator = operator
        self.value = value

    def accept(self, visitor: 'ExprVisitor') -> Any:
        return visitor.visit_literal_expr(self)

class Lambda(Expr):
    def __init__(self, operator:Token,function:Expr):
        self.operator = operator
        self.function = function

    def accept(self, visitor: 'ExprVisitor') -> Any:
        return visitor.visit_lambda_expr(self)

class Lambda_Var(Expr):
    def __init__(self, operator:Token):
        self.operator = operator

    def accept(self, visitor: 'ExprVisitor') -> Any:
        return visitor.visit_lambda_var_expr(self)

