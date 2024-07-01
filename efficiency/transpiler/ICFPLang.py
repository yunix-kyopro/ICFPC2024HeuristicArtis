import sys
from typing import List
from Scanner import Scanner
from Token import Token
from TokenType import TokenType
from Parser import Parser
from AstPrinter import AstPrinter
from Interpreter import Interpreter, RunTimeError
from Transpiler import Transpiler
from PyTranspiler import PyTranspiler


class ICFPLang:
    hadError = False
    hadRuntimeError = False

    def __init__(self):
        pass

    @classmethod
    def interpret(cls, args: List[str]):
        cls.interpreter = Interpreter(cls.runtime_error)
        if len(args) > 2:
            print(f"Usage: plox [script]")
            sys.exit(64)
        elif len(args) == 2:
            cls._run_file(args[1])
        else:
            cls._run_prompt()

    @classmethod
    def _run_file(cls, path: str):
        print("run file")
        with open(path, "r") as f:
            cls.run(f.read())

        if cls.hadError:
            sys.exit(65)

    @classmethod
    def _run_prompt(cls):
        while True:
            line = input("> ")
            if not line:
                break
            cls.run(line)
            cls.hadError = False

    @classmethod
    def run(cls, source: str):
        scanner = Scanner(source, cls._error)
        tokens = scanner.scan_tokens()
        # print(tokens)

        # for token in tokens:
        # print(token.to_string())
        parser = Parser(tokens, cls.error)
        expr = parser.expression()
        # print(expr)

        transpiler = Transpiler(cls.runtime_error)
        result = transpiler.evaluate(expr)
        print("result:", result)

        # statements = parser.parse()
        # if cls.hadError:
        #     return

        # result = cls.interpreter.evaluate(expr)
        # print("result:", result)

        ast_printer = AstPrinter()
        #2rint(ast_printer.print(expr))

    @classmethod
    def _error(cls, line: int, message: str):
        cls.report(line, "", message)

    @classmethod
    def report(cls, line: int, where: str, message: str):
        print(f"[line {line}] Error{where}: {message}")
        cls.hadError = True

    @classmethod
    def error(cls, token: Token, message: str):
        if token.type == TokenType.EOF:
            cls.report(token.line, " at end", message)
        else:
            cls.report(token.line, f" at '{token.lexeme}'", message)
        print("parser error", cls.hadError)

    @classmethod
    def runtime_error(cls, runtime_error: RunTimeError):
        print(f"{runtime_error}\n[line {runtime_error.token.line}]")
        cls.hadRuntimeError = True
