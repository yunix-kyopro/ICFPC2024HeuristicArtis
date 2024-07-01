from Token import Token


class RunTimeError(Exception):
    def __init__(self, token: Token, message: str):
        self.token = token
        self.message = message
