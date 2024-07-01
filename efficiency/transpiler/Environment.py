from typing import Any
from Token import Token
from RunTimeError import RunTimeError


class Environment:
    def __init__(self, enclosing: "Environment" = None):
        self.values = dict()
        self.enclosing = enclosing

    def define(self, name: str, value: Any):
        self.values[name] = value
    
    def get(self, name: str):
        if name in self.values.keys():
            return self.values[name]
        
        return 0
        # raise RunTimeError(name, f"Undefined variable '{name}'.")
    
    def erase(self, name: str):
        self.values.pop(name)
        return 
        # raise RunTimeError(name, f"Undefined variable '{name}'.")

    # def get(self, name: Token):
    #     if name.lexeme in self.values.keys():
    #         return self.values[name.lexeme]

    #     if self.enclosing is not None:
    #         return self.enclosing.get(name)

    #     raise RunTimeError(name, f"Undefined variable '{name.lexeme}'.")

    # def assign(self, name: Token, value: Any):
    #     if name.lexeme in self.values.keys():
    #         self.values[name.lexeme] = value
    #         return

    #     if self.enclosing is not None:
    #         self.enclosing.assign(name, value)
    #         return

    #     raise RunTimeError(name, f"Undefined variable '{name.lexeme}'.")
