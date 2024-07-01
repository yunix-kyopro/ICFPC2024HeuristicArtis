from dataclasses import dataclass
from TokenType import TokenType
from typing import Union


@dataclass
class Token:
    type: TokenType
    value: Union[str, int, bool]

    def to_string(self):
        return f"{self.type} {self.text} {self.text}"
