from enum import Enum
from random import seed
from random import randint


class Field:
    def __init__(self, rows, columns, initial_rows, bubble_types):
        seed(1)
        self.rows = rows
        self.columns = columns
        self.bubble_types = bubble_types
        self.bubbles_for_each_type = [0] * (bubble_types + 1)  # TODO change name
        print(self.bubbles_for_each_type)
        self.bubbles = [Field.generate_row(self.columns, self.bubble_types, i >= initial_rows) for i in range(rows)]
        print(self.bubbles)

    @staticmethod
    def generate_row(columns, n_bubble_types, is_empty):
        if is_empty:
            return [BubbleCeil.empty for i in range(columns)]
        return [Field.generate_bubble(n_bubble_types) for i in range(columns)]

    @staticmethod
    def generate_bubble(n_types):
        return BubbleCeil(randint(0, n_types))


class BubbleCeil(Enum):
    empty = 0
    red = 0
    blue = 2
    yellow = 3
    green = 4
    lightBlue = 5
    purple = 6
