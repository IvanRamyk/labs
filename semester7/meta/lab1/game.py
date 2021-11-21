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
                 speed,
                 frame_rate):



        self.frame_rate = frame_rate
        self.game_over = False
        all_sprites = pygame.sprite.Group()
        self.field = Field(rows, columns, rows // 2, bubble_types, bubble_size, speed, all_sprites)

        pygame.mixer.pre_init(44100, 16, 2, 4096)
        pygame.init()
        pygame.font.init()
        self.surface = pygame.display.set_mode((width, height))
        pygame.display.set_caption(caption)
        self.clock = pygame.time.Clock()
        self.keydown_handlers = defaultdict(list)
        self.keyup_handlers = defaultdict(list)
        self.mouse_handlers = [self.field.shoot_to_point]

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type in (pygame.MOUSEBUTTONUP,):
                for handler in self.mouse_handlers:
                    handler(event.pos)

    def run(self):
        while not self.game_over:
            self.handle_events()

            self.field.update()
            self.field.sprites.draw(self.surface)
            x_min = 0
            y_min = 0
            x_max = (self.field.columns + 0.5) * self.field.bubble_size
            y_max = self.field.rows * self.field.bubble_size
            pygame.draw.line(self.surface, (200, 200, 200), (x_min, y_max),
                             (x_max, y_max))
            pygame.draw.line(self.surface, (200, 200, 200), (x_max, y_min), (x_max, y_max))
            pygame.display.update()
            self.surface.fill((0, 0, 0))
            self.clock.tick(self.frame_rate)