from abc import ABC, ABCMeta, abstractmethod


class Callable(ABC):
    def call(self, interpreter, arguments):
        pass

    def arity(self):
        pass
