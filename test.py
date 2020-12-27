from PIL import Image, ImageDraw
from pathlib import Path

import _game

import random

def draw_player(cell, d):
    cx = cell.pos.x
    cy = cell.pos.y
    radius = cell.radius
    d.ellipse((cx-radius, cy-radius, cx+radius, cy+radius), fill="red")

Path("images").mkdir(exist_ok=True)

_game.initRandom(444444)

game = _game.Game()

viewer = 800

map_size = 5000

image = Image.new("RGB", (viewer, viewer), (255,255,255))
image2 = Image.new("RGB", (map_size, map_size), (255,255,255))
draw = ImageDraw.Draw(image)
draw2 = ImageDraw.Draw(image2)


player_num = 50

u_list = [i for i in range(player_num)]
target = [{"x": 0, "y": 0} for i in range(player_num)]

for i in u_list:
    game.addUser(str(i))


tick_num = 2000
# random go
for i in range(tick_num):
    tick_image2 = Image.new("RGB", (map_size, map_size), (255,255,255))

    for j in range(player_num):
        if i % 200 == 0:
            target[j]["x"] = 5000 * random.random()
            target[j]["y"] = 5000 * random.random()
            #print(target[j]["x"], target[j]["y"])

        game.movePlayer(str(j), target[j]["x"], target[j]["y"])



    if i % 10000 == 0:
        print(i)
    game.tick()

    for i in game.users:
        u = game.users[i]
        c = next(iter(u.cells))
        draw_player(c, draw2)

for i in game.users:
    u = game.users[i]
    c = next(iter(u.cells))
    draw_player(c, draw2)


cx = c.pos.x
cy = c.pos.y
radius = c.radius
#draw2.ellipse((cx-radius, cy-radius, cx+radius, cy+radius), fill="red")
draw.ellipse((viewer/2-radius, viewer/2-radius, viewer/2+radius ,viewer/2+radius), fill="red")

print(cx, cy)


for f in game.foods:
    x = f.pos.x
    y = f.pos.y
    radius = f.radius

    rela_center_x = viewer/2 - (cx-x)
    rela_center_y = viewer/2 - (cy-y)
    if c.pos.dist(f.pos) <= viewer/2:
        draw.ellipse((rela_center_x-radius, rela_center_y-radius, rela_center_x+radius ,rela_center_y+radius), fill="black")

    draw2.ellipse((x-radius, y-radius, x+radius, y+ radius), fill="black")

image.save("images/test.jpg")
image2.save("images/test2.jpg")

print(len(game.users))
