import pmma, time, math, random
from typing import List

display = pmma.Display()
display.create([1280, 720], fullscreen=False, vsync=True)

shapes: List[pmma.Shapes2D.RadialPolygon] = []
for _ in range(100_000):
    shape = pmma.Shapes2D.RadialPolygon()
    shape.shape_center.generate_from_random()
    shape.shape_color.generate_from_random(generate_alpha=False)
    shape.set_radius(50)
    shapes.append(shape)

total = []
n = 0
while True:
    s = time.perf_counter()
    display.clear()

    for shape in shapes:
        shape.render()
        shape.shape_color.generate_from_random(generate_alpha=False)

    display.refresh(limit_refresh_rate=False)
    e = time.perf_counter()
    n += 1

    if n > 10:
        total.append(1/(e-s))
        print(f"Average FPS: {sum(total)/len(total)} ({len(total)})")

    if n > 65:
        break