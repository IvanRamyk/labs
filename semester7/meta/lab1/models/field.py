from random import seed
from random import randint

import pygame

from models.ball import Ball
from models.bubble import Bubble
from models.queue_element import QueueElement


class Field:
    def __init__(self, rows, columns, initial_rows, bubble_types, bubble_size, speed, sprites: pygame.sprite.Group):
        seed()
        self.sprites = sprites
        self.bubble_size = bubble_size
        self.speed = speed
        self.rows = rows
        self.columns = columns
        self.bubble_types = bubble_types
        self.bubbles_for_each_type = [0] * (bubble_types + 1)
        self.bubbles = [self.generate_row(i, self.columns, self.bubble_types) for i in range(initial_rows)]
        self.bubble_sprites = []
        self.bubble_map = dict()
        for bubble_row in self.bubbles:
            for bubble in bubble_row:
                self.sprites.add(bubble)
                self.bubble_sprites.append(bubble)
                self.bubble_map[(bubble.column, bubble.row)] = bubble
        self.game_field = ((0, 0), ((self.columns + 0.5) * self.bubble_size, self.rows * self.bubble_size))
        self.queue_y = self.bubble_size * (self.rows + 1)
        self.queue = []
        self.generate_new_queue(6)
        self.ball = self.generate_new_ball(-1)
        self.sprites.add(self.ball)
        self.ready_to_shoot = True

    def game_field_left(self):
        return self.game_field[0][0]

    def game_field_right(self):
        return self.game_field[1][0]

    def game_field_bottom(self):
        return self.game_field[1][1]

    def game_field_up(self):
        return self.game_field[0][1]

    def update(self):
        self.sprites.update()
        self.ball.update()

    def shoot_to_point(self, point):
        if self.ready_to_shoot:
            self.ready_to_shoot = False
            self.ball.shoot(point)

    def nearest_bubble_center(self, position):
        x = position[0]
        y = position[1]
        y -= self.bubble_size // 2
        prev_row = y // self.bubble_size
        row = prev_row if abs(y - prev_row * self.bubble_size) < abs(y - (prev_row + 1) * self.bubble_size) else \
            prev_row + 1
        x -= self.bubble_size // 2
        if row % 2:
            x -= self.bubble_size // 2
        prev_column = x // self.bubble_size
        column = prev_column if abs(x - prev_column * self.bubble_size) < abs(x - (prev_column + 1) * self.bubble_size) \
            else prev_column + 1
        if column >= self.columns:
            column -= 1
        return row, column

    def ball_stopped(self, position):
        new_bubble_position = self.nearest_bubble_center(position)
        self.ball.kill()
        new_bubble = Bubble(self, new_bubble_position[0], new_bubble_position[1], self.ball.color_type)
        self.bubble_sprites.append(new_bubble)
        self.sprites.add(new_bubble)
        self.bubble_map[(new_bubble.column, new_bubble.row)] = new_bubble
        generate_new_queue_element = False
        if self.count_color_group(new_bubble.column, new_bubble.row) > 2:
            self.delete_color_group(new_bubble.column, new_bubble.row)
            self.delete_bubbles_in_air()
            generate_new_queue_element = True
        if not self.process_queue(generate_new_queue_element):
            self.generate_rows()
        self.ready_to_shoot = True

    def generate_rows(self):
        new_bubble_map = dict()
        for key in self.bubble_map:
            new_bubble_map[(key[0], key[1] + 2)] = self.bubble_map[key]
            new_bubble_map[(key[0], key[1] + 2)].move_up(2)
        self.bubble_map = new_bubble_map
        new_bubbles = [self.generate_row(i, self.columns, self.bubble_types) for i in range(2)]
        for bubble_row in new_bubbles:
            for bubble in bubble_row:
                self.sprites.add(bubble)
                self.bubble_sprites.append(bubble)
                self.bubble_map[(bubble.column, bubble.row)] = bubble

    def delete_bubbles_in_air(self):
        used = dict()
        for i in range(self.columns):
            if (0, i) in self.bubble_map:
                self.mark_dfs(i, 0, used)
        for key in list(self.bubble_map.keys()):
            if key not in used:
                self.bubble_sprites.remove(self.bubble_map[key])
                self.bubble_map[key].kill()
                del self.bubble_map[key]

        # print(used)

    def mark_dfs(self, x, y, used):
        used[x, y] = True
        differences = []
        if y % 2 == 1:
            differences += [(0, -1), (-1, 0), (0, 1), (1, -1), (1, 0), (1, 1)]
        else:
            differences += [(-1, -1), (-1, 0), (-1, 1), (0, -1), (1, 0), (0, 1)]
        for diff in differences:
            next_x = x + diff[0]
            next_y = y + diff[1]
            if (not (next_x, next_y) in used) and ((next_x, next_y) in self.bubble_map):
                self.mark_dfs(next_x, next_y, used)

    def process_queue(self, generate_new_element):
        self.ball = self.generate_new_ball(self.queue[0].type)
        self.sprites.add(self.ball)
        self.queue[0].kill()
        del self.queue[0]
        for i in self.queue:
            i.move_left(1.2 * self.bubble_size)
        if generate_new_element:
            self.queue.append(self.generate_queue_element(self.bubble_size * (0.2 + 1.2 * len(self.queue)),
                                                          self.queue_y, self.bubble_types, True))
            self.sprites.add(self.queue[-1])
        if len(self.queue) == 0:
            self.generate_new_queue(6)
            return False
        else:
            self.queue[0].make_visible()
            return True

    def generate_row(self, row, columns, n_bubble_types):
        return [self.generate_bubble(row, i, n_bubble_types) for i in range(columns)]

    def generate_bubble(self, row, column, n_types):
        return Bubble(self, row, column, randint(0, n_types))

    def generate_queue_element(self, x, y, n_types, is_hidden):
        return QueueElement(self, x, y, randint(0, n_types), is_hidden)

    def generate_new_queue(self, size):
        self.queue = [self.generate_queue_element(self.bubble_size * (0.2 + 1.2 * i),
                                                  self.queue_y,
                                                  self.bubble_types, i != 0) for i in range(size)]
        for q in self.queue:
            self.sprites.add(q)

    def generate_new_ball(self, color):
        x_center = (self.rows + 0.5) * self.bubble_size // 2
        if color == -1:
            return Ball(self, x_center, self.queue_y, randint(0, self.bubble_types), self.speed)
        return Ball(self, x_center, self.queue_y, color, self.speed)

    def count_color_group(self, x, y):
        used = dict()
        return self.count_dfs(x, y, used)

    def delete_color_group(self, x, y):
        used = dict()
        return self.dfs_delete(x, y, used)

    def count_dfs(self, x, y, used):
        used[(x, y)] = True
        differences = []
        if y % 2 == 1:
            differences += [(0, -1), (-1, 0), (0, 1), (1, -1), (1, 0), (1, 1)]
        else:
            differences += [(-1, -1), (-1, 0), (-1, 1), (0, -1), (1, 0), (0, 1)]
        count = 1
        for diff in differences:
            next_x = x + diff[0]
            next_y = y + diff[1]
            if (not (next_x, next_y) in used) and ((next_x, next_y) in self.bubble_map) and \
                    self.bubble_map[(next_x, next_y)].type == self.bubble_map[(x, y)].type:
                count += self.count_dfs(next_x, next_y, used)
        return count

    def dfs_delete(self, x, y, used):
        used[(x, y)] = True
        differences = []
        if y % 2 == 1:
            differences += [(0, -1), (-1, 0), (0, 1), (1, -1), (1, 0), (1, 1)]
        else:
            differences += [(-1, -1), (-1, 0), (-1, 1), (0, -1), (1, 0), (0, 1)]
        for diff in differences:
            next_x = x + diff[0]
            next_y = y + diff[1]
            if (not (next_x, next_y) in used) and ((next_x, next_y) in self.bubble_map) and \
                    self.bubble_map[(next_x, next_y)].type == self.bubble_map[(x, y)].type:
                self.dfs_delete(next_x, next_y, used)
        bubble = self.bubble_map[(x, y)]
        del self.bubble_map[(x, y)]
        self.bubble_sprites.remove(bubble)
        bubble.kill()
