import pygame
from pygame import K_UP, K_DOWN, K_LEFT, K_RIGHT

from models.screen import Screen


class Player(pygame.sprite.Sprite):
    def __init__(self, screen: Screen):
        self.screen = screen
        super(Player, self).__init__()
        self.surf = pygame.Surface((75, 25))
        self.surf.fill((0, 0, 0))
        self.rect = self.surf.get_rect()

    def update(self, pressed_keys):
        if pressed_keys[K_UP]:
            self.rect.move_ip(0, -5)
        if pressed_keys[K_DOWN]:
            self.rect.move_ip(0, 5)
        if pressed_keys[K_LEFT]:
            self.rect.move_ip(-5, 0)
        if pressed_keys[K_RIGHT]:
            self.rect.move_ip(5, 0)
        if self.rect.left < 0:
            self.rect.left = 0
        if self.rect.right > self.screen.width:
            self.rect.right = self.screen.width
        if self.rect.top <= 0:
            self.rect.top = 0
        if self.rect.bottom >= self.screen.height:
            self.rect.bottom = self.screen.height
