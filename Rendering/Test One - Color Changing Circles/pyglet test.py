#!/usr/bin/env python3

import argparse
import random
import pyglet
from pyglet import shapes

# ---- CLI ----
parser = argparse.ArgumentParser()
parser.add_argument("--count", "-c", type=int, default=100_000)
parser.add_argument("--size", type=float, default=50)
parser.add_argument("--window-size", type=int, nargs=2, default=(1280, 720))
args = parser.parse_args()

count = args.count
radius = args.size
win_w, win_h = args.window_size

window = pyglet.window.Window(win_w, win_h, "Circle Benchmark")
batch = pyglet.graphics.Batch()

circles = []
total = []
n = 0

# Create circles
for _ in range(count):
    x = random.uniform(radius, win_w - radius)
    y = random.uniform(radius, win_h - radius)

    circle = shapes.Circle(
        x, y, radius,
        color=(
            random.randint(0, 255),
            random.randint(0, 255),
            random.randint(0, 255)
        ),
        batch=batch
    )
    circles.append(circle)

@window.event
def on_draw():
    window.clear()
    batch.draw()

def update(dt):
    global n
    # Change color per circle (much cheaper than per-vertex!)
    for c in circles:
        c.color = (
            random.randint(0, 255),
            random.randint(0, 255),
            random.randint(0, 255)
        )

    n += 1
    if n > 10:
        total.append(1/dt)
        print(f"Average FPS: {sum(total)/len(total)} ({len(total)})")

    if n > 65:
        pyglet.app.exit()

pyglet.clock.schedule_interval(update, 1/100_000)

pyglet.app.run()