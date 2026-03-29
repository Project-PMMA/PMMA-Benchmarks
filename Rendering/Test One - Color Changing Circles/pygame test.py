import pygame
import random
import math
import time
import argparse
from array import array

parser = argparse.ArgumentParser()
parser.add_argument("--count", type=int, default=100_000,
    help="Number of octagons (WARNING: very heavy for Pygame!)")
parser.add_argument("--size", type=int, default=50,
    help="Radius of each octagon")
parser.add_argument("--window-size", type=int, nargs=2, default=(1280, 720))
parser.add_argument("--seed", type=int, default=None)
args = parser.parse_args()

if args.seed is not None:
    random.seed(args.seed)

OCT_COUNT = args.count
RADIUS = args.size
WIN_W, WIN_H = args.window_size

pygame.init()
screen = pygame.display.set_mode((WIN_W, WIN_H), pygame.SRCALPHA)
clock = pygame.time.Clock()

# Precompute octagon points relative to center
oct_points = []
for i in range(8):
    theta = (math.pi * 2 * i) / 8
    oct_points.append((math.cos(theta) * RADIUS, math.sin(theta) * RADIUS))

# Random positions
positions = [
    (random.randint(RADIUS, WIN_W - RADIUS),
     random.randint(RADIUS, WIN_H - RADIUS))
    for _ in range(OCT_COUNT)
]

# FPS counters
frame_counter = 0
last_report = time.time()

total = []
n = 0

running = True
while running:
    s = time.perf_counter()
    for e in pygame.event.get():
        if e.type == pygame.QUIT:
            running = False

    screen.fill((0, 0, 0, 255))

    # Draw all octagons with random color
    for (cx, cy) in positions:
        r = random.randrange(256)
        g = random.randrange(256)
        b = random.randrange(256)

    pygame.draw.circle(screen, (r, g, b), (cx, cy), RADIUS)

    pygame.display.flip()

    e = time.perf_counter()

    n += 1

    if n > 10:
        total.append(1/(e-s))
        print(f"Average FPS: {sum(total)/len(total)} ({len(total)})")

    if n > 65:
        break

pygame.quit()