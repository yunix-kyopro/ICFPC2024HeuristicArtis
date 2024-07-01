from generated.Expr import ExprVisitor, Expr, Binary, Unary, If, Literal, Lambda, Lambda_Var


class AstPrinter(ExprVisitor):
    def __init__(self):
        pass

    def print(self, expr: Expr) -> str:
        return expr.accept(self)

    def visit_binary_expr(self, expr: Binary) -> str:
        return self.parenthesize(expr.operator.value, expr.left, expr.right)
    
    def visit_unary_expr(self, expr: Unary) -> str:
        return self.parenthesize(expr.operator.value, expr.right)
    
    def visit_if_expr(self, expr: If) -> str:
        return self.parenthesize("if", expr.condition, expr.then_branch, expr.else_branch)
    
    def visit_literal_expr(self, expr: Literal) -> str:
        return self.parenthesize("literal "+str(expr.value))
    
    def visit_lambda_expr(self, expr: Lambda) -> str:
        return self.parenthesize(f"lambda v{expr.operator.value}",  expr.function)
    
    def visit_lambda_var_expr(self, expr: Lambda_Var) -> str:
        return self.parenthesize(f"v{expr.operator.value}")

    # def visit_grouping_expr(self, expr: Grouping) -> str:
    #     return self.parenthesize("group", expr.expression)

    # def visit_literal_expr(self, expr: Literal) -> str:
    #     if expr.value is None:
    #         return "nil"
    #     return str(expr.value)

    # def visit_unary_expr(self, expr: Unary) -> str:
    #     return self.parenthesize(expr.operator.lexeme, expr.right)

    def parenthesize(self, name: str, *exprs: Expr) -> str:
        builder = []
        builder.append("(")
        builder.append(name)
        for expr in exprs:
            builder.append(" ")
            builder.append(expr.accept(self))
        builder.append(")")

        return "".join(builder)
