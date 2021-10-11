import pygame
import sys

from collections import defaultdict

from models.field import Field


class Game:
    def __init__(self,
                 caption,
                 width,
                 height,
                 rows,
                 columns,
                 bubble_types,
                 bubble_size,
                 frame_rate):



        self.frame_rate = frame_rate
        self.game_over = False
        all_sprites = pygame.sprite.Group()
        self.field = Field(rows, columns, rows // 2, bubble_types, bubble_size, all_sprites)

        pygame.mixer.pre_init(44100, 16, 2, 4096)
        pygame.init()
        pygame.font.init()
        self.surface = pygame.display.set_mode((width, height))
        pygame.display.set_caption(caption)
        self.clock = pygame.time.Clock()
        self.keydown_handlers = defaultdict(list)
        self.keyup_handlers = defaultdict(list)
        self.mouse_handlers = []

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                for handler in self.keydown_handlers[event.key]:
                    handler(event.key)
            elif event.type == pygame.KEYUP:
                for handler in self.keydown_handlers[event.key]:
                    handler(event.key)
            elif event.type in (pygame.MOUSEBUTTONDOWN,
                                pygame.MOUSEBUTTONUP,
                                pygame.MOUSEMOTION):
                for handler in self.mouse_handlers:
                    handler(event.type, event.pos)

    def run(self):
        while not self.game_over:
            self.handle_events()

            self.field.update()
            self.field.sprites.draw(self.surface)

            pygame.display.update()
            self.surface.fill((0, 0, 0))
            self.clock.tick(self.frame_rate)