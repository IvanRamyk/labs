import pygame.sprite


class QueueElement(pygame.sprite.Sprite):
    def __init__(self, field, x, y, color_type, is_hidden):
        pygame.sprite.Sprite.__init__(self)
        self.isHidden = is_hidden
        self.size = field.bubble_size
        self.type = color_type
        self.field = field
        self.x = x
        self.y = y
        self.color = get_color_by_number(color_type) if not is_hidden else (180, 180, 180)
        self.image = pygame.Surface((self.size, self.size))
        pygame.draw.circle(self.image, self.color, (self.size // 2, self.size // 2), self.size // 2 - 1)
        self.rect = self.image.get_rect()
        self.rect.center = (self.x + self.size / 2, self.y + self.size / 2)


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
