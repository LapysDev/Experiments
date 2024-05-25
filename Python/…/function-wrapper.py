from typing import Callable

def function(callback: Callable[[int, int], str], *arguments, **keywordArguments):
  return callback(*arguments, **keywordArguments)
