from enum import Enum
from random import seed
from random import randint

import pygame

from models.bubble import Bubble


class Field:
    def __init__(self, rows, columns, initial_rows, bubble_types, bubble_size, sprites: pygame.sprite.Group):
        self.sprites = sprites
        seed(1)
        self.bubble_size = bubble_size
        self.rows = rows
        self.columns = columns
        self.bubble_types = bubble_types
        self.bubbles_for_each_type = [0] * (bubble_types + 1)  # TODO change name
        print(self.bubbles_for_each_type)
        self.bubbles = [self.generate_row(i, self.columns, self.bubble_types) for i in range(initial_rows)]
        for bubble_row in self.bubbles:
            for bubble in bubble_row:
                self.sprites.add(bubble)
        print(self.bubbles)

    def update(self):
        self.sprites.update()

    def generate_row(self, row, columns, n_bubble_types):
        return [self.generate_bubble(row, i, n_bubble_types) for i in range(columns)]

    def generate_bubble(self, row, column, n_types):
        return Bubble(self, row, column, randint(0, n_types))


class BubbleCeil(Enum):
    empty = 0
    red = 1
    blue = 2
    yellow = 3
    green = 4
    lightBlue = 5
    purple = 6
