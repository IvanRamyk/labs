import math

import pygame.sprite


class Ball(pygame.sprite.Sprite):
    def __init__(self, field, x, y, color_type, speed):
        pygame.sprite.Sprite.__init__(self)
        self.size = field.bubble_size
        self.type = color_type
        self.field = field
        self.x = x
        self.y = y
        self.speed = speed
        self.moving = False  # TODO rename
        self.color_type = color_type
        self.color = get_color_by_number(color_type)
        self.image = pygame.Surface((self.size, self.size))
        pygame.draw.circle(self.image, self.color, (self.size // 2, self.size // 2), self.size // 2 - 2)
        self.rect = self.image.get_rect()
        self.rect.center = (self.x + self.size / 2, self.y + self.size / 2)
        self.velocity = (0, 0)

    def shoot(self, point):
        vel = point[0] - self.x, point[1] - self.y
        norm = math.sqrt(vel[0] ** 2 + vel[1] ** 2)
        self.velocity = vel[0] / norm, vel[1] / norm
        self.moving = True

    def check_collision(self):
        for bubble in self.field.bubble_sprites:
            if math.dist((bubble.rect.x, bubble.rect.y), (self.rect.x, self.rect.y)) <= self.size - 4:
                return True

    def update(self):
        if self.moving:
            self.rect.x += self.velocity[0] * self.speed
            self.rect.y += self.velocity[1] * self.speed
            if self.rect.x <= self.field.game_field_left():
                self.rect.x = 0
                self.velocity = (-self.velocity[0], self.velocity[1])
            if self.rect.x + self.size >= self.field.game_field_right():
                self.rect.x = self.field.game_field_right() - self.size
                self.velocity = (-self.velocity[0], self.velocity[1])
            # if pygame.sprite.spritecollideany(self, self.field.bubble_sprites) or self.rect.bottom <= 0:
            if self.check_collision() or self.rect.bottom <= 0:
                self.moving = False
                print("rect", self.rect)
                self.field.ball_stopped((self.rect.left + self.size // 2, self.rect.top + self.size // 2))
                self.rect.inflate_ip(self.velocity[0] * self.speed, self.velocity[1] * self.speed)


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
