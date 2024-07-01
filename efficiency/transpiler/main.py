from ICFPLang import ICFPLang
import sys
sys.setrecursionlimit(100000)
# from Token import Token
# from TokenType import TokenType
# # from generated.Expr import Expr, Binary, Grouping, Literal, Unary
# from AstPrinter import AstPrinter


def main():
    lox = ICFPLang()
    lox.interpret(sys.argv)
    # expression = Binary(
    #     Unary(
    #         Token(TokenType.MINUS, "-", None, 1),
    #         Literal(123),
    #     ),
    #     Token(TokenType.STAR, "*", None, 1),
    #     Grouping(Literal(45.67)),
    # )
    # ast_printer = AstPrinter()
    # print(ast_printer.print(expression))


if __name__ == "__main__":
    main()
