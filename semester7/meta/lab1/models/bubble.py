import pygame.sprite


class Bubble(pygame.sprite.Sprite):
    def __init__(self, field, row, column, color_type):
        pygame.sprite.Sprite.__init__(self)
        self.size = field.bubble_size
        self.type = color_type
        self.row = row
        self.column = column
        self.field = field
        self.x = column * field.bubble_size
        if row % 2 == 1:
            self.x += field.bubble_size // 2
        self.y = row * self.size
        self.color = get_color_by_number(color_type)
        self.image = pygame.Surface((self.size, self.size))
        pygame.draw.circle(self.image, self.color, (self.size // 2, self.size // 2), self.size // 2 - 2)
        self.rect = self.image.get_rect()
        self.rect.center = (self.x + self.size / 2, self.y + self.size / 2)

    def move_up(self, rows):
        self.row += rows
        self.rect.y += rows * self.size


def get_color_by_number(color_type):
    if color_type == 0:
        return 255, 0, 0
    if color_type == 1:
        return 0, 255, 0
    if color_type == 2:
        return 0, 0, 255
    if color_type == 3:
        return 0, 255, 255
    if color_type == 4:
        return 255, 0, 255
    if color_type == 5:
        return 255, 255, 0
    return 255, 255, 255
